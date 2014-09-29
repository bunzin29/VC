#include "stdafx.h"
#include "GenerateDirectory.h"


// ----------- パブリック関数 ----------- //
// コンストラクタ
GenerateDirectory::GenerateDirectory(void)
{
}

// 初期設定を行う
void GenerateDirectory::Init(String^ dir, int outfmt, BackgroundWorker^ worker, DoWorkEventArgs^ doWkEvt, long cnt)
{
	// 実行スレッド設定
	mWorker  = worker;
	mDoWkEvt = doWkEvt;
	// プログレスバー用変数初期化
	mAllCnt  = cnt;
	mExeCnt  = 0;

	// カレントディレクトリ設定
	mCurrentDir = dir;

	// 出力フォーマットを指定して出力クラス生成
	mOtree = gcnew OutputTree(outfmt);
}

// 実行する
bool GenerateDirectory::Exec(String^ /*dirPath*/, String^ /*filePath*/)
{
	bool ret = true;
	
	if (mCurrentDir == nullptr) {	// カレントディレクトリがヌルの場合
		// 戻り値に失敗を設定
		ret = false;

	} else {
		// 初期化
		Init();

		// ルートディレクトリを設定
		RootDirectory(mCurrentDir);

		// サブディレクトリ検索
		array<String^>^ d = Directory::GetDirectories(mCurrentDir);
		Array::Sort(d);

		if (d->Length > 0) {
			// サブディレクトリ検索
			SerchSubDirectory(mCurrentDir, IsFiles(mCurrentDir));
		}
		
		// カレントディレクトリ検索
		SerchCurrentFiles(mCurrentDir);

		// 後処理
		After();
	}

	return ret;
}


// ----------- プライベート関数 ----------- //
// 初期化を行う
void GenerateDirectory::Init(void)
{
	String^ path = nullptr;
	String^ file = nullptr;
	String^ ext = nullptr;
	String^ fileName = nullptr;

	mIndent = 0;								// インデント
	mCurrentFileNum = GetFiles(mCurrentDir);	// カレントのファイル数
	mShcFile = true;

	// ファイル出力設定
	// パネルまたはデフォルト保存先指定
	if (mDirPath != nullptr && mFileName != nullptr) {
		// T.B.D

	} else {
		//アプリケーションを開始した実行可能ファイルの、ファイル名を含まないパスを取得
		path = System::Windows::Forms::Application::StartupPath;

		// カレントディレクトリ設定
		fileName = mCurrentDir;

		// ディレクトリ名をファイル名に設定
		file = fileName->Remove(0, fileName->LastIndexOf("\\") + 1);

		// 出力ファイルの拡張子を設定
		ext = "txt";
	}

	// OutputFileクラス
	mOfile = gcnew OutputFile();
	// 出力先設定
	mOfile->Init(path, file, ext);
}

// 後処理を行う
void GenerateDirectory::After(void)
{
#ifndef _DEBUG		// 生成したファイルを開く
	String^ filePath;

	filePath = mOfile->getFilePath();

	if (filePath != nullptr && filePath != "") {
		System::Diagnostics::Process::Start(filePath);
	}
#endif

	// CloseFileでヌルチェックを行っている
	mOfile->CloseFile();
}

// ルートディレクトリ名を出力する
void GenerateDirectory::RootDirectory(String^ dir)
{
	String^ dirName;		// ディレクトリ名

	// ディレクトリ名取得
	dirName = dir->Remove(0, dir->LastIndexOf("\\") + 1);
	// 文字列出力
	SetOutput(mIndent, dirName, OT_MARK_NONE);
}

// カレントディレクトリを検索する
void GenerateDirectory::SerchCurrentFiles(String^ dir)
{
	// ファイル検索が有効の場合
	if (mShcFile) {
		// (複数)ファイルを指定してファイル検索
		array<String^>^ files = Directory::GetFiles(dir);
		Array::Sort(files);

		// ファイル検索
		SerchFiles(files);
	}
}

// ファイル数を取得する
int GenerateDirectory::GetFiles(String^ dir)
{
	array<String^>^ files;

	// 指定したディレクトリのファイルを取得
	files =  Directory::GetFiles(dir);

	return files->Length;
}

