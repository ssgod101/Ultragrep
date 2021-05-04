#include "GrepScannerWin32.h"

GrepResult grepResult;
mutex mut;
regex expression;
bool verbose;

void addFileResult(FileResult) {}

DWORD WINAPI grepFile(LPVOID lp) {
	string path = *reinterpret_cast<string*>(lp);
	ifstream inFile;
	inFile.open(path);
	string currentLine;
	int lineNumber = 0;
	FileResult results;
	results.fileName = path;
	smatch matches;
	while (getline(inFile, currentLine)) {
		lineNumber++;
		string::const_iterator begin(currentLine.cbegin());
		int numMatches = 0;
		FileMatch match;

		while (regex_search(begin, currentLine.cend(), matches, expression)) {
			numMatches++;
			begin += matches.position() + matches.length();
		}
		if (numMatches > 0) {
			if (verbose) {
				cout << "Matched " << numMatches << ": " << path << " [" << lineNumber << "] " << currentLine << endl;
			}
			if (numMatches == 1) {
				match.lineNumber = "[" + to_string(lineNumber) + "]";
				match.line = currentLine;
			}
			else if (numMatches > 1) {
				match.lineNumber = "[" + to_string(lineNumber) + ":" + to_string(numMatches) + "]";
				match.line = currentLine;
			}
			results.allMatches += numMatches;
			results.matches.push_back(match);
		}
	}
	if (!results.matches.empty()) {
		lock_guard<mutex> lk(mut);
		grepResult.push_back(results);
	}
	return 0;
}

GrepScannerWin32::GrepScannerWin32(GrepSettings g) : gSett(g)
{
	//setup for scan
	threadPool.clear();
	if (gSett.getDirectory() == ""&&gSett.getExpression() == ""&&gSett.getExtList().empty() && !gSett.getVerbose()) {
		//GrepSettings is empty, display error.
	}
	dirPath = gSett.getDirectory();
	expression.assign(gSett.getExpression());
	verbose = gSett.getVerbose();
	if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
		//scan the one file only and nothing else.
		//also check if that file has same extension in extension list.
		noError = true;
	}
	else {
		noError = false;
	}
}

void GrepScannerWin32::beginScan()
{
	time_t startTime = clock();
	fs::recursive_directory_iterator iter(dirPath);
	fs::recursive_directory_iterator end;
	string extMatch = "";
	for (size_t i = 0; i < gSett.getExtList().size(); ++i) {
		extMatch += gSett.getExtList().at(i);
		if (i != gSett.getExtList().size() - 1) {
			extMatch = extMatch + "|";
		}
	}
	cout << extMatch << endl;
	regex reg(extMatch);
	for (; iter != end; ++iter) {
		if (fs::is_directory(iter->path())) {
			//		//check if verbose
			if (gSett.getVerbose()) {
				cout << "Scanning: " << iter->path() << endl;
			}
		}
		else {
			if (iter->path().has_extension()) {
				string ext = iter->path().extension().string();
				string path = iter->path().string();
				if (regex_match(ext, reg)) {
					if (gSett.getVerbose()) {
						cout << "Grepping: " << path << endl;
					}
					//thread grep(&UltraGrepperC11::grepFile, &grepper,path);
					DWORD threadID = 0;
					threadPool.push_back(CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(grepFile), &path, 0, &threadID));
					//grep.join();
				}
				//cout << ext << endl;
			}
		}
	}
	for (size_t i = 0; i < threadPool.size();++i) {
		WaitForSingleObject(threadPool[i],INFINITE);
	}
	for (size_t i = 0; i < threadPool.size(); ++i) {
		CloseHandle(threadPool[i]);
	}
	time_t endTime = clock();
	float totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;
	grepResult.setTime(totalTime);
	grepResult.showResults();
}
