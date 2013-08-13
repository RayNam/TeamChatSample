create table user (
    id integer primary key autoincrement,
    team_id integer,
    token varchar(40) unique
);

create table team (
    id integer primary key autoincrement,
    owner_user_id integer unique
);
