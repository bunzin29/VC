#pragma once

#include "OutputTree.h"
#include "OutputFile.h"

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::ComponentModel;

ref class GenerateDirectory
{
public:
	// コンストラクタ
	GenerateDirectory(void);

	// 初期設定
	void Init(String^ dir, int outfmt, BackgroundWorker^ worker, DoWorkEventArgs^ doWkEvt, long cnt);
	// 実行
	bool Exec(String^ dirPath, String^ filePath);

private:
	OutputTree^ mOtree;
	OutputFile^ mOfile;

	String^ mCurrentDir;		// カレントディレクトリ
	int     mIndent;			// インデント
	int     MCurrentFileNum;	// カレントディレクトリのファイル数

	bool    mShcFile;			// ファイル検索

	String^ mDirPath;			// ファイル保存先ディレクトリ
	String^ mFileName;			// ファイル名

	BackgroundWorker^ mWorker;
	DoWorkEventArgs^  mDoWkEvt;
	long              mAllCnt;
	long              mExeCnt;

	// 初期化
	void Init();
	// 後処理
	void After();
	// ルートディレクトリ
	void rootDirectory(String^ dir);
	// カレントディレクトリ検索
	void serchCurrentFiles(String^ dir);
	// ファイル数取得
	int getFiles(String^ dir);
	// サブディレクトリ検索
	void serchSubDirectory(String^ dir, bool exFile);
	// ファイル検索
	void serchFiles(array<String^>^ files);
	// ファイルが存在するか
	bool isFiles(String^ dir);
	// 出力文字列設定
	bool setOutput(int indent, String^ out, unsigned char mark);
	// プログレスバー更新
	bool updatePrg(void);
	// 実行スレッド判定
	bool endExeThread(void);

};

