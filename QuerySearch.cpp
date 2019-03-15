/**
 *@file QuerySearch1.0.cpp
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
using namespace std;

//term_freq is used to store a term with its PostList.
typedef pair<string, PostList*> term_PostList;

//CompareTerm is used in std::sort to determine the order of terms.
bool CompareTerm(term_PostList a, term_PostList b)
{
	//Put the term with small frequency in front of large frequency.
	return (a.second->freq < b.second->freq);
}

vector<string> InvertedFileIndex::QuerySearch(std::string& query, float threshold=1.0)
{
	/*
	QuerySearch was used to doing the index for the documents which contain terms in the query.

	input:
	string query: Query contains one or several words which the user want to index. If there
	              are several words in the query, there should be a space between different words.
	float threshould: Threshold is used to determine how many terms in query should be used to index.
	                  It should be in the range of (0, 1]. The default number here is 1.0.

	output:
	vector<string> Filenames: The result of the index is stored in a list of filenames.
	*/

	vector<term_PostList> termlist;
	vector<string> Filenames;
	stringstream terms;
	string term;
	map<string, PostList*>::iterator it;
	set<string>::iterator iter;
	term_PostList* tp;
	int term_num, i;

	//First we turn the query into seperate terms which are stemmed and not in StopWord,
	//terms and their freqquency will be stored in termlist.
	terms << query;
	while (terms >> term)
	{
		//Stem the term.
		Porter2Stemmer::trim(term);
		Porter2Stemmer::stem(term);

		//Check if the term is in StopWord. If the term is in StopWord, just leave
		//this term and get next one.
		iter = StopWord.find(term);
		if (iter != StopWord.end()) continue;

		//Find this term in InvertedIndex. If this term is in InvertedIndex, insert it into termlist.
		it = InvertedIndex.find(term);
		if (it != InvertedIndex.end())
		{
		    tp = new term_PostList();
			tp->first = it->first;
			tp->second = it->second;
			termlist.push_back(*tp);
		}
	}

	//Report an error if there is no term in the termlist.
	if (termlist.size() == 0)
	{
		cout << "Can't find query in the documents, please change the query and try again."
			 << endl;

		//Return an empty vector.
		return Filenames;
	}

	//Sort the term list according to frequency of every term.
	sort(termlist.begin(), termlist.end(), CompareTerm);

	//Calculate how many terms would be used in index.
	term_num = int(termlist.size() * threshold);

	//In case that term = 0.
	if (term_num == 0) term_num++;

	//Get intersection bewteen documents containing selected terms. Here use set_intersection to
	//achieve it.
	set<int> doclist(termlist[0].second->docID.begin(), termlist[0].second->docID.end());    // initialization !
	for (i = 1; i < term_num; ++i)
	{
		auto p = new set<int>;
		set_intersection(termlist[i].second->docID.begin(), termlist[i].second->docID.end(),
			             doclist.begin(), doclist.end(), insert_iterator<set<int>>(*p, (*p).begin()));
		doclist = *p;
		delete p;
	}

	//Turn the DocID into it's filename and store it in Filenames.
	for (auto it_doc : doclist)
	{
		Filenames.push_back(Documents[it_doc]);
	}

	return Filenames;
}
