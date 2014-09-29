#pragma once

#include "GenerateDirectory.h"

using namespace System;
using namespace System::IO;

// メインクラス
ref class Main
{
// パブリック関数
public:
	// コンストラクタ
	Main(void);
	
	// 実行する
	bool Start(String^ dir, bool tab, BackgroundWorker^ worker, DoWorkEventArgs^ e, long cnt);

// プライベート変数
private:
	GenerateDirectory^ mGenDir;		// ディレクトリ構成生成クラス
};

