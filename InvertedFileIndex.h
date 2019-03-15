#ifndef __INVERTEDFILEINDEX_H__
#define __INVERTEDFILEINDEX_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <utility>
#include <algorithm>

class PostList
{
public:
    friend class InvertedFileIndex;
    PostList():freq(0),docID(0){};
    ~PostList(){};
public:
    int freq;
    std::vector<int> docID;                     // Documents[docID] is the filename
};


class InvertedFileIndex
{
public:
	InvertedFileIndex() {};
    bool GetStopWord();                         // Run a word count and identify the stop words
    bool UpdateIndex();                         // Create inverted index over the Shakespeare set with word stemming.
                                                // The stop words in the set Stopword must not be included.
    void InsertWord(std::string word, int docID);
//    void CompressIndex();  Compress 先直接不做了，解决完第二个版本看时间再考虑
    std::vector<std::string> QuerySearch(std::string query, float threshold); // return names of the files containing the query after thresholding
	~InvertedFileIndex();
//private:
    std::map<std::string, PostList*> InvertedIndex;
    std::set<std::string> StopWord;             // Updated by GetStopWord()
    std::vector<std::string> Documents;              // Updated by GetStopWord()
};

#endif