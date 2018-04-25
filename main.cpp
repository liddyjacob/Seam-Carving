


#include "seam.hpp"
#include <string>
using std::string;
int main(int argc, char** argv){

  if (argc != 4){
    std::cerr << "Usage: ./seam (filename) <#vseams> <#hseams>\n"
         << "\tExample: /seam bug.pgm 14 0\n";
    return -1;
  }

  string filename(argv[1]);
  int vseams = atoi(argv[2]);
  int hseams = atoi(argv[3]);

  carve(filename, vseams, hseams);

  return 0;
}
