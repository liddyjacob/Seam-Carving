//Find the minimum path in specified direction;
//
#pragma once
#include "pgm2matrix.hpp"
#include "matrix.hpp"
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::vector;

enum VectorType{ ROWS, COLS };

// IF type is row, remove 1 from each row.
// If type is col, remove 1 from eac col.
// Decreases nrows or ncols by one.
//
void seamcarve(Matrix& m, VectorType type){

  if (type == COLS){transpose(m);} 

  vector<int> path = shortest_path(diff_matrix(m));
  //assert(path.size() == m.ncols());
  
  for (int n = 0; n < path.size(); ++n){
    m.shrink_row(n, path[n]);
  }
  m.adjust();

  if (type == COLS){transpose(m);}
  
  //print(m, std::cout);
  return;
}

void carve(string filename, int vseams, int hseams){
  
  vector<string> fname_parts = split(filename, '.');
  if (fname_parts.back() != "pgm") { 
    std::cerr << "Error: File extension is not pgm\n";
    return;
  }
  
  ifstream pgm;
    pgm.open(filename.c_str());

  if (!pgm.is_open()){
    std::cerr << "Error: File Refused to Open.\n";
    return;
  }

  PGMinfo pinfo = pgm2matrix(pgm);

  pgm.close();

  for (int v = 0; v < vseams; ++v){seamcarve(pinfo.matrix, ROWS);}
  for (int h = 0; h < hseams; ++h){seamcarve(pinfo.matrix, COLS);}

  fname_parts.pop_back();
  fname_parts.back() +="_processed";
  fname_parts.push_back("pgm");

  string newfilename;
  for (string& part : fname_parts){
    newfilename += part + '.';
  }
  newfilename.pop_back();

  ofstream carved(newfilename.c_str());

  carved << pinfo.magic_str << '\n';
  carved << pinfo.comments;// << '\n';
  carved << pinfo.matrix.ncols() << ' ' << pinfo.matrix.nrows() << '\n';
  carved << pinfo.max_gray << '\n';
  print(pinfo.matrix, carved, ' ');
}


