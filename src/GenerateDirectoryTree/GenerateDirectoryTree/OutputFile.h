#pragma once

using namespace System;
using namespace System::IO;


ref class OutputFile
{
public:
	// �R���X�g���N�^
	OutputFile(void);


	// �����ݒ�
	void Init(String^ path, String^ file, String^ ext);
	// �t�@�C���o��
	bool OutFile(String^ s);
	// �t�@�C���N���[�Y
	void CloseFile();

	// �A�N�Z�T
	String^ getFilePath(void);
	// �t�@�C���ۑ��`��
	void setFileExt(String^ fileExt);
	String^ getFileExt();
	// �ۑ���
	void setOutputPath(String^ opPath);
	String^ getOutputPath();
	// �t�@�C����
	void setFileName(String^ fileName);
	String^ getFilename();

private:
	// �t�@�C���p�X(�S��)
	String^ mFilePath;
	// �t�@�C���ۑ��`��
	String^ mFileExt;
	// �ۑ���
	String^ mOutputPath;
	// �t�@�C����
	String^ mOutputFileName;

	// �t�@�C���X�g���[�}�[
	StreamWriter^ mSw;

};

