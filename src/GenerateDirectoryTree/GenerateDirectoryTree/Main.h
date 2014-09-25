#pragma once

#include "GenerateDirectory.h"

using namespace System;
using namespace System::IO;

// デバッグ用
using namespace System::Diagnostics;

ref class Main
{
public:
	// コンストラクタ
	Main(void);

	// 実行
	bool Start(String^ dir, bool tab);

private:
	GenerateDirectory^ mGenDir;
};

