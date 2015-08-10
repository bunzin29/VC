using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Collections;

using Microsoft.WindowsAPICodePack;
using Microsoft.WindowsAPICodePack.Dialogs;
using Microsoft.WindowsAPICodePack.Dialogs.Controls;


namespace ImageDivider
{
	using CS = ImageDivider.MainForm.Constants;

	public partial class MainForm : Form
	{
		private ArrayList mImageList;			// 画像リスト(フルパス)
		private ArrayList mFileNameList;		// 画像ファイル名リスト
		private int mShowIdx;					// 表示中の画像インデックス
		private int mImageNum;					// 画像ファイル数
		private Size mThumbnail;				// サムネイル画像サイズ
		private WorkerClass mWc;				// ワーカークラス

		private Ini mIni;						// iniファイルクラス
		// 設定プロパティ
		private String mIniListView;			// リストビューの表示形式

		// 画像表示関連
		private Bitmap[] mImageOut;				// 出力画像
		private String[] mImageOutFileName;		// 出力画像ファイル名
		private int mImageOutMax;				// 最大バッファ
		private int mImageOutIdx;				// インデックス位置

		// サブフォーム
		private bool mSubFormEnable = true;
		private SubForm mSubForm;

		// ログ
		private MyLog mLog;

		// メモリ表示単位
		private String mMemUnit;

		// ミューテックス
		private static Mutex mxListView = new Mutex();

		// デリゲート
		delegate void DelegateSetController(bool en);
		delegate bool DelegateShowImage(int idx);
		delegate void DelegateSelectListView(int idx);

		// コンストラクタ
		public MainForm()
		{
			InitializeComponent();


			InitFile();			// iniファイル初期化
			InitLog();			// ログファイル初期化

			WriteLog("---------------------------- START  ----------------------------");

			InitThread();		// スレッド初期設定

			InitWindows();		// ウィンドウ初期設定
			InitPicBox();		// ピクチャーボックス初期設定
			InitListView();		// リストビュー形式設定
			InitDir();			// 入力、出力ディレクトリ初期設定

			InitMemory();		// メモリ関連

			initImage();		// 画像表示初期設定
			mImageNum = 0;		// 画像ファイル数初期化
		}

		// 永続スレッド設定
		private void InitThread()
		{
			// メモリ表示単位初期化
			String mUnit = GetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_MEM_UNIT_KEY, CS.INI_MEM_UNIT_DEFAULT);
			while (true) {
				if (mUnit == CS.INI_MEM_UNIT_K) {
					radio_K.Checked = true;
					radio_M.Checked = false;
					break;
				} else if (mUnit == CS.INI_MEM_UNIT_M) {
					radio_K.Checked = false;
					radio_M.Checked = true;
					break;
				} else {
					SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_MEM_UNIT_KEY, CS.INI_MEM_UNIT_DEFAULT);
					mUnit = CS.INI_MEM_UNIT_DEFAULT;
				}
			}
			mMemUnit = mUnit;

