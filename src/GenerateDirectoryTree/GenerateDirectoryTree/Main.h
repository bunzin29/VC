#pragma once

#include "GenerateDirectory.h"

using namespace System;
using namespace System::IO;

// �f�o�b�O�p
using namespace System::Diagnostics;

ref class Main
{
public:
	// �R���X�g���N�^
	Main(void);

	// ���s
	bool Start(String^ dir, bool tab);

private:
	GenerateDirectory^ mGenDir;
};

