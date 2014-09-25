#include "stdafx.h"
#include "OutputTree.h"

#ifdef _DEBUG
#define DEBUG_OUTPUT_TREE
#endif

// コンストラクタ
OutputTree::OutputTree(int outfmt)
{
	mOutputFormat = outfmt;
	mPreOut = nullptr;
}

// 出力
String^ OutputTree::Output(int indent, String^ out, unsigned char mark)
{
	String^ ret = nullptr;
	String^ output;

	output = outChar(mark, indent);
	if (output != nullptr) {
#ifdef DEBUG_OUTPUT_TREE
		Debug::WriteLine(output + out);
#endif
		ret = output + out;
	}

	return ret;
}

// マーク変換
String^ OutputTree::convMark(int mark)
{
	String^ ret = nullptr;

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

// インデント変換
String^ OutputTree::convIndent(int indent)
{
	String^ ret = "";

	for (int i = 0; i < indent; i++) {
		ret += TAB;
	}

	return ret;
}

// 出力
String^ OutputTree::outChar(int mark, int indent)
{
	int i;
	String^ ret = nullptr;
	String^ idt;
	String^ mk;

	mk = convMark(mark);		// マーク変換
	idt = convIndent(indent);	// インデント変換

	if (mPreOut == nullptr) {	// 前回値なし
		// マークのみ設定
		ret = mk;

		// 前回値設定
		mPreOut = gcnew array<int^>(1);
		mPreOut[0] = CL_STRING;
	} else {
		array<int^>^ preOutTmp;	// 前回値一次取得用
		
		// 前回値のサイズから前回値一次取得用生成
		int size = mPreOut->Length;
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


