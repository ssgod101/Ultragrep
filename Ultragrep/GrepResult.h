#pragma once
#include <string>
#include <vector>
using namespace std;

struct FileMatch {
	string lineNumber = "";
	string line = "";
};

struct FileResult {
	string fileName = "";
	int allMatches = 0;
	vector<FileMatch> matches;
};

class GrepResult
{
	int numFiles;
	int totalMatches;
	float time;
	vector<FileResult> totalFiles;
	mutex grepResultMutex;
	CRITICAL_SECTION crit;
public:
	GrepResult() :numFiles(0), totalMatches(0) { totalFiles.clear(); }
	~GrepResult() {}
	void push_back(FileResult f) {
		lock_guard<mutex> lk(grepResultMutex);
		totalFiles.push_back(f);
		numFiles++;
		totalMatches += f.allMatches;
	}
void setTime(float totalTime) {
	time = totalTime;
}
size_t size() {
	return totalFiles.size();
}
int getNumFiles() {
	return numFiles;
}
int getTotalMatches() {
	return totalMatches;
}
vector<FileResult> getVector() {
	return totalFiles;
}
float getTime() {
	return time;
}
void showResults() {
	cout << endl;
	cout << "Grep Report: " << endl;
	cout << endl;
	for (size_t i = 0; i < totalFiles.size(); ++i) {
		cout << totalFiles[i].fileName << endl;
		vector<FileMatch> matches = totalFiles[i].matches;
		for (int j = 0; j < matches.size(); ++j) {
			cout << left << setw(15) << matches[j].lineNumber;
			cout << left << setw(15) << matches[j].line;
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "Files with matches = " << numFiles << endl;
	cout << "Total number of matches = " << totalMatches << endl;
	cout << "Scan Completed in " << time << "s" << endl;
}
};

