#include "SnakeGame.h"
bool cmp(const int &x, const int &y)
{
	return x > y;
}
/*default constructor*/
SnakeGame::SnakeGame()
{
	wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	freq = 0.2;
	wallcnt = 0;
	snake = new Snake;
	food = new Food;
}

/*set the bkcolor for menu,and the logic of choose level*/
void SnakeGame::menu()
{
	/*set up the stage*/
	initgraph(640, 300);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(BLACK);
	setbkmode(OPAQUE);
	settextstyle(20, 10, "Fora");
	loadRecord();

	/*use keyboardListener to choose level*/
	bool stay = true; //keep looping if true
	int cursor = 0;   //the cur pos of cursor
	while (stay)
	{
		showMenu(cursor);
		char curkey = '1'; //default
		if (_kbhit())
		{
			curkey = _getch();
		}
		switch (curkey)
		{
		case 'w':
		case 'W':
			cursor = (cursor - 1 + 2) % 2;
			break;
		case 's':
		case 'S':
			cursor = (cursor + 1 + 2) % 2;
			break;
		case 'a':
		case 'A':
			stay = false;
			break;
		default:
			break;
		}
	}
	mode = cursor ? INFTY : BASIC; //if the cur pos is 1,means choose the INFTY mode

	/*simulate a loading action*/
	setfillcolor(GREEN);
	outtextxy(300, 180, "Loading");
	setfillcolor(GREEN);
	srand(time(NULL));
	for (int i = 0; i < 31; i++)
	{
		solidrectangle(20 * i, 200, 20 * (i + 1), 220);
		Sleep(1000 * 0.1 * (rand() % 3 + 1)); //a trick to make the loading speed change dynamically
	}
	/*into the game*/
	game();
}

/*show the Menu by output strings
* input:the cursor's pos(0 if in the first row)
*/
void SnakeGame::showMenu(int p)
{
	settextcolor(TITLE_COLOR);
	settextstyle(20, 10, "Fora");
	outtextxy(0, 0, "---------------Welcome to the GreedySnake World!---------------------------");
	outtextxy(0, 20, "-----------------Press 'w' or 's' to choose mode--------------------------------------");
	outtextxy(0, 40, "-----------------------Press 'a' to start!---------------------------------------------------");
	settextcolor(BASIC_COLOR);
	settextstyle(10, 8, "Courier");
	outtextxy(80, 120, "Basic Mode--\"Longer and loger!!\"");
	settextcolor(INFTY_COLOR);
	outtextxy(80, 150, "Infty Mode--\"Can you believe,Smith bites his tail!\"");
	setlinecolor(RED);
	for (int i = 0; i < WALL_WIDTH; i++)
	{
		line(5 + i, 100, 5 + i, 180);
		line(630 + i, 100, 630 + i, 180);
		line(5, 100 - i, 630, 100 - i);
		line(5, 180 - i, 630, 180 - i);
	}
	settextcolor(RED);
	/*show the cursor*/
	outtextxy(12, 120 + p * 30, "--->");
	outtextxy(12, 120 + (p ^ 1) * 30, "     "); //a little trick 0^1
}

/* reset the game
* if the mode is BASIC,the system will clear the stage
* if the mode is INFTY,the system will keep the scores and 'bodys' 
*/
void SnakeGame::reset()
{
	/*reset the parameters*/
	wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	int tem = snake->getscore();
	freq = 0.2;
	wallcnt = 0;
	/*if we are in the INFTY mode,then the map and the score won't be reset*/
	if (mode == INFTY)
	{
		delete snake;
		delete food;
		snake = new Snake;
		snake->getscore() = tem;
	}
	else
	{
		for (int i = 0; i < NR_COL; i++)
		{
			for (int j = 0; j < NR_ROW; j++)
			{
				Snake::vis[i][j] = NONE;
			}
		}
		delete snake;
		delete food;
		snake = new Snake;
		cleardevice();
	}
	food = new Food;
}

/*the main loop of the game,which inclues the phases behind:
* 0.draw the ui(only when enter the func)
* loop:
* 1.move the snake
* 2.generate the new food
* 3.key listen and deal with interrupt
* 4.go to loop
*/
void SnakeGame::game()
{
	/*set the basic graph ui*/
	initgraph(WIDTH, HEIGHT);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(BLACK);
	setbkmode(OPAQUE);
	settextcolor(WARNING_COLOR);
	settextstyle(10, 8, "Courier");
	show();

	/*show the food*/
	food->draw();

	/*the main loop of the game*/
	while (true)
	{
		loop:
		Sleep(1000 * freq);                             //control the fps of the game

		/*move the snake*/
		if (snake->move(wallcolor == snake->getheadcolor())) //true if the snake is dead
		{
			if (mode == BASIC)
			{
				putword(GAME_OVER);                   //show the gameover
				basic_record.push_back(snake->getscore()); //update the new score,show it and go back to the menu
				outputRecord();
				Sleep(1000 * 2);
				reset();
				menu();
			}
			else //in the infty mode,the game won't end
			{
				infty_record.push_back(snake->getscore()); //update the score each time you died
				outputRecord();
				Sleep(1000 * 0.3);
				//putword(GO_ON);//delete the output due to the print problem,will declare in the report
				while (!_kbhit())
					;
				reset();
				goto loop;//it's bad
				//putword(CLEAR);
			}
		}
		/*generate the new food if possible*/
		food->generate();

		/*get the input from the keyboard*/
		char curkey = '1';
		if (_kbhit())
		{
			curkey = _getch();
		}
		show();

		/*deal with the pause interrupt*/
		if (pauseInterrupt(curkey) != CONTINUE)
		{
			/*update the score,show it and then go back to the menu*/
			if (mode == BASIC)
				basic_record.push_back(snake->getscore());
			else
				infty_record.push_back(snake->getscore());
			;
			outputRecord();
			Sleep(1000 * 2);
			reset();
			menu();
		}
		else
		{
			putword(CLEAR);//we need to clear the pause sentence
			snake->changedir(curkey);
		}
	}
}

