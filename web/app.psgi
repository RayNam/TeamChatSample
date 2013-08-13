use strict;
use warnings;
use utf8;
use File::Spec;
use File::Basename;
use lib File::Spec->catdir(dirname(__FILE__), 'extlib', 'lib', 'perl5');
use lib File::Spec->catdir(dirname(__FILE__), 'lib');
use Amon2::Lite;
use Try::Tiny;
use Log::Minimal;
use Furl;
use Data::UUID;
use Crypt::CBC;
use Crypt::OpenSSL::AES;
use MIME::Base64;
use JSON::XS;

our $VERSION = '0.01';

my $client_secret = $ENV{LOBI_CLIENT_SECRET} or die "set LOBI_CLIENT_SECRET enviroment value";
my $furl = Furl->new;

# put your configuration here
sub load_config {
    my $c = shift;

    my $config = +{
        'DBI' => [
            'dbi:SQLite:dbname=sqlite3.db',
            '',
            '',
        ],
    };

    $config;
}

# https://github.com/nakamap/docs/wiki/ExID#perl%E3%81%AE%E6%9A%97%E5%8F%B7%E5%8C%96%E3%82%B5%E3%83%B3%E3%83%97%E3%83%AB
sub encode_aes {
    my ($input) = @_;

    my $iv = Crypt::CBC->random_bytes( 16 );

    my $cbc = Crypt::CBC->new(
        -key         => $client_secret,
        -cipher      => 'Crypt::OpenSSL::AES',
        -keysize     => 32,
        -iv          => $iv,
        -header      => 'none',
        -padding     => 'standard',
    );

    my $cipher = $cbc->encrypt( $input );
    return ( encode_base64( $iv, '' ), encode_base64( $cipher, '' ) );
}

post '/signup' => sub {
    my $c = shift;

    try {
        my $uuid = Data::UUID->new->create_str;

        $c->dbh->insert("user", { team_id => undef, token => $uuid });
        my $id = $c->dbh->func('last_insert_rowid');
        my $row = $c->dbh->selectrow_hashref(
            "select * from user where id = ?", {}, $id
        );

        my ($iv, $cipher) = encode_aes($id);

        $c->render_json({ user => { %$row, iv => $iv, cipher => $cipher } });
    }
    catch {
        warnf "err: %s", $_;
        $c->render_json({error => 1});
    };
};

get '/teams' => sub {
    my ($c) = @_;

    try {
        my @teams = $c->dbh->selectall_arrayref(
            'select * from team',
            { Slice => {} },
        );
        $c->render_json({ teams => \@teams });
    }
    catch {
        warnf "err: %s", $_;
        $c->render_json({error => 1 });
    };
};

post '/teams' => sub {
    my ($c) = @_;

    try {
        my $token = $c->req->param('token') or die "not found token param";

        my $txn = $c->dbh->txn_scope;

        my $user = $c->dbh->selectrow_hashref(
            'select * from user where token = ?', {}, $token
        ) or die "not found user";

        $c->dbh->insert("team", { owner_user_id => $user->{id} });
        my $team = $c->dbh->selectrow_hashref(
            'select * from team where id = ?', {}, $c->dbh->func('last_insert_rowid')
        );

        $c->dbh->do_i('update user set', { team_id => $team->{id} }, 'WHERE', { id => $user->{id} });

        # https://github.com/nakamap/docs/wiki/Tutorial:-%E3%83%81%E3%83%BC%E3%83%A0%E3%83%81%E3%83%A3%E3%83%83%E3%83%88%E3%82%92%E5%AE%9F%E8%A3%85%E3%81%99%E3%82%8B#%E3%83%81%E3%83%A3%E3%83%83%E3%83%88%E3%82%B0%E3%83%AB%E3%83%BC%E3%83%97%E3%82%92%E4%BD%9C%E3%82%8B
        my $res = $furl->post(
            "https://thanks.nakamap.com/1/groups",
            [],
            {
                me_ex_id           => $user->{id},
                client_secret      => $client_secret,
                group_ex_id        => $team->{id},
                name               => "team $team->{id}",
                description        => "description $team->{id}",
                can_join           => "superuser",
                can_invite         => "superuser",
                can_add_members    => "superuser",
                can_part           => "superuser",
                can_remove         => "superuser",
                unique_for_user    => "lobi_sample_team",
            }
        );
        infof "/1/teams res: %s", $res->content;

        my $json = decode_json($res->content);
        die "faild lobi groups" unless $res->is_success && ! exists $json->{error};

        $txn->commit;

        $c->render_json({ team => $team });
    }
    catch {
        warnf "err: %s", $_;
        $c->render_json({error => 1 });
    };
};

post '/teams/{id}/join' => sub {
    my ($c, $param) = @_;

    try {
        my $team_id = $param->{id};
        my $token   = $c->req->param('token') or die "not found token param";

        my $txn = $c->dbh->txn_scope;

        my $user = $c->dbh->selectrow_hashref(
            'select * from user where token = ?', {}, $token
        ) or die "not found user";

        my $team = $c->dbh->selectrow_hashref(
            'select * from team where id = ?', {}, $team_id
        ) or die "not found team";

        # have owner team ?
        my $my_owner_team = $c->dbh->selectrow_hashref(
            'select * from team where owner_user_id = ?', {}, $user->{id}
        );

        if ( $my_owner_team ) {
            die "owner user can't join other team";
        }

        $c->dbh->do_i('update user set', { team_id => $team_id }, 'WHERE', { id => $user->{id} });

        # https://github.com/nakamap/docs/wiki/Tutorial:-%E3%83%81%E3%83%BC%E3%83%A0%E3%83%81%E3%83%A3%E3%83%83%E3%83%88%E3%82%92%E5%AE%9F%E8%A3%85%E3%81%99%E3%82%8B#%E3%83%81%E3%83%A3%E3%83%83%E3%83%88%E3%82%B0%E3%83%AB%E3%83%BC%E3%83%97%E3%81%AB%E5%8F%82%E5%8A%A0%E3%81%99%E3%82%8B
        my $res = $furl->post(
            "https://thanks.nakamap.com/1/group/join",
            [],
            {
                client_secret      => $client_secret,
                me_ex_id           => $user->{id},
                target_user_ex_ids => $user->{id},
                group_ex_id        => $team_id,
            }
        );

        infof "group/join res: %s", $res->content;
        my $json = decode_json($res->content);

        die "faild lobi group/join" unless $res->is_success && ! exists $json->{error};

        $txn->commit;
        $c->render_json({ team => $team });
    }
    catch {
        warnf "err: %s", $_;
        $c->render_json({error => 1});
    };
};

# load plugins
__PACKAGE__->load_plugin('DBI');
__PACKAGE__->load_plugin('Web::JSON');

__PACKAGE__->to_app();
