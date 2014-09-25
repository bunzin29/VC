#pragma once

#include "OutputTree.h"
#include "OutputFile.h"

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;

ref class GenerateDirectory
{
public:
	// �R���X�g���N�^
	GenerateDirectory(void);

	// �����ݒ�
	void Init(String^ dir, int outfmt);
	// ���s
	bool Exec(String^ dirPath, String^ filePath);

private:
	OutputTree^ mOtree;
	OutputFile^ mOfile;

	String^ mCurrentDir;		// �J�����g�f�B���N�g��
	int     mIndent;			// �C���f���g
	int     MCurrentFileNum;	// �J�����g�f�B���N�g���̃t�@�C����

	bool    mShcFile;			// �t�@�C������

	String^ mDirPath;			// �t�@�C���ۑ���f�B���N�g��
	String^ mFileName;			// �t�@�C����

	// ������
	void Init();
	// �㏈��
	void After();
	// ���[�g�f�B���N�g��
	void rootDirectory(String^ dir);
	// �J�����g�f�B���N�g������
	void serchCurrentFiles(String^ dir);
	// �t�@�C�����擾
	int getFiles(String^ dir);
	// �T�u�f�B���N�g������
	void serchSubDirectory(String^ dir, bool exFile);
	// �t�@�C������
	void serchFiles(array<String^>^ files);
	// �t�@�C�������݂��邩
	bool isFiles(String^ dir);
	// �o�͕�����ݒ�
	bool setOutput(int indent, String^ out, unsigned char mark);

};

