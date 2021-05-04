#pragma once
#include "global.h"
#include "UltraGrepperC11.h"
class GrepScannerC11
{
	GrepSettings gSett;
	fs::path dirPath;
	vector<thread> threadPool;
	bool noError;
public:
	GrepScannerC11(GrepSettings gs);
	GrepScannerC11() {}
	~GrepScannerC11(){}
	void beginScan();
	bool pathIsValid() {
		return noError;
	}
};

