#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

int main() {
	Board prueba;
	
	prueba.inicializeBoard();
	prueba.printBoard();

	while (!prueba.gameOver()) {
		system("cls");
		prueba.updateBoard();
		prueba.printBoard();
		Sleep(100);
	}
	return 0;
}