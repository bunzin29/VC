using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using iTextSharp.text;
using iTextSharp.text.pdf;

namespace FileAnalyzer
{
    class PDF : File
    {
        private PdfReader mPdfReader;

        // コンストラクタ
        public PDF(String fileName)
        {
            this.mFileName = fileName;
            try {
                mPdfReader = new PdfReader(fileName);
            } catch (Exception) {
                mPdfReader = null;
            }
        }

        // デストラクタ
        ~PDF()
        {
            if (mPdfReader != null) {
                mPdfReader.Close();
                mPdfReader = null;
            }
        }

        // ページ数取得
        public override int GetPage()
        {
            if (mPdfReader != null) {
                return mPdfReader.NumberOfPages;
            } else {
                return 0;
            }
        }

        // 閉じる
        public void Close()
        {
            if (mPdfReader != null) {
                mPdfReader.Close();
                mPdfReader = null;
            }
        }

    }
}
