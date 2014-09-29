#include "stdafx.h"
#include "Main.h"

#include "OutputTree.h"


// ----------- �p�u���b�N�֐� ----------- //
// �R���X�g���N�^
Main::Main(void)
{
	// �f�B���N�g���\�������N���X
	mGenDir = gcnew GenerateDirectory();
}

// ���s����
bool Main::Start(String^ dir, bool tab, BackgroundWorker^ worker, DoWorkEventArgs^ e, long cnt)
{
	bool ret = true;		// �߂�l

	if (tab) {
		// �^�u�o��
		mGenDir->Init(dir, OUTPUT_FORMAT_TAB, worker, e, cnt);
	} else {
		// �c���[�o��
		mGenDir->Init(dir, OUTPUT_FORMAT_TREE, worker, e, cnt);
	}

	// ���s
	ret = mGenDir->Exec(nullptr, nullptr);

	return ret;
}
