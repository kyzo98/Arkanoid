#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <fstream>

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
	int data[dataNum];							//Array donde guardamos la data del archivo
	getData(data, dataNum);						//Función para leer y guardar la data dentro del array

	Board prueba(data);							//Creamos el board con el constructor por valores que sacamos del array data

	prueba.inicializeBoard();					//Inicializamos el board
	prueba.printBoard();						//Pintamos la primera vez el board

	while (!prueba.gameOver()) {				//Mientras la función gameOver() no devuelva true se ejectutará el juego
		system("cls");							//Limpiamos la pantalla anterior
		prueba.updateBoard();					//Actualizamos los movimientos sobre el board
		prueba.printBoard();					//Pintamos el board
		Sleep(100);								//100 milisegundos entre acción y acción
	}

	if (prueba.youWin()) {
		system("cls");
		std::cout << "YOU WIN" << std::endl;
		std::cout << "Score: " << prueba.getScore() << std::endl;
	}

	if (prueba.gameOver()) {
		system("cls");
		std::cout << "YOU LOSE" << std::endl;
		std::cout << "Score: " << prueba.getScore() << std::endl;
	}

	system("pause");
	return 0;
}