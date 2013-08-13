#TeamChat sample

LobiSDKを使ったチームチャットアプリのサンプルプロジェクトです。

[Tutorial:-チームチャットを実装する](https://github.com/nakamap/docs/wiki/Tutorial:-チームチャットを実装する)
に記載されているチュートリアルをもとにした具体的なアプリの実装方法になります。

サーバ側、クライアント側（iOS）それぞれのサンプルプロジェクトが含まれています。


## sample server

### prepare

* まず、 [developer site](http://developer.lobi.co/) でアプリの登録をし、 client id, client secret などを取得しましょう。
* サーバ側では、新しめの perl と sqlite が必用です。 もし手元に perl の環境がない場合は [plenv](https://github.com/tokuhirom/plenv) などと用いるとよいでしょう。また、 v1.0 以降の [carton](https://github.com/miyagawa/carton) が必用となっています。
* 下記に、 perl の環境を整えた後のセットアップの手順を示します。

```
$ git clone https://github.com/nakamap/TeamChatSample.git
$ cd Teamchatsample/web
$ cpanm Carton ( more than v1.0 )
$ carton install
$ sqlite3 sqlite3.db < sql/sqlite3.sql
$ LOBI_CLIENT_SECRET=..... carton exec -- plackup # start server on 5000 port default.
```

### spec

今回はシンプルな実装を行う為に下記の仕様とする。

* サーバでは、ユーザとチームの管理をする
* ユーザは１つのチームに所属する事が出来る。同時に複数のチームに所属する事は出来ない。
* ユーザはチームを新たに作成する事が出来る。チームの作成者は、他のチームに移動する事が出来ない。

実際には、管理者がチームを移動をする際には、チームを解散させるなどの処理を記述する必用があるでしょう。また、今回はサンプルとして、分かりやすさを優先するため、ユーザをAPI経由で作成した際に token を発行し、その token を用いてサーバと通信をする事で送り手の判断を行うというシンプルな実装を行いました。この処理も要件に応じて実装する事が必用でしょう。

### api

#### POST /signup

新しくユーザの作成を行う

##### response

```
{
    user => {
        {
            id: Int,
            team_id: Int,
            token: Str,
            iv: Str,
            cipher :Str,
        }
    }
}
```

#### POST /teams

新しくチームの作成を行う

##### require

* token

##### response

```
{
    team => {
        id: Int,
        owner_user_id: Int,
    },
}
```

#### POST /teams/:id/join

既存のチームに参加する

##### require

* token

##### response

```
{
    team => {
        id: Int,
        owner_user_id: Int,
    },
}
```

#### GET /teams

チーム一覧を取得する

##### response

```
{
    teams => [
        {
            id: Int,
            owner_user_id: Int,
        },
        .....
    ],
}
```

##sample iOS
クライアントサイド（iOS）サンプルアプリの説明です。

###prepare
 [developer site](http://developer.lobi.co/) で取得したclient_idを`AppDelegate.m`に記入します。
 
 ```
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
（略）

#warning ご自身のLobiSDKのclient_idに置き換えて下さい。
    NKConfiguration *configuration = [NKConfiguration currentConfiguration];
    configuration.clientID = @"REPLACE_ME";

（略） 
}
 ```
 
 下図のようにTARGETのInfoタブより、URL Typesを編集します。 "nakamapapp-<クライアントID>"という形式のURLスキームを登録してください。

※下図のNAKAMAP_CLIENT_IDは、クライアントIDと置き換えてください。

 ![info.plist](https://raw.github.com/wiki/nakamap/docs/images/ios/plist1.png)


`TeamChatAPIClient.m`内のTeamChatAPIBaseURLStringをご自身のサーバーのURLに設定してください。


```
#define TeamChatAPIBaseURLString @"http://localhost:5000/"
```

###usage

####サインアップ

サインアップしていない場合は、`Signup`ボタンがアクティブになっています。ボタンをタップしてサインアップしてください。

![](https://github.com/nakamap/TeamChatSample/tree/master/ios/Sample/Resources/team_chat_1.png)

####チーム一覧の取得
サインアップが成功すると、現在作成されているチームの一覧が表示されます。

####チームへの所属
セルをタップすることで、そのチームに所属する事が出来ます。所属チームを切り替えて同時に複数のチームに所属する事が出来ないことを試してみてください。

####チームの新規作成
チームの新規作成は`Create`ボタンをタップして下さい。
自分がチームを作成した場合は他のチームに移ることができません。

![](https://github.com/nakamap/TeamChatSample/tree/master/ios/Sample/Resources/team_chat_2.png)
　![](https://github.com/nakamap/TeamChatSample/tree/master/ios/Sample/Resources/team_chat_3.png)