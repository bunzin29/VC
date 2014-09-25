#include "stdafx.h"
#include "OutputTree.h"

#ifdef _DEBUG
#define DEBUG_OUTPUT_TREE
#endif

// �R���X�g���N�^
OutputTree::OutputTree(int outfmt)
{
	mOutputFormat = outfmt;
	mPreOut = nullptr;
}

// �o��
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

// �}�[�N�ϊ�
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

// �C���f���g�ϊ�
String^ OutputTree::convIndent(int indent)
{
	String^ ret = "";

	for (int i = 0; i < indent; i++) {
		ret += TAB;
	}

	return ret;
}

// �o��
String^ OutputTree::outChar(int mark, int indent)
{
	int i;
	String^ ret = nullptr;
	String^ idt;
	String^ mk;

	mk = convMark(mark);		// �}�[�N�ϊ�
	idt = convIndent(indent);	// �C���f���g�ϊ�

	if (mPreOut == nullptr) {	// �O��l�Ȃ�
		// �}�[�N�̂ݐݒ�
		ret = mk;

		// �O��l�ݒ�
		mPreOut = gcnew array<int^>(1);
		mPreOut[0] = CL_STRING;
	} else {
		array<int^>^ preOutTmp;	// �O��l�ꎟ�擾�p
		
		// �O��l�̃T�C�Y����O��l�ꎟ�擾�p����
		int size = mPreOut->Length;
		preOutTmp = gcnew array<int^>(size);

		// �z��R�s�[
		Array::Copy(mPreOut, preOutTmp, mPreOut->Length);

		// �V���ɑO��l�z�񐶐�
		delete []mPreOut;
		mPreOut = nullptr;
		mPreOut = gcnew array<int^>(indent + 1);

		for (i = 0; i <= indent; i++) {
			// �}�[�N����
			if ((indent - 1) == i) {	// �Ō�̂ЂƂO
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

				// �}�[�N��ʂŔ���
				switch (mark) {
					case OT_MARK_BR:
						// �}�[�N�p��
						mPreOut[i] = CL_MARK_CONT;
						break;
					case OT_MARK_ED:
						// �}�[�N�I��
						mPreOut[i] = CL_MARK_END;
						break;
					case OT_MARK_VT:
						// �}�[�N�p��
						mPreOut[i] = CL_MARK_CONT;
						break;
					default:
						// �}�[�N�I��
						mPreOut[i] = CL_MARK_END;
						break;
				}

			} else if (indent == i) {	// �Ō�
				mPreOut[i] = CL_STRING;

			} else {
				int cl = (int)preOutTmp->GetValue(i);
				if (cl == CL_STRING) {
					// �}�[�N����
					mPreOut[i] = CL_NO_MARK;
				} else if (cl == CL_MARK_CONT) {
					// �}�[�N�p��
					mPreOut[i] = CL_MARK_CONT;
				} else if (cl == CL_MARK_END) {
					// �}�[�N�I��
					mPreOut[i] = CL_MARK_END;
				} else if (cl == CL_NO_MARK) {
					// �}�[�N����
					mPreOut[i] = CL_NO_MARK;
				}

				if (((int)mPreOut->GetValue(i)) == CL_MARK_CONT) {
					switch (mOutputFormat) {
						case OUTPUT_FORMAT_TREE:
							ret += " �b ";
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


