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

	}
}
