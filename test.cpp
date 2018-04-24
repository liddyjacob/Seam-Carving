
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


  Matrix energy = diff_matrix(pinfo.matrix);
  std::cout << "----------- ENERGY MATRIX  ------------\n";
  print(energy, std::cout, ' ');


  pgm.close();
  }

  return 0;
}
