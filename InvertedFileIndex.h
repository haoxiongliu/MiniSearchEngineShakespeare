#ifndef __INVERTEDFILEINDEX_H__
#define __INVERTEDFILEINDEX_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

struct Occurence
{
    std::string DocID;
    int times;
};

class InvertedFileIndex
{
public:
    InvertedIndex();      
    bool GetStopWord();                         // Run a word count and identify the stop words
    bool GetSynonym();                          // Map all the synonyms into the map Synonym
    bool UpdateIndex();                         // Create inverted index over the Shakespeare set with word stemming.
                                                // The stop words in the set Stopword must not be included.
    void CompressIndex();
    std::string QuerySearch(std::string query);
    ~InvertedIndex();
private:
    typedef std::vector<Occurence> WordInfo;
    std::map<std::string, WordInfo> InvertedIndex;
    std::map<std::string, std::string> Synonym;
    std::set<std::string> StopWord;
};

#endif




































string word;

while ( all the word ){
    if (exclude.find(word) == exclude.end())
        Put the word into the map
}