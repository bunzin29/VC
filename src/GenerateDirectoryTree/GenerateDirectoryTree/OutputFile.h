#pragma once

using namespace System;
using namespace System::IO;


ref class OutputFile
{
public:
	// コンストラクタ
	OutputFile(void);


	// 初期設定
	void Init(String^ path, String^ file, String^ ext);
	// ファイル出力
	bool OutFile(String^ s);
	// ファイルクローズ
	void CloseFile();

	// アクセサ
	String^ getFilePath(void);
	// ファイル保存形式
	void setFileExt(String^ fileExt);
	String^ getFileExt();
	// 保存先
	void setOutputPath(String^ opPath);
	String^ getOutputPath();
	// ファイル名
	void setFileName(String^ fileName);
	String^ getFilename();

private:
	// ファイルパス(全部)
	String^ mFilePath;
	// ファイル保存形式
	String^ mFileExt;
	// 保存先
	String^ mOutputPath;
	// ファイル名
	String^ mOutputFileName;

	// ファイルストリーマー
	StreamWriter^ mSw;

};

