/**
 *@file test.cpp
 *@brief test program for querying
 *
 */
 #include "InvertedFileIndex.h"
 #include <iostream>
 #include <chrono>
 #include <ratio>
 #include <ctime>

int main()
{
    // Finish test program here
    InvertedFileIndex SearchEngine;
    SearchEngine.GetStopWord();
    SearchEngine.UpdateIndex();
	std::cout << "Please enter the query, and if you want to quit, just enter 'quit!':" << std::endl;
	std::string str;
	std::getline(std::cin, str);
	while (str != "q")
	{
	    using namespace std::chrono;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        std::vector<std::string> res;
        int times = 10000;
        for(int i = 0; i < times; i++)
            res = SearchEngine.QuerySearch2(str, 1.0);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << "Search Engine spends " << time_span.count() << "s in "
                  << times << " times and retrives " << res.size()
			      << " documents." << std::endl;
		int i = 0;
		for (auto it : res) {
			i++;
			std::cout << "No." << i << ": " << it << std::endl;
		}
		std::cout << std::endl << "Please enter the query, and if you want to quit, enter 'q':" << std::endl;
		std::getline(std::cin, str);
	}
    return 0;
}
