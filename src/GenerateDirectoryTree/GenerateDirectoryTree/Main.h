#pragma once

#include "GenerateDirectory.h"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;

// �f�o�b�O�p
using namespace System::Diagnostics;

ref class Main
{
public:
	// �R���X�g���N�^
	Main(void);
	
	// ���s
	bool Start(String^ dir, bool tab, BackgroundWorker^ worker, DoWorkEventArgs^ e, long cnt);

private:
	GenerateDirectory^ mGenDir;
};

