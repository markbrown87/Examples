#ifndef Clauses_DWJ
#define Clauses_DWJ

//*********************************************************
//
// File: Clauses.h
// Author: David W. Juedes
// Date: Jan. 30th, 2018
// Purpose: This file defines a class hierarchy for boolean formula for HW #1.
// 
//*********************************************************
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <cassert>
//#include <string>

using namespace std;

enum node_types {AND_node,OR_node,Var_node,Not_node};

//
// The abstract class boolean formula
//
class boolean_formula {
 public:
  virtual void print_it(vector<string> & names) = 0;
  virtual bool evaluate_it(vector<bool> &truth_assignment) = 0;
};

//
// The class of a single variable
//
class variable:public boolean_formula {
 public:
  int var_num;
  // Constructor
  variable(int n) {
    var_num=n;
  }

  virtual void print_it(vector<string> & names) {
    cout << names[var_num];
  }
  virtual bool evaluate_it(vector<bool> &truth_assignment) {
    return truth_assignment[var_num];
  }
};

//*************************************************************************
//Not formula
//*************************************************************************

class NOT_F:public boolean_formula {
 public:
  boolean_formula *F;
  NOT_F(boolean_formula *Q) {
    F=Q;
  }
  virtual void print_it(vector<string> &names) {
    cout << "-";
    F->print_it(names);
  }
  virtual bool evaluate_it(vector<bool> &truth_assignment) {
    return !F->evaluate_it(truth_assignment);
  }

  boolean_formula *base;
};

//**************************************************************
//   And Class
//**************************************************************
class AND_F:public boolean_formula {
 public:
  boolean_formula *left;
  boolean_formula *right;
  // Constructor!
  AND_F(boolean_formula *l, boolean_formula *r) {
    left= l;
    right = r;
  }
  // Standard functions
  virtual void print_it(vector<string> &names) {
    //cout << "Got to here " << endl;
    cout << "(";
    left->print_it(names);
    cout << "+";
    right->print_it(names);
    cout <<")";
  }
  
  virtual bool evaluate_it(vector<bool> &truth_assignment) {
    //bool truth=true;
    return left->evaluate_it(truth_assignment) & right->evaluate_it(truth_assignment);
  }
  

};

//*******************************************************
// OR Node
//*******************************************************
class OR_F:public boolean_formula {
 public:
  boolean_formula *left;
  boolean_formula *right;
  OR_F(boolean_formula *l,boolean_formula *r) {
    left=l;right=r;
  }
  virtual void print_it(vector<string> &names) {
    cout << "(";
    left->print_it(names);
    cout << "|";
    right->print_it(names);
    cout << ")";
  }
  virtual bool evaluate_it(vector<bool> &truth_assignment) {
    
    return left->evaluate_it(truth_assignment) | right->evaluate_it(truth_assignment);
  }
  
};

#endif

  
  
