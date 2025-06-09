#include "./lib/console.h"  
#include "./lib/httplib.h"  
#include "webserver.h"  
#include "webview/webview.h"
#include <cmrc/cmrc.hpp>
#include <iostream>  


using namespace std;  

using namespace httplib;  

// 初期化  
Console console;
Server server;

CMRC_DECLARE(mypages);


int port;

#include <random>


static void randomPort() {
	random_device rm;
	mt19937 mt(rm());
	uniform_int_distribution<int> dist(19132, 65535); // ポート番号の範囲
	port = dist(mt);
}



static int load() {
	server.listen("127.0.0.1", port);
	return 0;
}


static void backend() {
	try
	{
		server.Get("/hi", [](const Request& req, Response& res) {
			console.log("GETリクエストを受信しました。");
			res.set_content("Hello, World!", "text/plain");
			});

		server.set_mount_point("/", "./pages");

		console.log("サーバーを起動しました");
		load();
	}
	catch (const std::exception&)
	{
		console.error("サーバーの起動に失敗しました。");
		exit(1);
	}
}

static int client() {  
   try  
   {  
	   auto fs = cmrc::mypages::get_filesystem();
       webview::webview w(true, nullptr);  
	   w.init(R"(window.addEventListener('contextmenu', function(e) {
    e.preventDefault();
  });)");
       w.set_title("Web Server");  
       //w.navigate("http://localhost:" + to_string(port) + "/");  
	   auto file = fs.open("index.html");
	   string html(file.begin(), file.end());
	   w.set_html(html);
       w.run();  

       return 0;  
   }  
   catch (const std::exception&)  
   {  
       return -1;  
   }  
}

int main()  
{ 
	randomPort();
	thread b(backend);
	int status = client();

	if (status == 0) {
		console.log("正常にWindowが閉じられました。");
		exit(1);
		
	}
	else {
		console.error("何かしらの原因で正常に閉じれませんでした");
	}

	// server init
	b.join();
   return 0;  
}



//使用 ライブラリ


// https://github.com/webview/webview.git 


// https://github.com/yhirose/cpp-httplib.git

//概要 C++でWebサーバーを立てて、WebViewで表示するサンプルコードです。

