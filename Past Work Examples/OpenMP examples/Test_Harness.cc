// ***************************************************************
// File:Test_Harness.cc
// Purpose: Tests sequential class for CS 4000
//
// Compile: g++ Test_Harness.cc
// Written by: David W. Juedes
// Date: January 30, 2018
// ***************************************************************
#include <iostream>
#include <string>

#include "SeqCounting.cc"

int main() {
  SeqCounting obj;
  string line;
  while (!cin.eof()) {
    getline(cin,line);
    if (!cin.fail()) {
      cout << "Formula: : " << line << endl;
      cout << "Number of Satisfying Assignments = " << obj.SatisfyingAssignments(line) <<endl;
    }
  }
}
