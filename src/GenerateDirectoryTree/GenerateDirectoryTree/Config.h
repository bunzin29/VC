#pragma once

using namespace System;

// ソフトウェアバージョン
#define SOFTWARE_VERSION	"0.0.1"

// 設定クラス
public ref  class Config {
// パブリック変数
public:
	String^ version;	// バージョン情報

// パブリック関数
public:
	// コンストラクタ
	Config()
	{
		version = SOFTWARE_VERSION;
	}
};
