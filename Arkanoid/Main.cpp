#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <map>

#define VK_NUM_0 '0'
#define VK_NUM_1 '1'
#define VK_NUM_2 '2'

enum class GameState{ EXIT, MENU, PLAY, SCORE, RANKING};
enum class Keyboard{ K_ESC, K_LEFT, K_RIGHT, K_0, K_1, K_2, K_NUM };

int const dataNum = 5;		//Constante en la que definimos el n�mero de valores que recogeremos del fichero

//Funci�n en la que pasamos un array para guardar en �l lo que leemos en un archivo
void getData(int data[], int size) {
	char ignore;								//Char para ignorar los ; del archivo
	std::ifstream dataIn("data.txt");			//dataIn es el archivo de donde extraemos data.txt

	if (dataIn.is_open()) {						//Si se abre el archivo data.txt
		while (!dataIn.eof()) {					//Mientras entre informaci�n
			for(int i = 0; i < size; i++)		//Leemos tantos datos como int como size tiene el array
				dataIn >> data[i] >> ignore;	//Guardamos cada int del archivo en un espacio del array
		}
		dataIn.close();							//Una vez terminado el proceso se cierra el archivo
	}
}
 
//Funci�n que lee el r�nking.txt y lo guarda en un map que le pasamos
void readRanking(std::map<std::string, int> &r) {
	std::string key;							//String que guardar� la key (nombre del player)
	int score;
	r.clear();									//Vaciamos para asegurarnos que no quedan keys residuales
	std::ifstream dataIn("ranking.txt");		//dataIn es el archivo de donde extraemos ranking.txt

	if (dataIn.is_open()) {						//Si se abre el archivo data.txt
		while (!dataIn.eof()) {					//Mientras entre informaci�n
			dataIn >> key >> score;				//Guardamos cada key con su score
			r[key] = score;
		}
		dataIn.close();							//Una vez terminado el proceso se cierra el archivo
	}
}

//Funci�n que retorna el score m�s bajo del map que le pasamos
int getLowestScore(std::map<std::string, int> r) {
	if (!r.empty()) {
		auto f = r.begin();
		int lowest = f->second;
		for (auto it = r.begin(); it != r.end(); it++)
			if (lowest > it->second)
				lowest = it->second;

		return lowest;
	}
	else {
		return 0;
	}
}

//Funci�n que elimina del map al jugador de menor puntuaci�n
void deleteLowestRanked(std::map<std::string, int> &r){
	auto f = r.begin();
	int lowest = f->second;
	std::string lowestPlayer = f->first;
	for (auto it = r.begin(); it != r.end(); it++)
		if (lowest > it->second) {
			lowest = it->second;
			lowestPlayer = it->first;
		}

	r.erase(lowestPlayer);
}

//Funci�n que guarda el map dentro de ranking.txt
void saveRanking(std::map<std::string, int> r) {
	std::ofstream dataOut;
	dataOut.open("ranking.txt", std::ofstream::out | std::ofstream::trunc);

	if (dataOut.is_open())
	{
		for (auto it = r.begin(); it != r.end(); it++)
			dataOut << it->first << " " << it->second << std::endl;
		dataOut.close();
	}
}

//Funci�n que imprime el ranking en orden de puntuaci�n
void printRanking(std::map<std::string, int> r) {
	if (!r.empty()) {
		int t = r.size();
		for (int i = 0; i < t; i++) {
			auto f = r.begin();
			int highest = f->second;
			std::string highestPlayer = f->first;
			for (auto it = r.begin(); it != r.end(); it++) {
				if (highest < it->second) {
					highest = it->second;
					highestPlayer = it->first;
				}
			}

			std::cout << i+1 << "- " << highestPlayer << " " << highest << std::endl;
			r.erase(highestPlayer);
		}
	}
	else {
		std::cout << "No scores saved." << std::endl;
	}
}

