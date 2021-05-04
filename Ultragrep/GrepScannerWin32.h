#pragma once
#include "global.h"
class GrepScannerWin32
{
	GrepSettings gSett;
	fs::path dirPath;
	vector<HANDLE> threadPool;
	bool noError;
public:
	GrepScannerWin32(GrepSettings g);
	GrepScannerWin32() {}
	~GrepScannerWin32() {}
	void beginScan();
	bool pathIsValid() {
		return noError;
	}
};

