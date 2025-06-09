#include "./lib/console.h"
#include "webserver.h"
#include "webview/webview.h"
#include <cmrc/cmrc.hpp>
#include <iostream>

using namespace std;

// 初期化
Console console;

CMRC_DECLARE(mypages);

int port;

#include <random>

static int client()
{
	try
	{
		auto fs = cmrc::mypages::get_filesystem();
		webview::webview w(true, nullptr);
		w.set_size(900, 750, WEBVIEW_HINT_NONE);
		w.init(R"(window.addEventListener('contextmenu', function(e) {
    e.preventDefault();
  });)");
		w.set_title("");
		// w.navigate("http://localhost:" + to_string(port) + "/");
		auto file = fs.open("index.html");
		string html(file.begin(), file.end());
		w.set_html(html);

		w.run();

		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

int main()
{
	int status = client();

	if (status == 0)
	{
		console.log("正常にWindowが閉じられました。");
		exit(1);
	}
	else
	{
		console.error("何かしらの原因で正常に閉じれませんでした");
	}
	return 0;
}

// 使用 ライブラリ

// https://github.com/webview/webview.git

// https://github.com/yhirose/cpp-httplib.git

// 概要 C++でWebサーバーを立てて、WebViewで表示するサンプルコードです。
