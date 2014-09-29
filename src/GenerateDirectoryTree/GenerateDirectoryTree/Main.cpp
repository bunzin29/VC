#include "stdafx.h"
#include "Main.h"

#include "OutputTree.h"


// ----------- パブリック関数 ----------- //
// コンストラクタ
Main::Main(void)
{
	// ディレクトリ構成生成クラス
	mGenDir = gcnew GenerateDirectory();
}

// 実行する
bool Main::Start(String^ dir, bool tab, BackgroundWorker^ worker, DoWorkEventArgs^ e, long cnt)
{
	bool ret = true;		// 戻り値

	if (tab) {
		// タブ出力
		mGenDir->Init(dir, OUTPUT_FORMAT_TAB, worker, e, cnt);
	} else {
		// ツリー出力
		mGenDir->Init(dir, OUTPUT_FORMAT_TREE, worker, e, cnt);
	}

	// 実行
	ret = mGenDir->Exec(nullptr, nullptr);

	return ret;
}
