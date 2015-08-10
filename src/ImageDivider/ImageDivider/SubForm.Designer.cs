namespace ImageDivider
{
	partial class SubForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.listview_image_list = new System.Windows.Forms.ListView();
			this.imageList = new System.Windows.Forms.ImageList(this.components);
			this.SuspendLayout();
			// 
			// listview_image_list
			// 
			this.listview_image_list.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listview_image_list.HideSelection = false;
			this.listview_image_list.Location = new System.Drawing.Point(12, 14);
			this.listview_image_list.Name = "listview_image_list";
			this.listview_image_list.Size = new System.Drawing.Size(504, 455);
			this.listview_image_list.TabIndex = 7;
			this.listview_image_list.UseCompatibleStateImageBehavior = false;
			this.listview_image_list.SelectedIndexChanged += new System.EventHandler(this.listview_image_list_SelectedIndexChanged);
			this.listview_image_list.Click += new System.EventHandler(this.listview_image_list_Click);
			// 
			// imageList
			// 
			this.imageList.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
			this.imageList.ImageSize = new System.Drawing.Size(16, 16);
			this.imageList.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// SubForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(528, 481);
			this.Controls.Add(this.listview_image_list);
			this.KeyPreview = true;
			this.Name = "SubForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "SubForm";
			this.Shown += new System.EventHandler(this.SubForm_Shown);
			this.ResizeEnd += new System.EventHandler(this.SubForm_ResizeEnd);
			this.SizeChanged += new System.EventHandler(this.SubForm_SizeChanged);
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.SubForm_KeyDown);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ListView listview_image_list;
		private System.Windows.Forms.ImageList imageList;
	}
}