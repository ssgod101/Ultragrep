#include "GrepScannerC11.h"

GrepScannerC11::GrepScannerC11(GrepSettings gs) : gSett(gs) {
	//setup for scan
	threadPool.clear();
	if (gSett.getDirectory() == ""&&gSett.getExpression() == ""&&gSett.getExtList().empty() && !gSett.getVerbose()) {
		//GrepSettings is empty, display error.
	}
	dirPath = gSett.getDirectory();
	if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
		//scan the one file only and nothing else.
		//also check if that file has same extension in extension list.
		cout << "Hi" << endl;
		noError = true;
	}
	else {
		noError = false;
	}
}

void GrepScannerC11::beginScan() {
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
	UltraGrepperC11 grepper(gSett);
	for (; iter != end;++iter) {
		if (fs::is_directory(iter->path())) {
	//		//check if verbose
			if (gSett.getVerbose()) {
				cout << "Scanning: " << iter->path() << endl;
			}
		}
		else{
			if (iter->path().has_extension()) {
				string ext = iter->path().extension().string();
				string path = iter->path().string();
				if (regex_match(ext, reg)) {
					if (gSett.getVerbose()) {
						cout << "Grepping: " << path << endl;
					}
					//thread grep(&UltraGrepperC11::grepFile, &grepper,path);
					threadPool.push_back(thread(&UltraGrepperC11::grepFile, &grepper, path));
					//grep.join();
				}
				//cout << ext << endl;
			}
		}
	}
	for (size_t i = 0; i < threadPool.size(); ++i) {
		threadPool[i].join();
	}
	time_t endTime = clock();
	float totalTime = double(endTime - startTime) / CLOCKS_PER_SEC;
	grepper.setTime(totalTime);
	grepper.showResults();
}


