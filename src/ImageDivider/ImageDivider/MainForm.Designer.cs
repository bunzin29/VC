namespace ImageDivider
{
    partial class MainForm
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
            if (disposing && (components != null)) {
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
			this.components = new System.ComponentModel.Container();
			this.picbox_image = new System.Windows.Forms.PictureBox();
			this.txt_in = new System.Windows.Forms.TextBox();
			this.txt_out = new System.Windows.Forms.TextBox();
			this.btn_in = new System.Windows.Forms.Button();
			this.btn_out = new System.Windows.Forms.Button();
			this.btn_read = new System.Windows.Forms.Button();
			this.listview_image_list = new System.Windows.Forms.ListView();
			this.progressBar = new System.Windows.Forms.ProgressBar();
			this.btn_next = new System.Windows.Forms.Button();
			this.btn_pre = new System.Windows.Forms.Button();
			this.btn_copy = new System.Windows.Forms.Button();
			this.panel1 = new System.Windows.Forms.Panel();
			this.btn_delLog = new System.Windows.Forms.Button();
			this.imageList = new System.Windows.Forms.ImageList(this.components);
			this.radio_Details = new System.Windows.Forms.RadioButton();
			this.panel2 = new System.Windows.Forms.Panel();
			this.radio_LaggeIcon = new System.Windows.Forms.RadioButton();
			this.chkBox_sub = new System.Windows.Forms.CheckBox();
			this.worker_main = new System.ComponentModel.BackgroundWorker();
			this.txt_Pmem = new System.Windows.Forms.TextBox();
			this.txt_Vmem = new System.Windows.Forms.TextBox();
			this.lab_Pmem = new System.Windows.Forms.Label();
			this.lab_Vmem = new System.Windows.Forms.Label();
			this.panel3 = new System.Windows.Forms.Panel();
			this.radio_M = new System.Windows.Forms.RadioButton();
			this.radio_K = new System.Windows.Forms.RadioButton();
			((System.ComponentModel.ISupportInitialize)(this.picbox_image)).BeginInit();
			this.panel1.SuspendLayout();
			this.panel2.SuspendLayout();
			this.panel3.SuspendLayout();
			this.SuspendLayout();
			// 
			// picbox_image
			// 
			this.picbox_image.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.picbox_image.BackColor = System.Drawing.SystemColors.AppWorkspace;
			this.picbox_image.Location = new System.Drawing.Point(14, 73);
			this.picbox_image.Name = "picbox_image";
			this.picbox_image.Size = new System.Drawing.Size(728, 430);
			this.picbox_image.TabIndex = 0;
			this.picbox_image.TabStop = false;
			// 
			// txt_in
			// 
			this.txt_in.Location = new System.Drawing.Point(77, 16);
			this.txt_in.Name = "txt_in";
			this.txt_in.Size = new System.Drawing.Size(322, 19);
			this.txt_in.TabIndex = 1;
			this.txt_in.TextChanged += new System.EventHandler(this.txt_in_TextChanged);
			// 
			// txt_out
			// 
			this.txt_out.Location = new System.Drawing.Point(77, 46);
			this.txt_out.Name = "txt_out";
			this.txt_out.Size = new System.Drawing.Size(322, 19);
			this.txt_out.TabIndex = 2;
			this.txt_out.TextChanged += new System.EventHandler(this.txt_out_TextChanged);
			// 
			// btn_in
			// 
			this.btn_in.Location = new System.Drawing.Point(14, 12);
			this.btn_in.Name = "btn_in";
			this.btn_in.Size = new System.Drawing.Size(44, 23);
			this.btn_in.TabIndex = 3;
			this.btn_in.Text = "入力";
			this.btn_in.UseVisualStyleBackColor = true;
			this.btn_in.Click += new System.EventHandler(this.btn_in_Click);
			// 
			// btn_out
			// 
			this.btn_out.Location = new System.Drawing.Point(14, 44);
			this.btn_out.Name = "btn_out";
			this.btn_out.Size = new System.Drawing.Size(44, 23);
			this.btn_out.TabIndex = 4;
			this.btn_out.Text = "出力";
			this.btn_out.UseVisualStyleBackColor = true;
			this.btn_out.Click += new System.EventHandler(this.btn_out_Click);
			// 
			// btn_read
			// 
			this.btn_read.Location = new System.Drawing.Point(417, 16);
			this.btn_read.Name = "btn_read";
			this.btn_read.Size = new System.Drawing.Size(44, 23);
			this.btn_read.TabIndex = 5;
			this.btn_read.Text = "読込";
			this.btn_read.UseVisualStyleBackColor = true;
			this.btn_read.Click += new System.EventHandler(this.btn_read_Click);
			// 
			// listview_image_list
			// 
			this.listview_image_list.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listview_image_list.HideSelection = false;
			this.listview_image_list.Location = new System.Drawing.Point(757, 73);
			this.listview_image_list.Name = "listview_image_list";
			this.listview_image_list.Size = new System.Drawing.Size(174, 493);
			this.listview_image_list.TabIndex = 6;
			this.listview_image_list.UseCompatibleStateImageBehavior = false;
			this.listview_image_list.SelectedIndexChanged += new System.EventHandler(this.listview_image_list_SelectedIndexChanged);
			this.listview_image_list.Click += new System.EventHandler(this.listview_image_list_Click);
			// 
			// progressBar
			// 
			this.progressBar.Location = new System.Drawing.Point(501, 16);
			this.progressBar.Name = "progressBar";
			this.progressBar.Size = new System.Drawing.Size(166, 23);
			this.progressBar.TabIndex = 10;
			// 
			// btn_next
			// 
			this.btn_next.Anchor = System.Windows.Forms.AnchorStyles.Left;
			this.btn_next.Font = new System.Drawing.Font("MS UI Gothic", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.btn_next.Location = new System.Drawing.Point(124, 0);
			this.btn_next.Name = "btn_next";
			this.btn_next.Size = new System.Drawing.Size(99, 64);
			this.btn_next.TabIndex = 8;
			this.btn_next.Text = "次へ [F2]";
			this.btn_next.UseVisualStyleBackColor = true;
			this.btn_next.Click += new System.EventHandler(this.btn_next_Click);
			// 
			// btn_pre
			// 
			this.btn_pre.Anchor = System.Windows.Forms.AnchorStyles.Left;
			this.btn_pre.Font = new System.Drawing.Font("MS UI Gothic", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.btn_pre.Location = new System.Drawing.Point(0, 0);
			this.btn_pre.Name = "btn_pre";
			this.btn_pre.Size = new System.Drawing.Size(99, 64);
			this.btn_pre.TabIndex = 7;
			this.btn_pre.Text = "前へ [F1]";
			this.btn_pre.UseVisualStyleBackColor = true;
			this.btn_pre.Click += new System.EventHandler(this.btn_pre_Click);
			// 
			// btn_copy
			// 
			this.btn_copy.Anchor = System.Windows.Forms.AnchorStyles.Left;
			this.btn_copy.Font = new System.Drawing.Font("MS UI Gothic", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.btn_copy.Location = new System.Drawing.Point(252, 0);
			this.btn_copy.Name = "btn_copy";
			this.btn_copy.Size = new System.Drawing.Size(99, 64);
			this.btn_copy.TabIndex = 11;
			this.btn_copy.Text = "コピー [F3]";
			this.btn_copy.UseVisualStyleBackColor = true;
			this.btn_copy.Click += new System.EventHandler(this.btn_copy_Click);
			// 
			// panel1
			// 
			this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.panel1.Controls.Add(this.panel3);
			this.panel1.Controls.Add(this.lab_Vmem);
			this.panel1.Controls.Add(this.lab_Pmem);
			this.panel1.Controls.Add(this.txt_Vmem);
			this.panel1.Controls.Add(this.txt_Pmem);
			this.panel1.Controls.Add(this.btn_delLog);
			this.panel1.Controls.Add(this.btn_copy);
			this.panel1.Controls.Add(this.btn_pre);
			this.panel1.Controls.Add(this.btn_next);
			this.panel1.Location = new System.Drawing.Point(14, 509);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(728, 64);
			this.panel1.TabIndex = 13;
			// 
			// btn_delLog
			// 
			this.btn_delLog.Location = new System.Drawing.Point(382, 24);
			this.btn_delLog.Name = "btn_delLog";
			this.btn_delLog.Size = new System.Drawing.Size(75, 23);
			this.btn_delLog.TabIndex = 12;
			this.btn_delLog.Text = "ログ削除";
			this.btn_delLog.UseVisualStyleBackColor = true;
			this.btn_delLog.Click += new System.EventHandler(this.btn_delLog_Click);
			// 
			// imageList
			// 
			this.imageList.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
			this.imageList.ImageSize = new System.Drawing.Size(16, 16);
			this.imageList.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// radio_Details
			// 
			this.radio_Details.AutoSize = true;
			this.radio_Details.Checked = true;
			this.radio_Details.Location = new System.Drawing.Point(8, 9);
			this.radio_Details.Name = "radio_Details";
			this.radio_Details.Size = new System.Drawing.Size(42, 16);
			this.radio_Details.TabIndex = 14;
			this.radio_Details.TabStop = true;
			this.radio_Details.Text = "List";
			this.radio_Details.UseVisualStyleBackColor = true;
			this.radio_Details.CheckedChanged += new System.EventHandler(this.radio_Details_CheckedChanged);
			// 
			// panel2
			// 
			this.panel2.Controls.Add(this.radio_LaggeIcon);
			this.panel2.Controls.Add(this.radio_Details);
			this.panel2.Location = new System.Drawing.Point(685, 12);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(84, 55);
			this.panel2.TabIndex = 15;
			// 
			// radio_LaggeIcon
			// 
			this.radio_LaggeIcon.AutoSize = true;
			this.radio_LaggeIcon.Location = new System.Drawing.Point(8, 31);
			this.radio_LaggeIcon.Name = "radio_LaggeIcon";
			this.radio_LaggeIcon.Size = new System.Drawing.Size(44, 16);
			this.radio_LaggeIcon.TabIndex = 15;
			this.radio_LaggeIcon.Text = "Icon";
			this.radio_LaggeIcon.UseVisualStyleBackColor = true;
			this.radio_LaggeIcon.CheckedChanged += new System.EventHandler(this.radio_LaggeIcon_CheckedChanged);
			// 
			// chkBox_sub
			// 
			this.chkBox_sub.AutoSize = true;
			this.chkBox_sub.Location = new System.Drawing.Point(785, 22);
			this.chkBox_sub.Name = "chkBox_sub";
			this.chkBox_sub.Size = new System.Drawing.Size(81, 16);
			this.chkBox_sub.TabIndex = 16;
			this.chkBox_sub.Text = "SubWindow";
			this.chkBox_sub.UseVisualStyleBackColor = true;
			this.chkBox_sub.CheckedChanged += new System.EventHandler(this.chkBox_sub_CheckedChanged);
			// 
			// worker_main
			// 
			this.worker_main.WorkerReportsProgress = true;
			this.worker_main.WorkerSupportsCancellation = true;
			this.worker_main.DoWork += new System.ComponentModel.DoWorkEventHandler(this.worker_main_DoWork);
			this.worker_main.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.worker_main_ProgressChanged);
			this.worker_main.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.worker_main_RunWorkerCompleted);
			// 
			// txt_Pmem
			// 
			this.txt_Pmem.Location = new System.Drawing.Point(567, 13);
			this.txt_Pmem.Name = "txt_Pmem";
			this.txt_Pmem.ReadOnly = true;
			this.txt_Pmem.Size = new System.Drawing.Size(69, 19);
			this.txt_Pmem.TabIndex = 13;
			this.txt_Pmem.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			// 
			// txt_Vmem
			// 
			this.txt_Vmem.Location = new System.Drawing.Point(567, 38);
			this.txt_Vmem.Name = "txt_Vmem";
			this.txt_Vmem.ReadOnly = true;
			this.txt_Vmem.Size = new System.Drawing.Size(69, 19);
			this.txt_Vmem.TabIndex = 14;
			this.txt_Vmem.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			// 
			// lab_Pmem
			// 
			this.lab_Pmem.AutoSize = true;
			this.lab_Pmem.Location = new System.Drawing.Point(510, 17);
			this.lab_Pmem.Name = "lab_Pmem";
			this.lab_Pmem.Size = new System.Drawing.Size(53, 12);
			this.lab_Pmem.TabIndex = 15;
			this.lab_Pmem.Text = "物理メモリ";
			// 
			// lab_Vmem
			// 
			this.lab_Vmem.AutoSize = true;
			this.lab_Vmem.Location = new System.Drawing.Point(510, 41);
			this.lab_Vmem.Name = "lab_Vmem";
			this.lab_Vmem.Size = new System.Drawing.Size(53, 12);
			this.lab_Vmem.TabIndex = 16;
			this.lab_Vmem.Text = "仮想メモリ";
			// 
			// panel3
			// 
			this.panel3.Controls.Add(this.radio_M);
			this.panel3.Controls.Add(this.radio_K);
			this.panel3.Location = new System.Drawing.Point(641, 6);
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size(84, 55);
			this.panel3.TabIndex = 17;
			// 
			// radio_M
			// 
			this.radio_M.AutoSize = true;
			this.radio_M.Location = new System.Drawing.Point(8, 31);
			this.radio_M.Name = "radio_M";
			this.radio_M.Size = new System.Drawing.Size(54, 16);
			this.radio_M.TabIndex = 15;
			this.radio_M.Text = "Mbyte";
			this.radio_M.UseVisualStyleBackColor = true;
			this.radio_M.CheckedChanged += new System.EventHandler(this.radio_M_CheckedChanged);
			// 
			// radio_K
			// 
			this.radio_K.AutoSize = true;
			this.radio_K.Checked = true;
			this.radio_K.Location = new System.Drawing.Point(8, 9);
			this.radio_K.Name = "radio_K";
			this.radio_K.Size = new System.Drawing.Size(52, 16);
			this.radio_K.TabIndex = 14;
			this.radio_K.TabStop = true;
			this.radio_K.Text = "Kbyte";
			this.radio_K.UseVisualStyleBackColor = true;
			this.radio_K.CheckedChanged += new System.EventHandler(this.radio_K_CheckedChanged);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoScroll = true;
			this.ClientSize = new System.Drawing.Size(947, 578);
			this.Controls.Add(this.chkBox_sub);
			this.Controls.Add(this.panel2);
			this.Controls.Add(this.panel1);
			this.Controls.Add(this.progressBar);
			this.Controls.Add(this.listview_image_list);
			this.Controls.Add(this.btn_read);
			this.Controls.Add(this.btn_out);
			this.Controls.Add(this.btn_in);
			this.Controls.Add(this.txt_out);
			this.Controls.Add(this.txt_in);
			this.Controls.Add(this.picbox_image);
			this.KeyPreview = true;
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "ImageDivider";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.Shown += new System.EventHandler(this.MainForm_Shown);
			this.ResizeEnd += new System.EventHandler(this.MainForm_ResizeEnd);
			this.SizeChanged += new System.EventHandler(this.MainForm_SizeChanged);
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainForm_KeyDown);
			((System.ComponentModel.ISupportInitialize)(this.picbox_image)).EndInit();
			this.panel1.ResumeLayout(false);
			this.panel1.PerformLayout();
			this.panel2.ResumeLayout(false);
			this.panel2.PerformLayout();
			this.panel3.ResumeLayout(false);
			this.panel3.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox picbox_image;
        private System.Windows.Forms.TextBox txt_in;
        private System.Windows.Forms.TextBox txt_out;
        private System.Windows.Forms.Button btn_in;
        private System.Windows.Forms.Button btn_out;
        private System.Windows.Forms.Button btn_read;
		private System.Windows.Forms.ListView listview_image_list;
		private System.Windows.Forms.ProgressBar progressBar;
		private System.Windows.Forms.Button btn_next;
		private System.Windows.Forms.Button btn_pre;
		private System.Windows.Forms.Button btn_copy;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.ImageList imageList;
		private System.Windows.Forms.RadioButton radio_Details;
		private System.Windows.Forms.Panel panel2;
		private System.Windows.Forms.RadioButton radio_LaggeIcon;
		private System.Windows.Forms.CheckBox chkBox_sub;
		private System.Windows.Forms.Button btn_delLog;
		private System.ComponentModel.BackgroundWorker worker_main;
		private System.Windows.Forms.TextBox txt_Pmem;
		private System.Windows.Forms.Label lab_Vmem;
		private System.Windows.Forms.Label lab_Pmem;
		private System.Windows.Forms.TextBox txt_Vmem;
		private System.Windows.Forms.Panel panel3;
		private System.Windows.Forms.RadioButton radio_M;
		private System.Windows.Forms.RadioButton radio_K;
    }
}

