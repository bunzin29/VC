#pragma once

#include "OutputTree.h"
#include "OutputFile.h"

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::ComponentModel;


// �f�B���N�g���\�������N���X
ref class GenerateDirectory
{
// �p�u���b�N�֐�
public:
	// �R���X�g���N�^
	GenerateDirectory(void);

	// �����ݒ���s��
	void Init(String^ dir, int outfmt, BackgroundWorker^ worker, DoWorkEventArgs^ doWkEvt, long cnt);
	// ���s����
	bool Exec(String^ dirPath, String^ filePath);

// �v���C�x�[�g�ϐ�
private:
	OutputTree^       mOtree;			// �c���[�o�̓N���X
	OutputFile^       mOfile;			// �t�@�C���o�̓N���X

	String^           mCurrentDir;		// �J�����g�f�B���N�g��
	int               mIndent;			// �C���f���g
	int               mCurrentFileNum;	// �J�����g�f�B���N�g���̃t�@�C����

	bool              mShcFile;			// �t�@�C������

	String^           mDirPath;			// �t�@�C���ۑ���f�B���N�g��
	String^	          mFileName;		// �t�@�C����

	BackgroundWorker^ mWorker;			// ���C���X���b�h
	DoWorkEventArgs^  mDoWkEvt;			// ���C���X���b�h�̃C�x���g�n���h��
	// �v���O���X�o�[�X�V�p�ϐ�
	long              mAllCnt;			// ���s����S�Ẵf�B���N�g���y�уt�@�C����
	long              mExeCnt;			// ���s�����f�B���N�g���y�уt�@�C����

// �v���C�x�[�g�֐�
private:
	// ���������s��
	void Init(void);
	// �㏈�����s��
	void After(void);
	// ���[�g�f�B���N�g�������o�͂���
	void RootDirectory(String^ dir);
	// �J�����g�f�B���N�g������������
	void SerchCurrentFiles(String^ dir);
	// �t�@�C�������擾����
	int GetFiles(String^ dir);
	// �T�u�f�B���N�g������������
	void SerchSubDirectory(String^ dir, bool exFile);
	// �t�@�C����������
	void SerchFiles(array<String^>^ files);
	// �t�@�C�������݂��邩
	bool IsFiles(String^ dir);
	// �o�͕������ݒ肷��
	bool SetOutput(int indent, String^ out, unsigned char mark);
	// �v���O���X�o�[���X�V����
	bool UpdatePrg(void);
	// ���s�X���b�h�𔻒肷��
	bool EndExeThread(void);

};

