// A Basic C++ implementation of Longest Common Subseqence
// Written by David W. Juedes

/*----------------------------------------------------------------------
 * Name: Mark Brown (mb899115)
 * Date: 4/1/2018
 * Description: Transform this code into parallel using OpenMPI
 *
 *----------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <mpi.h>


using namespace std;


// This code checks whether 
// x[i..n-1] a sequence of y[j..m-1], where n is the length of
// x, m is the length of y.
// This is solely used to check the correctness of the solution.

bool Is_subsequence(int i, int j, string &x, string &y) {
	if (i >= x.length()) return true; // Consumed all of x's characters.
	if (j >= y.length()) return false; // Can't consume y's first.

	if (x[i] == y[j]) {
		return Is_subsequence(i + 1, j + 1, x, y);
	}
	else {
		return Is_subsequence(i, j + 1, x, y);
	}
}


int max3(int x, int y, int z) {
	return max(max(x, y), z);
}
int max3_loc(int x, int y, int z) {
	if (max3(x, y, z) == x) return 1;
	if (max3(x, y, z) == y) return 2;
	if (max3(x, y, z) == z) return 3;
}
int max_loc(int x, int y) {
	if (max(x, y) == x) return 1;
	else { return 2; }
}

//
// Recursively construct the longest common subsequence from the dynamic
// programming table "from"
//
string rec_string(string &x1,
	string &y1,
	vector<vector<pair<int, pair<int, int> > > > & from,
	int m,
	int n) {
	pair<int, pair<int, int> > t;
	if (n == 0) return "";
	if (m == 0) return "";
	t = from[m][n];
	if (t.first == 1) {
		assert(x1[m - 1] == y1[n - 1]);
		return rec_string(x1, y1, from, m - 1, n - 1) + x1[m - 1];
	}
	else {
		return rec_string(x1, y1, from, t.second.first, t.second.second);
	}
}

// Compute the longest common subsequence.
int main(int argc, char *argv[]) {
	string x1;
	string y1;
	int n, k;

	vector<vector<int> > LCS;

	char *strX;
	char *strY;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &k);
	
	if (k == 0) {
		if (argc > 0) {
			// MPI send out information
			getline(cin, x1);
			getline(cin, y1);

			strX = new char[x1.length()+1];
			strcpy(strX, x1.c_str());
			strY = new char[y1.length()+1];
			strcpy(strY, y1.c_str());
		}
		else {
			cout << "Error: Not enough arguments provided" << endl;
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
	}

	int buffer[2];

	if (k == 0) {
		buffer[0] = x1.length();
		buffer[1] = y1.length() / n;

		for (int i = 0; i < n; i++) {
			if (i == n - 1)
				buffer[1] += buffer[1] % n;

			MPI_Send(&buffer, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&strX[0], buffer[0], MPI_CHAR, i, 0, MPI_COMM_WORLD);
			MPI_Send(&strY[buffer[1]*i], buffer[1], MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}
	}

	MPI_Recv(&buffer, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	strX = new char[buffer[0]];
	strY = new char[buffer[1]];

	MPI_Recv(&strX[0], buffer[0], MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&strY[0], buffer[1], MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	LCS.resize(buffer[0] + 1);
	if (k == 0) {
		for (int i = 0; i <= buffer[0]; i++)
			LCS[i].resize(buffer[1] + 1);
	}
	else {
		for (int i = 0; i <= buffer[0]; i++)
			LCS[i].resize(buffer[1]);
	}
	
	LCS[0][0] = 0;
	for (int i = 0; i <= buffer[0]; i++) {
		LCS[i][0] = 0;
	}
	if (k == 0) {
		for (int i = 0; i <= buffer[1]; i++) {
			LCS[0][i] = 0;
		}
	}
	else {
		for (int i = 0; i < buffer[1]; i++) {
			LCS[0][i] = 0;
		}
	}

	// Basically make this portion OpenMPI
	int l, prev = 0, prev2 = 0;
	for (int i = 1; i <= buffer[0]; i++) {
		for (int j = 1; j <= buffer[1]; j++) {
			if (k == 0)
				l = j;
			else
				l = j - 1;
			if (l == 0) {
				MPI_Recv(&prev, 1, MPI_INT, k - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(&prev2, 1, MPI_INT, k - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
			else {
				prev = LCS[i][l - 1];
				prev2 = LCS[i - 1][l - 1];
			}
			
			if (j == l) {
				if (strX[i - 1] == strY[l - 1]) {
					LCS[i][l] = max3(prev2 + 1, LCS[i - 1][l],prev); 
				}
				else {
					LCS[i][l] = max(LCS[i - 1][l], prev);
				}
			}
			else {
				if (strX[i - 1] == strY[l]) {
					LCS[i][l] = max3(prev2 + 1, LCS[i - 1][l], prev);
				}
				else {
					LCS[i][l] = max(LCS[i - 1][l], prev);
				}
			}

			if (j == buffer[1] && k != n - 1) {
				MPI_Send(&LCS[i][l], 1, MPI_INT, k + 1, 0, MPI_COMM_WORLD);
				MPI_Send(&LCS[i - 1][l], 1, MPI_INT, k + 1, 0, MPI_COMM_WORLD);
			}

		}
	}
	
	
	if (k == n-1) 
		cout << LCS[buffer[0]][buffer[1]-1] << endl;

	delete[] strX;
	delete[] strY;

	MPI_Finalize();
	return 0;
}