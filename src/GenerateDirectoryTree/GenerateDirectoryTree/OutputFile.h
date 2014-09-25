#pragma once

using namespace System;
using namespace System::IO;

using namespace Microsoft::Office::Interop::Excel;


ref class OutputFile
{
public:
	// �R���X�g���N�^
	OutputFile(void);


	// �����ݒ�
	void Init(String^ path, String^ file, String^ ext, bool excel);
	// �t�@�C���o��
	bool OutFile(String^ s);
	// �t�@�C���N���[�Y
	void CloseFile();

	// �A�N�Z�T
	// �t�@�C���ۑ��`��
	void setFileExt(String^ fileExt);
	String^ getFileExt();
	// �ۑ���
	void setOutputPath(String^ opPath);
	String^ getOutputPath();
	// �t�@�C����
	void setFileName(String^ fileName);
	String^ getFilename();

private:
	// �t�@�C���ۑ��`��
	String^ mFileExt;
	// �ۑ���
	String^ mOutputPath;
	// �t�@�C����
	String^ mOutputFileName;

	// �t�@�C���X�g���[�}�[
	StreamWriter^ mSw;

	// �G�N�Z���o��
	bool mExcel;
	Microsoft::Office::Interop::Excel::Application^ mExcelApl;
	Workbook^ mWb;
};

