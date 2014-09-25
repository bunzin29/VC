#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;

ref class OutputTree
{
// �}�[�N���
#define OT_MARK_NONE		(0)
#define OT_MARK_BR			(1)
#define OT_MARK_ED			(2)
#define OT_MARK_VT			(3)

// �}�[�N
#define ST_MARK_NO			""
#define ST_MARK_BR			"��"
#define ST_MARK_ED			"��"
#define ST_MARK_VT			""

// �o�̓t�H�[�}�b�g
#define OUTPUT_FORMAT_TREE	(0)
#define OUTPUT_FORMAT_TAB	(1)
#define OUTPUT_FORMAT_EXCEL	(2)

#define TAB					"\t"

// ���
#define CL_STRING			(1)		// ������(�f�B���N�g��/�t�@�C��)
#define CL_MARK_CONT		(2)		// �}�[�N�p��
#define CL_MARK_END			(3)		// �}�[�N�I��
#define CL_NO_MARK			(4)		// �}�[�N����

public:
	// �R���X�g���N�^
	OutputTree(int outfmt);

	// �o��
	String^ Output(int indent, String^ out, unsigned char mark);

private:
	// �}�[�N�ϊ�
	String^ convMark(int mark);
	// �C���f���g�ϊ�
	String^ convIndent(int indent);
	// �o��
	String^ outChar(int mark, int indent);

	// �o�̓t�H�[�}�b�g
	int mOutputFormat;
	// �O��l
	array<int^>^ mPreOut;
	
};