/*return the status according to the curkey
* input:curkey
* output:CONTINUE if the user press 'p'/'P' or hasn't choose to pause;
* BACK_TO_MENU for default
*/
int SnakeGame::pauseInterrupt(char &curkey) const
{
	char _ch;
	if (curkey == 'p' || curkey == 'P')
	{
		putword(PAUSE);
		while (!_kbhit())
			;
		curkey = _getch();
		return (curkey == 'p' || curkey == 'P') ? CONTINUE : BACK_TO_MENU;
	}
	return CONTINUE;
}

/*show the words to the screen according to the sig we send
* - GAME_OVER:tell you that you are pugai
* - PAUSE:ask you  to continue or go back to the main menu
* - GO_ON:for the infty mode,tell you that you can go on
* - CLEAR: clear the CENTRAL_AREA
*/
void SnakeGame::putword(SIGNAL _sig) const
{
	switch (_sig)
	{
	case GAME_OVER:
		settextcolor(WARNING_COLOR);
		outtextxy(CENTRAL_AREA, "GAMEOVER! GO BACK TO THE MENU.");
		break;
	case PAUSE:
		settextcolor(PAUSE_COLOR);
		outtextxy(PAUSE_AREA, "PAUSING");
		break;
	case GO_ON:
		settextcolor(PAUSE_COLOR);
		outtextxy(CENTRAL_AREA, "DIE,DIE,DIE!PRESS ANY KEY TO GO ON.");
		break;
	case CLEAR:
		settextcolor(WHITE);
		outtextxy(PAUSE_AREA, "                                         ");
		break;
	default:
		break;
	}
}

/*the func to show the necessary background*/
void SnakeGame::show()
{
	showWall();
	showRecord();
}

/*the func to show the wall
* according the wallcnt,the wall's color will change
*/
void SnakeGame::showWall()
{
	wallcnt++;
	if (wallcnt >= 20) //true,we will randomly change the color of the wall
	{
		srand(time(NULL));
		wallcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
		wallcnt = 0;
	}
	setlinecolor(wallcolor);
	for (int i = 0; i < WALL_WIDTH; i++) //the WALL_WIDTH represents the width of wall we need to draw
	{
		line(i, 0, i, HEIGHT);
		line(0, i, BOARD, i);
		line(0, HEIGHT - i, BOARD, HEIGHT - i);
		line(BOARD - i, HEIGHT, BOARD - i, 0);
	}
}

/*load the local record,attention:the data.txt must exist*/
void SnakeGame::loadRecord()
{
	freopen("data.txt", "r", stdin);
	int t;
	basic_record.clear();
	infty_record.clear();
	for (int i = 0; i < 5; i++)
	{
		cin >> t;
		basic_record.push_back(t);
	}
	sort(basic_record.begin(), basic_record.end(), cmp);
	for (int i = 0; i < 5; i++)
	{
		cin >> t;
		infty_record.push_back(t);
	}
	sort(infty_record.begin(), infty_record.end(), cmp);
}

/*output the record to the local*/
void SnakeGame::outputRecord()
{
	freopen("data.txt", "w", stdout);
	sort(basic_record.begin(), basic_record.end(), cmp);
	sort(infty_record.begin(), infty_record.end(), cmp);
	for (int i = 0; i < 5; i++)
	{
		cout << basic_record[i] << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << infty_record[i] << endl;
	}
}

/*show the top 5 of the two modes*/
void SnakeGame::showRecord()
{
	/*show the current score*/
	settextcolor(RED);
	outtextxy(BOARD + 10, 30, "<SCORE>");
	TCHAR r[5];
	_stprintf_s(r, _T("%d"), snake->getscore());
	outtextxy(BOARD + 40, 50, r);

	/*set the speed according to the current score*/
	freq = 0.2 - (snake->getscore() / 10) * 0.05;
	if (freq <= 0.05)
		freq = 0.08;

	/*show the history scores*/
	settextcolor(BLUE);
	outtextxy(BOARD + 20, 70, "Basic Top 5");
	settextcolor(RED);
	for (int i = 0; i < 5; i++)
	{
		_stprintf_s(r, _T("%d"), basic_record[i]);
		outtextxy(BOARD + 20, 90 + 20 * i, r);
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
