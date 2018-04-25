
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using std::fill;
using std::cout;
using std::vector;
using std::ifstream;

#include "matrix.hpp"
#include "pgm2matrix.hpp"
#include "seam.hpp"


int main(){
  {
  Matrix m(3,5);
  m[1][4] = 3;
  std::cout << "m[1][4] = " << m[1][4] << '\n';
  }

  {
  vector<int> matrixdata(36);
     std::fill(matrixdata.begin(), matrixdata.end(), 2);

  Matrix m(6,6);
    m.fill(matrixdata);
    m[3][4] = -18;

  Matrix n(4, 9);
    n.fill(matrixdata);
    n[1][8] = 133;

  Matrix q(3,3);
    q.fill(matrixdata);
    q[1][1] = 1;

  std::cout << "----------- MATRIX m ------------\n";
  print(m, std::cout);

  std::cout << "----------- MATRIX n ------------\n";
  print(n, std::cout);
 
  std::cout << "----------- MATRIX q ------------\n";
  print(q, std::cout);
 
  }

  {
  ifstream pgm;
    pgm.open("tset.pgm");

  PGMinfo pinfo = pgm2matrix(pgm);

  std::cout << "----------- BUG MATRIX  ------------\n";
  print(pinfo.matrix, std::cout, ' ');

  transpose(pinfo.matrix);
  std::cout << "----------- TRANSPOSED BUG MATRIX  ------------\n";
  print(pinfo.matrix, std::cout, ' ');



  Matrix energy = diff_matrix(pinfo.matrix);
  std::cout << "----------- ENERGY^T MATRIX  ------------\n";
  print(energy, std::cout, ' ');


  pgm.close();
  }
  {
 vector<int> matrixdata(36);
     std::fill(matrixdata.begin(), matrixdata.end(), 2);


  Matrix n(4, 9);
    n.fill(matrixdata);
    n[1][8] = 133;

  std::cout << "----------- MATRIX n ------------\n";
  print(n, std::cout);
 

  transpose(n);

  std::cout << "----------- MATRIX n^t ------------\n";
  print(n, std::cout);
 
  transpose(n);

  std::cout << "----------- MATRIX n^t^t ------------\n";
  print(n, std::cout);
  }

  {
  vector<int> matrixdata(36);
     std::fill(matrixdata.begin(), matrixdata.end(), 2);

  ifstream pgm;
    pgm.open("tset.pgm");

  PGMinfo pinfo = pgm2matrix(pgm);
  seamcarve(pinfo.matrix, ROWS);
  seamcarve(pinfo.matrix, COLS);

  std::cout << "--------- SHORTEST PATH ON TEST.PGM ---------------\n";
  for (int& i : shortest_path(pinfo.matrix)){
   std::cout << i << '\n';
  }

  pgm.close();
  }
 
  {
  std::cout << " == Excel Test == \n";

  ifstream pgm("exel.pgm");
  PGMinfo pinfo = pgm2matrix(pgm);
  pgm.close();

  std::cout << "Collected Matrix: \n";
  print(pinfo.matrix, std::cout);

  std::cout << "Removing vertical seam: \n";
  seamcarve(pinfo.matrix, ROWS);
  print(pinfo.matrix, std::cout);
  }
  {
  std::cout << " == Excel Test == \n";

  ifstream pgm("exel.pgm");
  PGMinfo pinfo = pgm2matrix(pgm);
  pgm.close();

  std::cout << "Collected Matrix: \n";
  print(pinfo.matrix, std::cout);

  std::cout << "Removing horizontal seams: \n";
  seamcarve(pinfo.matrix, COLS);
  seamcarve(pinfo.matrix, COLS);

  print(pinfo.matrix, std::cout);
  }
  
  return 0;
}
