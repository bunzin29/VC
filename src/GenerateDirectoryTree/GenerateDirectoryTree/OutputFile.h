#pragma once

using namespace System;
using namespace System::IO;


// �t�@�C���o�̓N���X
ref class OutputFile
{
// �p�u���b�N�֐�
public:
	// �R���X�g���N�^
	OutputFile(void);

	// �����ݒ���s��
	void Init(String^ path, String^ file, String^ ext);
	// �t�@�C���o�͂��s��
	bool OutFile(String^ s);
	// �t�@�C���N���[�Y����
	void CloseFile(void);

	// �A�N�Z�T
	// �t�@�C���p�X���擾����
	String^ GetFilePath(void);
	// �t�@�C���ۑ��`����ݒ肷��
	void SetFileExt(String^ fileExt);
	// �t�@�C���ۑ��`�����擾����
	String^ GetFileExt();
	// �ۑ����ݒ肷��
	void SetOutputPath(String^ opPath);
	// �ۑ�����擾����
	String^ GetOutputPath();
	// �t�@�C������ݒ肷��
	void SetFileName(String^ fileName);
	// �t�@�C�������擾����
	String^ GetFilename();

// �v���C�x�[�g�ϐ�
private:
	StreamWriter^ mSw;			// �t�@�C���X�g���[�}�[

	String^ mFilePath;			// �t�@�C���p�X(�S��)
	String^ mFileExt;			// �t�@�C���ۑ��`��
	String^ mOutputPath;		// �ۑ���
	String^ mOutputFileName;	// �t�@�C����
};
