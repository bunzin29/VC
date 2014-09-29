#pragma once

#include "Config.h"
#include "Main.h"

namespace GenerateDirectoryTree {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Form1 �̊T�v
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		Main^   mMain;				// ���C���N���X
		Config^ mConfig;			// �ݒ�N���X
		String^ mInputDirList;		//�t���p�X���i�[����z��
		long    mAllDirCnt;			// ���s����f�B���N�g���y�уt�@�C������

		// �t�H�[���R���g���[��
	private:
		System::Windows::Forms::Button^            btn_exe;				// ���s�{�^��
		System::Windows::Forms::Button^            btn_clear;			// �N���A�{�^��
		System::Windows::Forms::CheckBox^          cb_tab;				// �^�u�`�F�b�N�{�b�N�X
		System::ComponentModel::BackgroundWorker^  bgw_exe;				// ���s�X���b�h
		System::Windows::Forms::MenuStrip^         menuStrip;					// ���j���[
		System::Windows::Forms::ToolStripMenuItem^ �w���vToolStripMenuItem;		// ���j���[���ځF�w���v
		System::Windows::Forms::ToolStripMenuItem^ �o�[�W����ToolStripMenuItem;	// ���j���[���ځF�o�[�W����
		System::Windows::Forms::ProgressBar^       progressBar;			// �v���O���X�o�[
		System::Windows::Forms::ListBox^           lb_in_dir;			// �f�B���N�g�����X�g�{�b�N�X

	public:
		Form1(void)
		{
			InitializeComponent();

			mMain      = gcnew Main();		// ���C���N���X
			mConfig    = gcnew Config();	// �ݒ�N���X
			mAllDirCnt = 0;

#ifdef _DEBUG
			lb_in_dir->Items->Add("E:\\GitHub\\VC\\src\\GenerateDirectoryTree\\bin\\05_�c���^(CV#3)");
#endif

		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}


	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->lb_in_dir = (gcnew System::Windows::Forms::ListBox());
			this->btn_exe = (gcnew System::Windows::Forms::Button());
			this->btn_clear = (gcnew System::Windows::Forms::Button());
			this->cb_tab = (gcnew System::Windows::Forms::CheckBox());
			this->bgw_exe = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->�w���vToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�o�[�W����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->menuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// lb_in_dir
			// 
			this->lb_in_dir->AllowDrop = true;
			this->lb_in_dir->FormattingEnabled = true;
			this->lb_in_dir->HorizontalScrollbar = true;
			this->lb_in_dir->ItemHeight = 12;
			this->lb_in_dir->Location = System::Drawing::Point(12, 34);
			this->lb_in_dir->Name = L"lb_in_dir";
			this->lb_in_dir->SelectionMode = System::Windows::Forms::SelectionMode::MultiSimple;
			this->lb_in_dir->Size = System::Drawing::Size(385, 76);
			this->lb_in_dir->TabIndex = 0;
			this->lb_in_dir->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::lb_in_dir_SelectedIndexChanged);
			this->lb_in_dir->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::lb_in_dir_DragDrop);
			this->lb_in_dir->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::lb_in_dir_DragEnter);
			// 
			// btn_exe
			// 
			this->btn_exe->Location = System::Drawing::Point(12, 121);
			this->btn_exe->Name = L"btn_exe";
			this->btn_exe->Size = System::Drawing::Size(75, 23);
			this->btn_exe->TabIndex = 1;
			this->btn_exe->Text = L"���s";
			this->btn_exe->UseVisualStyleBackColor = true;
			this->btn_exe->Click += gcnew System::EventHandler(this, &Form1::btn_exe_Click);
			// 
			// btn_clear
			// 
			this->btn_clear->Location = System::Drawing::Point(102, 121);
			this->btn_clear->Name = L"btn_clear";
			this->btn_clear->Size = System::Drawing::Size(75, 23);
			this->btn_clear->TabIndex = 2;
			this->btn_clear->Text = L"�N���A";
			this->btn_clear->UseVisualStyleBackColor = true;
			this->btn_clear->Click += gcnew System::EventHandler(this, &Form1::btn_clear_Click);
			// 
			// cb_tab
			// 
			this->cb_tab->AutoSize = true;
			this->cb_tab->Location = System::Drawing::Point(204, 125);
			this->cb_tab->Name = L"cb_tab";
			this->cb_tab->Size = System::Drawing::Size(43, 16);
			this->cb_tab->TabIndex = 3;
			this->cb_tab->Text = L"Tab";
			this->cb_tab->UseVisualStyleBackColor = true;
			// 
			// bgw_exe
			// 
			this->bgw_exe->WorkerReportsProgress = true;
			this->bgw_exe->WorkerSupportsCancellation = true;
			this->bgw_exe->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker_DoWork);
			this->bgw_exe->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::backgroundWorker1_ProgressChanged);
			this->bgw_exe->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker1_RunWorkerCompleted);
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->�w���vToolStripMenuItem});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(417, 26);
			this->menuStrip->TabIndex = 4;
			this->menuStrip->Text = L"menuStrip";
			// 
			// �w���vToolStripMenuItem
			// 
			this->�w���vToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->�o�[�W����ToolStripMenuItem});
			this->�w���vToolStripMenuItem->Name = L"�w���vToolStripMenuItem";
			this->�w���vToolStripMenuItem->Size = System::Drawing::Size(75, 22);
			this->�w���vToolStripMenuItem->Text = L"�w���v(&H)";
			// 
			// �o�[�W����ToolStripMenuItem
			// 
			this->�o�[�W����ToolStripMenuItem->Name = L"�o�[�W����ToolStripMenuItem";
			this->�o�[�W����ToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->�o�[�W����ToolStripMenuItem->Text = L"�o�[�W����(&V)";
			this->�o�[�W����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::�o�[�W����ToolStripMenuItem_Click);
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(254, 120);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(143, 23);
			this->progressBar->TabIndex = 5;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(417, 151);
			this->Controls->Add(this->progressBar);
			this->Controls->Add(this->cb_tab);
			this->Controls->Add(this->btn_clear);
			this->Controls->Add(this->btn_exe);
			this->Controls->Add(this->lb_in_dir);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public :
		// �f���Q�[�g
		delegate void delSetControl(bool en);
		delSetControl^ mDelSetCtrl;
	
	private:
		// �R���g���[���ݒ�
		void SetControl(bool en)
		{
			if (en) {
				// �L���ݒ�
				setEnableCtrl();
			} else {
				// �����ݒ�
				setDisableCtrl();
			}
		}

	private:
		// �R���g���[���L��
		void setEnableCtrl(void)
		{
			this->btn_exe->Enabled   = true;
			this->btn_clear->Enabled = true;
		}

	private:
		// �R���g���[������
		void setDisableCtrl(void)
		{
			this->btn_exe->Enabled   = false;
			this->btn_clear->Enabled = false;

		}

	private:
		// �h���b�O&�h���b�v����
		System::Void lb_in_dir_DragDrop(System::Object^  /*sender*/, System::Windows::Forms::DragEventArgs^  e)
		{
			array<String^>^ s = (array<String^>^)e->Data->GetData(DataFormats::FileDrop, false);
			for (int i = 0; i < s->Length; i++) {
#ifdef _DEBUG
				Debug::WriteLine(s[i]);
#endif
				// ���͕�����ݒ�
				mInputDirList = s[i];

				DirectoryInfo^ di = gcnew DirectoryInfo(s[i]);
				if (di->Exists) {
					// �f�B���N�g���̂ݒǉ�
					this->lb_in_dir->Items->Add(s[i]);
				}
			}
		}

	private:
		// �h���b�O�G���^�[
		System::Void lb_in_dir_DragEnter(System::Object^  /*sender*/, System::Windows::Forms::DragEventArgs^  e)
		{
			if(e->Data->GetDataPresent(DataFormats::FileDrop)) {
				e->Effect = DragDropEffects::All;
			} else {
				e->Effect = DragDropEffects::None;
			}
		}

	private:
		// �A�C�e���ύX
		System::Void lb_in_dir_SelectedIndexChanged(System::Object^  /*sender*/, System::EventArgs^  /*e*/)
		{
			// T.B.D
		}

	private:
		// ���s�{�^��
		System::Void btn_exe_Click(System::Object^  /*sender*/, System::EventArgs^  /*e*/)
		{
#if 1
			mDelSetCtrl = gcnew delSetControl(this, &GenerateDirectoryTree::Form1::SetControl);
			mDelSetCtrl->Invoke(false);
#endif
			// �X���b�h�N��
			bgw_exe->RunWorkerAsync();
		}

	private:
		// �N���A
		System::Void btn_clear_Click(System::Object^  /*sender*/, System::EventArgs^  /*e*/)
		{
			int i;
				 
			// �I�����ꂽ���ڂ̂ݍ폜
			for (i = 0; i < lb_in_dir->SelectedIndices->Count; i++) {
				lb_in_dir->Items->RemoveAt(lb_in_dir->SelectedIndices[i]);
			}

			// �S�폜
			if (i == 0) {
				while (lb_in_dir->Items->Count > 0) {
					lb_in_dir->Items->RemoveAt(0);
				}
			}
		}

	private:
		// �X���b�h���s����
		System::Void backgroundWorker_DoWork(System::Object^  /*sender*/, System::ComponentModel::DoWorkEventArgs^  e)
		{
			int i;
			int procCnt = 0;
			int cnt;

			// ���s����f�B���N�g����
			cnt = this->lb_in_dir->Items->Count;

			// ���s����S�Ẵf�B���N�g���y�уt�@�C�������v�Z
			mAllDirCnt = 0;
			for (i = 0; i < cnt; i++) {
				mAllDirCnt += Directory::GetDirectories(this->lb_in_dir->Items[i]->ToString(),
							"*", System::IO::SearchOption::AllDirectories)->Length;
				mAllDirCnt += Directory::GetFiles(this->lb_in_dir->Items[i]->ToString(),
							"*", System::IO::SearchOption::AllDirectories)->Length;
			}


			for (i = 0; i < cnt; i++) {
#ifdef _DEBUG	// �f�o�b�O�ł͖���
				Debug::WriteLine(this->lb_in_dir->Items[i]->ToString());
#endif

#ifndef _DEBUG
				if (i != 0) {
					System::Windows::Forms::DialogResult result =
							MessageBox::Show("�����ď������܂����H", "", MessageBoxButtons::YesNo);
					if (result != System::Windows::Forms::DialogResult::Yes) {
						break;
					}
				}
#endif
				mMain->Start(this->lb_in_dir->Items[i]->ToString(), this->cb_tab->Checked,
					this->bgw_exe, e, mAllDirCnt);
				procCnt++;
			}
			
#ifndef _DEBUG	// �f�o�b�O�ł͖���
			if (procCnt > 0) {
				MessageBox::Show("����I��");
			}
#endif
		}

	private:
		// �ύX
		System::Void backgroundWorker1_ProgressChanged(System::Object^  /*sender*/, System::ComponentModel::ProgressChangedEventArgs^  e)
		{
			int value;
			
			value = e->ProgressPercentage;
			this->progressBar->Value = value;
		}

	private:
		// �X���b�h�I��
		System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  /*sender*/, System::ComponentModel::RunWorkerCompletedEventArgs^  /*e*/)
		{
			mDelSetCtrl = gcnew delSetControl(this, &GenerateDirectoryTree::Form1::SetControl);
			mDelSetCtrl->Invoke(true);
		}

	private:
		// �o�[�W����
		System::Void �o�[�W����ToolStripMenuItem_Click(System::Object^  /*sender*/, System::EventArgs^  /*e*/)
		{
			String^ ver;

			ver = mConfig->version;
			MessageBox::Show("�\�t�g�E�F�A�o�[�W�����F " + ver, "�o�[�W�������");
		}

};
}

