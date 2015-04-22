using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using iTextSharp.text;
using iTextSharp.text.pdf;

using Microsoft.WindowsAPICodePack.Dialogs;
using Microsoft.WindowsAPICodePack.Dialogs.Controls;

namespace FileAnalyzer
{

    public partial class Form1 : Form
    {
        // 表示単位
        const int OUT_SIZE_BYTE  = 0;
        const int OUT_SIZE_KBYTE = 1;
        const int OUT_SIZE_MBYTE = 2;
        const int OUT_SIZE_GBYTE = 3;
        const int OUT_SIZE_TBYTE = 4;

        int mOutSize = 0;
        long mOutAllSize = 0;


        public Form1()
        {
            InitializeComponent();

            Init();

        }

        // 初期化処理
        private void Init()
        {
            comb_all_size.Items.Add("byte");
            comb_all_size.Items.Add("Kbyte");
            comb_all_size.Items.Add("Mbyte");
            comb_all_size.SelectedIndex = 0;
            mOutSize = 0;
        }

        // ファイル追加
        private void AddFile(String file)
        {
            System.Diagnostics.Debug.WriteLine(file);

            String size = "err";
            String page = "";

            String ext = Path.GetExtension(file);   // 拡張子

            if (ext == ".pdf") {
                PDF pdf = new PDF(file);
                page = pdf.GetPage().ToString();
                pdf.Close();
            }
            FileInfo fi = new FileInfo(file);
            long fileSize = fi.Length;
            // 3桁ごとにカンマを付ける
            size = fileSize.ToString("#,#");

            dataGridView1.Rows.Add(file, size, page);
        }

        // ディレクトリ選択
        private void btn_dir_Click(object sender, EventArgs e)
        {
            CommonOpenFileDialog dialog = new CommonOpenFileDialog();

            // フォルダを開く設定
            dialog.IsFolderPicker = true;
            // 読み取り専用フォルダ/コントロールパネルは開かない
            dialog.EnsureReadOnly = false;
            dialog.AllowNonFileSystemItems = false;
            // パス指定
            dialog.DefaultDirectory = Application.StartupPath;

            // 開く
            CommonFileDialogResult ret = dialog.ShowDialog();

            if (ret == CommonFileDialogResult.Ok) {
                // OK
                String dir = dialog.FileName;
                txt_dir.Text = dir;     // テキストボックスに設定
            } else if (ret == CommonFileDialogResult.Cancel) {
                // キャンセル
            } else {

            }

            dataGridView1.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;

        }

        // ディレクトリ検索
        private void SerchDirectory(String dir, bool subDir, String [] filter)
        {
            // ファイル取得
            SerchFile(dir, filter);

            if (!subDir) return;

            // ディレクトリ取得
            String[] dirs = Directory.GetDirectories(dir);
            Array.Sort(dirs);

            foreach (String d in dirs) {
                // ファイル取得
                SerchFile(d, filter);

                // ディレクトリ検索(再帰)
                SerchDirectory(d, subDir, filter);
            }
        }

        // ファイル検索
        private void SerchFile(String dir, String [] filter)
        {
            if (filter != null) {           // フィルタあり
                List<String> files = new List<String>();

                // ファイル取得
                foreach (String f in filter) {
                    files.AddRange(Directory.GetFiles(dir, f));
                }
                files.Sort();
                foreach (String f in files) {
                    AddFile(f);
                }
            } else {                            // フィルタなし
                String[] files = Directory.GetFiles(dir);
                Array.Sort(files);
                foreach (String f in files) {
                    AddFile(f);
                }
            }
        }


        // ファイル選択ボタン
        private void btn_file_Click(object sender, EventArgs e)
        {
            //OpenFileDialogクラスのインスタンスを作成
            OpenFileDialog ofd = new OpenFileDialog();

            //はじめのファイル名を指定する
            //はじめに「ファイル名」で表示される文字列を指定する
            ofd.FileName = "default.html";
            //はじめに表示されるフォルダを指定する
            //指定しない（空の文字列）の時は、現在のディレクトリが表示される
            ofd.InitialDirectory = @"C:\";
            //[ファイルの種類]に表示される選択肢を指定する
            //指定しないとすべてのファイルが表示される
            ofd.Filter =
                "HTMLファイル(*.html;*.htm)|*.html;*.htm|すべてのファイル(*.*)|*.*";
            //[ファイルの種類]ではじめに
            //「すべてのファイル」が選択されているようにする
            ofd.FilterIndex = 2;
            //タイトルを設定する
            ofd.Title = "開くファイルを選択してください";
            //ダイアログボックスを閉じる前に現在のディレクトリを復元するようにする
            ofd.RestoreDirectory = true;
            //存在しないファイルの名前が指定されたとき警告を表示する
            //デフォルトでTrueなので指定する必要はない
            ofd.CheckFileExists = true;
            //存在しないパスが指定されたとき警告を表示する
            //デフォルトでTrueなので指定する必要はない
            ofd.CheckPathExists = true;

            //ダイアログを表示する
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                //OKボタンがクリックされたとき
                //選択されたファイル名を表示する
                Console.WriteLine(ofd.FileName);
            }
        }

        // クリアボタン
        private void btn_clr_Click(object sender, EventArgs e)
        {
            // 全てクリア
            dataGridView1.Rows.Clear();
        }

