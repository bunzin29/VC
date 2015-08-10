using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageDivider
{
	using CS = ImageDivider.SubForm.Constants;

	public partial class SubForm : Form
	{
		private MainForm mMainForm;
		private Ini mIni;
		private MyLog mLog;

		private Size mThumbnail;				// サムネイル画像サイズ

		public SubForm(MainForm mainForm, Ini ini, MyLog log)
		{
			InitializeComponent();

			listview_image_list.LostFocus += new EventHandler(ListView_LostFocus);

			mMainForm  = mainForm;
			mIni = ini;
			mLog = log;

			Init();

			InitWindows();

			this.ControlBox = !this.ControlBox;
		}

		public static class Constants
		{
			public const String INI_SECTIOIN_SUB = "SUB";
			// ウィンドウサイズ
			public const String INI_WINDOW_SIZE_H_KEY = "WindowH";
			public const String INI_WINDOW_SIZE_W_KEY = "WindowW";
			// ウィンドウ位置
			public const String INI_WINDOW_POS_X_KEY = "WindowPosX";
			public const String INI_WINDOW_POS_Y_KEY = "WindowPosY";
			// サムネイル画像サイズ
			public const String INI_THUMBNAIL_W_KEY = "ThumbnailW";
			public const String INI_THUMBNAIL_W_DEFAULT = "80";
			public const String INI_THUMBNAIL_H_KEY = "ThumbnailH";
			public const String INI_THUMBNAIL_H_DEFAULT = "80";
		}

		// 初期化
		private void Init()
		{
			String tnW, tnH;
			tnW = GetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_THUMBNAIL_W_KEY, CS.INI_THUMBNAIL_W_DEFAULT);
			tnH = GetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_THUMBNAIL_H_KEY, CS.INI_THUMBNAIL_H_DEFAULT);

			mThumbnail = new Size(int.Parse(tnW), int.Parse(tnH));
			imageList.ImageSize = mThumbnail;
			listview_image_list.LargeImageList = imageList;

			ColumnHeader columnName = new ColumnHeader();
			columnName.Text = "ファイル名";

			// カラム追加
			listview_image_list.Columns.Add(columnName);
			// サイズ自動調整
			listview_image_list.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
		}

		// ウィンドウ初期設定
		private void InitWindows()
		{
			String defH, defW;
			String h, w;

			// 現在のサイズ取得
			defH = this.Height.ToString();
			defW = this.Width.ToString();

			// ini設定値取得
			h = GetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_SIZE_H_KEY, defH);
			w = GetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_SIZE_W_KEY, defW);

			// 現在値とini値が異なっている場合
			if (h != defH) {
				this.Height = int.Parse(h);
			}
			if (w != defW) {
				this.Width = int.Parse(w);
			}

			String defX, defY;
			String X, Y;

			// 現在の位置取得
			defX = this.Left.ToString();
			defY = this.Top.ToString();

			// ini設定値取得
			X = GetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_POS_X_KEY, defX);
			Y = GetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_POS_Y_KEY, defY);

			// 現在値とini値が異なっている場合
			if (X != defX) {
				this.Left = int.Parse(X);
			}
			if (Y != defY) {
				this.Top = int.Parse(Y);
			}

		}


		// リストクリア
		public void ListViewClear()
		{
			listview_image_list.Items.Clear();
		}

		// リスト追加
		public void ListViewAdd(int idx, String fileNameFP, String fileName)
		{
			Bitmap bm = new Bitmap(fileNameFP);
			Image thumbnail = Util.createThumbnail(bm, mThumbnail.Width, mThumbnail.Height);

			imageList.Images.Add(thumbnail);
			ListViewItem item = new ListViewItem(fileName);
			item.ImageIndex = idx;
			listview_image_list.Items.Add(item);
		}

		// コントロール有効/無効
		public void ListViewCtrl(bool en)
		{
			listview_image_list.Enabled = en;
		}

		// リストビューのアイテム選択
		public void SelectListView(int idx)
		{
			listview_image_list.SelectedItems.Clear();
			// フォーカス
			listview_image_list.FocusedItem = listview_image_list.Items[idx];
			// 選択
			listview_image_list.Items[idx].Selected = true;
			listview_image_list.Select();
			// 指定した項目がコントロール内に表示されるようする
			listview_image_list.EnsureVisible(idx);
		}

		// リストビューのアイテムの文字色設定
		public void ListViewCol(int idx, Color col)
		{
			listview_image_list.SelectedItems[0].ForeColor = col;
		}

		// iniファイルから値を取得
		private String GetIniValue(String sec, String key, String def)
		{
			String val = mIni[sec, key];
			if (val == "") {
				// デフォルト値
				mIni[sec, key] = def;
				val = mIni[sec, key];
			}

			return val;
		}

		// iniファイルに値を設定
		private void SetIniValue(String sec, String key, String val)
		{
			mIni[sec, key] = val;
		}

		// リストビュークリック
		private void listview_image_list_Click(object sender, EventArgs e)
		{
			if (listview_image_list.SelectedItems.Count > 0) {
				int idx = listview_image_list.SelectedItems[0].Index;
				mMainForm.SetImageIdx(idx);
			}
		}

		// リストビュー変更
		private void listview_image_list_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (listview_image_list.SelectedItems.Count > 0) {
				int idx = listview_image_list.SelectedItems[0].Index;
				if (idx != mMainForm.GetShowImageIdx()) {
					mMainForm.SetImageIdx(idx);
				}
			}
		}

		// リストビューフォーカス失った
		private void ListView_LostFocus(object sender, EventArgs e)
		{
			Form f = Form.ActiveForm;
			if (f != null && f.Equals(this)) {
				listview_image_list.Focus();
			}
		}

		// キーイベント
		private void SubForm_KeyDown(object sender, KeyEventArgs e)
		{
			// キーイベント
			if (e.KeyCode == Keys.F1) {
				// 前の画像へ
				mMainForm.preImageSet();
				e.Handled = true;
			} else if (e.KeyCode == Keys.F2) {
				// 次の画像へ
				mMainForm.nextImageSet();
				e.Handled = true;
			} else if (e.KeyCode == Keys.F3) {
				// コピー
				mMainForm.copySet();
				e.Handled = true;
			}
		}

		// ウィンドウサイズ変更
		private void SubForm_SizeChanged(object sender, EventArgs e)
		{
			SetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_SIZE_H_KEY, this.Height.ToString());
			SetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_SIZE_W_KEY, this.Width.ToString());

		}

		// ウィンドウ移動終了
		private void SubForm_ResizeEnd(object sender, EventArgs e)
		{
			SetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_POS_X_KEY, this.Left.ToString());
			SetIniValue(CS.INI_SECTIOIN_SUB, CS.INI_WINDOW_POS_Y_KEY, this.Top.ToString());
		}

		// フォーム表示
		private void SubForm_Shown(object sender, EventArgs e)
		{
			WriteLog("SubForm表示");
		}

		// ログ出力
		private void WriteLog(String str)
		{
			Util.WriteLog(this, mLog, str);
		}


	}
}
