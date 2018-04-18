#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ifstream;

#include "matrix.hpp"

std::vector<std::string> split(const std::string& s, char delim){

  std::vector<std::string> toks;
  std::string tok;
  std::istringstream tokstream(s);
  
  while (std::getline(tokstream, tok, delim)){

    toks.push_back(tok);

  }

  return toks;
}


bool isMagicNumber(string line){

return true;
}
bool isComment(string line){

return true;
}
bool isDimensions(string line){

return true;
}
bool isMaxGrey(string line){
   
return true;
}
PGMinfo pgm2matrix(ifstream& file){

  string line, mgc_str, dim_str, gray_str;

  while (getline(file, line)){
    if (line.back() == '\r'){line.pop_back();}
    if (isMagicNumber(line)) { mgc_str = line; }
    if (isComment(line)) { continue; }
    if (isDimensions(line)) { dim_str = line; }
    if (isMaxGrey(line)) { gray_str = line; break; } 
  }

  PGMinfo pinfo;
  if (mgc_str.size() == 0){
    std::cerr << "No magic number in file!\n";
    abort();
  }

  if (dim_str.size() == 0 ){
    std::cerr << "No dimension in file!\n";
    abort();
  }
  return pinfo;
}

