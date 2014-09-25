#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;

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

public:
	// コンストラクタ
	OutputTree(int outfmt);

	// 出力
	String^ Output(int indent, String^ out, unsigned char mark);

private:
	// マーク変換
	String^ convMark(int mark);
	// インデント変換
	String^ convIndent(int indent);
	// 出力
	String^ outChar(int mark, int indent);

	// 出力フォーマット
	int mOutputFormat;
	// 前回値
	array<int^>^ mPreOut;
	
};

