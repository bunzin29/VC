#include "stdafx.h"
#include "GenerateDirectory.h"

// コンストラクタ
GenerateDirectory::GenerateDirectory(void)
{
}

// ----------- public ----------- //

// 初期設定
void GenerateDirectory::Init(String^ dir, int outfmt)
{
	// カレントディレクトリ設定
	mCurrentDir = dir;
	// 出力フォーマットを指定して出力クラス生成
	mOtree = gcnew OutputTree(outfmt);
}

// 実行
bool GenerateDirectory::Exec(String^ dirPath, String^ filePath)
{
	bool ret = true;
	
	if (mCurrentDir == nullptr) {	// カレントディレクトリがヌルの場合
		// 戻り値に失敗を設定
		ret = false;

	} else {
		// 初期化
		Init();

		// ルートディレクトリを設定
		rootDirectory(mCurrentDir);

		// サブディレクトリ検索
		array<String^>^ d = Directory::GetDirectories(mCurrentDir);
		Array::Sort(d);

		if (d->Length > 0) {
			// サブディレクトリ検索
			serchSubDirectory(mCurrentDir, isFiles(mCurrentDir));
		}
		
		// カレントディレクトリ検索
		serchCurrentFiles(mCurrentDir);

		// 後処理
		After();
	}

	return ret;
}

// ----------- private ----------- //

// 初期化
void GenerateDirectory::Init()
{
	String^ path = nullptr;
	String^ file = nullptr;
	String^ ext = nullptr;
	String^ fileName = nullptr;

	mIndent = 0;								// インデント
	MCurrentFileNum = getFiles(mCurrentDir);	// カレントのファイル数
	mShcFile = true;

	// ファイル出力設定
	// パネルまたはデフォルト保存先指定
	if (mDirPath != nullptr && mFileName != nullptr) {

	} else {
		path = System::Windows::Forms::Application::StartupPath;

		fileName = mCurrentDir;

		file = fileName->Remove(0, fileName->LastIndexOf("\\") + 1);
		ext = "txt";
	}

	// OutputFileクラス
	mOfile = gcnew OutputFile();
	// 出力先設定
	mOfile->Init(path, file, ext);
}

// 後処理
void GenerateDirectory::After()
{
	// CloseFileでヌルチェックを行っている
	mOfile->CloseFile();
}

// ファイル数取得
int GenerateDirectory::getFiles(String^ dir)
{
	array<String^>^ files;

	// 指定したディレクトリのファイルを取得
	files =  Directory::GetFiles(dir);

	return files->Length;
}

// ルートディレクトリ
void GenerateDirectory::rootDirectory(String^ dir)
{
	String^ dirName;

	dirName = dir->Remove(0, dir->LastIndexOf("\\") + 1);
	// 文字列出力
	setOutput(mIndent, dirName, OT_MARK_NONE);
}

// カレントディレクトリ検索
void GenerateDirectory::serchCurrentFiles(String^ dir)
{
	// ファイル検索が有効の場合
	if (mShcFile) {
		// (複数)ファイルを指定してファイル検索
		array<String^>^ files = Directory::GetFiles(dir);
		Array::Sort(files);
		serchFiles(files);
	}
}

// サブディレクトリ検索
void GenerateDirectory::serchSubDirectory(String^ dir, bool exFile)
{
	array<String^>^ dirs;		// ディレクトリ一覧
	String^ dirName;

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
				setOutput(mIndent, dirName, OT_MARK_BR);
			} else {					// ファイルが存在しない
				setOutput(mIndent, dirName, OT_MARK_ED);
			}
		} else {
			setOutput(mIndent, dirName, OT_MARK_BR);
		}

		// サブディレクトリ検索(再帰)
		bool isFile = isFiles(dirs[i]);
		serchSubDirectory(dirs[i], isFile);

		if (mShcFile) {
			// 全てのファイル検索
			array<String^>^ files = Directory::GetFiles(dirs[i]);
			Array::Sort(files);
			serchFiles(files);
		}
	}

	mIndent--;				// インデントデクリメント

	return;
}

// ファイル検索
void GenerateDirectory::serchFiles(array<String^>^ files)
{
	int i;
	String^ fileName;

	// ファイルが存在する場合
	if (files->Length > 0) {
		mIndent++;			// インデントインクリメント
		for (i = 0; i < files->Length; i++) {
			fileName = IO::Path::GetFileName(files[i]);
			if (i == files->Length - 1) {
				setOutput(mIndent, fileName, OT_MARK_ED);
			} else {
				setOutput(mIndent, fileName, OT_MARK_BR);
			}
		}
		mIndent--;			// インデントデクリメント
	}
}

// ファイルが存在するか
bool GenerateDirectory::isFiles(String^ dir)
{
	bool ret;
	int fileNum;

	fileNum = getFiles(dir);
	if (fileNum > 0) {
		ret = true;
	} else {
		ret = false;
	}

	return ret;
}


// 出力文字列設定
bool GenerateDirectory::setOutput(int indent, String^ out, unsigned char mark)
{
	bool ret = false;
	String^ data = nullptr;

	if (mOtree != nullptr) {
		// インデント、出力文字列、マーク、終端種別を指定して出力
		data = mOtree->Output(indent, out, mark);
		ret = true;

		// データ取得成功の場合
		if (data != nullptr && mOfile != nullptr) {
			// データをファイル出力する
			mOfile->OutFile(data);
		}
	}

	return ret;
}


