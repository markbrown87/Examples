///<summary>
/// Name: Mark Brown
///	Date: 3/2/2018
/// Description: Counts the number of complete true statements provided via the test_harness input
///    then returns the number of true statements.  
///	Credit: Dr. David Juedes provided all files for testing this. The code below has been modified by 
///		me (Mark Brown) but all rights are reserved for Dr. David Juedes.
///
///</summary>


#include "Tokenizer.h"
#include "Clauses.h"
#include "Parse_Formula.h"
#include <sstream>
#include <bitset>
#include <math.h>
using namespace std;


class SeqCounting {
public:
  int SatisfyingAssignments(string formula) {
    istringstream in(formula);
    Tokenizer_dwj my_tokenizer;
    my_tokenizer.init_it(in);
    vector<string> names;
    map<string,int> my_map;
    boolean_formula *x;
	bitset<16> truth_bitset;
	vector<bool> truth_assign;
	int count = 0;
	
    x = read_formula(my_map,names,my_tokenizer);
	
	//sets truth_assignt to all false
	for(int i = 0; i < names.size(); ++i)
		truth_assign.push_back(false);
	
	//converts 2^n to bitset binary
	for(int i = 0; i < pow(2, names.size()); ++i){
		truth_bitset = bitset<16>(i);
		
		//sets the individual bits to 0 or 1 (false or true) for truth_assign to be tested
		for( int m = 0; m < names.size(); ++m){
			truth_assign[m] = truth_bitset[m];
		}
		
		//tests truth_assign and increments count for all true statements
		if(x->evaluate_it(truth_assign))
			count++;
	}
	
    return count;
  }
};
