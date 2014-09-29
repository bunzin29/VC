#include "stdafx.h"
#include "Main.h"

#include "OutputTree.h"

// コンストラクタ
Main::Main(void)
{
	mGenDir = gcnew GenerateDirectory();

}

// 実行
bool Main::Start(String^ dir, bool tab, BackgroundWorker^ worker, DoWorkEventArgs^ e, long cnt)
{
	bool ret = true;

	if (tab) {
		mGenDir->Init(dir, OUTPUT_FORMAT_TAB, worker, e, cnt);
	} else {
		mGenDir->Init(dir, OUTPUT_FORMAT_TREE, worker, e, cnt);
	}

	mGenDir->Exec(nullptr, nullptr);

	return ret;
}

