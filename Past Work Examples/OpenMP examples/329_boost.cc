//***************************************************************
// File: 329_boost.cc
// Written by David W. Juedes for CS 4000
//
//
// Purpose:  This code solves Project Euler problem #329.
// This code uses the boost library to calculate the gcd of
// two large integers.
// Note: This probably wouldn't need the large integer class.
//
// Task: Use OpenMP to make this code run faster.
//
//*************************************************************

//*************************************************************
// Modified by Mark Brown
// Date: 14/2/2018
// ID: mb899115@ohio.edu
// Description:
//	File is meant to be modified to aid in the learning of
//	how to parallelize code.
//*************************************************************

#include <iostream>
#include <set>
#include <boost/multiprecision/cpp_int.hpp>
#include <omp.h>

using namespace std;
using namespace boost::multiprecision;




bool primes[501];

int main() {

  // calculate the primes up to 500 

  for (int i=2;i<=500;i++) {
    primes[i] = true;
  }
  int next_p = 2;
  primes[1] = false;

  // Sieve of Eratosthenes to calculate primes from 1 to 500.
  bool done = false;
  while (!done){
    for (int j=next_p+next_p;j<=500;j=j+next_p) primes[j]=false;
    next_p++;
    while ((next_p<=500)&&(!primes[next_p])) next_p++;
    if (next_p > 500) done=true;
  }

  
  string croaks = "PPPPNNPPPNPPNPN";
  //  cout << croaks.length() << endl;

  int bits[16];
  
  for (int i=0;i<16;i++) {
    bits[i] = (1<<i);
    //cout << bits[i] << endl;
  }

  //cout << (1<<15) << endl; 

  long long sum_prob = 0;


  //After understanding the code and where the majority of the load (time) is located, I inserted a parallel for here
  //  in hopes to reduce the time to run. Which of course it did.
  #pragma omp parallel for reduction (+:sum_prob)
  for (int i=1;i<=500;i++) {

    // Compute the probability that the frog, starting at position
    // i croaks PPPPNNPPPNPPNPN
    // By trying all possible moves.
    int move[16];

    for (int j=0;j<(1<<15);j++) {
      
      //cout << j << endl;
      for (int k=15;k>=0;k--) {
	if ((bits[k] & (j))>0) {
	  //cout << 1; 
	  move[k]=-1;// Move[k] = -1
	} else {//cout << 0;
	  move[k]=1;} // Move[k]=1
      }
      //cout << endl;
    

      long long prob = 1;
      int cur_loc = i;
      for (int k=0;k<=14;k++) {
	if ((primes[cur_loc])&&(croaks[k]=='P')) {
	  prob=prob*2;
	} 
	if ((!primes[cur_loc])&&(croaks[k]=='N')) {
	  prob=prob*2;
	}
	if (cur_loc == 1) {cur_loc = 2; continue;}
	if (cur_loc == 500) {cur_loc = 499; continue;}
	cur_loc+=move[k];
      }

      sum_prob+=prob;
    }
    //cout << sum_prob << endl;
       

  }
  
  cpp_int num;
  cpp_int den;
  cpp_int gcd_n_d;
  long long d = 235092492288000ll;
  num = sum_prob;
  den = d;
  gcd_n_d = gcd(num,den);

  cout << "Probability = " << sum_prob << "/" << 235092492288000ll << endl;
  //cout << "GCD  = " <<gcd_n_d << endl;
  cout << "Reduced form:" << endl;
  cout << sum_prob/gcd_n_d << "/"<< d/gcd_n_d << endl; 

}

