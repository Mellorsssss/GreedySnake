#pragma once
#include "marco.h" //the marco we use in the *.c
#include <cstring>
#include <deque>
#include <graphics.h>
#include <random>
#include <time.h>
#include <utility>
using namespace std;
/*In the GreadySnake(I mistakely spell the 'Greedy',whatever).h,
* class Snake:our main character,the cute Snake
* class Food :the poor food to be eaten by the Snake
*/
class Snake;
class Food;
typedef pair<int, int> pos;

class Snake
{
	friend class SnakeGame;
	friend class Food;

private:
	enum dir
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	} curdir;
	deque<pos> body;                           //the head and body's pos
	COLORREF headcolor;                        //used to judge if the snake can go across wall now
	void display(int i, COLORREF color) const; //the func to draw
	bool infty;                                //infty mode
	int score;                                 //the score
	static STATUS vis[NR_COL][NR_ROW];         //the status are:NONE,BODY_IN,FOOD_IN,SPECIAL_IN
public:
	Snake();
	~Snake() {}
	int length() const { return body.size(); }; //the length of the snake
	bool bodycheck() const;                     //true if the head hit the body
	int foodcheck() const;                      //true if the head hit the food
	bool boundcheck(pos a) const;               //true if the head hit the wall
	bool move(bool ok);                         //move the snake due to the cur dir,return true if the snake is dead now
	void changedir(char c);                     //set the cur dir by decoding the keycode
};

class Food
{
	friend class SnakeGame;
	friend class Snake;

private:
	pos curpos; //the only food's pos
	int cnt;    //the num of food has appeared
	int count;  //the timeout of the 'ChangeColor food'

public:
	Food();
	~Food() {}
	void display(pos _pos, COLORREF color) const;          //draw the body
	void generate();                                       //generate the new food if possible
	bool isSpecial() { return (cnt % SPECIAL_TIME == 0); } //judge if the cur food is the 'ChangeColor food'
};
