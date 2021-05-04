#pragma once
#include "global.h"
class UltraGrepperWin32
{
	GrepSettings gSett;
	regex expression;
	GrepResult grepResult;
	CRITICAL_SECTION crit;

	void addFileResult(FileResult f) {
		EnterCriticalSection(&crit);
		grepResult.push_back(f);
		LeaveCriticalSection(&crit);
	}
public:
	UltraGrepperWin32(GrepSettings g) :gSett(g) {
		expression.assign(g.getExpression());
	}
	UltraGrepperWin32() {}
	~UltraGrepperWin32() {}
	void setTime(double time) {
		grepResult.setTime(time);
	}
	void showResults();
};