// サブディレクトリを検索する
void GenerateDirectory::SerchSubDirectory(String^ dir, bool exFile)
{
	array<String^>^ dirs;		// ディレクトリ一覧
	String^         dirName;	// ディレクトリ名	

	// 実行スレッド動作確認
	if (EndExeThread()) {
		return;
	}

	mIndent++;					// インデントインクリメント

	// 全てのディレクトリ取得
	dirs = Directory::GetDirectories(dir);
	Array::Sort(dirs);

	// 全てのサブディレクトリを検索(再帰)
	for (int i = 0; i < dirs->Length; i++) {
		// ディレクトリ名取得
		dirName = dirs[i]->Remove(0, dirs[i]->LastIndexOf("\\") + 1);

		if (i == (dirs->Length - 1)) {	// 最後のディレクトリ
			if (exFile) {				// ファイルが存在する
				SetOutput(mIndent, dirName, OT_MARK_BR);
			} else {					// ファイルが存在しない
				SetOutput(mIndent, dirName, OT_MARK_ED);
			}
		} else {
			SetOutput(mIndent, dirName, OT_MARK_BR);
		}

		// サブディレクトリ検索(再帰)
		bool isFile = IsFiles(dirs[i]);
		SerchSubDirectory(dirs[i], isFile);

		if (mShcFile) {		// ファイル検索が有効の場合
			// 全てのファイル検索
			array<String^>^ files = Directory::GetFiles(dirs[i]);
			Array::Sort(files);
			SerchFiles(files);
		}
	}

	mIndent--;				// インデントデクリメント
}

// ファイル検索する
void GenerateDirectory::SerchFiles(array<String^>^ files)
{
	int     i;
	String^ fileName;		// ファイル名

	// ファイルが存在する場合
	if (files->Length > 0) {
		mIndent++;			// インデントインクリメント
		for (i = 0; i < files->Length; i++) {
			// ファイル名取得
			fileName = IO::Path::GetFileName(files[i]);
			if (i == files->Length - 1) {		// ファイルが最後か判定
				SetOutput(mIndent, fileName, OT_MARK_ED);
			} else {
				SetOutput(mIndent, fileName, OT_MARK_BR);
			}
		}
		mIndent--;			// インデントデクリメント
	}
}

// ファイルが存在するか
bool GenerateDirectory::IsFiles(String^ dir)
{
	bool ret;			// 戻り値
	int  fileNum;		// ファイル数

	// ファイル数取得
	fileNum = GetFiles(dir);
	if (fileNum > 0) {
		ret = true;
	} else {
		ret = false;
	}

	return ret;
}

// 出力文字列を設定する
bool GenerateDirectory::SetOutput(int indent, String^ out, unsigned char mark)
{
	bool    ret  = false;		// 戻り値
	String^ data = nullptr;		// データ格納用

	if (mOtree != nullptr) {
		// インデント、出力文字列、マーク、終端種別を指定して出力
		data = mOtree->Output(indent, out, mark);
		ret = true;

		// データ取得成功の場合
		if (data != nullptr && mOfile != nullptr) {
			// データをファイル出力する
			mOfile->OutFile(data);

			// プログレスバー更新
			UpdatePrg();
		}
	}

	return ret;
}

// プログレスバーを更新する
bool GenerateDirectory::UpdatePrg(void)
{
	bool   ret = true;		// 戻り値
	double tmp;				// データ一時格納用

	mExeCnt++;		// カウントアップ

	// プログレスバーの設定値計算(0～100)
	tmp = (double)mExeCnt / (double)mAllCnt;
	tmp *= 100.0;

	mWorker->ReportProgress((int)tmp);

	return ret;
}

// 実行スレッドを判定する
bool GenerateDirectory::EndExeThread(void)
{
	bool ret = false;		// 戻り値

	// 実行スレッドのキャンセルを要求したか
	if (mWorker->CancellationPending) {
		mDoWkEvt->Cancel = true;
		ret = true;
	}

	return ret;
}
