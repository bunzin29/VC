﻿using System.Runtime.InteropServices;
using System.Text;
 
/// <summary>
/// INIファイルを読み書きするクラス
/// </summary>
public class Ini
{
	[DllImport("kernel32.dll")]
	private static extern int GetPrivateProfileString(
		string lpApplicationName,
		string lpKeyName,
		string lpDefault,
		StringBuilder lpReturnedstring,
		int nSize,
		string lpFileName);

	[DllImport("kernel32.dll")]
	private static extern int WritePrivateProfileString(
		string lpApplicationName,
		string lpKeyName,
		string lpstring,
		string lpFileName);
 
	string filePath;
	  /// <summary>
    /// ファイル名を指定して初期化します。
    /// ファイルが存在しない場合は初回書き込み時に作成されます。
    /// </summary>
	public Ini(string filePath)
	{
        this.filePath = filePath;
		//
/*		if (!System.IO.File.Exists(filePath)) {
			using (System.IO.FileStream hStream = System.IO.File.Create(filePath)) {
				if (hStream != null) {
					hStream.Close();
				}
			}
		}
 */
    }
 
    /// <summary>
    /// sectionとkeyからiniファイルの設定値を取得、設定します。 
    /// </summary>
    /// <returns>指定したsectionとkeyの組合せが無い場合は""が返ります。</returns>
    public string this[string section,string key] {
        set {
            WritePrivateProfileString(section, key, value, filePath);
        }
        get {
            StringBuilder sb = new StringBuilder(256);
            GetPrivateProfileString(section, key, string.Empty, sb, sb.Capacity, filePath);
            return sb.ToString();
        }
    }
 
    /// <summary>
    /// sectionとkeyからiniファイルの設定値を取得します。
    /// 指定したsectionとkeyの組合せが無い場合はdefaultvalueで指定した値が返ります。
    /// </summary>
    /// <returns>
    /// 指定したsectionとkeyの組合せが無い場合はdefaultvalueで指定した値が返ります。
    /// </returns>
    public string GetValue(string section, string key, string defaultvalue) {
        StringBuilder sb = new StringBuilder(256);
        GetPrivateProfileString(section, key, defaultvalue, sb, sb.Capacity, filePath);
        return sb.ToString();
    }



}

/* --------------------------------------------------
---------------------- 使用方法 --------------------
//ファイルを指定して初期化
IniFile ini = new IniFile("./test.ini");
 
//書き込み
ini["section", "key"] = "value";
 
//読み込み
string value = ini["section", "key"];
 
Console.WriteLine(value);
 
//この様に書き込まれる。
//[section]
//key=value
 
---------------------------------------------------*/