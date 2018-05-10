#include <iostream>

//#include <mpi.h>

using namespace std;



// Count the number of triples x, y, z such that
// x + y = z for x < y < z and
// 1<= x,y,z <= 10,000

int main(int argc, char *argv[]) {
  int m;
  if (argc !=2) {
    cout << "Needs at least one argument " << endl;
    exit(-1);
  } else {
    m =atoi(argv[1]);
    cout << m << endl;
  }
  
  long long count = 0;
  
  for (int x=1;x<=m;x++) {
    for (int y=x+1;y<=m;y++) {
      for (int z=y+1;z<=m;z++) {

	long long x1 = x;
	long long y1 = y;
	long long z1 = z;
	if (x1 + y1 == z1) {
	  count++;
	}
      }
    }
  }
  cout << count << endl;
}