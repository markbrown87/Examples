/*
* Mark Brown
*	11/04/2016
* Description: A file used for the game of checkers which is the child of the class game. This will house the
* meat and potatoes of the checkers game handling the restart, make_move, is_legal, and display_status of the game.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string> 
#include <cstring>
#include <iostream>
#include <queue>

#include "checkers.h"
#include "colors.h"
#include "spaces.h"

namespace main_savitch_14{

	checkers::checkers() {};//default constructor

	void checkers::restart(){
		//a board set up in integer code for a blank board
		int new_board [8][8]  = {
			{0, 2, 0, 2, 0, 2, 0, 2},
			{2, 0, 2, 0, 2, 0, 2, 0},
			{0, 2, 0, 2, 0, 2, 0, 2},
			{1, 0, 1, 0, 1, 0, 1, 0},
			{0, 1, 0, 1, 0, 1, 0, 1},
			{3, 0, 3, 0, 3, 0, 3, 0},
			{0, 3, 0, 3, 0, 3, 0, 3},
			{3, 0, 3, 0, 3, 0, 3, 0}		}; 
		//copying the new_board to the new board
		for(int i = 0; i<8;i++){
			for(int z = 0; z<8;z++)
				board[i][z].set_space(new_board[i][z]);
		}
		//calling the parent function to increment the move_number
		game::restart();
	}

	void checkers::display_status() const{
			char letter = 'A';
			for(int a = 0; a < 8; a++){
			std::cout << letter << "   ";
			for(int b = 0; b < 8; b++){
				//Good versus Evil -> with the pieces labelled as such
				if(board[a][b].is_red())
					std::cout << B_RED << "|   |" << RESET;
				else if (board[a][b].is_black())
					std::cout << B_BLACK << "|   |" << RESET;
				else if (board[a][b].is_evil())
					std::cout << B_BLACK << "|(E)|" << RESET;
				else if (board[a][b].is_good())
					std::cout << B_BLACK << "|(G)|" << RESET;
				else if (board[a][b].is_eking())
					std::cout << B_BLACK << RED << "|(K)|" << RESET;
				else if (board[a][b].is_gking())
					std::cout << B_BLACK << GREEN <<"|(K)|" << RESET;
				}
			std::cout << endl;
			letter++;//increments the letter
			}
		std::cout << endl << YELLOW << "      1    2    3    4    5    6    7    8" << RESET <<endl;
		std::cout << endl << "Good piece(s) count: " << get_count(3) <<" and Evil piece(s) count: " << get_count(2) << endl << endl;
	}
	//function used to check if the move is legal or not
	bool checkers::is_legal(const std::string& move)const{
		int current_alpha, next_alpha, current_num, next_num, holder, item;
		bool check = false;
		if(isdigit(move[0]) || isdigit(move[2]))
			return false;
		holder = strlen(move.c_str());
		if(holder %2 == 1) return false;
		//converts the letter into usable data
		current_alpha = convert_to_number(toupper(move[0]));
		//converts the number into usable data
		current_num = move[1] - '1';

		if(is_human_move() && (board[current_alpha][current_num].is_evil() || board[current_alpha][current_num].is_eking() || board[current_alpha][current_num].is_red() || board[current_alpha][current_num].is_black()))
			return false;
		if(is_computer_move() && (board[current_alpha][current_num].is_good() || board[current_alpha][current_num].is_gking() || board[current_alpha][current_num].is_red() || board[current_alpha][current_num].is_black()))
			return false;
		item = board[current_alpha][current_num].is_space();
		int i = 0;
		while(i<holder-2){
			current_alpha = convert_to_number(toupper(move[i]));
			current_num = move[i+1] - '1';
			next_alpha = convert_to_number(toupper(move[i+2]));
			next_num = move[i+3] - '1';
			if(next_alpha < 0 || next_alpha > 7 || next_num > 7 || next_num < 0 ){//sets the boundaries of the board
				check = false;
			}
				if (is_regular_move(current_alpha, current_num, next_alpha, next_num)){
					check = true;
				}
				else if(is_jump_move(current_alpha, current_num, next_alpha, next_num, item)){
					check = true;
				}
				else check = false;
			i+=2;
		}
		return check;
	}

	void checkers::make_move(const std::string& move){
		int current_alpha, next_alpha, current_num, next_num, holder, item;
		current_alpha = convert_to_number(toupper(move[0]));
		current_num = move[1] - '1';
		item = board[current_alpha][current_num].is_space();
		
		holder = strlen(move.c_str());
		
		for(int i = 0; i < holder-2; i+=2){
			current_alpha = convert_to_number(toupper(move[i]));
			current_num = move[i+1] - '1';
			next_alpha = convert_to_number(toupper(move[i+2]));
			next_num = move[i+3] - '1';
			if(is_jump_move(current_alpha, current_num, next_alpha, next_num, item)){
				board [next_alpha][next_num].set_space(board[current_alpha][current_num].is_space());
				make_jump_move(current_alpha, current_num, next_alpha, next_num);
				turn_king(next_alpha, next_num);
			}
			else if(is_regular_move(current_alpha, current_num, next_alpha, next_num)){
				board [next_alpha][next_num].set_space(board[current_alpha][current_num].is_space());
				turn_king(next_alpha, next_num);
			}
			board[current_alpha][current_num].set_space(1);
		}
		//increments the move_number
		game::make_move(move);
	}
	//function used to convert the letter 
	int checkers::convert_to_number(char a) const{
		if(a == 'A')
			return 0;
		else if(a == 'B')
			return 1;
		else if(a == 'C')
			return 2;
		else if(a == 'D')
			return 3;
		else if(a == 'E')
			return 4;
		else if(a == 'F')
			return 5;
		else if(a == 'G')
			return 6;
		else if(a == 'H')
			return 7;
		else
			return 9;
	}
	
	char checkers::convert_back(int a) const{
		if(a == 0)
			return 'A';
		else if(a == 1)
			return 'B';
		else if(a == 2)
			return 'C';
		else if(a == 3)
			return 'D';
		else if(a == 4)
			return 'E';
		else if(a == 5)
			return 'F';
		else if(a == 6)
			return 'G';
		else if(a == 7)
			return 'H';
	}
	//counts the number of pieces on the board in regards to 'int a'
	int checkers::get_count(int a)const{
		int tmp =0;
		for(int i=0;i<8;++i){
			for(int j=0; j<8;++j){
				if(board[i][j].is_space() == a || board[i][j].is_space() == a+2)
					tmp++;
			}
		}
		return tmp;
	}
	//checks for game over
	bool checkers::is_game_over() const{
		if(get_count(2) == 0 || get_count(3) == 0)
			return true;
	}
	//checks is it's the human move
	bool checkers::is_human_move()const{
		if(game::next_mover() == 0)
			return true;
		else
			return false;
	}
	//checks if it's the computer's move
	bool checkers::is_computer_move()const{
		if(game::next_mover() == 2)
			return true;
		else
			return false;
	}
	//checks if it's a legel human move
	bool checkers::is_regular_move(int current_alpha, int current_num, int next_alpha, int next_num)const{
		if(is_human_move()){
			if(board[current_alpha][current_num].is_good()){
				if(board[next_alpha][next_num].is_black() && (current_num - 1 == next_num || current_num + 1 == next_num) && (current_alpha - 1 == next_alpha) ) 
					return true;
				else return false;
			}
			else if(board[current_alpha][current_num].is_gking()){
				if(board[next_alpha][next_num].is_black() && (current_num - 1== next_num || current_num + 1== next_num) && (current_alpha - 1== next_alpha || current_alpha + 1== next_alpha))					
					return true;
				else return false;
			}
		}
		else if(is_computer_move()){
			if(board[current_alpha][current_num].is_evil()){
				if(board[next_alpha][next_num].is_black() && (current_num - 1 == next_num|| current_num + 1== next_num) && (current_alpha + 1== next_alpha))
					return true;
			}
			else if(board[current_alpha][current_num].is_eking()){
				if(board[next_alpha][next_num].is_black() && (current_num - 1== next_num || current_num + 1== next_num) && (current_alpha - 1 == next_alpha|| current_alpha + 1== next_alpha))
					return true;
			}
		}
		else return false;
	}
	
	bool checkers::is_jump_move(int current_alpha, int current_num, int next_alpha, int next_num, int item)const{
		if(is_human_move()){
			if(item == 3){
				if(board[current_alpha-1][current_num+1].is_evil() || board[current_alpha-1][current_num-1].is_evil()|| board[current_alpha-1][current_num+1].is_eking()|| board[current_alpha-1][current_num-1].is_eking()){
					if(board[next_alpha][next_num].is_black() && (((current_alpha-2) == next_alpha && (current_num+2) == next_num) || ((current_alpha-2) == next_alpha && (current_num-2) == next_num)))
						return true;
					else return false;
				}
				else return false;
			}
			else if(item == 5){
				if(board[current_alpha-1][current_num+1].is_evil() || board[current_alpha-1][current_num-1].is_evil() || board[current_alpha+1][current_num+1].is_evil() || board[current_alpha+1][current_num-1].is_evil() || board[current_alpha+1][current_num+1].is_eking() || board[current_alpha+1][current_num-1].is_eking() ||board[current_alpha-1][current_num+1].is_eking()|| board[current_alpha-1][current_num-1].is_eking()){
					if(board[next_alpha][next_num].is_black()  && (((current_alpha-2) == next_alpha && (current_num+2) == next_num) || ((current_alpha-2) == next_alpha && (current_num-2) == next_num)||((current_alpha+2) == next_alpha && (current_num+2) == next_num) || ((current_alpha+2) == next_alpha && (current_num-2) == next_num)))
						return true;
					else return false;
				}
				else return false;
			}
		}
		else if(is_computer_move()){
			if(item == 2){
				if(board[current_alpha+1][current_num+1].is_good() || board[current_alpha+1][current_num-1].is_good()|| board[current_alpha+1][current_num+1].is_gking() || board[current_alpha+1][current_num-1].is_gking()){
					if(board[next_alpha][next_num].is_black() && (((current_alpha+2) == next_alpha && (current_num+2) == next_num) || ((current_alpha+2) == next_alpha && (current_num-2) == next_num)))
						return true;
					else return false;
				}
				else return false;
			}
			else if(item == 4){
				if(board[current_alpha-1][current_num+1].is_good() || board[current_alpha-1][current_num-1].is_good() || board[current_alpha+1][current_num+1].is_good() || board[current_alpha+1][current_num-1].is_good() || board[current_alpha+1][current_num+1].is_gking()|| board[current_alpha+1][current_num-1].is_gking() ||board[current_alpha-1][current_num+1].is_gking()|| board[current_alpha-1][current_num-1].is_gking()){
					if(board[next_alpha][next_num].is_black()  && (((current_alpha-2) == next_alpha && (current_num+2) == next_num) || ((current_alpha-2) == next_alpha) && ((current_num-2) == next_num)||((current_alpha+2) == next_alpha)) && ((current_num+2) == next_num) || ((current_alpha+2) == next_alpha && (current_num-2) == next_num))
						return true;
					else return false;
				}
				else return false;
			}
		}
	}
	void checkers::make_jump_move(int current_alpha, int current_num, int next_alpha, int next_num){
		if((next_alpha == current_alpha-2)&&(next_num == current_num+2))
			board[next_alpha+1][next_num-1].set_space(1);
		else if((next_alpha == current_alpha-2) && (next_num == current_num-2))
			board[next_alpha+1][next_num+1].set_space(1);
		else if((next_alpha == current_alpha+2) && (next_num == current_num+2))
			board[next_alpha-1][next_num-1].set_space(1);
		else if((next_alpha == current_alpha+2)&&(next_num == current_num-2))
			board[next_alpha-1][next_num+1].set_space(1);
	}
	void checkers::turn_king(int next_alpha, int next_num){
		if(is_human_move()){
			if(next_alpha == 0)
				board[next_alpha][next_num].set_space(5);
		}
		else if(is_computer_move()){
			if(next_alpha == 7)
				board[next_alpha][next_num].set_space(4);
		}
	}
	
	void checkers::compute_moves(std::queue<string>& moves)const{
		string current, move1, move2, move3, move4, move5, move6, move7, move8, holder;
		char a,a1,a2,a3,a4,a5,a6,a7,a8,n,n1,n2,n3,n4,n5,n6,n7,n8;
		
		for(int i=0;i<8;++i)
			for(int j=0;j<8;++j){
				current = "";
				move1 = "";
				move2 = "";
				move3 = "";
				move4 = "";
				move5 = "";
				move6 = "";
				move7 = "";
				move8 = "";
				holder = "";
				
				if(board[i][j].is_space()>1){
					//current location
					a = i + 'A';
					n = j + '1';
					//bottom right
				a1 = a + 1;
				n1 = n + 1;
				//bottom left
				a2 = a + 1;
				n2 = n - 1;
				//king moves
				//top right
				a3 = a - 1;
				n3 = n + 1;
				//top left
				a4 = a - 1;
				n4 = n - 1;
				//bottom jump left
				a5 = a + 2;
				n5 = n - 2;
				//bottom jump right
				a6 = a + 2;
				n6 = n + 2;
				//king jumps
				//top jump right
				a7 = a - 2;
				n7 = n + 2;
				//top jump left
				a8 = a - 2;
				n8 = n - 2;
				
				current += a;
				current += n;
				move1 += a1; 
				move1 += n1;
				move2 += a2; 
				move2 += n2;
				move3 += a3; 
				move3 += n3;
				move4 += a4; 
				move4 += n4;
				move5 += a5; 
				move5 += n5;
				move6 += a6; 
				move6 += n6;
				move7 += a7; 
				move7 += n7;
				move8 += a8; 
				move8 += n8;
				
				holder = current+move1;
				if(is_legal(holder))
					moves.push(holder);
				holder = current+move2;
				if(is_legal(holder))
					moves.push(holder);
				holder = current+move3;
				if(is_legal(holder))
					moves.push(holder);
				holder = current+move4;
				if(is_legal(holder))
					moves.push(holder);
				holder = current+move5;
				if(is_legal(holder))
					moves.push(holder);
				holder = current+move6;
				if(is_legal(holder))
					moves.push(holder);
				holder = current+move7;
				if(is_legal(holder))
					moves.push(holder);
				holder = current+move8;
				if(is_legal(holder))
					moves.push(holder);
				}
			}
	}
	
	int checkers::evaluate()const{
		int points = 0;
		for(int i=0;i<8;++i){
			for(int j=0;j<8;++j){
				if(board[i][j].is_eking())
					points +=2;
				else if(board[i][j].is_evil())
					++points;
				else if(board[i][j].is_gking())
					points -=2;
				else if(board[i][j].is_good())
					--points;
			}
		}
		return points;
	}
}