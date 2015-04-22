namespace FileAnalyzer
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_dir = new System.Windows.Forms.Button();
            this.btn_file = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.File = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Size = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Page = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.btn_clr = new System.Windows.Forms.Button();
            this.txt_dir = new System.Windows.Forms.TextBox();
            this.btn_exe = new System.Windows.Forms.Button();
            this.chk_subdir = new System.Windows.Forms.CheckBox();
            this.chk_filter = new System.Windows.Forms.CheckBox();
            this.txt_filter = new System.Windows.Forms.TextBox();
            this.btn_csv = new System.Windows.Forms.Button();
            this.txt_all_size = new System.Windows.Forms.TextBox();
            this.txt_all_page = new System.Windows.Forms.TextBox();
            this.lab_all_size = new System.Windows.Forms.Label();
            this.lab_all_page = new System.Windows.Forms.Label();
            this.comb_all_size = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_dir
            // 
            this.btn_dir.Location = new System.Drawing.Point(613, 8);
            this.btn_dir.Name = "btn_dir";
            this.btn_dir.Size = new System.Drawing.Size(49, 23);
            this.btn_dir.TabIndex = 1;
            this.btn_dir.Text = "フォルダ";
            this.btn_dir.UseVisualStyleBackColor = true;
            this.btn_dir.Click += new System.EventHandler(this.btn_dir_Click);
            // 
            // btn_file
            // 
            this.btn_file.Location = new System.Drawing.Point(12, 303);
            this.btn_file.Name = "btn_file";
            this.btn_file.Size = new System.Drawing.Size(75, 23);
            this.btn_file.TabIndex = 2;
            this.btn_file.Text = "ファイル";
            this.btn_file.UseVisualStyleBackColor = true;
            this.btn_file.Click += new System.EventHandler(this.btn_file_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.File,
            this.Size,
            this.Page});
            this.dataGridView1.Location = new System.Drawing.Point(12, 37);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.RowHeadersVisible = false;
            this.dataGridView1.RowTemplate.Height = 21;
            this.dataGridView1.Size = new System.Drawing.Size(871, 185);
            this.dataGridView1.TabIndex = 3;
            // 
            // File
            // 
            this.File.FillWeight = 133.2271F;
            this.File.HeaderText = "ファイル";
            this.File.Name = "File";
            this.File.ReadOnly = true;
            // 
            // Size
            // 
            this.Size.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.Size.HeaderText = "サイズ";
            this.Size.Name = "Size";
            this.Size.ReadOnly = true;
            // 
            // Page
            // 
            this.Page.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.Page.HeaderText = "ページ";
            this.Page.Name = "Page";
            this.Page.ReadOnly = true;
            // 
            // btn_clr
            // 
            this.btn_clr.Location = new System.Drawing.Point(808, 8);
            this.btn_clr.Name = "btn_clr";
            this.btn_clr.Size = new System.Drawing.Size(75, 23);
            this.btn_clr.TabIndex = 4;
            this.btn_clr.Text = "クリア";
            this.btn_clr.UseVisualStyleBackColor = true;
            this.btn_clr.Click += new System.EventHandler(this.btn_clr_Click);
            // 
            // txt_dir
            // 
            this.txt_dir.Location = new System.Drawing.Point(105, 10);
            this.txt_dir.Name = "txt_dir";
            this.txt_dir.Size = new System.Drawing.Size(502, 19);
            this.txt_dir.TabIndex = 5;
            // 
            // btn_exe
            // 
            this.btn_exe.Location = new System.Drawing.Point(13, 8);
            this.btn_exe.Name = "btn_exe";
            this.btn_exe.Size = new System.Drawing.Size(75, 23);
            this.btn_exe.TabIndex = 6;
            this.btn_exe.Text = "実行";
            this.btn_exe.UseVisualStyleBackColor = true;
            this.btn_exe.Click += new System.EventHandler(this.btn_exe_Click);
            // 
            // chk_subdir
            // 
            this.chk_subdir.AutoSize = true;
            this.chk_subdir.Checked = true;
            this.chk_subdir.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chk_subdir.Location = new System.Drawing.Point(12, 241);
            this.chk_subdir.Name = "chk_subdir";
            this.chk_subdir.Size = new System.Drawing.Size(92, 16);
            this.chk_subdir.TabIndex = 7;
            this.chk_subdir.Text = "サブディレクトリ";
            this.chk_subdir.UseVisualStyleBackColor = true;
            // 
            // chk_filter
            // 
            this.chk_filter.AutoSize = true;
            this.chk_filter.Location = new System.Drawing.Point(12, 263);
            this.chk_filter.Name = "chk_filter";
            this.chk_filter.Size = new System.Drawing.Size(57, 16);
            this.chk_filter.TabIndex = 8;
            this.chk_filter.Text = "フィルタ";
            this.chk_filter.UseVisualStyleBackColor = true;
            this.chk_filter.CheckedChanged += new System.EventHandler(this.chk_filter_CheckedChanged);
            // 
            // txt_filter
            // 
            this.txt_filter.Enabled = false;
            this.txt_filter.Location = new System.Drawing.Point(105, 263);
            this.txt_filter.Name = "txt_filter";
            this.txt_filter.Size = new System.Drawing.Size(296, 19);
            this.txt_filter.TabIndex = 9;
            // 
            // btn_csv
            // 
            this.btn_csv.Location = new System.Drawing.Point(727, 8);
            this.btn_csv.Name = "btn_csv";
            this.btn_csv.Size = new System.Drawing.Size(75, 23);
            this.btn_csv.TabIndex = 10;
            this.btn_csv.Text = "CSV出力";
            this.btn_csv.UseVisualStyleBackColor = true;
            this.btn_csv.Click += new System.EventHandler(this.btn_csv_Click);
            // 
            // txt_all_size
            // 
            this.txt_all_size.Location = new System.Drawing.Point(691, 241);
            this.txt_all_size.Name = "txt_all_size";
            this.txt_all_size.Size = new System.Drawing.Size(100, 19);
            this.txt_all_size.TabIndex = 11;
            // 
            // txt_all_page
            // 
            this.txt_all_page.Location = new System.Drawing.Point(691, 266);
            this.txt_all_page.Name = "txt_all_page";
            this.txt_all_page.Size = new System.Drawing.Size(100, 19);
            this.txt_all_page.TabIndex = 12;
            // 
            // lab_all_size
            // 
            this.lab_all_size.AutoSize = true;
            this.lab_all_size.Location = new System.Drawing.Point(633, 244);
            this.lab_all_size.Name = "lab_all_size";
            this.lab_all_size.Size = new System.Drawing.Size(52, 12);
            this.lab_all_size.TabIndex = 13;
            this.lab_all_size.Text = "全サイズ：";
            // 
            // lab_all_page
            // 
            this.lab_all_page.AutoSize = true;
            this.lab_all_page.Location = new System.Drawing.Point(633, 269);
            this.lab_all_page.Name = "lab_all_page";
            this.lab_all_page.Size = new System.Drawing.Size(53, 12);
            this.lab_all_page.TabIndex = 14;
            this.lab_all_page.Text = "全ページ：";
            // 
            // comb_all_size
            // 
            this.comb_all_size.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comb_all_size.FormattingEnabled = true;
            this.comb_all_size.Location = new System.Drawing.Point(797, 240);
            this.comb_all_size.Name = "comb_all_size";
            this.comb_all_size.Size = new System.Drawing.Size(51, 20);
            this.comb_all_size.TabIndex = 15;
            this.comb_all_size.SelectedIndexChanged += new System.EventHandler(this.comb_all_size_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(895, 404);
            this.Controls.Add(this.comb_all_size);
            this.Controls.Add(this.lab_all_page);
            this.Controls.Add(this.lab_all_size);
            this.Controls.Add(this.txt_all_page);
            this.Controls.Add(this.txt_all_size);
            this.Controls.Add(this.btn_csv);
            this.Controls.Add(this.txt_filter);
            this.Controls.Add(this.chk_filter);
            this.Controls.Add(this.chk_subdir);
            this.Controls.Add(this.btn_exe);
            this.Controls.Add(this.txt_dir);
            this.Controls.Add(this.btn_clr);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.btn_file);
            this.Controls.Add(this.btn_dir);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_dir;
        private System.Windows.Forms.Button btn_file;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn File;
        private System.Windows.Forms.DataGridViewTextBoxColumn Size;
        private System.Windows.Forms.DataGridViewTextBoxColumn Page;
        private System.Windows.Forms.Button btn_clr;
        private System.Windows.Forms.TextBox txt_dir;
        private System.Windows.Forms.Button btn_exe;
        private System.Windows.Forms.CheckBox chk_subdir;
        private System.Windows.Forms.CheckBox chk_filter;
        private System.Windows.Forms.TextBox txt_filter;
        private System.Windows.Forms.Button btn_csv;
        private System.Windows.Forms.TextBox txt_all_size;
        private System.Windows.Forms.TextBox txt_all_page;
        private System.Windows.Forms.Label lab_all_size;
        private System.Windows.Forms.Label lab_all_page;
        private System.Windows.Forms.ComboBox comb_all_size;
    }
}

