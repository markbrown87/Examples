//***************************************************************************
// File: MPI_pythagorean.cc
// Author: David W. Juedes
// Date: March 1, 2018
// Find the MPI bug, fix it, and solve the problem.
//
//***************************************************************************

#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

//
// Counts how many Pythagorean triples there are
// of the form x<y<z <=m such that x mod n = k
// Get's sent m from process 0!
// Reports its answer to process 0
//
int solve_it(int k, int n) {
  int m;
  
  MPI_Recv(&m,1,MPI_INT,0,0,MPI_COMM_WORLD,NULL);
  int count=0;
  for (int x=1+k;x<=m;x+=n) {
    for (int y=x+1;y<=m;y++) {
      for (int z=y+1;z<=m;z++) {

	long long x1 = x;
	long long y1 = y;
	long long z1 = z;
	if (x1*x1 + y1*y1 == z1*z1) {
	  count++;
	}
      }
    }
  }
  MPI_Send(&count,1,MPI_INT,0,0,MPI_COMM_WORLD);
  return 0;
}


int main(int argc, char *argv[]) {
  int m;
  int k;
  int n;
  if (argc !=2) {
    cout << "Needs at least one argument " << endl;
    exit(-1);
  } else {
    m =atoi(argv[1]);
    cout << m << endl;
  }

  
  MPI_Init(&argc,&argv);

  MPI_Comm_size(MPI_COMM_WORLD,&n);
  MPI_Comm_rank(MPI_COMM_WORLD,&k);
  
  // Send m to everyone
  // This needed to be moved before the if statment. This function is used to
  //   divide up the work so that shouldn't be after the "solve_it" function
  for (int i = 0; i<n; i++) {
	  MPI_Send(&m, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  int res = solve_it(k,n);
  if (k==0) {
    int sum=0;
    int res=0;
    // Get the answer from everyone
    for (int i=0;i<n;i++) {
      MPI_Recv(&res,1,MPI_INT,i,0,MPI_COMM_WORLD,NULL);
      sum+=res;
    }
    cout << sum << endl;
  }
  MPI_Finalize();
}