/*
@file QuerySearch1.0.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "stemmer/porter2_stemmer.h"
#include "invertedfileindex.h"
#include <list>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>
using namespace std;

//term_freq is used to store a term with its postlist.
typedef pair<string, Postlist*> term_postlist;

//CompareTerm is used in std::sort to determine the order of terms.
bool CompareTerm(term_postlist a, term_postlist b)
{
	//Put the term with small frequency in front of large frequency.
	return (a.second->freq < b.second->freq);
}

vector<string> InvertedFileIndex::QuerySearch(string query, float threshold=1.0)
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

	vector<term_postlist> termlist;
	vector<int> doclist, doclist_;
	vector<string> Filenames;
	stringstream terms;
	string term;
	map<string, Postlist*>::iterator it;
	set<string>::iterator iter;
	term_postlist tp;
	int term_num, i, doc_num;

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
			tp.first = it->first;
			tp.second = it->second;
			termlist.push_back(tp);
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
	for (i = 0; i < term_num; ++i)
	{
		//doclist_ is used because the result of the intersection of two vectors must be stored in
		//a new vector.
		set_intersection(termlist[i].second->docID.begin(), termlist[i].second->docID.end(), 
			             doclist.begin(), doclist.end(), doclist_);
		doclist = doclist_;
	}

	//Turn the DocID into it's filename and store it in Filenames.
	doc_num = doclist.size();
	for (i = 0; i < doc_num; ++i)
	{
		Filenames[i] = Documents[doclist[i]];
	}

	return Filenames;
}