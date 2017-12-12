
#include "stdafx.h"
#include <iostream>
#include <conio.h> // track all the pressing

bool gameOver;
const int width = 20;
const int height = 20;
int x, y; // the coordinates of our snake
int fruitX, fruitY; // the coordinates that eats the snake
int score; 
int tailX[100], tailY[100]; 
int nTail; 

// store moving
enum eDirections {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirections dir;

// Setting
void Setup(){
	gameOver = false; // default, the beginning of the game
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
// to draw map
void Draw(){
	system("cls");
	// to draw borders
	for (int i = 0; i < width+1; i++) // up
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++){ // 
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				std::cout << "#";
			}
			if (i == y && j == x)
			{
				std::cout << "0";
			}
			else if (i == fruitY && j == fruitX){
				std::cout << 'f';
			}
			else{
				// the drawing of the tail
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i){
						print = true;
						std::cout << "o";
					}
				}
				if (!print)
				{
					std::cout << " ";
				}
			}
				
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width+1; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score:" << score << std::endl;
}
// track all the pressing from user
void Input(){
	if (_kbhit()) // true, if user pressed a button on the keyboard
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x': // out
			gameOver = true;
		}

	}
}

void Logic(){
	// create tail
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	// the creation of the tail, so he repeated all the movement of the snake
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	// limit the wall
	//if (x > width || x<0 || y>height || y < 0)
	//	gameOver = true;
	// if we go outside, then go on the other side of the wall
	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;
	if (y >= height-1)
		y = 0;
	else if (y < 0)
		y = height - 2;

	// check to eating tail
	for (int i = 0; i < nTail; i++)
	{
		if ( tailX[i] == x && tailY[i] == y){
			gameOver = true;
		}
	}
	// change fruit, increase score
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++; // to eat fruit - to increase tail
	}
}


int main(int argc, char* argv[])
{
	Setup();
	while (!gameOver){
		Draw();
		Input();
		Logic();
	}
	return 0;
}

