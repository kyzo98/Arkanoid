#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

Board::Board()
{
	//Filas, columna, filas de bloques, score
	rows = 20+2;
	columns = 30+2;
	rowsFilled = rows / 2;
	score = 0;

	//Valores de la cola points
	for (int i = 0; i < rowsFilled * (columns-2); i++) {
		points.push_back(rand() % 5 + 1);
	}

	//Valores iniciales de la ball
	ball.position.x = columns / 2;
	ball.position.y = rows / 2;
	ball.velocity.x = -1;
	ball.velocity.y = 1;
	ball.sprite = '*';

	//Valores iniciales de la platform
	for (int i = 0; i < 3; i++) {
		platform.position[i].x = columns / 2 + i;
		platform.position[i].y = rows - 3;
	}
	platform.sprite = '-';

	//Creamos el array 2D de box
	box = new Box*[rows];
	for (int i = 0; i < rows; i++)
		box[i] = new Box[columns];
}

Board::Board(int data[])
{
	//Filas, columna, filas de bloques, score
	rows = data[0] + 2;
	columns = data[1] + 2;
	rowsFilled = data[2];
	score = 0;

	//Valores de la cola points
	for (int i = 0; i < rowsFilled * (columns - 2); i++) {
		points.push_back(rand()%data[4] + data[3]);
	}

	//Valores iniciales de la ball
	ball.position.x = columns / 2;
	ball.position.y = rows / 2;
	ball.velocity.x = 1;
	ball.velocity.y = 1;
	ball.sprite = '*';

	//Valores iniciales de la platform
	for (int i = 0; i < 3; i++) {
		platform.position[i].x = columns / 2 + i;
		platform.position[i].y = rows - 3;
	}
	platform.sprite = '-';

	//Creamos el array 2D de box
	box = new Box*[rows];
	for (int i = 0; i < rows; i++)
		box[i] = new Box[columns];
}

Board::~Board()
{
}

bool Board::platformCollision() {
	bool collision = false;
	for (int i = 0; i < 3; i++) {
		if (((ball.position.y + ball.velocity.y == platform.position[i].y) && (ball.position.x + ball.velocity.x == platform.position[i].x)) || ((ball.position.y == platform.position[i].y) && (ball.position.x == platform.position[i].x)))
			collision = true;
	}
	return collision;
}

bool Board::blockCollision() {
	bool collision = false;
	if (box[ball.position.y][ball.position.x].block == true) {
		collision = true;
		box[ball.position.y][ball.position.x].block = false;
		score += points.front();
		points.pop_front();
	}
	return collision;
}

bool Board::gameOver() {
	if (GetAsyncKeyState(VK_ESCAPE) || youWin())
		return true;
	else
		return false;
}

bool Board::youWin() {
	if (points.empty())
		return true;
	else
		return false;
}

int Board::getScore() {
	return score;
}

void Board::inicializeBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1) {
				box[i][j].show = '_';
				box[i][j].block = false;
			}
			else if (j == 0 || j == columns - 1) {
				box[i][j].show = '|';
				box[i][j].block = false;
			}
			else if (i == ball.position.y && j == ball.position.x) {
				box[i][j].show = ball.sprite;
				box[i][j].block = false;
			}
			else if (i <= rowsFilled) {
				box[i][j].show = '@';
				box[i][j].block = true;
			}
			else {
				box[i][j].show = ' ';
				box[i][j].block = false;
			}
		}
	}
	for (int i = 0; i < 3; i++)
		box[platform.position[i].y][platform.position[i].x].show = platform.sprite;
}

void Board::updatePlatform() {
	if (GetAsyncKeyState(VK_LEFT)) {
		for (int i = 0; i < 3; i++) {
			platform.position[i].x--;
			if (platform.position[i].x == columns - 1)
				platform.position[i].x = 1;
			else if (platform.position[i].x == 0) {
				platform.position[i].x = columns - 2;
			}
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		for (int i = 0; i < 3; i++) {
			platform.position[i].x++;
			if (platform.position[i].x == columns - 1)
				platform.position[i].x = 1;
			else if (platform.position[i].x == 0) {
				platform.position[i].x = columns - 2;
			}
		}
	}

	for (int i = 0; i < 3; i++)
		box[platform.position[i].y][platform.position[i].x].show = platform.sprite;
}

void Board::updateBall() {
	if (blockCollision() || ball.position.y == 1 || ball.position.y == rows - 2 || platformCollision())
		ball.velocity.y *= -1;

	if (ball.position.x == 1 || ball.position.x == columns - 2)
		ball.velocity.x *= -1;

	ball.position.x += ball.velocity.x;
	ball.position.y += ball.velocity.y;
}

void Board::updateBoard() {
	updateBall();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1)
				box[i][j].show = '_';
			else if (j == 0 || j == columns - 1)
				box[i][j].show = '|';
			else if (i == ball.position.y && j == ball.position.x)
				box[i][j].show = ball.sprite;
			else if (i <= rowsFilled) {
				if (box[i][j].block)
					box[i][j].show = '@';
				else
					box[i][j].show = ' ';
			}
			else
				box[i][j].show = ' ';
		}
	}
	updatePlatform();
}

void Board::printBoard() {
	std::cout << "Score: " << score << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << box[i][j].show;
		std::cout<<std::endl;
	}
}