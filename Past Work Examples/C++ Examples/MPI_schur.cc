//***************************************************************************
// File: MPI_schur.cc
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
// Counts how many Schur triples there are
// of the form x<y<z <=m such that x+1 mod n = k
// Get's sent m from process 0 via Broadcast!
// Reports its answer to process 0
//
int solve_it(int k, int n, int m) {
  MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD); // Send m to everyone
  int count=0;
  for (int x=1+k;x<=m;x+=n) {
    for (int y=x+1;y<=m;y++) {
      for (int z=y+1;z<=m;z++) {

	if (x + y == z) {
	  count++;
	}
      }
    }
  }
  if (k!=0) {
    MPI_Send(&count,1,MPI_INT,0,0,MPI_COMM_WORLD);
    return 0;
  } else {
    return count;
  }
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
  int res = solve_it(k,n,m);
  if (k==0) {
    // Send m to everyone
    int sum=res;
    int res1=0;
    // Get the answer from everyone
    for (int i=0;i<n;i++) {
      MPI_Recv(&res1,1,MPI_INT,i,0,MPI_COMM_WORLD,NULL);
      sum+=res1;
    }
    cout << sum << endl;
  }
  MPI_Finalize();
}