			worker_main.RunWorkerAsync();
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
			h = GetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_SIZE_H_KEY, defH);
			w = GetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_SIZE_W_KEY, defW);

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
			X = GetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_POS_X_KEY, defX);
			Y = GetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_POS_Y_KEY, defY);

			// 現在値とini値が異なっている場合
			if (X != defX) {
				this.Left = int.Parse(X);
			}
			if (Y != defY) {
				this.Top = int.Parse(Y);
			}

		}

		// ピクチャーボックス初期設定
		private void InitPicBox()
		{
			// ズーム：サイズ比率を維持したまま表示
			picbox_image.SizeMode = PictureBoxSizeMode.Zoom;
		}

		// リストビュー形式設定
		private void InitListView()
		{
			// 表示形式取得
			mIniListView = GetIniValue(CS.INI_SECTIOIN_SYSTEM,
				CS.INI_LIST_VIEW_TYPE_KEY, CS.INI_LIST_VIEW_TYPE_DEFAULT);
			if (mIniListView == CS.INI_LIST_VIEW_TYPE_DETAILS) {
				radio_Details.Checked = true;
				radio_LaggeIcon.Checked = false;
			} else if (mIniListView == CS.INI_LIST_VIEW_TYPE_ICON) {
				radio_Details.Checked = false;
				radio_LaggeIcon.Checked = true;
			} else {
				mIniListView = CS.INI_LIST_VIEW_TYPE_DEFAULT;
				if (mIniListView == CS.INI_LIST_VIEW_TYPE_DETAILS) {
					radio_Details.Checked = true;
					radio_LaggeIcon.Checked = false;
				} else if (mIniListView == CS.INI_LIST_VIEW_TYPE_ICON) {
					radio_Details.Checked = false;
					radio_LaggeIcon.Checked = true;
				}
			}

			if (radio_Details.Checked) {
				ListViewDetails();
			} else if (radio_LaggeIcon.Checked) {
				ListViewLaggeIcon();
			} else {
				// デフォルト
				radio_Details.Checked = true;
				ListViewDetails();
			}

			// サムネイル画像サイズ
			String tnW, tnH;
			tnW = GetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_THUMBNAIL_W_KEY, CS.INI_THUMBNAIL_W_DEFAULT);
			tnH = GetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_THUMBNAIL_H_KEY, CS.INI_THUMBNAIL_H_DEFAULT);

			mThumbnail = new Size(int.Parse(tnW), int.Parse(tnH));
			imageList.ImageSize = mThumbnail;
			listview_image_list.LargeImageList = imageList;

			ColumnHeader columnName = new ColumnHeader();
			columnName.Text = "ファイル名";

			// カラム追加
			listview_image_list.Columns.Add(columnName);
			// サイズ自動調整
			listview_image_list.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);

#if DEBUG
			// デバッグ用
			txt_in.Text = "E:\\VC_TEST\\ImageDivider\\drawable";
			//txt_in.Text = "E:\\down\\2015年";
			txt_out.Text = "E:\\tmp";