        // 実行ボタン
        private void btn_exe_Click(object sender, EventArgs e)
        {
            String dir = txt_dir.Text;
            if (dir == "") {
                // ディレクトリが選択されていない
                return;
            }
            if (Directory.Exists(dir) == false) {
                // 存在しないディレクトリ
                return;
            }

            // フィルタ
            String filter = txt_filter.Text;
            if (!chk_filter.Checked) {
                // フィルタ無効
                filter = null;
            }
            if (filter == "") {
                filter = null;
            }

            String [] split;
            if (filter != null) {
                split = filter.Split(new Char[] {' ', ',', ':', '\t'});
            } else {
                split = null;
            }

            // ディレクトリ検索
            SerchDirectory(dir, chk_subdir.Checked, split);

            // 結果出力
            outResult();
        }

        // 結果表示
        private void outResult()
        {
            // 総サイズ表示
            outAllSize(1);
            // 総ページ数表示
            outAllPage(2);
        }

        // 総サイズ表示
        private void outAllSize(int idx)
        {
            long allSize = 0;
            double dallSize = 0;
            int row = dataGridView1.RowCount;
            String str = "";

            for (int r = 0; r < row; r++) {
                DataGridViewRow rowData = dataGridView1.Rows[r];
                long s = long.Parse(((String)rowData.Cells[idx].Value).Replace(",", ""));
                allSize += s;
            }
            dallSize = mOutAllSize = allSize;
            switch (comb_all_size.SelectedIndex) {
                case OUT_SIZE_BYTE:     // byte
                default:
                    str = allSize.ToString("#,#").ToString();
                    break;
                case OUT_SIZE_KBYTE:     // Kbyte
                    dallSize /= 1024;
                    str = dallSize.ToString("n1").ToString();

                    break;
                case OUT_SIZE_MBYTE:     // Mbyte
                    dallSize /= 1048576;
                    str = dallSize.ToString("n1").ToString();

                    break;

            }

            txt_all_size.Text = str;

        }

        // 総ページ数表示
        private void outAllPage(int idx)
        {
            long allPage = 0;
            int row = dataGridView1.RowCount;
            for (int r = 0; r < row; r++) {
                DataGridViewRow rowData = dataGridView1.Rows[r];
                long p = long.Parse((String)rowData.Cells[idx].Value);
                allPage += p;
            }
            txt_all_page.Text = allPage.ToString();
        }

        // フィルタチェックボックス
        private void chk_filter_CheckedChanged(object sender, EventArgs e)
        {
            if (chk_filter.Checked) {
                txt_filter.Enabled = true;
            } else {
                txt_filter.Enabled = false;
            }
        }

        // CSV出力ボタン
        private void btn_csv_Click(object sender, EventArgs e)
        {
            if (dataGridView1.RowCount > 0) {
                Encoding enc = Encoding.GetEncoding("Shift_JIS");
                int colCount = dataGridView1.Columns.Count;
                int lastColIndex = colCount - 1;

                // 出力ファイルを開く
                StreamWriter sr = new StreamWriter("out.csv", false, enc);

                int row = dataGridView1.RowCount;
                for (int r = 0; r < row; r++ ) {
                    DataGridViewRow rowData = dataGridView1.Rows[r];
                    if (rowData != null) {

                        for (int i = 0; i < colCount; i++) {
                            // フィールド取得

                            String field = (String)rowData.Cells[i].Value;
                            // "で囲む
                            field = EncloseDoubleQuotesIfNeed(field);
                            // フィールドを書き込む
                            sr.Write(field);

                            // カンマを書き込む
                            if (lastColIndex > i) {
                                sr.Write(',');
                            }
                        }
                        // 改行
                        sr.Write("\r\n");
                    }
                }

                // 閉じる
                sr.Close();
            }
        }

        /// <summary>
        /// 必要ならば、文字列をダブルクォートで囲む
        /// </summary>
        private string EncloseDoubleQuotesIfNeed(string field)
        {
            if (NeedEncloseDoubleQuotes(field)) {
                return EncloseDoubleQuotes(field);
            }
            return field;
        }

        /// <summary>
        /// 文字列をダブルクォートで囲む
        /// </summary>
        private string EncloseDoubleQuotes(string field)
        {
            if (field.IndexOf('"') > -1)
            {
                //"を""とする
                field = field.Replace("\"", "\"\"");
            }
            return "\"" + field + "\"";
        }

        /// <summary>
        /// 文字列をダブルクォートで囲む必要があるか調べる
        /// </summary>
        private bool NeedEncloseDoubleQuotes(string field)
        {
            return field.IndexOf('"') > -1 ||
                field.IndexOf(',') > -1 ||
                field.IndexOf('\r') > -1 ||
                field.IndexOf('\n') > -1 ||
                field.StartsWith(" ") ||
                field.StartsWith("\t") ||
                field.EndsWith(" ") ||
                field.EndsWith("\t");
        }

        // 単位変更
        private void comb_all_size_SelectedIndexChanged(object sender, EventArgs e)
        {
            double size = mOutAllSize;
            String str = "";

            if (txt_all_size.Text == "") return;

            if (mOutSize != comb_all_size.SelectedIndex) {
                mOutSize = comb_all_size.SelectedIndex;
            } else {
                return;
            }

            switch (comb_all_size.SelectedIndex) {
                case OUT_SIZE_BYTE:     // byte
                default:
                    str = mOutAllSize.ToString("#,#").ToString();
                    break;
                case OUT_SIZE_KBYTE:     // Kbyte
                    size /= 1024;
                    str = size.ToString("n1").ToString();

                    break;
                case OUT_SIZE_MBYTE:     // Mbyte
                    size /= 1048576;
                    str = size.ToString("n1").ToString();

                    break;

            }

            txt_all_size.Text = str;
        }
    }
}
