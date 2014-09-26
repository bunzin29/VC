#pragma once

using namespace System;
using namespace System::IO;

#define SOFTWARE_VERSION	"0.0.1"

public ref  class Config {
	public:
		String^ version;

	public:
		Config()
		{
			version = SOFTWARE_VERSION;
		}

};

