#include "stdafx.h"
#include "OutputFile.h"

// コンストラクタ
OutputFile::OutputFile(void)
{
}

// 初期化
void OutputFile::Init(String^ path, String^ file, String^ ext)
{
	String^ f;
	mOutputPath = path;
	mOutputFileName = file;
	mFileExt = ext;

	f = path + "\\" + file + "." + ext;
//	f = file + "." + ext;
	// ファイルオープン
	mSw = gcnew StreamWriter(f);

}

// ファイル書き込み
bool OutputFile::OutFile(String^ s)
{
	bool ret;
	// ファイルオープン中
	if (mSw != nullptr) {
		mSw->WriteLine(s);
		ret = true;
	} else {
		ret = false;

	}

	return ret;
}

// ファイルクローズ
void OutputFile::CloseFile()
{
	if (mSw != nullptr) {
		mSw->Close();
	}

}

// ファイル保存形式
void OutputFile::setFileExt(String^ fileExt)
{
	mFileExt = fileExt;
}
String^ OutputFile::getFileExt()
{
	return mFileExt;
}

// 保存先
void OutputFile::setOutputPath(String^ opPath)
{
	mOutputPath = opPath;
}
String^ OutputFile::getOutputPath()
{
	return mOutputPath;
}

// ファイル名
void OutputFile::setFileName(String^ fileName)
{
	mOutputFileName = fileName;
}
String^ OutputFile::getFilename()
{
	return mOutputFileName;
}

