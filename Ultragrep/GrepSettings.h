#pragma once
#include <string>
#include <vector>
using namespace std;
class GrepSettings
{
	bool verbose;
	string directory;
	string expression;
	vector<string> extList;
public:
	GrepSettings() { 
		verbose=false; 
	directory=""; 
	expression=""; 
	extList.clear(); 
	}
	~GrepSettings() {}

	void setVerbose(bool v) {
		verbose = v;
	}
	void setDirectory(string d) {
		directory = d;
	}
	void setExpression(string e) {
		expression = e;
	}
	void setExtList(string l) {
		if (l.at(0) != '.') {
			//big error
		}
		string buildExt = "";
		//not completed
		for (size_t i = 0; i < l.length(); ++i) {
			if (l.at(i) == '.' && i != 0) {
				extList.push_back(buildExt);
				buildExt = "";
			}
			buildExt += l.at(i);
			if (i == l.length() - 1) {
				extList.push_back(buildExt);
				buildExt = "";
			}
		}
	}
	bool getVerbose() {
		return verbose;
	}
	string getDirectory() {
		return directory;
	}
	string getExpression() {
		return expression;
	}
	vector<string> getExtList() {
		return extList;
	}
};

