/**
 *@file main.cpp
 *@brief main program for querying
 *
 */
 #include "InvertedFileIndex.h"
 #include <iostream>
 #include <chrono>
 #include <ratio>
 #include <ctime>

int main()
{
    // Finish main program here
    InvertedFileIndex SearchEngine;
	float threshold = 1.0;
    SearchEngine.GetStopWord();
    SearchEngine.UpdateIndex();
	std::cout << "Please enter the query, and if you want to quit, just enter 'q':" << std::endl;
	std::string str;
	std::getline(std::cin, str);
	while (str != "q")
	{
	    using namespace std::chrono;
		std::cout << "Enter threshold: ";
		std::cin >> threshold;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        std::vector<std::string> res;
        int times = 10000;
        for(int i = 0; i < times; i++)
            res = SearchEngine.QuerySearch2(str, threshold);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		if (threshold == 1.0) SearchEngine.Test(res, str);
		if (res.size() == 0)
			std::cout << "Search Engine fails to retrive documents. " << std::endl
			          << "It's possible that your query is contained in StopList, or there is no such terms in documents."
			          << std::endl;
		else
		{
			std::cout << "Search Engine spends " << time_span.count() << "s in "
				<< times << " times and retrives " << res.size()
				<< " documents." << std::endl;
			int i = 0;
			for (auto it : res) {
				i++;
				std::cout << "No." << i << ": " << it << std::endl;
			}
		}
		std::cout << std::endl << "Please enter the query, and if you want to quit, enter 'q':" << std::endl;
		std::getline(std::cin, str); //To avoid get empty input.
		std::getline(std::cin, str);
	}
    return 0;
}
