#include "stdafx.h"
#include "OutputFile.h"

// ----------- パブリック関数 ----------- //
// コンストラクタ
OutputFile::OutputFile(void)
{
}

// 初期化を行う
void OutputFile::Init(String^ path, String^ file, String^ ext)
{
	// ファイル情報設定
	mOutputPath     = path;
	mOutputFileName = file;
	mFileExt        = ext;

	// ファイル名(パス)を設定
	mFilePath = path + "\\" + file + "." + ext;

	// ファイルオープン
	mSw = gcnew StreamWriter(mFilePath);
}

// ファイル出力を行う
bool OutputFile::OutFile(String^ s)
{
	bool ret;		// 戻り値

	// ファイルオープン中
	if (mSw != nullptr) {
		// ファイル出力
		mSw->WriteLine(s);
		ret = true;
	} else {
		ret = false;
	}

	return ret;
}

// ファイルクローズする
void OutputFile::CloseFile(void)
{
	if (mSw != nullptr) {
		mSw->Close();
	}
}

// ファイルパスを取得する
String^ OutputFile::GetFilePath(void)
{
	return mFilePath;
}

// ファイル保存形式を取得する
void OutputFile::SetFileExt(String^ fileExt)
{
	mFileExt = fileExt;
}
// ファイル保存形式を取得する
String^ OutputFile::GetFileExt()
{
	return mFileExt;
}

// 保存先を設定する
void OutputFile::SetOutputPath(String^ opPath)
{
	mOutputPath = opPath;
}
// 保存先を取得する
String^ OutputFile::GetOutputPath()
{
	return mOutputPath;
}

// ファイル名を設定する
void OutputFile::SetFileName(String^ fileName)
{
	mOutputFileName = fileName;
}
// ファイル名を取得する
String^ OutputFile::GetFilename()
{
	return mOutputFileName;
}

