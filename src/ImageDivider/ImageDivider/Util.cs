using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageDivider
{
	public class Util
	{

		// サムネイル画像生成
		static public Image createThumbnail(Image image, int w, int h)
		{
			try {
				Bitmap canvas = new Bitmap(w, h);

				Graphics g = Graphics.FromImage(canvas);
				g.FillRectangle(new SolidBrush(Color.White), 0, 0, w, h);

				float fw = (float)w / (float)image.Width;
				float fh = (float)h / (float)image.Height;

				float scale = Math.Min(fw, fh);
				fw = image.Width * scale;
				fh = image.Height * scale;

				g.DrawImage(image, (w - fw) / 2, (h - fh) / 2, fw, fh);
				g.Dispose();

				return canvas;
			}
			catch (Exception e) {
				MessageBox.Show(e.Message);
				return null;
			}
		}

		// ログ出力
		static public void WriteLog(object cls, MyLog log, String str)
		{
			// 名前空間まで含めてクラス名を取得
			var fullClassName = cls.GetType().FullName;
			// クラス名のみ取得
			var className = cls.GetType().Name;

			if (log != null) {
				log.Write("[" + className + "]" + str);
			}
		}

	}
}
