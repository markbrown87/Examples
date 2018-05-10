/*
* Mark Brown
*	11/04/2016
* Description: header file that connects the parent class game to child class checkers
*
*/

#include <string>
#include <queue>
#include "game.h"
#include "spaces.h"

namespace main_savitch_14{
	
	class checkers:public game{	
		public: 
			checkers();
			int convert_to_number(char a)const;
			int get_count(int a)const;
			bool is_human_move()const;
			bool is_computer_move()const;
			bool is_regular_move(int current_alpha, int current_num, int next_alpha, int next_num)const;
			bool is_jump_move(int current_alpha, int current_num, int next_alpha, int next_num, int item)const;
			void make_jump_move(int current_alpha, int current_num, int next_alpha, int next_num);
			void turn_king(int next_alpha, int next_num);
			char convert_back(int a) const;
		protected:
			virtual void restart();
			virtual void display_status() const;
			virtual bool is_legal(const std::string& move)const;
			virtual void make_move(const std::string& move);
			virtual bool is_game_over()const;
			virtual game* clone()const
				{ return new checkers(*this); }
			virtual void compute_moves(std::queue<std::string>& moves) const;
			virtual int evaluate()const;
		private:
			spaces board[8][8];
			int evil_count, good_count;
	};
	
}