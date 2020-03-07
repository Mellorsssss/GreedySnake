#pragma once
#ifndef MARCO_H
#define MARCO_H
/*BASIC PARAMETERS*/
#define WIDTH 640+80
#define HEIGHT 480
#define BOARD 640
#define ROW_HEIGHT 20
#define COL_WIDTH 20
#define BODY_SIZE 20
#define NR_COL (WIDTH)/(COL_WIDTH)
#define NR_ROW (HEIGHT)/(ROW_HEIGHT)
#define INIT_LENGTH 3

/*COLOR*/
#define BK_COLOR WHITE
#define HEAD_COLOR RED
#define BODY_COLOR BLUE
#define FOOD_COLOR BLACK

/*SIGNAL OF THE GAME*/
typedef int SIGNAL;

#define GAME_OVER 1
#define PAUSE 2
#define CENTRAL_AREA 320,240
typedef int STATUS;
#define NONE 0
#define BODY_IN 1
#define FOOD_IN 2

/*FUNCTION*/
#define RANDOM(m,n) rand()%(n-m+1)+m
const int d[][2] = {
	{0,-1},
    {0,1},
    {-1,0},
    {1,0} };
#endif