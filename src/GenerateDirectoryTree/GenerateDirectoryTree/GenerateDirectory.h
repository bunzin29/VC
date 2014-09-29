#pragma once

#include "OutputTree.h"
#include "OutputFile.h"

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::ComponentModel;


// ディレクトリ構成生成クラス
ref class GenerateDirectory
{
// パブリック関数
public:
	// コンストラクタ
	GenerateDirectory(void);

	// 初期設定を行う
	void Init(String^ dir, int outfmt, BackgroundWorker^ worker, DoWorkEventArgs^ doWkEvt, long cnt);
	// 実行する
	bool Exec(String^ dirPath, String^ filePath);

// プライベート変数
private:
	OutputTree^       mOtree;			// ツリー出力クラス
	OutputFile^       mOfile;			// ファイル出力クラス

	String^           mCurrentDir;		// カレントディレクトリ
	int               mIndent;			// インデント
	int               mCurrentFileNum;	// カレントディレクトリのファイル数

	bool              mShcFile;			// ファイル検索

	String^           mDirPath;			// ファイル保存先ディレクトリ
	String^	          mFileName;		// ファイル名

	BackgroundWorker^ mWorker;			// メインスレッド
	DoWorkEventArgs^  mDoWkEvt;			// メインスレッドのイベントハンドラ
	// プログレスバー更新用変数
	long              mAllCnt;			// 実行する全てのディレクトリ及びファイル数
	long              mExeCnt;			// 実行したディレクトリ及びファイル数

// プライベート関数
private:
	// 初期化を行う
	void Init(void);
	// 後処理を行う
	void After(void);
	// ルートディレクトリ名を出力する
	void RootDirectory(String^ dir);
	// カレントディレクトリを検索する
	void SerchCurrentFiles(String^ dir);
	// ファイル数を取得する
	int GetFiles(String^ dir);
	// サブディレクトリを検索する
	void SerchSubDirectory(String^ dir, bool exFile);
	// ファイル検索する
	void SerchFiles(array<String^>^ files);
	// ファイルが存在するか
	bool IsFiles(String^ dir);
	// 出力文字列を設定する
	bool SetOutput(int indent, String^ out, unsigned char mark);
	// プログレスバーを更新する
	bool UpdatePrg(void);
	// 実行スレッドを判定する
	bool EndExeThread(void);

};

