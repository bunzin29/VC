#pragma once

using namespace System;

// �\�t�g�E�F�A�o�[�W����
#define SOFTWARE_VERSION	"0.0.1"

// �ݒ�N���X
public ref  class Config {
// �p�u���b�N�ϐ�
public:
	String^ version;	// �o�[�W�������

// �p�u���b�N�֐�
public:
	// �R���X�g���N�^
	Config()
	{
		version = SOFTWARE_VERSION;
	}
};
