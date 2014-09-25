#include "stdafx.h"
#include "OutputFile.h"

// �R���X�g���N�^
OutputFile::OutputFile(void)
{
}

// ������
void OutputFile::Init(String^ path, String^ file, String^ ext)
{
	String^ f;
	mOutputPath = path;
	mOutputFileName = file;
	mFileExt = ext;

	f = path + "\\" + file + "." + ext;
//	f = file + "." + ext;
	// �t�@�C���I�[�v��
	mSw = gcnew StreamWriter(f);

}

// �t�@�C����������
bool OutputFile::OutFile(String^ s)
{
	bool ret;
	// �t�@�C���I�[�v����
	if (mSw != nullptr) {
		mSw->WriteLine(s);
		ret = true;
	} else {
		ret = false;

	}

	return ret;
}

// �t�@�C���N���[�Y
void OutputFile::CloseFile()
{
	if (mSw != nullptr) {
		mSw->Close();
	}

}

// �t�@�C���ۑ��`��
void OutputFile::setFileExt(String^ fileExt)
{
	mFileExt = fileExt;
}
String^ OutputFile::getFileExt()
{
	return mFileExt;
}

// �ۑ���
void OutputFile::setOutputPath(String^ opPath)
{
	mOutputPath = opPath;
}
String^ OutputFile::getOutputPath()
{
	return mOutputPath;
}

// �t�@�C����
void OutputFile::setFileName(String^ fileName)
{
	mOutputFileName = fileName;
}
String^ OutputFile::getFilename()
{
	return mOutputFileName;
}

