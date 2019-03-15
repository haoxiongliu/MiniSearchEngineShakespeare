#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "InvertedFileIndex.h"
using namespace std;

InvertedFileIndex::InvertedFileIndex(){
    return;
}

InvertedFileIndex::~InvertedFileIndex(){
    return;
}

bool InvertedFileIndex::UpdateIndex()
{
    string word;
    string dirname = "StemmedShakespeare";
    int docID = 0;
    for (const auto &doc : Documents)
    {
        ifstream ShakespearFile(dirname + "\\" + doc);
        if (ShakespearFile.is_open()){
            while (ShakespearFile >> word){
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

void InvertedFileIndex::InsertWord(string word, int docID)
{
    auto map_it = InvertedIndex.find(word);
    if (map_it == InvertedIndex.cend()){
        // If the word is not included in the map, insert a new key
        PostList *p = new PostList();
        (*p).freq = 1;
        (*p).docID.push_back(docID);
        InvertedIndex.insert(pair<std::string, PostList*>(word, p));
    }else{
        // If the word is already included in the map, update the PostList
		(*(map_it->second)).freq ++;
        (*(map_it->second)).docID.push_back(docID);
    }
    return;
}
