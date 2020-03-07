#pragma once
#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "GreadySnake.h"
#include "marco.h"
#include <iostream>
#include <conio.h>
using namespace std;
char GAME_OVER_TIPS[] = "Hello World";
class SnakeGame {
private:
	Snake* snake;
	Food* food;
	COLORREF wallcolor;
	double freq;
	int cnt;
public:
	SnakeGame();
	void game();
	void putword(SIGNAL _sig)const;
	void show();
	void showWall();
	void showRecord();
	void reset();
};

SnakeGame::SnakeGame() {
	wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	freq = 0.2;
	cnt = 0;
	snake = new Snake;
	food = new Food;
}

void SnakeGame::reset() {
	wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	delete snake;
	delete food;
	snake = new Snake;
	food = new Food;
	freq = 0.2;
	cnt = 0;
}
void SnakeGame::game() {
	initgraph(1000, 1000);
	setbkcolor(WHITE);   
	cleardevice();       
	setfillcolor(BLACK); 
	setbkmode(OPAQUE);
	settextcolor(WARNING_COLOR);
	showWall();
	food->display(food->curpos, FOOD_COLOR);
	while (true) {
		Sleep(1000*freq);
		if (snake->move(wallcolor==snake->headcolor))
		{
			putword(GAME_OVER);
			while (!_kbhit());
			reset();
		}
		food->generate();
		char curkey='1';
		if(_kbhit()){
			curkey = _getch();
		}
		show();
		snake->changedir(curkey);
	}
}

void SnakeGame::putword(SIGNAL _sig)const {
	switch (_sig)
	{
	case GAME_OVER:
		settextcolor(WARNING_COLOR);
		outtextxy(CENTRAL_AREA, "GAMEOVER!"); break;
	default:
		break;
	}
}

void SnakeGame::showWall() {
	cnt++;
	if (cnt >= 20) { 
		srand(time(NULL));
		wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
		cnt = 0;
	}
	setlinecolor(wallcolor);
	line(0, 0, 0, HEIGHT);
	line(0, 0, BOARD, 0);
	line(0, HEIGHT, BOARD, HEIGHT);
	line(BOARD, HEIGHT, BOARD, 0);
}

void SnakeGame::showRecord() {
	settextcolor(TIP_COLOR);
	outtextxy(BOARD+20, 30, "Your current score is ");
	TCHAR record[5];
	_stprintf_s(record, _T("%d"), snake->score);
	outtextxy(BOARD+40,50, record);
	freq = 0.2-(snake->score/10)*0.05;
	if (freq < 0)freq = 0.05;
}

void SnakeGame::show() {
	showWall();
	showRecord();
}

#endif