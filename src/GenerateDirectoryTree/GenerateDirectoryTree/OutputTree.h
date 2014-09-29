#pragma once

using namespace System;
using namespace System::IO;
#ifdef _DEBUG
using namespace System::Diagnostics;
#endif

// ツリー出力クラス
ref class OutputTree
{
// マーク種別
#define OT_MARK_NONE		(0)
#define OT_MARK_BR			(1)
#define OT_MARK_ED			(2)
#define OT_MARK_VT			(3)

// マーク
#define ST_MARK_NO			""
#define ST_MARK_BR			"├"
#define ST_MARK_ED			"└"
#define ST_MARK_VT			""

// 出力フォーマット
#define OUTPUT_FORMAT_TREE	(0)
#define OUTPUT_FORMAT_TAB	(1)
#define OUTPUT_FORMAT_EXCEL	(2)

#define TAB					"\t"

// 種別
#define CL_STRING			(1)		// 文字列(ディレクトリ/ファイル)
#define CL_MARK_CONT		(2)		// マーク継続
#define CL_MARK_END			(3)		// マーク終了
#define CL_NO_MARK			(4)		// マーク無し

// パブリック関数
public:
	// コンストラクタ
	OutputTree(int outfmt);

	// 出力する
	String^ Output(int indent, String^ out, unsigned char mark);

// プライベート変数
private:
	int          mOutputFormat;		// 出力フォーマット
	array<int^>^ mPreOut;			// 前回値

// プライベート関数
private:
	// マークを変換する
	String^ ConvMark(int mark);
	// インデントを変換する
	String^ ConvIndent(int indent);
	// 出力文字列を生成する
	String^ OutString(int mark, int indent);
};

