using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;
using System.IO;
using System.Collections;
using System.Drawing;

namespace ImageDivider
{
	class WorkerClass
	{
		private Control mForm;					// フォーム(親)
		private string[] mFileList;				// ファイルリスト
		private ArrayList mFileNameList;		// 画像ファイル名リスト
		private bool mRun;						// 実行中
		private MyLog mLog;						// ログ
        private ArrayList mEnableExtension;     // 有効拡張子

		// 状態通知
		public delegate void SubThreadRunningEventHandler_State(int stateVal);
		public event SubThreadRunningEventHandler_State OnSubThreadState;
		// リスト設定
		public delegate void SubThreadRunningEventHandler_SetList(ArrayList list);
		public event SubThreadRunningEventHandler_SetList OnSubThreadSetList;
		// 画像設定
		public delegate void SubThreadRunningEventHandler_SetImage(int idx, String fileName);
		public event SubThreadRunningEventHandler_SetImage OnSubThreadSetImage;
		// 終了通知
		public event EventHandler OnSubThreadFinished;

		// コンストラクタ
		public WorkerClass(Control mainThreadForm, string dir, MyLog log)
		{
			mForm = mainThreadForm;
			mLog = log;

            mEnableExtension = new ArrayList();
            mEnableExtension.Add(".jpg");
            mEnableExtension.Add(".png");
            mEnableExtension.Add(".bmp");
            mEnableExtension.Add(".JPG");
            mEnableExtension.Add(".PNG");
            mEnableExtension.Add(".BMP");
        }

		// ファイルリスト設定
		public void SetFileList(string[] fileList)
		{
			mFileList = fileList;
		}

		// スレッド動作設定
		public void SetRun(bool run)
		{
			mRun = run;
		}

		// 実行
		public void Execute(object state)
		{
			try {
				int idxList = 0;
				int idxImage = 0;
				ArrayList noUseList = new ArrayList();
				int fileSize = mFileList.Length;
				if (mFileNameList != null) {
					mFileNameList = null;
				}
				mFileNameList = new ArrayList();

				WriteLog("ファイル名取得開始");

				// ファイル名
				for (int i = 0; i < fileSize; i++) {
					if (!mRun) return;
					if (IsImageFile(mFileList[i])) {
						// パスからファイル名取得
						string fileName = Path.GetFileName(mFileList[i]);

						mFileNameList.Add(fileName);
						idxList++;
					} else {
						noUseList.Add(i);
					}
				}

				WriteLog("ファイル名取得終了");

				mForm.Invoke(OnSubThreadSetList, new object[] { mFileNameList });

				WriteLog("サムネイル作成開始");

				for (int i = 0; i < fileSize; i++) {
					if (!mRun) break;
					try {
						if (!noUseList.Contains(i)) {
							mForm.Invoke(OnSubThreadSetImage, new object[] { idxImage, mFileList[i] });
							idxImage++;

							int stateVal = i / fileSize;
							mForm.Invoke(OnSubThreadState, new object[] { stateVal });
						}
					}
					catch(Exception e) {
						// 画像ファイルでない
						MessageBox.Show(e.Message);
					}
				}

				WriteLog("サムネイル作成終了");

				if (idxList != idxImage) {
					String errLog = "Error:idxList(" + idxList + ") idxImage(" + idxImage + ")";
						
					// エラー表示
					MessageBox.Show(
						errLog,
						"caption",
						MessageBoxButtons.OKCancel,
						MessageBoxIcon.Information,
						MessageBoxDefaultButton.Button1,
						MessageBoxOptions.DefaultDesktopOnly);

					WriteLog(errLog);

				}

			}
			finally {
				// Invoke()を使って終了を通知する
				mForm.Invoke(OnSubThreadFinished, new object[] { this, EventArgs.Empty });
			}
		}

		// 画像ファイル判定
		private bool IsImageFile(String fileName)
		{
            return mEnableExtension.Contains(Path.GetExtension(fileName));

            //bool ret = true;
            //try {
            //    System.Drawing.Image img = System.Drawing.Image.FromFile(fileName);

            //    //イメージのファイル形式を調べる
            //    if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Bmp)) {
            //        //Console.WriteLine("ビットマップ (BMP) イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Gif)) {
            //        //Console.WriteLine("GIF (Graphics Interchange Format) イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Jpeg)) {
            //        //Console.WriteLine("JPEG (Joint Photographic Experts Group) イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Png)) {
            //        //Console.WriteLine("W3C PNG (Portable Network Graphics) イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Exif)) {
            //        //Console.WriteLine("Exif (Exchangeable Image File) 形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Tiff)) {
            //        //Console.WriteLine("TIFF (Tagged Image File Format) イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Icon)) {
            //        //Console.WriteLine("Windows アイコン イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Emf)) {
            //        //Console.WriteLine("拡張メタファイル (EMF) イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.Wmf)) {
            //        //Console.WriteLine("Windows メタファイル (WMF) イメージ形式です");
            //    } else if (img.RawFormat.Equals(System.Drawing.Imaging.ImageFormat.MemoryBmp)) {
            //        //Console.WriteLine("メモリ ビットマップ イメージ形式です");
            //    } else {
            //        ret = false;
            //    }

            //    img.Dispose();

            //}
            //catch {
            //    return false;
            //}
            //finally {

            //}

            //return ret;
		}

		// ログ出力
		private void WriteLog(String str)
		{
			Util.WriteLog(this, mLog, str);
		}

	}

}
