/**
 *@file test.cpp
 *@brief test program for querying
 *
 */
 #include "InvertedFileIndex.h"
 #include <Windows.h>
 #pragma comment( lib, "winmm.lib")


int main()
{
    // Finish test program here
	DWORD t1, t2;
    InvertedFileIndex SearchEngine;
    SearchEngine.GetStopWord();
    SearchEngine.UpdateIndex();
	std::cout << "Please enter the query, and if you want to quit, just enter 'quit!':" << std::endl;
	std::string str;
	std::getline(std::cin, str);
	while (str != "quit")
	{
		t1 = timeGetTime();
		std::vector<std::string> res = SearchEngine.QuerySearch2(str, 1.0);
		t2 = timeGetTime();
		std::cout << "Search Engine spends " << (t2 - t1) * 1.0 / 1000 << "s, and retrives " << res.size() 
			      << " documents." << std::endl;
		int i = 0;
		for (auto it : res) {
			i++;
			std::cout << "No." << i << ": " << it << std::endl;
		}
		std::cout << std::endl << "Please enter the query, and if you want to quit, just enter 'quit!':" << std::endl;
		std::getline(std::cin, str);
	}
    return 0;
}
