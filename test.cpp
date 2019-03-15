/**
 *@file test.cpp
 *@brief test program for querying
 *
 */

 #include "InvertedFileIndex.h"


int main()
{
    // Finish test program here
    InvertedFileIndex SearchEngine;
    SearchEngine.GetStopWord();
    SearchEngine.UpdateIndex();
    std::string str = "highway Gadshill";
    std::vector<std::string> res = SearchEngine.QuerySearch(str, 1.0);
    for(auto it : res){
        std::cout << it << ' ';
    }

    return 0;
}
