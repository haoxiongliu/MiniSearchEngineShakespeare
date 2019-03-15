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
	std::string OriDir = "ShakespeareComplete"; // Original text
	std::string DstDir = "StemmedShakespeare";  // Stemmed text

	// create a directory
    std::string command = "mkdir " + DstDir;
    system(command.c_str());

    // open the original directory
    DIR *dir;
    struct dirent *entry;
    if((dir = opendir(OriDir.c_str())) == NULL){
        std::cout << "Directory open failed" << std::endl;
        return false;
    }

    std::ifstream in;       // in stream
	std::ofstream out;      // out stream
	std::string filename;
	std::string to_stem;
	std::map<std::string, int> term_freq;   // collection frequency
	int doc_num = 0;
	while((entry = readdir(dir)) != NULL) {
        filename = entry->d_name;
        if(filename == "." || filename == "..") continue;
		out.open(DstDir + "\\" + filename);
		in.open(OriDir + "\\" + filename);

		while (in >> to_stem) {
			Porter2Stemmer::trim(to_stem);
			Porter2Stemmer::stem(to_stem);

            if(to_stem == "") continue;
            term_freq[to_stem]++;

			out << to_stem << ' ';
		}
		in.close();
		out.close();
		InvertedFileIndex::Documents.push_back(filename);
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
    for(std::vector<pair>::iterator it = vec_tf.begin(); it != vec_tf.end(); ++it){
    //  if(it->second > 3*doc_num){  for arbitrary collections of documents   
        if(it->first != "henri"){   // for Shakespeare Complete Works
            StopWord.insert(it->first);
        }
        else break;
    }
    std::cout << "Word Count Finished" << std::endl;

	return true;
}
