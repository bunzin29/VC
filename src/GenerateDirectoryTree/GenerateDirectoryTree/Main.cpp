#include "stdafx.h"
#include "Main.h"

#include "OutputTree.h"

// �R���X�g���N�^
Main::Main(void)
{
	mGenDir = gcnew GenerateDirectory();

}

// ���s
bool Main::Start(String^ dir, bool tab)
{
	bool ret = true;

//	mGenDir->Init("E:\\VC_TEST\\Sample", OUTPUT_FORMAT_TREE);
	if (tab) {
		mGenDir->Init(dir, OUTPUT_FORMAT_TAB);
	} else {
		mGenDir->Init(dir, OUTPUT_FORMAT_TREE);
	}

	mGenDir->Exec(nullptr, nullptr);

	return ret;
}

