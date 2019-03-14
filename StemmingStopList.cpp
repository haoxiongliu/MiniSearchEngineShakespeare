/**
 * @file StemmingStopList.cpp
 *
 * Implement stemming and choosing stop list.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <direct.h>
#include "stemmer/porter2_stemmer.h"
#include "invertedfileindex.h"


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
	while((entry = readdir(dir)) != NULL) {
        filename = entry->d_name;
		out.open(DstDir + "\\" + filename);
		in.open(OriDir + "\\" + filename);

		while (in >> to_stem) {
			Porter2Stemmer::trim(to_stem);
			Porter2Stemmer::stem(to_stem);

			out << to_stem << ' ';
		}
		in.close();
		out.close();
		InvertedFileIndex::Documents.push_back(filename);
	}

	// deal with stop word

	return true;
}

InvertedFileIndex::InvertedFileIndex(){
    return;
}

InvertedFileIndex::~InvertedFileIndex(){
    return;
}
