#pragma once

#include "GenerateDirectory.h"

using namespace System;
using namespace System::IO;

// ���C���N���X
ref class Main
{
// �p�u���b�N�֐�
public:
	// �R���X�g���N�^
	Main(void);
	
	// ���s����
	bool Start(String^ dir, bool tab, BackgroundWorker^ worker, DoWorkEventArgs^ e, long cnt);

// �v���C�x�[�g�ϐ�
private:
	GenerateDirectory^ mGenDir;		// �f�B���N�g���\�������N���X
};

