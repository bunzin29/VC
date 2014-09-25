#pragma once

using namespace System;
using namespace System::IO;

using namespace Microsoft::Office::Interop::Excel;


ref class OutputFile
{
public:
	// コンストラクタ
	OutputFile(void);


	// 初期設定
	void Init(String^ path, String^ file, String^ ext, bool excel);
	// ファイル出力
	bool OutFile(String^ s);
	// ファイルクローズ
	void CloseFile();

	// アクセサ
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
	// ファイル保存形式
	String^ mFileExt;
	// 保存先
	String^ mOutputPath;
	// ファイル名
	String^ mOutputFileName;

	// ファイルストリーマー
	StreamWriter^ mSw;

	// エクセル出力
	bool mExcel;
	Microsoft::Office::Interop::Excel::Application^ mExcelApl;
	Workbook^ mWb;
};

