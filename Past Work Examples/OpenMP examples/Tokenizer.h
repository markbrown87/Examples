#ifndef Tokenizer_DWJ
#define Tokenizer_DWJ

#include <iostream>
#include <regex>
#include <string>

using namespace std;

enum token_type {AND_T, OR_T, NOT_T, VAR_T, LEFT_T, RIGHT_T,EOF_T,ERROR_T,NONE_T};

class Tokenizer_dwj {
 public:
  string line;
  token_type t;
  string stored_string;
  
  //regex test_pattern("Test");
  
  void get_next_token(istream &in) {
    regex and_pattern("[+]");
    regex or_pattern ("[|]");
    regex not_pattern("[-]");
    regex var_pattern ("[a-zA-Z][a-zA-Z0-9]*");
    regex left_pattern ("[(]");
    regex right_pattern ("[)]");
    smatch s;
    if (line.length()==0) {
      getline(in,line);
      if (!in.fail()) {
	strip_whitespace();
      } else {
	t=EOF_T;
	return;
      }
    }
    //cout << "Here!" << endl;
    // int first;
    int last;
    int my_last;
    t = NONE_T;
    my_last=0;
    if (regex_search(line,s,and_pattern)) {
      if (s.position() == 0) {
	t = AND_T;
	my_last= s.str().length();
	stored_string = s.str();
	
      }
    } 
    if (regex_search(line,s,or_pattern)) {
      if (s.position() == 0) {
	t = OR_T;
	my_last= s.str().length();
	stored_string = s.str();
      }
    } 
    if (regex_search(line,s,not_pattern)) {
      if (s.position() == 0) {
	t = NOT_T;
	my_last= s.str().length();
	stored_string = s.str();
      }
    } 
    if (regex_search(line,s,left_pattern)) {
      if (s.position() == 0) {
	t = LEFT_T;
	my_last= s.str().length();
	stored_string = s.str();
      }
    }
    if (regex_search(line,s,right_pattern)) {
      if (s.position() == 0) {
	t = RIGHT_T;
	my_last= s.str().length();
	stored_string = s.str();
      }
    }
    if (regex_search(line,s,var_pattern)) {
      //cout << "Worked -- Var" <<endl;
      if (s.position() == 0) {
	last = s.str().length();
	if (last > my_last) {
	  t = VAR_T;
	  my_last= last;
	  stored_string = s.str();
	}
      }
    }
    if (t==NONE_T) {
      t=ERROR_T;
    } else {
      line.erase(0,my_last);
      strip_whitespace();
    }
    //cout << t << endl;
    //cout << stored_string << endl;
    //cout << my_last << endl;
    //cout << line << endl;
  }
  

  void strip_whitespace() {
    bool done=false;
    while ((line.length()!=0)&&(!done)) {
      if (isspace(line[0])) {
	line.erase(0,1);
      } else {
	done=true;
      }
    }
    //cout << "Done here!" << endl;
  }
  void init_it(istream &in)
  {
    string l1;
    //cout << "Test 1" << endl;
    getline(in,l1);
    line=l1;
    //cout << "****"  << endl;
    //cout << l1 << endl;
    if (in.fail()) {
      t=EOF_T;
      return;
    }
    //cout << "**" <<endl;
    strip_whitespace();
    get_next_token(in);
  }
  token_type next_token() {
    return t;
  }

  string token_string() {
    return stored_string;
  }
};

  
#endif
