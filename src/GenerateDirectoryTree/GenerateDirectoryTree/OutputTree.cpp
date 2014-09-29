#include "stdafx.h"
#include "OutputTree.h"

#ifdef _DEBUG
#define DEBUG_OUTPUT_TREE
#endif

// ----------- パブリック関数 ----------- //
// コンストラクタ
OutputTree::OutputTree(int outfmt)
{
	// 初期化
	mOutputFormat = outfmt;
	mPreOut       = nullptr;
}

// 出力する
String^ OutputTree::Output(int indent, String^ out, unsigned char mark)
{
	String^ ret = nullptr;		// 戻り値
	String^ output;				// 出力文字列

	// 出力する文字列を生成
	output = OutString(mark, indent);

	if (output != nullptr) {
#ifdef DEBUG_OUTPUT_TREE
		Debug::WriteLine(output + out);
#endif
		ret = output + out;
	}

	return ret;
}


// ----------- プライベート関数 ----------- //
// マークを変換する
String^ OutputTree::ConvMark(int mark)
{
	String^ ret = nullptr;		// 戻り値

	// int型からString型に変換
	switch (mark) {
		case OT_MARK_BR:
			ret = ST_MARK_BR;
			break;
		case OT_MARK_ED:
			ret = ST_MARK_ED;
			break;
		case OT_MARK_VT:
			ret = ST_MARK_VT;
			break;
		default:
			ret = ST_MARK_NO;
			break;
	}

	return ret;
}

// インデントを変換する
String^ OutputTree::ConvIndent(int indent)
{
	String^ ret = "";			// 戻り値

	// int型からString型に変換
	for (int i = 0; i < indent; i++) {
		ret += TAB;
	}

	return ret;
}

// 出力文字列を生成する
String^ OutputTree::OutString(int mark, int indent)
{
	int     i;
	String^ ret = nullptr;		// 戻り値
	String^ mk;					// マーク
	String^ idt;				// インデント

	mk  = ConvMark(mark);		// マーク変換
	idt = ConvIndent(indent);	// インデント変換

	if (mPreOut == nullptr) {	// 前回値なし
		// マークのみ設定
		ret = mk;

		// 前回値設定
		mPreOut    = gcnew array<int^>(1);
		mPreOut[0] = CL_STRING;
	} else {
		array<int^>^ preOutTmp;	// 前回値一次取得用
		
		// 前回値のサイズから前回値一次取得用生成
		int size  = mPreOut->Length;
		preOutTmp = gcnew array<int^>(size);

		// 配列コピー
		Array::Copy(mPreOut, preOutTmp, mPreOut->Length);

		// 新たに前回値配列生成
		delete []mPreOut;
		mPreOut = nullptr;
		mPreOut = gcnew array<int^>(indent + 1);

		for (i = 0; i <= indent; i++) {
			// マーク判定
			if ((indent - 1) == i) {	// 最後のひとつ前
				switch (mOutputFormat) {
					case OUTPUT_FORMAT_TREE:
						ret += " " + mk + " ";
						break;

					case OUTPUT_FORMAT_EXCEL:
					case OUTPUT_FORMAT_TAB:
						ret += TAB;
						break;

					default:
						break;
				}

				// マーク種別で判定
				switch (mark) {
					case OT_MARK_BR:
						// マーク継続
						mPreOut[i] = CL_MARK_CONT;
						break;
					case OT_MARK_ED:
						// マーク終了
						mPreOut[i] = CL_MARK_END;
						break;
					case OT_MARK_VT:
						// マーク継続
						mPreOut[i] = CL_MARK_CONT;
						break;
					default:
						// マーク終了
						mPreOut[i] = CL_MARK_END;
						break;
				}

			} else if (indent == i) {	// 最後
				mPreOut[i] = CL_STRING;

			} else {
				int cl = (int)preOutTmp->GetValue(i);
				if (cl == CL_STRING) {
					// マーク無し
					mPreOut[i] = CL_NO_MARK;
				} else if (cl == CL_MARK_CONT) {
					// マーク継続
					mPreOut[i] = CL_MARK_CONT;
				} else if (cl == CL_MARK_END) {
					// マーク終了
					mPreOut[i] = CL_MARK_END;
				} else if (cl == CL_NO_MARK) {
					// マーク無し
					mPreOut[i] = CL_NO_MARK;
				}

				if (((int)mPreOut->GetValue(i)) == CL_MARK_CONT) {
					switch (mOutputFormat) {
						case OUTPUT_FORMAT_TREE:
							ret += " ｜ ";
							break;

						case OUTPUT_FORMAT_EXCEL:
						case OUTPUT_FORMAT_TAB:
							ret += TAB;
							break;

						default:
							break;
					}
				} else {
					switch (mOutputFormat) {
						case OUTPUT_FORMAT_TREE:
							ret += "    ";
							break;

						case OUTPUT_FORMAT_EXCEL:
						case OUTPUT_FORMAT_TAB:
							ret += TAB;
							break;

						default:
							break;
					}
				}
			}
		}
	}
	
	return ret;
}
