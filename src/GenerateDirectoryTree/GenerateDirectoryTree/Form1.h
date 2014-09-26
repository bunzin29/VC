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
	/// Form1 の概要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		Main^ mMain;
		String^ inputDirList;//フルパスを格納する配列

		// フォームコントロール
		System::Windows::Forms::Button^            btn_exe;				// 実行ボタン
		System::Windows::Forms::Button^            btn_clear;			// クリアボタン
		System::Windows::Forms::CheckBox^          cb_tab;				// タブチェックボックス
		System::ComponentModel::BackgroundWorker^  bgw_exe;				// 実行スレッド
		System::Windows::Forms::ListBox^           lb_in_dir;			// ディレクトリリストボックス

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//

			mMain = gcnew Main();

#ifdef _DEBUG
			lb_in_dir->Items->Add("E:\\GitHub\\VC\\src\\GenerateDirectoryTree\\bin\\05_議事録(CV#3)");
#endif

		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
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
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->lb_in_dir = (gcnew System::Windows::Forms::ListBox());
			this->btn_exe = (gcnew System::Windows::Forms::Button());
			this->btn_clear = (gcnew System::Windows::Forms::Button());
			this->cb_tab = (gcnew System::Windows::Forms::CheckBox());
			this->bgw_exe = (gcnew System::ComponentModel::BackgroundWorker());
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
			this->btn_exe->Text = L"実行";
			this->btn_exe->UseVisualStyleBackColor = true;
			this->btn_exe->Click += gcnew System::EventHandler(this, &Form1::btn_exe_Click);
			// 
			// btn_clear
			// 
			this->btn_clear->Location = System::Drawing::Point(107, 101);
			this->btn_clear->Name = L"btn_clear";
			this->btn_clear->Size = System::Drawing::Size(75, 23);
			this->btn_clear->TabIndex = 2;
			this->btn_clear->Text = L"クリア";
			this->btn_clear->UseVisualStyleBackColor = true;
			this->btn_clear->Click += gcnew System::EventHandler(this, &Form1::btn_clear_Click);
			// 
			// cb_tab
			// 
			this->cb_tab->AutoSize = true;
			this->cb_tab->Location = System::Drawing::Point(216, 107);
			this->cb_tab->Name = L"cb_tab";
			this->cb_tab->Size = System::Drawing::Size(43, 16);
			this->cb_tab->TabIndex = 3;
			this->cb_tab->Text = L"Tab";
			this->cb_tab->UseVisualStyleBackColor = true;
			// 
			// bgw_exe
			// 
			this->bgw_exe->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker_DoWork);
			this->bgw_exe->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::backgroundWorker1_ProgressChanged);
			this->bgw_exe->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker1_RunWorkerCompleted);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(417, 151);
			this->Controls->Add(this->cb_tab);
			this->Controls->Add(this->btn_clear);
			this->Controls->Add(this->btn_exe);
			this->Controls->Add(this->lb_in_dir);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private:
		// ドラッグ&ドロップ動作
		System::Void lb_in_dir_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
		{
				 array<String^>^ s = (array<String^>^)e->Data->GetData(DataFormats::FileDrop, false);
				 for (int i = 0; i < s->Length; i++) {
#ifdef _DEBUG
					 Debug::WriteLine(s[i]);
#endif
					 inputDirList = s[i];

					 DirectoryInfo^ di = gcnew DirectoryInfo(s[i]);

					 if (di->Exists) {
						 // ディレクトリのみ追加
						 this->lb_in_dir->Items->Add(s[i]);
					 }
				 }
		}

	private:
		// ドラッグエンター
		System::Void lb_in_dir_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
		{

				if(e->Data->GetDataPresent(DataFormats::FileDrop)) {
					e->Effect = DragDropEffects::All;
				} else {
					e->Effect = DragDropEffects::None;
				}

		}

	private:
		// アイテム変更
		System::Void lb_in_dir_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
		}

	private:
		// 実行ボタン
		System::Void btn_exe_Click(System::Object^  sender, System::EventArgs^  e)
		{
				 // スレッド起動
				 bgw_exe->RunWorkerAsync();
		}

	private:
		// クリア
		System::Void btn_clear_Click(System::Object^  sender, System::EventArgs^  e)
		{
				 int i;
				 
				 // 選択された項目のみ削除
				 for (i = 0; i < lb_in_dir->SelectedIndices->Count; i++) {
					 lb_in_dir->Items->RemoveAt(lb_in_dir->SelectedIndices[i]);
				 }

				 // 全削除
				 if (i == 0) {
					 while (lb_in_dir->Items->Count > 0) {
						 lb_in_dir->Items->RemoveAt(0);
					 }
				 }
		}

	private:
		// スレッド実行処理
		System::Void backgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
		{
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
								MessageBox::Show("続けて処理しますか？", "", MessageBoxButtons::YesNo);
						 if (result != System::Windows::Forms::DialogResult::Yes) {
							 break;
						 }
					 }
#endif

					 mMain->Start(this->lb_in_dir->Items[i]->ToString(), this->cb_tab->Checked);
					 procCnt++;
				 }
				 if (procCnt > 0) {
					 MessageBox::Show("正常終了");
				 } else {

				 }
		}

	private:
		// 変更
		System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
		{
		}

	private:
		// スレッド終了
		System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
		{
		}
};
}

