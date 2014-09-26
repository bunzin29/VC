#pragma once

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
		Main^ mMain;

		System::Windows::Forms::Button^  btn_exe;
		System::Windows::Forms::Button^  btn_clear;
		String^ inputDirList;//�t���p�X���i�[����z��
	private: System::Windows::Forms::CheckBox^  cb_Tab;


			 System::Windows::Forms::ListBox^  lb_in_dir;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//

			mMain = gcnew Main();

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
			this->cb_Tab = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// lb_in_dir
			// 
			this->lb_in_dir->AllowDrop = true;
			this->lb_in_dir->FormattingEnabled = true;
			this->lb_in_dir->HorizontalScrollbar = true;
			this->lb_in_dir->ItemHeight = 12;
			this->lb_in_dir->Location = System::Drawing::Point(12, 23);
			this->lb_in_dir->Name = L"lb_in_dir";
			this->lb_in_dir->SelectionMode = System::Windows::Forms::SelectionMode::MultiSimple;
			this->lb_in_dir->Size = System::Drawing::Size(385, 64);
			this->lb_in_dir->TabIndex = 0;
			this->lb_in_dir->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::lb_in_dir_SelectedIndexChanged);
			this->lb_in_dir->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::lb_in_dir_DragDrop);
			this->lb_in_dir->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::lb_in_dir_DragEnter);
			// 
			// btn_exe
			// 
			this->btn_exe->Location = System::Drawing::Point(12, 101);
			this->btn_exe->Name = L"btn_exe";
			this->btn_exe->Size = System::Drawing::Size(75, 23);
			this->btn_exe->TabIndex = 1;
			this->btn_exe->Text = L"���s";
			this->btn_exe->UseVisualStyleBackColor = true;
			this->btn_exe->Click += gcnew System::EventHandler(this, &Form1::btn_exe_Click);
			// 
			// btn_clear
			// 
			this->btn_clear->Location = System::Drawing::Point(107, 101);
			this->btn_clear->Name = L"btn_clear";
			this->btn_clear->Size = System::Drawing::Size(75, 23);
			this->btn_clear->TabIndex = 2;
			this->btn_clear->Text = L"�N���A";
			this->btn_clear->UseVisualStyleBackColor = true;
			this->btn_clear->Click += gcnew System::EventHandler(this, &Form1::btn_clear_Click);
			// 
			// cb_Tab
			// 
			this->cb_Tab->AutoSize = true;
			this->cb_Tab->Location = System::Drawing::Point(216, 107);
			this->cb_Tab->Name = L"cb_Tab";
			this->cb_Tab->Size = System::Drawing::Size(43, 16);
			this->cb_Tab->TabIndex = 3;
			this->cb_Tab->Text = L"Tab";
			this->cb_Tab->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(417, 151);
			this->Controls->Add(this->cb_Tab);
			this->Controls->Add(this->btn_clear);
			this->Controls->Add(this->btn_exe);
			this->Controls->Add(this->lb_in_dir);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void lb_in_dir_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
				 array<String^>^ s = (array<String^>^)e->Data->GetData(DataFormats::FileDrop, false);
				 for (int i = 0; i < s->Length; i++) {
#ifdef _DEBUG
					 Debug::WriteLine(s[i]);
#endif
					 inputDirList = s[i];

					 DirectoryInfo^ di = gcnew DirectoryInfo(s[i]);

					 if (di->Exists) {
						 // �f�B���N�g���̂ݒǉ�
						 this->lb_in_dir->Items->Add(s[i]);
					 }
				 }
			 }
	private: System::Void lb_in_dir_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {

				if(e->Data->GetDataPresent(DataFormats::FileDrop)) {
					e->Effect = DragDropEffects::All;
				} else {
					e->Effect = DragDropEffects::None;
				}

			 }
	private: System::Void lb_in_dir_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 }

	// ���s�{�^��
	private: System::Void btn_exe_Click(System::Object^  sender, System::EventArgs^  e) {
				 int i;
				 int procCnt = 0;
				 int cnt;

				 cnt = this->lb_in_dir->Items->Count;
				 for (i = 0; i < cnt; i++) {
#ifdef _DEBUG
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

					 mMain->Start(this->lb_in_dir->Items[i]->ToString(), this->cb_Tab->Checked);
					 procCnt++;
				 }
				 if (procCnt > 0) {
					 MessageBox::Show("����I��");
				 } else {

				 }
			 }

	// �N���A
	private: System::Void btn_clear_Click(System::Object^  sender, System::EventArgs^  e) {
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
};
}

