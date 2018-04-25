#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

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
bool isInt(string line){
  for (char& c : line){
    if (!isdigit(c)){ return false;}
  }
  return true;
}

bool isMagicNumber(string line){
  if (line.size() != 2) {return false;}
  if (line[0] != 'P') {return false;}
  if (!isdigit(line[1])){ return false;}
  
  return true;
}
bool isComment(string line){
  if (line.front() == '#') return true;

return false;
}
bool isDimensions(string line){
  vector<string> toks = split(line, ' ');
  if (toks.size() != 2) return false;
  if (!isInt(toks[0])) return false;
  if (!isInt(toks[1])) return false;
  return true;
}
bool isMaxGrey(string line){
  if (isInt(line)) return true;
  return false;
}

PGMinfo pgm2matrix(ifstream& file){

  string line, mgc_str, dim_str, gray_str, comments;

  while (getline(file, line)){
    if (line.back() == '\r'){line.pop_back();}
    if (isMagicNumber(line)) { mgc_str = line; }
    if (isComment(line)) { comments += (line + '\n'); }
    if (isDimensions(line)) { dim_str = line; }
    if (isMaxGrey(line)) { gray_str = line; break; } 
  }

  vector<int> data;
  int value;
  while (file >> value){
    data.push_back(value);
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

  if (gray_str.size() == 0){
      std::cerr << "No max gray value in file\n";
      abort();
  }



  pinfo.comments = comments;
  pinfo.magic_str = mgc_str;
  pinfo.dim_str = dim_str;
  pinfo.max_gray = atoi(gray_str.c_str());
  vector<string> ji = split(dim_str, ' ');
    size_t x = atoi(ji[1].c_str() );
    size_t y = atoi(ji[0].c_str() );

  pinfo.max_gray = atoi(gray_str.c_str() );

  Matrix m(x, y);
    m.fill(data);

  pinfo.matrix = m;
    return pinfo;
}

