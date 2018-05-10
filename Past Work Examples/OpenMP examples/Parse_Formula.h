#ifndef Parse_Formula_DWJ
#define Parse_Formula_DWJ
//****************************************************************
//
//File: Parse_Formula.h
//Author: David W. Juedes
//Purpose: This file is a recursive descent parser that
//reads/creates a boolean formula
//
//********************************************************
#include "Clauses.h"
#include "Tokenizer.h"

boolean_formula *read_formula(map<string,int> &var_nums,
			      vector<string> & names,
			      Tokenizer_dwj &my_tokenizer) {
  
  token_type t;
  string z;
  boolean_formula *left;
  boolean_formula *right;
  bool and_or;
  t=my_tokenizer.next_token();
  switch (t) {
  case VAR_T:
    
    z=my_tokenizer.token_string();
    if (var_nums.count(z)==0) {
      var_nums[z]=names.size();
      names.push_back(z);
    }
    my_tokenizer.get_next_token(cin);
    return new variable(var_nums[z]);
    break;
  case NOT_T:
    // Consume the token
    my_tokenizer.get_next_token(cin);
    return new NOT_F(read_formula(var_nums,names,my_tokenizer));
    break;
  case LEFT_T:
    // Consume it.
    my_tokenizer.get_next_token(cin);

    left = read_formula(var_nums,names,my_tokenizer);
    t=my_tokenizer.next_token();
    and_or =false;
    if (t==AND_T) {
      and_or = true;
    } else {
      if (t==OR_T) {
	and_or = false;
      } else {
	cout << "Parse error --- expected + or | " << endl;
	return NULL;
      }
    }
    // Consume + or |
    my_tokenizer.get_next_token(cin);
    right = read_formula(var_nums,names,my_tokenizer);
    t=my_tokenizer.next_token();
    if (t==RIGHT_T) {
      my_tokenizer.get_next_token(cin);
      if (and_or) {
	return new AND_F(left,right);
      } else {
	return new OR_F(left,right);
      }
    } else {
      cout << "ERROR --- expected )" << endl;
      cout << "Saw " << my_tokenizer.token_string() << endl;
      return NULL;
    }
  default: cout << "Error --- Saw " << my_tokenizer.token_string() << endl;
    return NULL;
  }
}

#endif

