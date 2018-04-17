#pragma once
#include <deque>

class Board
{
	struct Position {
		int x;
		int y;
	};
	struct Velocity {
		int x;
		int y;
	};
	struct Ball {
		Position position;
		Velocity velocity;
		char sprite;
	};
	struct Platform {
		Position position[3];
		char sprite;
	};
	struct Box {
		char show;
		bool block;
	};

private:
	int score;					//Variable dónde se guarda el score de la partida
	int rows;					//Número de filas del tablero
	int columns;				//Número de columnas del tablero
	Box **box;					//Array de caracteres para el tablero
	int rowsFilled;				//Número de filas que tendran bloques
	std::deque<int> points;		//Cola dónde se guardan las puntuaciones

	Ball ball;					//Pelota (incluye Posición (x,y) y Velocidad (x,y))
	Platform platform;			//Pelota (incluye una array de Posición[3] y un caracter)

public:
	Board();					//Constructor básico (genera un tablero 20x30 con 10 filas de bloques)
	Board(int data[]);			//Constructor por valores de array
	~Board();					//Destructor

	bool platformCollision();	//Devuelve true si la siguiente/actual posición de la ball forma parte de la plataforma
	bool blockCollision();		//Devuelve true si la siguiente posición de la ball es un block true
	bool gameOver();

	void inicializeBoard();

	void updateBall();
	void updatePlatform();
	void updateBoard();
	void printBoard();
};

