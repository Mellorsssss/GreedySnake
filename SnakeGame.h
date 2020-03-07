#pragma once
#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#define _CRT_SECURE_NO_WARNINGS
#include "GreadySnake.h"
#include "marco.h"
#include <iostream>
#include <conio.h>
using namespace std;
bool cmp(const int& x, const int& y) {
	return x > y;
}
char GAME_OVER_TIPS[] = "Hello World";
class SnakeGame {
private:
	Snake* snake;
	Food* food;
	COLORREF wallcolor;
	vector<int>basic_record,infty_record;
	double freq;
	int wallcnt;
	int mode;
public:
	SnakeGame();
	void menu();
	void game();
	void putword(SIGNAL _sig)const;
	void show();
	void showWall();
	void showRecord();
	void loadRecord();
	void outputRecord();
	void showMenu(int pos);
	void reset();
};

SnakeGame::SnakeGame() {
	wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	freq = 0.2;
	wallcnt = 0;
	snake = new Snake;
	food = new Food;
}

void SnakeGame::menu() {
	initgraph(400, 200);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(BLACK);
	setbkmode(OPAQUE);
	settextcolor(WARNING_COLOR);
	loadRecord();
	bool stay = true;
	int cursor = 0;
	while (stay) {
		showMenu(cursor);
		char curkey = '1';
		if (_kbhit()) {
			curkey = _getch();
		}
		switch (curkey) {
		case 'w':
		case 'W':
			cursor = (cursor - 1 + 2) % 2; break;
		case 's':
		case 'S':
			cursor = (cursor + 1 + 2) % 2; break;
		case 'a':
		case 'A':
			stay = false; break;
		default:break;
		}
	}
	mode = cursor?INFTY:BASIC;
	game();
}

void SnakeGame::reset() {
	wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	int tem = snake->score;
	freq = 0.2;
	wallcnt = 0;
	if (mode == INFTY) {
		delete snake;
		delete food;
		snake = new Snake;
		snake->score = tem;
	}
	else {
		for (int i = 0; i < snake->body.size(); i++) {
			Snake::vis[snake->body[i].first][snake->body[i].second] = NONE;
		}
		Snake::vis[food->curpos.first][food->curpos.second] = NONE;
		delete snake;
		delete food;
		snake = new Snake;
		cleardevice();
	}
	food = new Food;
}

void SnakeGame::game() {
	initgraph(WIDTH, HEIGHT);
	setbkcolor(WHITE);   
	cleardevice();       
	setfillcolor(BLACK); 
	setbkmode(OPAQUE);
	settextcolor(WARNING_COLOR);
	show();
	food->display(food->curpos, FOOD_COLOR);
	while (true) {
		Sleep(1000*freq);
		if (snake->move(wallcolor==snake->headcolor))
		{
			if (mode == BASIC)
			{
				putword(GAME_OVER);
				basic_record.push_back(snake->score);
				outputRecord();
			}
			else {
				infty_record.push_back(snake->score);
				outputRecord();
			}
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
	wallcnt++;
	if (wallcnt >= 20) { 
		srand(time(NULL));
		wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
		wallcnt = 0;
	}
	setlinecolor(wallcolor);
	line(0, 0, 0, HEIGHT);
	line(0, 0, BOARD, 0);
	line(0, HEIGHT, BOARD, HEIGHT);
	line(BOARD, HEIGHT, BOARD, 0);
}

void SnakeGame::loadRecord() {
	freopen("data.txt", "r", stdin);
	int t;
	basic_record.clear();
	infty_record.clear();
	for(int i=0;i<5;i++) {
		cin >> t;
		basic_record.push_back(t);
	}
	sort(basic_record.begin(), basic_record.end(),cmp);
	for (int  i = 0; i < 5; i++)
	{
		cin >> t;
		infty_record.push_back(t);
	}
	sort(infty_record.begin(), infty_record.end(),cmp);
}

void SnakeGame::outputRecord() {
	freopen("data.txt", "w", stdout);
	sort(basic_record.begin(), basic_record.end(),cmp);
	sort(infty_record.begin(), infty_record.end(),cmp);
	for (int i = 0; i <5; i++) {
		cout << basic_record[i] << endl;
	}
	for (int i = 0; i <5; i++)
	{
		cout << infty_record[i]<<endl;
	}
}

void SnakeGame::showRecord() {
	/*show the current score*/
	settextcolor(RED);
	outtextxy(BOARD+10, 30, "<SCORE>");
	TCHAR r[5];
	_stprintf_s(r, _T("%d"), snake->score);
	outtextxy(BOARD+40,50, r);

	/*set the speed according to the current score*/
	freq = 0.2-(snake->score/10)*0.05;
	if (freq <=0.05 )freq = 0.08;

	/*show the history scores*/
	settextcolor(BLUE);
	outtextxy(BOARD + 20, 70, "Basic Top 5");
	settextcolor(RED);
	for (int  i = 0; i < 5; i++)
	{
		_stprintf_s(r, _T("%d"), basic_record[i]);
		outtextxy(BOARD + 20, 90+20*i, r);
	}
	
	settextcolor(BLUE);
	outtextxy(BOARD + 20, 230, "Infty Top 5");
	settextcolor(RED);
	for (int i = 0; i < 5; i++)
	{
		_stprintf_s(r, _T("%d"), infty_record[i]);
		outtextxy(BOARD + 20, 250 + 20 * i, r);
	}
}

void SnakeGame::show() {
	showWall();
	showRecord();
}

void SnakeGame::showMenu(int p) {
	settextcolor(WARNING_COLOR);
	outtextxy(0 , 0, "---------------Welcome to the GreedySnake World!---------------------------");
	outtextxy(0, 20, "--------------------Press 'w' or 's' to choose mode-----------------------------------");
	outtextxy(0, 40, "---------------------------Press 'a' to start!-----------------------------------------------");
	settextcolor(BLACK);
	outtextxy(60, 80, "Basci Mode--\"Longer and loger¡­¡­\"");
	outtextxy(60, 120, "Infty Mode--\"Can you believe,Smith bites his tail!\"");
	settextcolor(RED);
	outtextxy(40, 80+p*40, "--->");
	outtextxy(40, 80 +(p^1) * 40, "     ");
}
#endif