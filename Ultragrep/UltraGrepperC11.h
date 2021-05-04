#pragma once
#include "global.h"

class UltraGrepperC11
{
	GrepSettings gSett;
	regex expression;
	GrepResult grepResult;
	mutex grepResultMutex;
	
	void addFileResult(FileResult f) {
		lock_guard<mutex> lk(grepResultMutex);
		grepResult.push_back(f);
	}
public:
	UltraGrepperC11(GrepSettings g):gSett(g) {
		expression.assign(g.getExpression());
	}
	UltraGrepperC11() {}
	~UltraGrepperC11() {}
	void setTime(double time) {
		grepResult.setTime(time);
	}
	void grepFile(string path);
	void showResults();
};

