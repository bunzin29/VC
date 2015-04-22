using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileAnalyzer
{
    abstract class File
    {
        protected String mFileName;           // ファイル名
        protected int mFileSize;              // ファイルサイズ

        // コンストラクタ
        public File()
        {
        }
        public File(String fileName)
        {
            this.mFileName = fileName;
        }

        ~File()
        {
        }

        public virtual int GetPage() { return 0; }

    }

}