int main() {
	GameState gameState = GameState::MENU;		//Variable para guardar el estado de ejecucu�n del juego: estado inicial MENU
	bool keyboard[int(Keyboard::K_NUM)];		//Array para guardar los valores de las teclas

	int menuSelector;							//Variable para guardar lo que selecciona el usuario
	std::string playerName;						//Variable para guardar el nombre del player
	int tmpScore;

	int data[dataNum];							//Array donde guardamos la data del archivo
	getData(data, dataNum);						//Funci�n para leer y guardar la data dentro del array

	Board board(data);							//Creamos el board con el constructor por valores que sacamos del array data

	std::map<std::string, int> ranking;			//Map para guardar el ranking

	do {
		//Key Controller
		keyboard[int(Keyboard::K_LEFT)] = GetAsyncKeyState(VK_LEFT);
		keyboard[int(Keyboard::K_RIGHT)] = GetAsyncKeyState(VK_RIGHT);
		keyboard[int(Keyboard::K_ESC)] = GetAsyncKeyState(VK_ESCAPE);
		keyboard[int(Keyboard::K_0)] = GetAsyncKeyState(VK_NUM_0);
		keyboard[int(Keyboard::K_1)] = GetAsyncKeyState(VK_NUM_1);
		keyboard[int(Keyboard::K_2)] = GetAsyncKeyState(VK_NUM_2);


		switch (gameState) {					//Switch de control de escenas del juego
		case GameState::MENU:					//L�gica del men�
			system("cls");
			std::cout << "------- ARKANOID -------" << std::endl;
			std::cout << "1- Play" << std::endl;
			std::cout << "2- Ranking" << std::endl;
			std::cout << "0- Exit" << std::endl;

			if(keyboard[int(Keyboard::K_ESC)] || keyboard[int(Keyboard::K_0)]) {	//En caso de que presione escape se cierra
				gameState = GameState::EXIT;
			}
			else if (keyboard[int(Keyboard::K_1)]) {
				gameState = GameState::PLAY;
			}
			else if (keyboard[int(Keyboard::K_2)]) {
				gameState = GameState::RANKING;
			}
			break;
		case GameState::PLAY:					//Juego
			board = *new Board(data);					//No se porque funciona esto
			board.inicializeBoard();					//Inicializamos el board
			board.printBoard();							//Pintamos la primera vez el board

			while (!board.gameOver()) {					//Mientras la funci�n gameOver() no devuelva true se ejectutar� el juego
				keyboard[int(Keyboard::K_LEFT)] = GetAsyncKeyState(VK_LEFT);
				keyboard[int(Keyboard::K_RIGHT)] = GetAsyncKeyState(VK_RIGHT);
				keyboard[int(Keyboard::K_ESC)] = GetAsyncKeyState(VK_ESCAPE);
				system("cls");							//Limpiamos la pantalla anterior
				board.updateBoard(keyboard[int(Keyboard::K_LEFT)], keyboard[int(Keyboard::K_RIGHT)]);		//Actualizamos los movimientos sobre el board
				board.printBoard();						//Pintamos el board

				if (keyboard[int(Keyboard::K_ESC)]) {	//En caso de que el player presione esc se sale del bucle sin gameOver true para cerrar el juego
					break;
				}

				Sleep(board.difficultyMs());			//Milisegundos entre acciones del juego
			}
			if(board.gameOver())
				gameState = GameState::SCORE;				//En caso de que el player pierda o gane guarda el score
			else
				gameState = GameState::EXIT;

			break;
		case GameState::SCORE:					//Guardar puntuaciones
			system("cls");
			tmpScore = board.getScore();
			std::cout << "GAME OVER" << std::endl;
			std::cout << "Your score is " << tmpScore << std::endl;
			std::cout << "Please eneter your name" << std::endl;
			std::cin >> playerName;

			readRanking(ranking);
			if (ranking.size() >= 5) {					//Si hay ya 5 puntuaciones guardadads
				if (tmpScore >= getLowestScore(ranking)) {//Si el score que hemos obtenido en la partida es mayor al m�s peque�o que hay guardado
					deleteLowestRanked(ranking);		//Elimina la puntuaci�n m�s baja existente
					ranking[playerName] = tmpScore;		//Guarda el nuevo player con su puntuaci�n
				}
			}
			else {
				ranking[playerName] = tmpScore;			//Guarda el nuevo player con su puntuaci�n
			}
			
			saveRanking(ranking);						//Guarda el map en el .txt
			gameState = GameState::MENU;				//Cambia de pantalla
			break;
		case GameState::RANKING:				//Mostrar r�nquing
			system("cls");
			std::cout << "RANKING" << std::endl;
			readRanking(ranking);						//Lee el ranking del fichero ranking.txt
			printRanking(ranking);						//Imprime el ranking

			if (keyboard[int(Keyboard::K_ESC)]) {		//En caso de que presione escape se cierra
				gameState = GameState::MENU;
				Sleep(100);								//Este sleep es para que no se cierre directamente el juego (al presionar una vez escape se va al men�, pero si en el men� presionas escape tambi�n se cierra entonces pongo un peque�o delay para que no ocurra esto)
			}
		}
	} while (gameState != GameState::EXIT);		//Bucle de control de escenas del juego, mientras el gameState no sea exit se fluir� entre escenas

	return 0;
}