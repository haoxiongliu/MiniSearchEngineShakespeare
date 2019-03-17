/**
* @file TestProgram.cpp
*
* Test the correctness of the InvertedIndex and QuerySearch.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "stemmer/porter2_stemmer.h"
#include "invertedfileindex.h"
#include <list>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>
#include <set>
#include <dirent.h>
using namespace std;

void InvertedFileIndex::Test(vector<string> res, string query)
{
	stringstream terms;
	string term;
	set<string> termlist;
	set<string> FileList;
	bool term_is_stopword = true;

	for (auto it : res) FileList.insert(it); //Put Filenames into a set for convenience.
	terms << query;
	while (terms >> term) //Get the terms in the query.
	{
		Porter2Stemmer::trim(term);
		Porter2Stemmer::stem(term);
		termlist.insert(term);
	}

	for (auto it_ : termlist) //Test if all terms are in the StopList.
	{
		auto iter = StopWord.find(it_);
		if (iter == StopWord.end())
		{
			term_is_stopword = false;
			break;
		}
	}

	for (auto it : StopWord) termlist.erase(it);

	if (term_is_stopword == true) //If all terms are in the StopList.
	{
		if (res.size() == 0) //If there are no documents retrieved, it is correct.
		{
			cout << "Correct: Query is in StopList or empty, and there are no documents retrieved." << endl;
			return;
		}
		else
		{
			cout << "Error: Query is in StopList or empty, but there are documents retrieved." << endl;
			return;
		}
	}

    std::string Dir = "StemmedShakespeare";
	std::ifstream in;       // in stream
	std::set<string>::iterator it_set;
	bool related_doc;
	for (const auto &filename : Documents) //Go through every document.
	{
		related_doc = false;
		ifstream in(Dir + "\\" + filename);
		while (in >> term) //Go through every term in the document.
		{
			it_set = termlist.find(term);
			if (it_set != termlist.end()) //If term is in termlist, then this filename should be retrieved.
			{
				related_doc = true;
				it_set = FileList.find(filename);
				if (it_set == FileList.end()) //If filename isn't in FileList, it's an error.
				{
					cout << "Error: " << filename << " contain the term " << term
						 << ", but is not retrieved." << endl;
					return;
				}
				break; //Document is relevance and retrieved, so just stop scanning.
			}
		}
		if (related_doc == false) //If no terms in termlist are in this document, this document is irrelevance.
		{
			it_set = FileList.find(filename);
			if (it_set != FileList.end()) //If filename is in FileList, it's an error.
			{
				cout << "Error: Document " << filename << " is retrieved, but in fact it is irrelevance." << endl;
				return;
			}
		}
	}
	cout << "Correct: The documents retrieved are all relevance, and other documents are all irrelevance." << endl;
	return;
}
