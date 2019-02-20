/*
* Mark Brown
*	11/04/2016
* Description: main file used to play the game checkers
*
*/

#include <iostream>
#include <cstring>
#include <stdlib.h>

#include <sstream>
#include <string>

#include "game.h"
#include "colors.h"
#include "checkers.h"
#include "spaces.h"


using namespace main_savitch_14;



int main(){
	checkers games;
	game::who winner;
	winner = games.play();
	if(winner == game::HUMAN)
		cout << "Congratulations >:[ You've won this time, Human. Don't get use to it.\n";
	else
		cout << "Hahahaha! I knew you couldn't beat me. Since I won you must now award Mark Brown full points on this project!! Or die mortal!.\n";
}
