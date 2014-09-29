#include "stdafx.h"
#include "OutputFile.h"

// ----------- �p�u���b�N�֐� ----------- //
// �R���X�g���N�^
OutputFile::OutputFile(void)
{
}

// ���������s��
void OutputFile::Init(String^ path, String^ file, String^ ext)
{
	// �t�@�C�����ݒ�
	mOutputPath     = path;
	mOutputFileName = file;
	mFileExt        = ext;

	// �t�@�C����(�p�X)��ݒ�
	mFilePath = path + "\\" + file + "." + ext;

	// �t�@�C���I�[�v��
	mSw = gcnew StreamWriter(mFilePath);
}

// �t�@�C���o�͂��s��
bool OutputFile::OutFile(String^ s)
{
	bool ret;		// �߂�l

	// �t�@�C���I�[�v����
	if (mSw != nullptr) {
		// �t�@�C���o��
		mSw->WriteLine(s);
		ret = true;
	} else {
		ret = false;
	}

	return ret;
}

// �t�@�C���N���[�Y����
void OutputFile::CloseFile(void)
{
	if (mSw != nullptr) {
		mSw->Close();
	}
}

// �t�@�C���p�X���擾����
String^ OutputFile::GetFilePath(void)
{
	return mFilePath;
}

// �t�@�C���ۑ��`�����擾����
void OutputFile::SetFileExt(String^ fileExt)
{
	mFileExt = fileExt;
}
// �t�@�C���ۑ��`�����擾����
String^ OutputFile::GetFileExt()
{
	return mFileExt;
}

// �ۑ����ݒ肷��
void OutputFile::SetOutputPath(String^ opPath)
{
	mOutputPath = opPath;
}
// �ۑ�����擾����
String^ OutputFile::GetOutputPath()
{
	return mOutputPath;
}

// �t�@�C������ݒ肷��
void OutputFile::SetFileName(String^ fileName)
{
	mOutputFileName = fileName;
}
// �t�@�C�������擾����
String^ OutputFile::GetFilename()
{
	return mOutputFileName;
}

