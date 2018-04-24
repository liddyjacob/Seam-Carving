#pragma once
// A matrix class implemented using vectors.
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
using std::string;
using std::vector;
using std::ostream;
using std::cout;

class MatVect{
public:

  MatVect(size_t len){
    fill(len);
  }

  MatVect(vector<int>& v){ store(v); }

  void fill(size_t len, int val = 0){
    storage.clear();
    storage.resize(len, val);
  }

  void store(vector<int> v){ storage = v; } 

  int& operator[](size_t j){
    if (j >= storage.size() || j < 0){ 
      std::cerr << "Col Index " << j << ": OUT OF RANGE ERROR\n";
      abort();
    }
    return storage[j];
  }

  int get(size_t j) const{ 
    if (j >= storage.size() || j < 0){ 
      std::cerr << "Col Index " << j << ": OUT OF RANGE ERROR\n";
      abort();
    }
    return storage[j];
  }
private:
  vector<int> storage;
};

class Matrix{
public:

  Matrix(size_t n = 0, size_t m = 0){
    num_rows = n;
    num_cols = m;

    for (int i = 0; i < n; ++i){
      MatVect row(m);
      rows.push_back(row);
    }
  }

  Matrix(const Matrix& m2){
    num_rows = m2.nrows();
    num_cols = m2.ncols();

    for (int i = 0; i < num_rows; ++i){
      MatVect row(num_cols);
      rows.push_back(row);
    }

    for (int i = 0; i < m2.nrows(); ++i){
      for (int j = 0; j < m2.ncols(); ++j){
        rows[i][j] = m2.get(i,j);
      }
    }
  }

  MatVect& operator[](size_t i){
    if (i >= num_rows || i < 0){
      std::cerr << "Row Index " << i << ": OUT OF RANGE ERROR\n";
      abort();
    }
    return rows[i];
  }

  int get(size_t i, size_t j) const{ 
    if (i >= num_rows || i < 0){
      std::cerr << "Row Index " << i << ": OUT OF RANGE ERROR\n";
      abort();
    }
    return rows[i].get(j);
  }


  void fill(vector<int>& data){

    if (data.size() != num_rows * num_cols){
      if (data.size() < num_rows * num_cols){
        std::cerr << "ERROR: Not enough data to fill matrix.\n";
        abort();
      } else {
        std::cerr << "WARNING: data size larger than matrix size\n";
      }
    }

    size_t i = 0;
    size_t j = 0;

    for (int& entry : data){
      rows[i][j] = entry; 
      ++j;
      if (j == num_cols){ j = 0; ++i; }
      if (i == num_rows){ break;      }
    }
  }
  
  int nrows() const{ return num_rows; }
  int ncols() const{ return num_cols; }

private:
  vector<MatVect> rows;
  size_t num_rows;
  size_t num_cols; 
};

struct PGMinfo{

  PGMinfo(){}

  Matrix matrix;
  int max_gray;
  string magic_str;
  string comments;
};


void print(Matrix& m, ostream& stream, char sep = '\t'){

  for (int i = 0; i < m.nrows(); ++i){
    for (int j = 0; j < m.ncols(); ++j){
      stream << sep << m[i][j];
    }
    stream << '\n';
  }
}

int abs(int i){ if (i > 0) return i; return -i;}

Matrix diff_matrix(Matrix m){

  //print(m, cout);
  Matrix diffm(m.nrows(), m.ncols());

  for(size_t i = 0; i < m.nrows(); ++i){
    for (size_t j = 0; j < m.ncols(); ++j){
      int diff = 0;
     
      
      if (i != 0){
        diff += abs(m[i][j] - m[i - 1][j]);
      }
      if (i != m.nrows() - 1){
        diff += abs(m[i][j] - m[i + 1][j]);
      }
      if (j != 0){
        diff += abs(m[i][j] - m[i][j - 1]);
      }
      if (j != m.ncols() - 1){
        diff += abs(m[i][j] - m[i][j + 1]);
      }
     diffm[i][j] = diff;
    }
  }
  //print(diffm, cout);
  return diffm;
}
