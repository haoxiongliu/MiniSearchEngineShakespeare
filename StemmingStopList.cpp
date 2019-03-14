/**
 * @file StemmingStopList.cpp
 *
 * transfer
 */

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "stemmer/porter2_stemmer.h"
#include "invertedfileindex.h"

namespace fs = std::filesystem;

std::string getFileName(const std::string& s) {

   char sep = '/';

#ifdef _WIN32
   sep = '\\';
#endif

   size_t i = s.rfind(sep, s.length());
   if (i != std::string::npos) {
      return(s.substr(i+1, s.length() - i));
   }

   return("");
}


bool InvertedFileIndex::GetStopWord(){
        
    std::string OriDir = "ShakespeareComplete";
    std::string DstDir = "StemmedShakespeare";
    
    
    std::ifstream in;
    std::ofstream out;
    std::string filename;
    std::string to_stem;
    
    for(auto & entry : fs::directory_iterator(OriDir)){
        in = entry.path();
        filename = getFileName(in);
        out = DstDir + "/" + filename;
        while(in >> to_stem){
            Porter2Stemmer::trim(to_stem);
            Porter2Stemmer::stem(to_stem);
            
            // deal with stop word
            
            out << to_stem << ' ';
        }
        InvertedFileIndex::Documents.push_back(filename);
    }

    // deal with stop word

    return true;
}
