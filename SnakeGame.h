#pragma once
#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "GreadySnake.h"
#include "marco.h"
#include <iostream>
#include <conio.h>
using namespace std;

class SnakeGame {
private:
	Snake snake;
	double freq;
	//Food _food;
public:
	SnakeGame();
	//void init();
	void game();
	void putword(SIGNAL _sig)const;
};

SnakeGame::SnakeGame() {
	freq = 0.1;
}

void SnakeGame::game() {
	initgraph(1000, 1000);
	setbkcolor(WHITE);   //set the 
	cleardevice();       //将背景颜色刷新到窗口上
	setfillcolor(BLACK); //设置填充的颜色为黑色，之后话填充的图形都是这个颜色
	//solidrectangle(20, 560, 560, 20);
	setbkmode(TRANSPARENT);
	outtextxy(0,0, GAME_OVER_TIP);
	while (true) {
		Sleep(1000*0.5);
		if (snake.move())
		{
			cout << "you lose" << endl;
			putword(GAME_OVER);
			system("pause");
		}
		char curkey='1';
		if(_kbhit()){
			curkey = _getch();
		}
		snake.changedir(curkey);
	}
}

void SnakeGame::putword(SIGNAL _sig)const {
	switch (_sig)
	{
	case GAME_OVER:
		outtextxy(CENTRAL_AREA, GAME_OVER_TIP); break;
	default:
		break;
	}
}
#endif