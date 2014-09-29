#include "stdafx.h"
#include "GenerateDirectory.h"


// ----------- �p�u���b�N�֐� ----------- //
// �R���X�g���N�^
GenerateDirectory::GenerateDirectory(void)
{
}

// �����ݒ���s��
void GenerateDirectory::Init(String^ dir, int outfmt, BackgroundWorker^ worker, DoWorkEventArgs^ doWkEvt, long cnt)
{
	// ���s�X���b�h�ݒ�
	mWorker  = worker;
	mDoWkEvt = doWkEvt;
	// �v���O���X�o�[�p�ϐ�������
	mAllCnt  = cnt;
	mExeCnt  = 0;

	// �J�����g�f�B���N�g���ݒ�
	mCurrentDir = dir;

	// �o�̓t�H�[�}�b�g���w�肵�ďo�̓N���X����
	mOtree = gcnew OutputTree(outfmt);
}

// ���s����
bool GenerateDirectory::Exec(String^ /*dirPath*/, String^ /*filePath*/)
{
	bool ret = true;
	
	if (mCurrentDir == nullptr) {	// �J�����g�f�B���N�g�����k���̏ꍇ
		// �߂�l�Ɏ��s��ݒ�
		ret = false;

	} else {
		// ������
		Init();

		// ���[�g�f�B���N�g����ݒ�
		RootDirectory(mCurrentDir);

		// �T�u�f�B���N�g������
		array<String^>^ d = Directory::GetDirectories(mCurrentDir);
		Array::Sort(d);

		if (d->Length > 0) {
			// �T�u�f�B���N�g������
			SerchSubDirectory(mCurrentDir, IsFiles(mCurrentDir));
		}
		
		// �J�����g�f�B���N�g������
		SerchCurrentFiles(mCurrentDir);

		// �㏈��
		After();
	}

	return ret;
}


// ----------- �v���C�x�[�g�֐� ----------- //
// ���������s��
void GenerateDirectory::Init(void)
{
	String^ path = nullptr;
	String^ file = nullptr;
	String^ ext = nullptr;
	String^ fileName = nullptr;

	mIndent = 0;								// �C���f���g
	mCurrentFileNum = GetFiles(mCurrentDir);	// �J�����g�̃t�@�C����
	mShcFile = true;

	// �t�@�C���o�͐ݒ�
	// �p�l���܂��̓f�t�H���g�ۑ���w��
	if (mDirPath != nullptr && mFileName != nullptr) {
		// T.B.D

	} else {
		//�A�v���P�[�V�������J�n�������s�\�t�@�C���́A�t�@�C�������܂܂Ȃ��p�X���擾
		path = System::Windows::Forms::Application::StartupPath;

		// �J�����g�f�B���N�g���ݒ�
		fileName = mCurrentDir;

		// �f�B���N�g�������t�@�C�����ɐݒ�
		file = fileName->Remove(0, fileName->LastIndexOf("\\") + 1);

		// �o�̓t�@�C���̊g���q��ݒ�
		ext = "txt";
	}

	// OutputFile�N���X
	mOfile = gcnew OutputFile();
	// �o�͐�ݒ�
	mOfile->Init(path, file, ext);
}

// �㏈�����s��
void GenerateDirectory::After(void)
{
#ifndef _DEBUG		// ���������t�@�C�����J��
	String^ filePath;

	filePath = mOfile->getFilePath();

	if (filePath != nullptr && filePath != "") {
		System::Diagnostics::Process::Start(filePath);
	}
#endif

	// CloseFile�Ńk���`�F�b�N���s���Ă���
	mOfile->CloseFile();
}

// ���[�g�f�B���N�g�������o�͂���
void GenerateDirectory::RootDirectory(String^ dir)
{
	String^ dirName;		// �f�B���N�g����

	// �f�B���N�g�����擾
	dirName = dir->Remove(0, dir->LastIndexOf("\\") + 1);
	// ������o��
	SetOutput(mIndent, dirName, OT_MARK_NONE);
}

// �J�����g�f�B���N�g������������
void GenerateDirectory::SerchCurrentFiles(String^ dir)
{
	// �t�@�C���������L���̏ꍇ
	if (mShcFile) {
		// (����)�t�@�C�����w�肵�ăt�@�C������
		array<String^>^ files = Directory::GetFiles(dir);
		Array::Sort(files);

		// �t�@�C������
		SerchFiles(files);
	}
}

// �t�@�C�������擾����
int GenerateDirectory::GetFiles(String^ dir)
{
	array<String^>^ files;

	// �w�肵���f�B���N�g���̃t�@�C�����擾
	files =  Directory::GetFiles(dir);

	return files->Length;
}

