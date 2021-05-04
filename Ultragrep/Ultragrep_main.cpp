#include "GrepScannerC11.h"
#include "GrepScannerWin32.h"

//Instructions
//Looks for files with a certain extention (has to be readable: txt, cpp, hpp)
//then searches inside those files to look for lines that contain the regex.
//Output is seperated by files and there can be multiple search results in one file
//Example result searching for word 'auto' in cpp files:
//ex: C:\Users\a_sawk\Documents\6. SleepWake\6. SleepWake\1. SWWin32.cpp
//ex: [19] auto delay = bind(randDist, randomEngine);
//ex: [60]    for (auto& t : threads)
//Example output after displaying results:
//ex: Files with matches = 3
//ex: Total number of matches = 6
//ex: Scan Completed in 0.00219044s

//Can get extra 10% bonus by implementing Win32 and C++11 threads using adapter pattern
//if test Win32 command works then use Win32 else use C++11.
//Build project first using c++11, then implement adapter pattern for win32 after.

//Interface
//template: ultragrep [-v] folder expr [extention-list]*
//Example: ultragrep -v c:\users [Gg]et .cpp.hpp.h
//Verbose means showing files as they are scanned and if a result is found
//No verbose just means displaying output
//Directory path should account for spaces
//Having '.' as directory path means scan current folder
//Expression is a regex statement
//Extention-list cannot have spaces between each extention (.cpp.hpp)
//If no extensions have been provided then default extention is .txt

//Steps to do decent
//Take in parameters and place into proper storage.
//Scan all files and all subfolders (must be recursive)
//If a file is found with the extention, output: Grepping: [insert path to file with extention]
//create new thread that scans each line in that file while main continues scanning for files. (grepping)
//store results in file object that contains vector of all lines found in that file.
//close file that was being grepped
//display final output at end.

//look up std::filesystem::recursive_directory_iterator

//Windows explorer tip: highlight directory and type cmd to open cmd in that directory!

int main(int argc, char* argv[]) {
	//max arguments = 5
	//min arguments = 3
	if (argc < 3 || argc > 5) {
		cout << "Big Error: parameters are wrong!" << endl;
		return 0;
	}
	for (int i = 0; i < argc; ++i) {
		cout << argv[i] << endl;
	}
	GrepSettings sett;
	string ver = argv[1];
	switch (argc) {
	case 3:
		sett.setDirectory(argv[1]);
		sett.setExpression(argv[2]);
		sett.setExtList(".txt");
		break;
	case 4:
		if (ver == "-v") { 
			sett.setVerbose(true);
			sett.setDirectory(argv[2]);
			sett.setExpression(argv[3]);
			sett.setExtList(".txt");
		}
		else {
			sett.setDirectory(argv[1]);
			sett.setExpression(argv[2]);
			sett.setExtList(argv[3]);
		}
		break;
	case 5:
		if (ver == "-v") { sett.setVerbose(true); }
		sett.setDirectory(argv[2]);
		sett.setExpression(argv[3]);
		sett.setExtList(argv[4]);
		break;
	}

	//Test if sample Win32 command works. If so use Win32 threads, else use C++11 Threads.
	//Currently default is C++11 for now...
	bool checkWIN32;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || !defined(__CYGWIN__)
	checkWIN32 = true;
#else
	tempBool = false;
#endif
	//checkWIN32 = false;
	if (checkWIN32) {
		GrepScannerWin32 grepScanner(sett);
		if (grepScanner.pathIsValid()) {
			grepScanner.beginScan();
		}
	}
	else {
		GrepScannerC11 grepScanner(sett);
		if (grepScanner.pathIsValid()) {
			/*thread scan(&GrepScannerC11::beginScan, &grepScanner);
			scan.join();*/
			grepScanner.beginScan();
		}
	}
}