#endif
		}

		// 入力、出力ディレクトリ初期設定
		private void InitDir()
		{
			String inDir, outDir;

			inDir = GetIniValue(CS.INI_SECTIOIN_SYSTEM,
				CS.INI_IN_DIR_KEY, CS.INI_IN_DIR_DEFAULT);
			if (inDir != CS.INI_IN_DIR_DEFAULT) {
				txt_in.Text = inDir;
			}

			outDir = GetIniValue(CS.INI_SECTIOIN_SYSTEM,
				CS.INI_OUT_DIR_KEY, CS.INI_OUT_DIR_DEFAULT);
			if (outDir != CS.INI_OUT_DIR_DEFAULT) {
				txt_out.Text = outDir;
			}
		}

		// サブフォーム初期設定
		private void initSubForm()
		{
			mSubForm = new SubForm(this, mIni, mLog);

			String sub;
			sub = GetIniValue(CS.INI_SECTIOIN_SYSTEM,
				CS.INI_SUB_WINDOWS_KEY, chkBox_sub.Checked.ToString());

			mSubForm.ShowInTaskbar = false;
			if (sub == "True") {
				mSubForm.Show();
				chkBox_sub.Checked = true;
				this.Focus();
			} else {
				chkBox_sub.Checked = false;
			}
		}

		// 画像表示初期設定
		private void initImage()
		{
			mImageOutMax = 3;
			mImageOut = new Bitmap[mImageOutMax];
			mImageOutFileName = new String[mImageOutMax];
			mImageOutIdx = 0;
		}

		// 固定値(文字列)定義クラス
		public static class Constants
		{
			// --- セクション ---
			// システム
			public const String INI_SECTIOIN_SYSTEM = "SYSTEM";

			// --- キー ---
			// ウィンドウサイズ
			public const String INI_WINDOW_SIZE_H_KEY = "WindowH";
			public const String INI_WINDOW_SIZE_W_KEY = "WindowW";
			// ウィンドウ位置
			public const String INI_WINDOW_POS_X_KEY = "WindowPosX";
			public const String INI_WINDOW_POS_Y_KEY = "WindowPosY";
			// リストビュー表示形式
			public const String INI_LIST_VIEW_TYPE_KEY = "ViewType";
			public const String INI_LIST_VIEW_TYPE_DEFAULT = INI_LIST_VIEW_TYPE_DETAILS;
			public const String INI_LIST_VIEW_TYPE_DETAILS = "details";
			public const String INI_LIST_VIEW_TYPE_ICON = "icon";
			// 入力ディレクトリ
			public const String INI_IN_DIR_KEY = "InDirectory";
			public const String INI_IN_DIR_DEFAULT = "";
			// 出力ディレクトリ
			public const String INI_OUT_DIR_KEY = "OutDirectory";
			public const String INI_OUT_DIR_DEFAULT = "";
			// サムネイル画像サイズ
			public const String INI_THUMBNAIL_W_KEY = "ThumbnailW";
			public const String INI_THUMBNAIL_W_DEFAULT = "80";
			public const String INI_THUMBNAIL_H_KEY = "ThumbnailH";
			public const String INI_THUMBNAIL_H_DEFAULT = "80";
			// メモリ表示
			public const String INI_MEM_UNIT_KEY = "MemoryUnit";
			public const String INI_MEM_UNIT_DEFAULT = INI_MEM_UNIT_K;
			public const String INI_MEM_UNIT_K = "Kbyte";
			public const String INI_MEM_UNIT_M = "Mbyte";
			// サブウィンドウ
			public const String INI_SUB_WINDOWS_KEY = "SubWindows";
		}

		// iniファイル
		private bool InitFile()
		{
			bool ret = true;

			String path = System.Reflection.Assembly.GetExecutingAssembly().Location;
			String iniFile = "./" + Path.GetFileNameWithoutExtension(path) + ".ini";

			mIni = new Ini(iniFile);

			return ret;
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

		// ログファイル
		private bool InitLog()
		{
			bool ret = true;

			String path = System.Reflection.Assembly.GetExecutingAssembly().Location;
			String logFile = "./" + Path.GetFileNameWithoutExtension(path) + ".log";

			mLog = new MyLog(logFile);

			return ret;
		}

		// ログ出力
		private void WriteLogEx(String str)
		{
			Util.WriteLog(this, mLog, str);
		}
		private void WriteLog(String str)
		{
			mLog.Write(str);
		}

		// メモリ関連出力
		private void InitMemory()
		{
			Microsoft.VisualBasic.Devices.ComputerInfo info =
				new Microsoft.VisualBasic.Devices.ComputerInfo();
#if DEBUG
			//合計物理メモリ
			Console.WriteLine("合計物理メモリ    : {0:#,0}Mバイト", info.TotalPhysicalMemory / 1000000);
			//利用可能な物理メモリ
			Console.WriteLine("利用可能物理メモリ: {0:#,0}Mバイト", info.AvailablePhysicalMemory / 1000000);
			//合計仮想メモリ
			Console.WriteLine("合計仮想メモリ    : {0:#,0}Mバイト", info.TotalVirtualMemory / 1000000);
			//利用可能な仮想メモリ
			Console.WriteLine("利用可能仮想メモリ: {0:#,0}Mバイト", info.AvailableVirtualMemory / 1000000);
#else
			//合計物理メモリ
			mLog.Write(String.Format("合計物理メモリ     :{0:#,0}Mバイト", info.TotalPhysicalMemory / 1000000));
			//利用可能な物理メモリ
			mLog.Write(String.Format("利用可能物理メモリ :{0:#,0}Mバイト", info.AvailablePhysicalMemory / 1000000));
			//合計仮想メモリ
			mLog.Write(String.Format("合計仮想メモリ     :{0:#,0}Mバイト", info.TotalVirtualMemory / 1000000));
			//利用可能な仮想メモリ
			mLog.Write(String.Format("利用可能仮想メモリ :{0:#,0}Mバイト", info.AvailableVirtualMemory / 1000000));
#endif
		}


		// --------------------
		// コントロールイベント
		// --------------------

		// フォーム表示
		private void MainForm_Shown(object sender, EventArgs e)
		{
			WriteLogEx("MainForm表示");

			if (mSubFormEnable) {
				initSubForm();	// サブフォーム
			}
		}

		// メインウィンドウサイズ変更
		private void MainForm_SizeChanged(object sender, EventArgs e)
		{
			SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_SIZE_H_KEY, this.Height.ToString());
			SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_SIZE_W_KEY, this.Width.ToString());
		}

		// メインウィンドウ移動終了
		private void MainForm_ResizeEnd(object sender, EventArgs e)
		{
			SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_POS_X_KEY, this.Left.ToString());
			SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_WINDOW_POS_Y_KEY, this.Top.ToString());
		}

		// 読み込みボタン
		private void btn_read_Click(object sender, EventArgs e)
		{
			// 読込みイベント
			ReadDirImage();
		}

		// 前へボタン
		private void btn_pre_Click(object sender, EventArgs e)
		{
			preImage();
		}

		// 次へボタン
		private void btn_next_Click(object sender, EventArgs e)
		{
			nextImage();
		}

		// 入力ディレクトリ選択ボタン
		private void btn_in_Click(object sender, EventArgs e)
		{
			SetDir(ref txt_in);
		}

		// 出力ディレクトリ選択ボタン
		private void btn_out_Click(object sender, EventArgs e)
		{
			SetDir(ref txt_out);
		}

		// コピーボタン
		private void btn_copy_Click(object sender, EventArgs e)
		{
			Evt_CopyImage();
		}

		// 表示形式変更ラジオボタン(Details)
		private void radio_Details_CheckedChanged(object sender, EventArgs e)
		{
			if (radio_Details.Checked) {
				ListViewDetails();
				SetIniValue(CS.INI_SECTIOIN_SYSTEM,
				CS.INI_LIST_VIEW_TYPE_KEY, CS.INI_LIST_VIEW_TYPE_DETAILS);
			}
		}

		// 表示形式変更ラジオボタン(LaggeIcon)
		private void radio_LaggeIcon_CheckedChanged(object sender, EventArgs e)
		{
			if (radio_LaggeIcon.Checked) {
				ListViewLaggeIcon();
				SetIniValue(CS.INI_SECTIOIN_SYSTEM,
					CS.INI_LIST_VIEW_TYPE_KEY, CS.INI_LIST_VIEW_TYPE_ICON);
			}
		}

		// メモリ表示形式変更ラジオボタン(K)
		private void radio_K_CheckedChanged(object sender, EventArgs e)
		{
			if (radio_K.Checked) {
				SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_MEM_UNIT_KEY, CS.INI_MEM_UNIT_K);
				mMemUnit = CS.INI_MEM_UNIT_K;
			}
		}

		// メモリ表示形式変更ラジオボタン(M)
		private void radio_M_CheckedChanged(object sender, EventArgs e)
		{
			if (radio_M.Checked) {
				SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_MEM_UNIT_KEY, CS.INI_MEM_UNIT_M);
				mMemUnit = CS.INI_MEM_UNIT_M;
			}
		}

		// ログ削除ボタン
		private void btn_delLog_Click(object sender, EventArgs e)
		{
			if (mLog != null) {
				mLog.Delete();
			}
		}

		// iniファイルを開く
		private void btn_openini_Click(object sender, EventArgs e)
		{
			String path = System.Reflection.Assembly.GetExecutingAssembly().Location;
			System.Diagnostics.Process p = System.Diagnostics.Process.Start(
				Path.GetFileNameWithoutExtension(path) + ".ini");
		}


		// キーイベント
		private void MainForm_KeyDown(object sender, KeyEventArgs e)
		{
			// キーイベント
			if (e.KeyCode == Keys.F1) {
				// 前の画像へ
				preImage();
				e.Handled = true;
			} else if (e.KeyCode == Keys.F2) {
				// 次の画像へ
				nextImage();
				e.Handled = true;
			} else if (e.KeyCode == Keys.F3) {
				// コピー
				Evt_CopyImage();
				e.Handled = true;
			}
		}

		// リストビュー選択
		private void listview_image_list_SelectedIndexChanged(object sender, EventArgs e)
		{
			mxListView.WaitOne();
			if (listview_image_list.SelectedItems.Count > 0) {
				if (mShowIdx != listview_image_list.SelectedItems[0].Index) {
					mShowIdx = listview_image_list.SelectedItems[0].Index;

					// スレッドを起動して画像表示
					Thread thread = new Thread(new ParameterizedThreadStart(this.ThreadShowImage));
					thread.Start(new ShowImageParam(mShowIdx, false));
				}
				int idx = listview_image_list.SelectedItems[0].Index;

				mSubForm.SelectListView(idx);
			} else {
				;
			}
			mxListView.ReleaseMutex();
		}

		// リストビュークリックイベント
		private void listview_image_list_Click(object sender, EventArgs e)
		{
			mxListView.WaitOne();
			if (listview_image_list.SelectedItems.Count > 0) {
				mShowIdx = listview_image_list.SelectedItems[0].Index;

				// スレッドを起動して画像表示
				Thread thread = new Thread(new ParameterizedThreadStart(this.ThreadShowImage));
				thread.Start(new ShowImageParam(mShowIdx, false));

			}
			mxListView.ReleaseMutex();
		}

		// メインフォームロード
		private void MainForm_Load(object sender, EventArgs e)
		{
			listview_image_list.LostFocus += new EventHandler(ListView_LostFocus);
		}

		// リストビューフォーカス失った
		private void ListView_LostFocus(object sender, EventArgs e)
		{
			Form f = Form.ActiveForm;
			if (f != null && f.Equals(this)) {
				listview_image_list.Focus();
			}
		}

		// 入力ディレクトリ変更
		private void txt_in_TextChanged(object sender, EventArgs e)
		{
			SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_IN_DIR_KEY, txt_in.Text);
		}

		// 出力ディレクトリ変更
		private void txt_out_TextChanged(object sender, EventArgs e)
		{
			SetIniValue(CS.INI_SECTIOIN_SYSTEM, CS.INI_OUT_DIR_KEY, txt_out.Text);
		}

		// サブウィンドウ表示
		private void chkBox_sub_CheckedChanged(object sender, EventArgs e)
		{
			SetIniValue(CS.INI_SECTIOIN_SYSTEM,
			CS.INI_SUB_WINDOWS_KEY, chkBox_sub.Checked.ToString());
			mSubForm.Visible = chkBox_sub.Checked;
		}


		// 画像読み込み
		private void ReadDirImage()
		{
			try
            {
				// ワーカースレッドが起動中の場合、停止する
				if (mWc != null) {
					mWc.SetRun(false);
				}
				mWc = null;

				// 入力ディレクトリ
				string dir = this.txt_in.Text;
				
				if (dir != null && dir != "" && Directory.Exists(dir)) {
					// 読み込みボタン無効
					btn_read.Enabled = false;

					// -- 初期化 --
					// リストクリア
					mxListView.WaitOne();
					listview_image_list.Items.Clear();
					if(mSubFormEnable) mSubForm.ListViewClear();
					mxListView.ReleaseMutex();

					// 画像リストの初期化
					if (mImageList != null) mImageList = null;
					mImageList = new ArrayList();

					// 画像ファイル名リストの初期化
					if (mFileNameList != null) mFileNameList = null;
					mFileNameList = new ArrayList();

					// ファイルリスト抽出
					string[] files = Directory.GetFiles(dir, "*", SearchOption.AllDirectories);
					WriteLogEx("ファイルリスト抽出完了 " + "ファイル数:" + files.Length);

					// スレッド起動
					mWc = new WorkerClass(this, dir, mLog);
					mWc.SetRun(true);
					mWc.SetFileList(files);
					// 状態通知
					mWc.OnSubThreadState += MainForm_SubThreadRunning_State;
					// リスト設定
					mWc.OnSubThreadSetList += MainForm_SubThreadRunning_SetList;
					// 画像設定
					mWc.OnSubThreadSetImage += MainForm_SubThreadRunning_SetImage;
					// 終了通知
					mWc.OnSubThreadFinished += MainForm_SubThreadFinished;

					// スレッドプールスレッドが実行するメソッドを設定
					WaitCallback waitCallback = new WaitCallback(mWc.Execute);

					// 別スレッドを作る
					// メソッドをスレッドプールキューに登録
					ThreadPool.QueueUserWorkItem(waitCallback);

				}
			}
			catch (Exception) {
			}
			finally {
			}
		}

		// 定期処理
		private void worker_main_DoWork(object sender, DoWorkEventArgs e)
		{
			while (true){
				worker_main.ReportProgress(0);
				Thread.Sleep(500);
			}
		}

		// 定期処理(イベント通知)
		private void worker_main_ProgressChanged(object sender, ProgressChangedEventArgs e)
		{
			System.Diagnostics.Process p = System.Diagnostics.Process.GetCurrentProcess();
			p.Refresh();

			int prm = 1;
			if (mMemUnit == CS.INI_MEM_UNIT_K) {
				prm = 1000;
			} else if (mMemUnit == CS.INI_MEM_UNIT_M) {
				prm = 1000000;
			}
			long pm = System.Diagnostics.Process.GetCurrentProcess().WorkingSet64 / prm;
			txt_Pmem.Text = String.Format("{0:#,0}", pm);

			long vm = System.Diagnostics.Process.GetCurrentProcess().VirtualMemorySize64 / prm;
			txt_Vmem.Text = String.Format("{0:#,0}", vm);
		}

		// 定期処理(終了)
		private void worker_main_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
		{

		}


		// ---------------------
		// サブスレッドメソッド
		// ---------------------

		// リスト追加
		private void MainForm_SubThreadRunning_SetList(ArrayList list)
		{
			int size = list.Count;
			for (int i = 0; i < size; i++) {
				// リストに追加
				mxListView.WaitOne();
				mFileNameList.Add(list[i]);
				mxListView.ReleaseMutex();
			}
		}


		// 画像追加
		private void MainForm_SubThreadRunning_SetImage(int idx, String FileName)
		{
			Bitmap bm = new Bitmap(FileName);
			// サムネイル画像生成
			Image thumbnail = Util.createThumbnail(bm, mThumbnail.Width, mThumbnail.Height);
			bm.Dispose();

			// サムネイル画像追加
			imageList.Images.Add(thumbnail);
			ListViewItem item = new ListViewItem((String)mFileNameList[idx]);
			item.ImageIndex = idx;
			listview_image_list.Items.Add(item);

			// サブフォーム通知
			if (mSubFormEnable) mSubForm.ListViewAdd(idx, FileName, (String)mFileNameList[idx]);

			// 画像リスト追加
			mImageList.Add(FileName);

			// ロード完了画像数
			mImageNum = idx + 1;

			if (idx == 0) {
				this.picbox_image.Image = PutImage(FileName);
				mShowIdx = 0;
				SelectListView(mShowIdx);
			}
		}

		// 状態通知
		private void MainForm_SubThreadRunning_State(int val)
		{
			// プログレスバー通知
			SetProgressBar(val);
		}

		// 終了通知
		private void MainForm_SubThreadFinished(object sender, EventArgs e)
		{
			// プログレスバー通知
			SetProgressBar(100);
			// 読み込みボタン有効
			btn_read.Enabled = true;

		}


		// ------------------------------
		// コントロール操作有のメソッド
		// ------------------------------

		// リストビューのアイテム選択
		private void SelectListView(int idx)
		{
			mxListView.WaitOne();
			listview_image_list.SelectedItems.Clear();
			// フォーカス
			listview_image_list.FocusedItem = listview_image_list.Items[idx];
			// 選択
			listview_image_list.Items[idx].Selected = true;
			listview_image_list.Select();
			// 指定した項目がコントロール内に表示されるようする
			listview_image_list.EnsureVisible(idx);

			mSubForm.SelectListView(idx);
			mxListView.ReleaseMutex();
		}

		// 画像表示(インデックス指定)
		private bool ShowImage(int idx)
		{
			bool ret = true;

			if (mImageList.Count >= idx + 1) {
				picbox_image.Image = PutImage((String)mImageList[idx]);
			} else {
				ret = false;
			}

			return ret;
		}

		// プログレスバー通知
		private void SetProgressBar(int val)
		{
			progressBar.Value = val;
		}

		// 画像コピー
		private bool CopyImage(int idx)
		{
			bool ret = true;
			Color col = Color.Blue;

			try {
				String fileName = (String)mFileNameList[idx];
				if (fileName != null) {
					String sFile = txt_in.Text + "\\" + fileName;
					String dFile = txt_out.Text + "\\" + fileName;
					bool eCopy = true;
					if (File.Exists(sFile)) {				// 入力ファイルが存在する
						if (File.Exists(dFile)) {			// 出力ファイルが存在する
							FileInfo fs = new FileInfo(sFile);
							FileInfo fd = new FileInfo(dFile);
							if (fs.Length == fd.Length) {	// ファイルサイズが同じ
								// コピーしない
								eCopy = false;
							} else {						// ファイルサイズが異なる
								String fn, fe;
								fe = Path.GetExtension(dFile);	// 拡張子
								eCopy = false;
								// ファイル名を決定する
								for (int i = 1; i < 100; i++) {
									String tmp;
									fn = Path.GetFileNameWithoutExtension(dFile) + "_" + i;
									tmp = txt_out.Text + "\\" + fn + fe;
									if (!File.Exists(tmp)) {
										dFile = tmp;
										col = Color.Red;
										eCopy = true;
										break;
									}
								}
							}
						}

						// ファイル(画像)コピー
						if (eCopy) {
							File.Copy(sFile, dFile, true);
						}

						// コピーした画像のファイル名を青色に変更
						listview_image_list.SelectedItems[0].ForeColor = col;
						mSubForm.ListViewCol(0, col);

						// 次へ
						nextImage();
					}
				}
			}
			catch {
				ret = true;
			}

			return ret;
		}

		// コントローラ設定
		private void SetController(bool en)
		{
			btn_read.Enabled = en;
			mxListView.WaitOne();
			listview_image_list.Enabled = en;
			if (mSubFormEnable) mSubForm.ListViewCtrl(en);
			mxListView.ReleaseMutex();
			btn_next.Enabled = en;
			btn_pre.Enabled = en;
		}

		// 次の画像へ
		private void nextImage()
		{
			if (mImageNum > 0) {
				mShowIdx++;
				if (mImageNum <= mShowIdx) {
					mShowIdx = 0;
				}
				// スレッドを起動して画像表示
				Thread thread = new Thread(new ParameterizedThreadStart(this.ThreadShowImage));
				thread.Start(new ShowImageParam(mShowIdx, true));
			}
		}

		// 前の画像へ
		private void preImage()
		{
			if (mImageNum > 0) {
				mShowIdx--;
				if (0 > mShowIdx) {
					mShowIdx = mImageNum - 1;
				}

				// スレッドを起動して画像表示
				Thread thread = new Thread(new ParameterizedThreadStart(this.ThreadShowImage));
				thread.Start(new ShowImageParam(mShowIdx, true));
			}
		}

		// Detailsに設定
		private void ListViewDetails()
		{
			listview_image_list.View = View.Details;
		}

		// LaggeIconに設定
		private void ListViewLaggeIcon()
		{
			listview_image_list.View = View.LargeIcon;
		}

		// メモリ単位設定
		private void SetMemoryUnit(String unit)
		{
			mMemUnit = unit;
		}

		// -----------------
		// スレッドメソッド
		// -----------------

		// 画像表示(スレッド)
		private void ThreadShowImage(object obj)
		{
			ShowImageParam prm = (ShowImageParam)obj;
			int index = prm.getIdx();
			bool listUpdate = prm.getUpdate();

			if (listUpdate) {
				DelegateSelectListView delSelListView = new DelegateSelectListView(SelectListView);
				this.Invoke(delSelListView, new object[] { index });
			}

			DelegateSetController delSetCtrl = new DelegateSetController(SetController);
			// コントロールロック
			this.Invoke(delSetCtrl, new object[] { false });
			
			while (true) {
				bool ret = (bool)this.Invoke(
					new DelegateShowImage(ShowImage), new object[] { index });
				if (ret) break;
			}

			// コントロールロック解除
			this.Invoke(delSetCtrl, new object[] { true });
		}

		// 画像コピー
		private void ThreadCopyImage(object obj)
		{
			int index = (int)obj;

			DelegateSetController delSetCtrl = new DelegateSetController(SetController);
			// コントロールロック
			this.Invoke(delSetCtrl, new object[] { false });

			while (true) {
				bool ret = (bool)this.Invoke(
				new DelegateShowImage(CopyImage), new object[] { index });
				if (ret) break;
			}

			// コントロールロック解除
			this.Invoke(delSetCtrl, new object[] { true });

		}



		// デリゲート用クラス(パラメータ)
		private class ShowImageParam
		{
			int idx;
			bool update;

			public ShowImageParam(int i, bool f)
			{
				idx = i;
				update = f;
			}

			public int getIdx()
			{
				return idx;
			}
			public bool getUpdate()
			{
				return update;
			}
		}


		// ディレクトリ選択
		private void SetDir(ref TextBox textBox)
		{
			CommonOpenFileDialog dialog = new CommonOpenFileDialog();

			// フォルダを開く設定
			dialog.IsFolderPicker = true;
			// 読み取り専用フォルダ/コントロールパネルは開かない
			dialog.EnsureReadOnly = false;
			dialog.AllowNonFileSystemItems = false;
			// パス指定
			dialog.DefaultDirectory = Application.StartupPath;
			dialog.InitialDirectory = textBox.Text;

			// 開く
			CommonFileDialogResult ret = dialog.ShowDialog();

			if (ret == CommonFileDialogResult.Ok) {
				// OK
				String dir = dialog.FileName;
				textBox.Text = dir;     // テキストボックスに設定
			} else if (ret == CommonFileDialogResult.Cancel) {
				// キャンセル
			} else {

			}
		}

		// ファイル(画像)コピーイベント
		private void Evt_CopyImage()
		{
			if (mImageNum > 0 && txt_in.Text != "" && txt_out.Text != "") {
				// スレッドを起動して画像表示
				Thread thread = new Thread(new ParameterizedThreadStart(this.ThreadCopyImage));
				thread.Start(mShowIdx);
			}
		}

		// 画像設定
		private Bitmap PutImage(String fileName)
		{
			try {
				Bitmap bm = null;
				if (mImageOut[mImageOutIdx] != null) {
					mImageOut[mImageOutIdx].Dispose();
					mImageOut[mImageOutIdx] = null;
					mImageOutFileName[mImageOutIdx] = "";
				}
				// 画像設定
				bm = mImageOut[mImageOutIdx] = new Bitmap(fileName);
				mImageOutFileName[mImageOutIdx] = fileName;

				// バッファインデックス設定
				mImageOutIdx++;
				if (mImageOutIdx >= mImageOutMax) {
					mImageOutIdx = 0;
				}

				return bm;
			}
			catch {
				return null;
			}
		}

		// --------------------
		// サブフォーム用公開メソッド
		// --------------------

		// 画像設定
		public void SetImageIdx(int idx)
		{
			if (mImageNum > 0) {
				mShowIdx = idx;

				// スレッドを起動して画像表示
				Thread thread = new Thread(new ParameterizedThreadStart(this.ThreadShowImage));
				thread.Start(new ShowImageParam(mShowIdx, true));
			}
		}

		// 表示中の画像インデックス取得
		public int GetShowImageIdx()
		{
			return mShowIdx;
		}

		// 前の画像へ
		public void preImageSet()
		{
			preImage();
		}

		// 次の画像へ
		public void nextImageSet()
		{
			nextImage();
		}

		// 画像コピー
		public void copySet()
		{
			Evt_CopyImage();
		}

	}
}
