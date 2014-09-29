#pragma once

#include "GenerateDirectory.h"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;

// デバッグ用
using namespace System::Diagnostics;

ref class Main
{
public:
	// コンストラクタ
	Main(void);
	
	// 実行
	bool Start(String^ dir, bool tab, BackgroundWorker^ worker, DoWorkEventArgs^ e, long cnt);

private:
	GenerateDirectory^ mGenDir;
};

