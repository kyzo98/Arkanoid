#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <fstream>

enum class GameState{ EXIT, MENU, PLAY, SCORE, RANKING};

int const dataNum = 5;		//Constante en la que definimos el número de valores que recogeremos del fichero

//Funcón en la que pasamos un array para guardar en él lo que leemos en un archivo
void getData(int data[], int size) {
	char ignore;								//Char para ignorar los ; del archivo
	std::ifstream dataIn("data.txt");			//dataIn es el archivo de donde extraemos data.txt

	if (dataIn.is_open()) {						//Si se abre el archivo data.txt
		while (!dataIn.eof()) {					//Mientras entre información
			for(int i = 0; i < size; i++)		//Leemos tantos datos como int como size tiene el array
				dataIn >> data[i] >> ignore;	//Guardamos cada int del archivo en un espacio del array
		}
		dataIn.close();							//Una vez terminado el proceso se cierra el archivo
	}
}

int main() {
	GameState gameState = GameState::MENU;		//Variable para guardar el estado de ejecucuón del juego: estado inicial MENU
	int menuSelector;							//Variable para guardar lo que selecciona el usuario

	int data[dataNum];							//Array donde guardamos la data del archivo
	getData(data, dataNum);						//Función para leer y guardar la data dentro del array

	Board board(data);							//Creamos el board con el constructor por valores que sacamos del array data

	do {
		switch (gameState) {					//Switch de control de escenas del juego
		case GameState::MENU:					//Lógica del menú
			system("cls");
			std::cout << "------- ARKANOID -------" << std::endl;
			std::cout << "1- Play" << std::endl;
			std::cout << "2- Ranking" << std::endl;
			std::cout << "0- Exit" << std::endl;

			std::cin >> menuSelector;					//Leemos usuario

			switch (menuSelector) {						//Switch para cambiar de escenas en función de lo que quiere el usuario
			case 0:
				gameState = GameState::EXIT;
				break;
			case 1:
				gameState = GameState::PLAY;
				break;
			case 2:
				gameState = GameState::RANKING;
				break;
			default:
				break;
			}
			break;
		case GameState::PLAY:					//Juego
			board.inicializeBoard();					//Inicializamos el board
			board.printBoard();							//Pintamos la primera vez el board

			while (!board.gameOver()) {					//Mientras la función gameOver() no devuelva true se ejectutará el juego
				system("cls");							//Limpiamos la pantalla anterior
				board.updateBoard();					//Actualizamos los movimientos sobre el board
				board.printBoard();						//Pintamos el board
				Sleep(100);								//100 milisegundos entre acción y acción
			}

			if (board.gameOver()) {						//En caso de que el player pierda o se retire
				gameState = GameState::SCORE;
			}

			break;
		case GameState::SCORE:					//Guardar puntuaciones
			system("cls");
			std::cout << "GAME OVER" << std::endl;
			std::cout << "Score: " << board.getScore() << std::endl;
			break;
		case GameState::RANKING:				//Mostrar ránquing
			
			break;
		}
	} while (gameState != GameState::EXIT);		//Bucle de control de escenas del juego, mientras el gameState no sea exit se fluirá entre escenas

	return 0;
}