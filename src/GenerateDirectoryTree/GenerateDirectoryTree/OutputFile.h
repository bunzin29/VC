#pragma once

using namespace System;
using namespace System::IO;


// ファイル出力クラス
ref class OutputFile
{
// パブリック関数
public:
	// コンストラクタ
	OutputFile(void);

	// 初期設定を行う
	void Init(String^ path, String^ file, String^ ext);
	// ファイル出力を行う
	bool OutFile(String^ s);
	// ファイルクローズする
	void CloseFile(void);

	// アクセサ
	// ファイルパスを取得する
	String^ GetFilePath(void);
	// ファイル保存形式を設定する
	void SetFileExt(String^ fileExt);
	// ファイル保存形式を取得する
	String^ GetFileExt();
	// 保存先を設定する
	void SetOutputPath(String^ opPath);
	// 保存先を取得する
	String^ GetOutputPath();
	// ファイル名を設定する
	void SetFileName(String^ fileName);
	// ファイル名を取得する
	String^ GetFilename();

// プライベート変数
private:
	StreamWriter^ mSw;			// ファイルストリーマー

	String^ mFilePath;			// ファイルパス(全部)
	String^ mFileExt;			// ファイル保存形式
	String^ mOutputPath;		// 保存先
	String^ mOutputFileName;	// ファイル名
};
