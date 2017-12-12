// Shake.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h> // отслеживает все нажати€

bool gameOver;
const int width = 20;
const int height = 20;
int x, y; // координаты нашей змейки
int fruitX, fruitY; // координаты того, что съедает змейка
int score; // общий счет
int tailX[100], tailY[100]; // хвост 
int nTail; // кол-во элементов в хвосте

// хранить движени€
enum eDirections {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirections dir;

// настройка
void Setup(){
	gameOver = false; // по умолчанию в начале игры
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
// отрисовка карты
void Draw(){
	system("cls");
	// отрисовка границ
	for (int i = 0; i < width+1; i++) // верхн€€
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
				// дорисовка хвоста
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
// отслеживать нажати€ от пользовател€
void Input(){
	if (_kbhit()) // true, если пользователь нажал кнопку на клавиатуре
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
		case 'x': // выход из игры
			gameOver = true;
		}

	}
}
// логика игры
void Logic(){
	// образование хвоста
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	// создание хвоста, чтобы он повтор€л полностью движение змейки
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
	// за пределы стены
	//if (x > width || x<0 || y>height || y < 0)
	//	gameOver = true;
	// если выходим за пределы, то выходить с другой стороны стены
	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;
	if (y >= height-1)
		y = 0;
	else if (y < 0)
		y = height - 2;

	// проверка на съедение хвоста
	for (int i = 0; i < nTail; i++)
	{
		if ( tailX[i] == x && tailY[i] == y){
			gameOver = true;
		}
	}
	// поехать фрукты, увеличение скоре
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++; // съели фрукт - увеличилс€ хвост
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

