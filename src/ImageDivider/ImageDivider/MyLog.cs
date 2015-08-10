using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageDivider
{
	// ログ管理クラス
	public class MyLog
	{
		private String mLogFile;			// ログファイル名(フルパス)
		private StreamWriter mStrmWrite;	// ストリーム

		// コンストラクタ
		public MyLog(String logFile)
		{
			mLogFile = logFile;

			mStrmWrite = new StreamWriter(mLogFile, true, System.Text.Encoding.GetEncoding("shift_jis"));
		}

		// デストラクタ
		~MyLog()
		{
			mLogFile = null;
			if (mStrmWrite != null) {
				//mStrmWrite.Close();
				mStrmWrite = null;
			}
		}

		// 開く
		public bool Open(bool apend)
		{
			try {
				if (mStrmWrite == null) {
					mStrmWrite = new StreamWriter(mLogFile, apend);
				}
					
				return true;
			}
			catch {
				return false;
			}
		}

		// 閉じる
		public bool Close()
		{
			try {
				if (mStrmWrite != null) {
					mStrmWrite.Close();
					mStrmWrite = null;
				}
				return true;
			}
			catch {
				return false;
			}

		}

		// 削除
		public void Delete()
		{
			Close();

			FileStream fs = new FileStream(mLogFile, FileMode.Open);
			fs.SetLength(0);
			fs.Close();

			Open(true);

		}

		// 書込み
		public bool Write(String str)
		{
			try {
				mStrmWrite.WriteLine(GetDate() + " :" + str);
				mStrmWrite.Flush();
				return true;
			}
			catch {
				return false;
			}
		}

		// 時刻取得(ログ用)
		private String GetDate()
		{
			return DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff");
		}
	}
}
