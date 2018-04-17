#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <fstream>

Board::Board()
{
	getData();
	if (rowsFilled > rows / 2)
		rowsFilled = rows / 2;

	ball.position.x = columns / 2;
	ball.position.y = rows / 2;
	ball.velocity.x = -1;
	ball.velocity.y = 1;
	ball.sprite = '*';

	for (int i = 0; i < 3; i++) {
		platform.position[i].x = columns / 2 + i;
		platform.position[i].y = rows - 3;
	}
	platform.sprite = '-';

	box = new char*[rows];
	for (int i = 0; i < rows; i++)
		box[i] = new char[columns];
}

Board::Board(int rows_, int columns_, int rowsFilled_)
{
	rows = rows_ + 2;
	columns = columns_ + 2;
	rowsFilled = rowsFilled_;

	ball.position.x = columns / 2;
	ball.position.y = rows / 2;
	ball.velocity.x = 0;
	ball.velocity.y = 1;
	ball.sprite = '*';

	for (int i = 0; i < 3; i++) {
		platform.position[i].x = columns / 2 + i;
		platform.position[i].y = rows - 3;
	}
	platform.sprite = '-';

	box = new char*[rows];
	for (int i = 0; i < rows; i++)
		box[i] = new char[columns];
}

Board::~Board()
{
}

bool Board::platformColision() {
	return (box[ball.position.y + ball.velocity.y][ball.position.x + ball.velocity.x] == '-');
}

bool Board::gameOver() {
	if (GetAsyncKeyState(VK_ESCAPE))
		return true;
	else
		return false;
}

void Board::inicializeBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1)
				box[i][j] = '_';
			else if (j == 0 || j == columns - 1)
				box[i][j] = '|';
			else if (i == ball.position.y && j == ball.position.x)
				box[i][j] = ball.sprite;
			else if (i <= rowsFilled)
				box[i][j] = '@';
			else
				box[i][j] = ' ';
		}
	}
	for (int i = 0; i < 3; i++)
		box[platform.position[i].y][platform.position[i].x] = platform.sprite;
}

void Board::getData() {
	char ignore;	//creo que esto es una cutrada pero por ahora es un "parche"
	std::ifstream dataIn("data.txt");
	if (dataIn.is_open()) {
		while (!dataIn.eof()) {
			dataIn >> rows >> ignore >> columns >> ignore >> rowsFilled >> ignore;
		}
		dataIn.close();
	}
}

void Board::updatePlatform() {
	

	if (GetAsyncKeyState(VK_LEFT)) {
		for (int i = 0; i < 3; i++) {
			platform.position[i].x--;
			if (platform.position[i].x == columns - 2)
				platform.position[i].x = 2;
			else if (platform.position[i].x == 1) {
				platform.position[i].x = columns - 3;
			}
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		for (int i = 0; i < 3; i++) {
			platform.position[i].x--;
			if (platform.position[i].x == columns - 2)
				platform.position[i].x = 2;
			else if (platform.position[i].x == 1) {
				platform.position[i].x = columns - 3;
			}
		}
	}

	for (int i = 0; i < 3; i++)
		box[platform.position[i].y][platform.position[i].x] = platform.sprite;
}

void Board::updateBall() {
	if (ball.position.y == 1 || ball.position.y == rows - 2 || platformColision())
		ball.velocity.y *= -1;
	if (ball.position.x == 1 || ball.position.x == columns - 2 || platformColision())
		ball.velocity.x *= -1;

	ball.position.x += ball.velocity.x;
	ball.position.y += ball.velocity.y;
}

void Board::updateBoard() {
	updateBall();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1)
				box[i][j] = '_';
			else if (j == 0 || j == columns - 1)
				box[i][j] = '|';
			else if (i == ball.position.y && j == ball.position.x)
				box[i][j] = ball.sprite;
			else if (i <= rowsFilled)
				box[i][j] = '@';
			else
				box[i][j] = ' ';
		}
	}
	updatePlatform();
}

void Board::printBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << box[i][j];
		std::cout<<std::endl;
	}
}