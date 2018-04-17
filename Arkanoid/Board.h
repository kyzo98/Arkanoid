#pragma once
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
		Position position;
		char sprite;
	};

private:
	int rows;
	int columns;
	char **box;
	int rowsFilled;

	Ball ball;
	Platform platform;

public:
	Board();
	Board(int rows_, int columns_, int rowsFilled_);
	~Board();

	bool platformColision();
	bool gameOver();

	void inicializeBoard();
	void getData();

	void updateBall();
	void updatePlatform();
	void updateBoard();
	void printBoard();
};

