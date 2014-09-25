#include "stdafx.h"
#include "GenerateDirectory.h"

// �R���X�g���N�^
GenerateDirectory::GenerateDirectory(void)
{
}

// ----------- public ----------- //

// �����ݒ�
void GenerateDirectory::Init(String^ dir, int outfmt)
{
	// �J�����g�f�B���N�g���ݒ�
	mCurrentDir = dir;
	// �o�̓t�H�[�}�b�g���w�肵�ďo�̓N���X����
	mOtree = gcnew OutputTree(outfmt);
}

// ���s
bool GenerateDirectory::Exec(String^ dirPath, String^ filePath)
{
	bool ret = true;
	
	if (mCurrentDir == nullptr) {	// �J�����g�f�B���N�g�����k���̏ꍇ
		// �߂�l�Ɏ��s��ݒ�
		ret = false;

	} else {
		// ������
		Init();

		// ���[�g�f�B���N�g����ݒ�
		rootDirectory(mCurrentDir);

		// �T�u�f�B���N�g������
		array<String^>^ d = Directory::GetDirectories(mCurrentDir);
		Array::Sort(d);

		if (d->Length > 0) {
			// �T�u�f�B���N�g������
			serchSubDirectory(mCurrentDir, isFiles(mCurrentDir));
		}
		
		// �J�����g�f�B���N�g������
		serchCurrentFiles(mCurrentDir);

		// �㏈��
		After();
	}

	return ret;
}

// ----------- private ----------- //

// ������
void GenerateDirectory::Init()
{
	String^ path = nullptr;
	String^ file = nullptr;
	String^ ext = nullptr;
	String^ fileName = nullptr;

	mIndent = 0;								// �C���f���g
	MCurrentFileNum = getFiles(mCurrentDir);	// �J�����g�̃t�@�C����
	mShcFile = true;

	// �t�@�C���o�͐ݒ�
	// �p�l���܂��̓f�t�H���g�ۑ���w��
	if (mDirPath != nullptr && mFileName != nullptr) {

	} else {
		path = System::Windows::Forms::Application::StartupPath;

		fileName = mCurrentDir;

		file = fileName->Remove(0, fileName->LastIndexOf("\\") + 1);
		ext = "txt";
	}

	// OutputFile�N���X
	mOfile = gcnew OutputFile();
	// �o�͐�ݒ�
	mOfile->Init(path, file, ext);
}

// �㏈��
void GenerateDirectory::After()
{
	// CloseFile�Ńk���`�F�b�N���s���Ă���
	mOfile->CloseFile();
}

// �t�@�C�����擾
int GenerateDirectory::getFiles(String^ dir)
{
	array<String^>^ files;

	// �w�肵���f�B���N�g���̃t�@�C�����擾
	files =  Directory::GetFiles(dir);

	return files->Length;
}

// ���[�g�f�B���N�g��
void GenerateDirectory::rootDirectory(String^ dir)
{
	String^ dirName;

	dirName = dir->Remove(0, dir->LastIndexOf("\\") + 1);
	// ������o��
	setOutput(mIndent, dirName, OT_MARK_NONE);
}

// �J�����g�f�B���N�g������
void GenerateDirectory::serchCurrentFiles(String^ dir)
{
	// �t�@�C���������L���̏ꍇ
	if (mShcFile) {
		// (����)�t�@�C�����w�肵�ăt�@�C������
		array<String^>^ files = Directory::GetFiles(dir);
		Array::Sort(files);
		serchFiles(files);
	}
}

// �T�u�f�B���N�g������
void GenerateDirectory::serchSubDirectory(String^ dir, bool exFile)
{
	array<String^>^ dirs;		// �f�B���N�g���ꗗ
	String^ dirName;

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
				setOutput(mIndent, dirName, OT_MARK_BR);
			} else {					// �t�@�C�������݂��Ȃ�
				setOutput(mIndent, dirName, OT_MARK_ED);
			}
		} else {
			setOutput(mIndent, dirName, OT_MARK_BR);
		}

		// �T�u�f�B���N�g������(�ċA)
		bool isFile = isFiles(dirs[i]);
		serchSubDirectory(dirs[i], isFile);

		if (mShcFile) {
			// �S�Ẵt�@�C������
			array<String^>^ files = Directory::GetFiles(dirs[i]);
			Array::Sort(files);
			serchFiles(files);
		}
	}

	mIndent--;				// �C���f���g�f�N�������g

	return;
}

// �t�@�C������
void GenerateDirectory::serchFiles(array<String^>^ files)
{
	int i;
	String^ fileName;

	// �t�@�C�������݂���ꍇ
	if (files->Length > 0) {
		mIndent++;			// �C���f���g�C���N�������g
		for (i = 0; i < files->Length; i++) {
			fileName = IO::Path::GetFileName(files[i]);
			if (i == files->Length - 1) {
				setOutput(mIndent, fileName, OT_MARK_ED);
			} else {
				setOutput(mIndent, fileName, OT_MARK_BR);
			}
		}
		mIndent--;			// �C���f���g�f�N�������g
	}
}

// �t�@�C�������݂��邩
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


// �o�͕�����ݒ�
bool GenerateDirectory::setOutput(int indent, String^ out, unsigned char mark)
{
	bool ret = false;
	String^ data = nullptr;

	if (mOtree != nullptr) {
		// �C���f���g�A�o�͕�����A�}�[�N�A�I�[��ʂ��w�肵�ďo��
		data = mOtree->Output(indent, out, mark);
		ret = true;

		// �f�[�^�擾�����̏ꍇ
		if (data != nullptr && mOfile != nullptr) {
			// �f�[�^���t�@�C���o�͂���
			mOfile->OutFile(data);
		}
	}

	return ret;
}


