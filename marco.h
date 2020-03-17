#pragma once
#ifndef MARCO_H
#define MARCO_H
#include <graphics.h>
/*BASIC PARAMETERS*/
#define WIDTH 640+120
#define HEIGHT 480
#define BOARD 640
#define ROW_HEIGHT 20
#define COL_WIDTH 20
#define BODY_SIZE 20
#define NR_COL (640)/(COL_WIDTH)
#define NR_ROW (HEIGHT)/(ROW_HEIGHT)
#define INIT_LENGTH 3
#define SPECIAL_TIME 5
#define STEPS 20
#define NR_COLOR 2
#define SPECIAL_FEEDBACK 3
#define NORMAL_FEEDBACK 1
#define BASIC 0
#define INFTY 1
#define WALL_WIDTH 6
#define CONTINUE true
#define BACK_TO_MENU false
/*COLOR*/
#define BK_COLOR WHITE
//#define HEAD_COLOR RED
#define BODY_COLOR BLUE
#define FOOD_COLOR BLACK
#define SPECIAL_FOOD_COLOR GREEN
#define WALL_COLOR RED
#define TIP_COLOR GREEN
#define WARNING_COLOR RED
#define PAUSE_COLOR BLUE
#define TITLE_COLOR (0,49,79)
#define BASIC_COLOR  (38,188,213)
#define INFTY_COLOR (78,29,76)

/*SIGNAL OF THE GAME*/
typedef int SIGNAL;

#define GAME_OVER 1
#define PAUSE 2
#define GO_ON 3
#define CLEAR 4
#define CENTRAL_AREA 200,240
#define PAUSE_AREA 650,400
typedef int STATUS;
#define NONE 0
#define BODY_IN 1
#define FOOD_IN 2
#define SPECIAL_IN 3

/*FUNCTION*/
#define RANDOM(m,n) rand()%(n-m+1)+m
const int d[][2] = {
	{0,-1},
    {0,1},
    {-1,0},
    {1,0} };
#define NR_COLOR_SUM 5
const COLORREF HW_COLOR[NR_COLOR_SUM] = {
	RED,GREEN,YELLOW,MAGENTA,DARKGRAY
};
#endif