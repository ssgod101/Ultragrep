#include "UltraGrepperWin32.h"

//DWORD __stdcall UltraGrepperWin32::grepFile(string path)
//{
//	ifstream inFile;
//	inFile.open(path);
//	string currentLine;
//	int lineNumber = 0;
//	FileResult results;
//	results.fileName = path;
//	smatch matches;
//	while (getline(inFile, currentLine)) {
//		lineNumber++;
//		string::const_iterator begin(currentLine.cbegin());
//		int numMatches = 0;
//		FileMatch match;
//		while (regex_search(begin, currentLine.cend(), matches, expression)) {
//			numMatches++;
//			begin += matches.position() + matches.length();
//		}
//		if (numMatches > 0) {
//			if (gSett.getVerbose()) {
//				cout << "Matched " << numMatches << ": " << path << " [" << lineNumber << "] " << currentLine << endl;
//			}
//			if (numMatches == 1) {
//				match.lineNumber = "[" + to_string(lineNumber) + "]";
//				match.line = currentLine;
//			}
//			else if (numMatches > 1) {
//				match.lineNumber = "[" + to_string(lineNumber) + ":" + to_string(numMatches) + "]";
//				match.line = currentLine;
//			}
//			results.allMatches += numMatches;
//			results.matches.push_back(match);
//		}
//	}
//	if (!results.matches.empty()) {
//		addFileResult(results);
//	}
//	return 0;
//}

void UltraGrepperWin32::showResults()
{
	cout << endl;
	cout << "Grep Report: " << endl;
	cout << endl;
	vector<FileResult> total = grepResult.getVector();
	for (size_t i = 0; i < total.size(); ++i) {
		cout << total[i].fileName << endl;
		vector<FileMatch> matches = total[i].matches;
		for (int j = 0; j < matches.size(); ++j) {
			cout << left << setw(15) << matches[j].lineNumber;
			cout << left << setw(15) << matches[j].line;
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "Files with matches = " << grepResult.getNumFiles() << endl;
	cout << "Total number of matches = " << grepResult.getTotalMatches() << endl;
	cout << "Scan Completed in " << grepResult.getTime() << "s" << endl;
}
