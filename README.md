Viqo
====

Viqo is a cross-platform "Nico Nama" comment viewer.

Viqo 是跨平台"nico生放"留言查看程序。

Viqo はクロスプラットフォームなニコニコ生放送用 コメントビューア（ニコ生 コメビュ）です。

* クロスプラットフォーム GUI アプリケーション
* Qt5 / C++
* オープンソース (MIT license)

このコメビュは *自由* であることを目指しています。

ダウンロード
------------

### [Version 1.7](https://github.com/diginatu/Viqo/releases/tag/v1.7)

### [Version 1.6](https://github.com/diginatu/Viqo/releases/tag/v1.6)

Ubuntu 14.04, Debian 7.7, OSX Yosemite, Windows 7, 8.1 などで動作確認されています。

#### 簡単な使い方

下の使いかたはだんだん古くなってきたのでここに最初立ちあげた時の設定など簡単にかきます

Linux 版の方は Viqo.sh を実行してください

まず起動したら、[編集]->[設定]からログイン方法を「コメビュからログイン」にし、ユーザ情報(メールアドレスとパスワード)を設定してから上の[取得]を押してください。user_sessionに何か入ったらログイン成功です。できたら[OK]で閉じます。

サイトからURLのアイコンドロップで受信できます。

ライセンス
----------

MIT ライセンス

注意
----

#### Dec 4, 2014 のコミットでセーブファイルの形式が変更されています。
以前の設定ファイルはそのまま今までどうり自動で開かれますが、次回からの保存は新しい形式になります。
メニューの設定をOKを押すことと、メニューの保存を押すことでそれぞれ別のファイルが作成されます。
設定を保存するときは **必ず両方の設定保存を完了してください** 。メニューの保存だけを押して Viqo を終了した場合一部の設定が引き継がれません。
次回からは気にせずそれぞれの保存したいときに保存できるようになります。

#### Nov 25, 2014 のコミットからセーブファイルの保存場所が変更されました。
それ以前からのコミットへバージョンアップする場合で以前のセーブファイルを使いたい場合はファイルを移動する必要があります。

 以前のセーブファイルは実行したカレントディレクトリに作成されていました。

 今後のバージョンでは QStandardPaths を使うため、

  * settings.json
  * user.sqlite

 の２ファイルを移動してください。

[QStandardPaths](http://qt-project.org/doc/qt-5/qstandardpaths.html#LocateOption-enum)

"The following table gives examples of paths on different operating systems." 以降のパス参考


### Viqoの目指す自由
 自由なソフトウェアというだけでなく、クロスプラットフォームで沢山の人が使えることや、多くの目的に素早く適応できるようにコマンドを入力できるようにするなどといった、使用面での自由度など、あらゆる自由を目標にしています。

使い方
------
* 基本的な使い方
  1. ファイル、メニューの設定から user_session を設定してください。詳細は以下の **設定画面** 。入力した user_session でニコニコ動画からログアウトするまでこの id は有効です。
  2. お気に入りのコミュニティをタブから選択するか、ブラウザから放送ページのアイコンをコメビュにドラッグアンドドロップするか、または放送id (urlなど) を入力して [受信] ボタンを押すとコメントを受信します。

* 画面上のボタン
  + [切断] で手動でコメントサーバから切断できます。（主コメントで /disconnect を受信した場合は自動で切断）

* 画面下部のタブ画面
  + コメント タブ
    - 受信されたコメントが、ここに表示されます。
    - 自動名前取得 にチェックを入れておくとコメント受信時にユーザ名を自動取得します
    - ユーザ名 コラムの ユーザ名(id) をダブルクリックすると手動でユーザ名を取得・再取得できます
  + コマンド タブ
    - それぞれのイベント時に任意のOSコマンドを実行できる機能です
    - 最後にある「コマンド実行文字列」が使えます

* メニュー
  + ファイル
    - 状態保存、読み込み (現在の設定状態を保存することができます)
      + 保存した内容は起動時に適応され、メニューの load でも適応できます。
      + Json形式なので手動で編集できます
      + 旧バージョンからコピーしてきても適応される設定はそのまま読まれます。
    - 設定
      + アカウント (セッション、ユーザ情報)
        * コメント受信にはセッションが必須です
        * ユーザ情報はお気に入りコミュ取得、次枠移動、コメント送信の一部などに必要なので必ず設定してください。
      + コメント
  + 編集
    - コメント一覧を消去
      + 非常にコメントが多い放送や長時間でコメントがたまった場合にコメント欄を消去できます。（新たに受信したコメントのみ表示されます）


###コマンド実行文字列

####コマンド一覧

```
%newTitle%    :  放送開始した放送のタイトル
%comment%     :  コメントのテキスト
%lastTime%    :  終了前何分に設定されているか（数字のみ）
%wakuURL%     :  現在受信しているの放送URL
```

####使用可能コマンド

```
            開始  コメント 終了 次枠
%newTitle%    O      X      X    X
%comment%     X      O      X    X  
%lastTime%    X      X      O    X  
%wakuURL%     X      X      X    O  
```
順次増やしていく予定です

コンパイル
----------

Qt5開発環境でこのプロジェクトをコンパイルしてください。
実行はできた実行ファイルを実行するだけです。

