#pragma once
#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#define _CRT_SECURE_NO_WARNINGS
#include "GreadySnake.h"
#include "marco.h"
#include <conio.h>
#include <iostream>
using namespace std;
/*the main logic of the game
* class SnakeGame:
* - has a Snake member and a Food member
* - draw the ui(menu and the main game)
* - show the records
* - so on¡­¡­ 
*/

class SnakeGame
{
private:
	Snake *snake;
	Food *food;
	COLORREF wallcolor;                     //the color of the wall,used to judge if the Snake can go across it
	vector<int> basic_record, infty_record; //the scores
	double freq;                            //determin the speed of the game
	int wallcnt;                            //the parameter the wall needs
	int mode;

public:
	SnakeGame();
	void menu();                     //show the start menu
	void game();                     //the main loop
	void putword(SIGNAL _sig) const; //put the words to the screen
	void show();                     //show the wall,record and so on
	void showWall();
	void showRecord();
	int pauseInterrupt(char& c)const;//deal with the pause interrupt
	void loadRecord();      //load the current record 'from' local
	void outputRecord();    //output the current record to the local
	void showMenu(int pos); //show the menu
	void reset();           //reset the game,has 'infty' mode and the 'basic' mode
};

#endif