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
	int lives;					//Número de vidas
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
	bool gameOver();			//Devuelve true si se apreta esc
	bool youWin();				//Devuelve true si rompes todos los bloques

	int getScore();				//Devuelve el score
	int difficultyMs();			//Devuelve los milisegundos que tarda en hace refresh según el número de bloques restantes

	void inicializeBoard();		//Prepara el board por primera vez

	void updateBall();			//Actualiza la bola
	void updatePlatform(bool l, bool r);		//Actualiza la plataforma
	void updateBoard(bool l, bool r);			//Actualiza todo el tablero
	void printBoard();			//Pinta el tablero
};