// �T�u�f�B���N�g������������
void GenerateDirectory::SerchSubDirectory(String^ dir, bool exFile)
{
	array<String^>^ dirs;		// �f�B���N�g���ꗗ
	String^         dirName;	// �f�B���N�g����	

	// ���s�X���b�h����m�F
	if (EndExeThread()) {
		return;
	}

	mIndent++;					// �C���f���g�C���N�������g

	// �S�Ẵf�B���N�g���擾
	dirs = Directory::GetDirectories(dir);
	Array::Sort(dirs);

	// �S�ẴT�u�f�B���N�g��������(�ċA)
	for (int i = 0; i < dirs->Length; i++) {
		// �f�B���N�g�����擾
		dirName = dirs[i]->Remove(0, dirs[i]->LastIndexOf("\\") + 1);

		if (i == (dirs->Length - 1)) {	// �Ō�̃f�B���N�g��
			if (exFile) {				// �t�@�C�������݂���
				SetOutput(mIndent, dirName, OT_MARK_BR);
			} else {					// �t�@�C�������݂��Ȃ�
				SetOutput(mIndent, dirName, OT_MARK_ED);
			}
		} else {
			SetOutput(mIndent, dirName, OT_MARK_BR);
		}

		// �T�u�f�B���N�g������(�ċA)
		bool isFile = IsFiles(dirs[i]);
		SerchSubDirectory(dirs[i], isFile);

		if (mShcFile) {		// �t�@�C���������L���̏ꍇ
			// �S�Ẵt�@�C������
			array<String^>^ files = Directory::GetFiles(dirs[i]);
			Array::Sort(files);
			SerchFiles(files);
		}
	}

	mIndent--;				// �C���f���g�f�N�������g
}

// �t�@�C����������
void GenerateDirectory::SerchFiles(array<String^>^ files)
{
	int     i;
	String^ fileName;		// �t�@�C����

	// �t�@�C�������݂���ꍇ
	if (files->Length > 0) {
		mIndent++;			// �C���f���g�C���N�������g
		for (i = 0; i < files->Length; i++) {
			// �t�@�C�����擾
			fileName = IO::Path::GetFileName(files[i]);
			if (i == files->Length - 1) {		// �t�@�C�����Ōォ����
				SetOutput(mIndent, fileName, OT_MARK_ED);
			} else {
				SetOutput(mIndent, fileName, OT_MARK_BR);
			}
		}
		mIndent--;			// �C���f���g�f�N�������g
	}
}

// �t�@�C�������݂��邩
bool GenerateDirectory::IsFiles(String^ dir)
{
	bool ret;			// �߂�l
	int  fileNum;		// �t�@�C����

	// �t�@�C�����擾
	fileNum = GetFiles(dir);
	if (fileNum > 0) {
		ret = true;
	} else {
		ret = false;
	}

	return ret;
}

// �o�͕������ݒ肷��
bool GenerateDirectory::SetOutput(int indent, String^ out, unsigned char mark)
{
	bool    ret  = false;		// �߂�l
	String^ data = nullptr;		// �f�[�^�i�[�p

	if (mOtree != nullptr) {
		// �C���f���g�A�o�͕�����A�}�[�N�A�I�[��ʂ��w�肵�ďo��
		data = mOtree->Output(indent, out, mark);
		ret = true;

		// �f�[�^�擾�����̏ꍇ
		if (data != nullptr && mOfile != nullptr) {
			// �f�[�^���t�@�C���o�͂���
			mOfile->OutFile(data);

			// �v���O���X�o�[�X�V
			UpdatePrg();
		}
	}

	return ret;
}

// �v���O���X�o�[���X�V����
bool GenerateDirectory::UpdatePrg(void)
{
	bool   ret = true;		// �߂�l
	double tmp;				// �f�[�^�ꎞ�i�[�p

	mExeCnt++;		// �J�E���g�A�b�v

	// �v���O���X�o�[�̐ݒ�l�v�Z(0�`100)
	tmp = (double)mExeCnt / (double)mAllCnt;
	tmp *= 100.0;

	mWorker->ReportProgress((int)tmp);

	return ret;
}

// ���s�X���b�h�𔻒肷��
bool GenerateDirectory::EndExeThread(void)
{
	bool ret = false;		// �߂�l

	// ���s�X���b�h�̃L�����Z����v��������
	if (mWorker->CancellationPending) {
		mDoWkEvt->Cancel = true;
		ret = true;
	}

	return ret;
}
