#pragma once

using namespace System;
using namespace System::IO;
#ifdef _DEBUG
using namespace System::Diagnostics;
#endif

// �c���[�o�̓N���X
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

// �p�u���b�N�֐�
public:
	// �R���X�g���N�^
	OutputTree(int outfmt);

	// �o�͂���
	String^ Output(int indent, String^ out, unsigned char mark);

// �v���C�x�[�g�ϐ�
private:
	int          mOutputFormat;		// �o�̓t�H�[�}�b�g
	array<int^>^ mPreOut;			// �O��l

// �v���C�x�[�g�֐�
private:
	// �}�[�N��ϊ�����
	String^ ConvMark(int mark);
	// �C���f���g��ϊ�����
	String^ ConvIndent(int indent);
	// �o�͕�����𐶐�����
	String^ OutString(int mark, int indent);
};

