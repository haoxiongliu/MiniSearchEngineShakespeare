/**
 *@file InvertedFileIndex.cpp
 *@brief Implement Inverted index.
 *
 */

#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "InvertedFileIndex.h"
using namespace std;

InvertedFileIndex::~InvertedFileIndex(){
    return;
}

/************************************************************************* 
 -  Function:       UpdateIndex
 -  Description:    Build the inverted index according to the stemmed 
                    documents and store the inverted index in the map
                    InvertedIndex
 -  Input:          \
 -  Output:         \
************************************************************************/
bool InvertedFileIndex::UpdateIndex()
{
    string word;
    string dirname = "StemmedShakespeare";
    int docID = 0;
    for (const auto &doc : Documents)
    {   //open every file
        ifstream ShakespearFile(dirname + "\\" + doc);
        if (ShakespearFile.is_open()){
            while (ShakespearFile >> word){
                // Handle all the words in one document
				if (StopWord.find(word) == StopWord.end())
                // If the word is not a stop word, insert the word into the map;
                    InsertWord(word, docID);
            }
        }// End of file
        else cout << "open file " << doc << "failed" << endl;
        docID ++;
    }
    return true;
}
/************************************************************************* 
 -  Function:       InsertWord
 -  Description:    Insert a word into the map InvertedIndex.
 -  Input:          param1: the word to be inserted
                    param2: the document ID
 -  Output:         \
************************************************************************/

void InvertedFileIndex::InsertWord(string word, int docID)
{
    auto map_it = InvertedIndex.find(word);
    if (map_it == InvertedIndex.cend()){
        // If the word is not included in the map, insert a new key
        PostList *p = new PostList();
        (*p).freq = 1;
        (*p).docID.push_back(pair<int, int>(docID, 1));
        InvertedIndex.insert(pair<std::string, PostList*>(word, p));
    }else{
        // If the word is already included in the map, update the PostList
        if (map_it->second->docID.back().first == docID){
            // If there is already the same word in this document
            (*(map_it->second)).docID.back().second ++;
        }else{
            // If the word hasn't appeared in this doc yet
            (*(map_it->second)).freq ++;
            (*(map_it->second)).docID.push_back(pair<int, int>(docID, 1));
        }
    }
    return;
}
