/**
 * @file StemmingStopList.cpp
 *
 * Implement stemming and choosing stop list.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <string>
#include <dirent.h>
#include <direct.h>
#include <algorithm>
#include "stemmer/porter2_stemmer.h"
#include "invertedfileindex.h"

namespace
{
bool CompareTermFreq(std::pair<std::string, int> a, std::pair<std::string, int> b)
{
	//Put the term with small frequency in front of large frequency.
	return (a.second > b.second);
}
}

bool InvertedFileIndex::GetStopWord()
{
	// if there is already a stop word list and a document list, restore them
	std::string StopWordFile("StopWordList.txt");
	std::string FilenamesFile("FilenamesList.txt");
	std::ifstream StopWordIn(StopWordFile);
	std::ifstream FilenamesIn(FilenamesFile);
	if(StopWordIn.is_open() && FilenamesIn.is_open())
    {
        // restore stop word list
        std::string term;
        while(StopWordIn >> term)
        {
            StopWord.insert(term);
        }

        // restore document list
        std::string filename;
        while(FilenamesIn >> filename)
        {
            Documents.push_back(filename);
        }
        StopWordIn.close();
        FilenamesIn.close();
        return true;
	}

    // otherwise, do word count and get stop word list from text in the Oridir
	std::string OriDir = "ShakespeareComplete"; // Original text
	std::string DstDir = "StemmedShakespeare";  // Stemmed text

	// create a directory
    std::string command = "mkdir " + DstDir;
    system(command.c_str());

    // open the original directory
    DIR *dir;
    struct dirent *entry;
    if((dir = opendir(OriDir.c_str())) == NULL)
    {
        std::cout << "Directory open failed" << std::endl;
        return false;
    }

    std::ifstream in;       // in stream
	std::ofstream out;      // out stream
	std::string filename;
	std::string to_stem;
	std::map<std::string, int> term_freq;   // collection frequency
	int doc_num = 0;
	std::ofstream FilenamesOut(FilenamesFile);
	while((entry = readdir(dir)) != NULL)
    {
        filename = entry->d_name;
        if(filename == "." || filename == "..") continue;
		out.open(DstDir + "\\" + filename);
		in.open(OriDir + "\\" + filename);

		while (in >> to_stem)
        {
            // stem the word
			Porter2Stemmer::trim(to_stem);
			Porter2Stemmer::stem(to_stem);

            // if the term becomes "" after stemming, omit it
            if(to_stem == "") continue;
            term_freq[to_stem]++;

            // write to the corresponding destination file in DstDir
			out << to_stem << ' ';
		}
		in.close();
		out.close();

        // store the list in FilenamesFile
		InvertedFileIndex::Documents.push_back(filename);
		FilenamesOut << filename << ' ';

		doc_num++;
	}

	typedef std::pair<std::string, int> pair;

	// deal with stop word
	// create a vector to do sorting
    std::vector<std::pair<std::string, int>> vec_tf;
    std::copy(term_freq.begin(), term_freq.end(),
              std::back_inserter<std::vector<pair>>(vec_tf));
    term_freq.clear();

    // sort
    std::sort(vec_tf.begin(), vec_tf.end(), CompareTermFreq);
    std::ofstream StopWordOut(StopWordFile);
    for(std::vector<pair>::iterator it = vec_tf.begin(); it != vec_tf.end(); ++it)
    {
        // if(it->second > 3*doc_num)  // for arbitrary collections of documents
        if(it->first != "henri") // for Shakespeare Complete Works
        {
            StopWord.insert(it->first);
            StopWordOut << it->first << ' ';
        }
        else break;
    }
    std::cout << "Word Count Finished" << std::endl;

	return true;
}
