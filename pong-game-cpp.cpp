#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

enum eDir{STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cBall(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	void Reset()
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void ChangeDirection(eDir d)
	{
		direction = d;
	}

	void RandomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
	}

	inline int GetX() { return x; }
	inline int GetY() { return y; }
	inline eDir GetDirection() { return direction; }

	void Move()
	{
		switch(direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		default:
			break;
		}
	}

	friend std::ostream & operator<<(std::ostream & o, cBall c)
	{
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
};

class cPaddle
{
private:
	int x = 0, y = 0;
	int originalX, originalY;
public:
	cPaddle()
	{
		x = 0;
		y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() { x = originalX; y = originalY; }
	inline int GetX() { return x; }
	inline int GetY() { return y; }
	inline void MoveUp() { y--; }
	inline void MoveDown() { y++; }
	friend std::ostream & operator<<(std::ostream & o, cPaddle c)
	{
		o << "Paddle [" << c.x << ", " << c.y << "]";
		return o;
	}
};

class cGameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall * ball;
	cPaddle * player1;
	cPaddle * player2;
	char ballChar = 'O';
public:
	cGameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		up2 = 'i';
		down1 = 's';
		down2 = 'k';
		score1 = 0;
		score2 = 0;
		width = w;
		height = h;
		ball = new cBall(w / 2, h / 2);
		player1 = new cPaddle(1, h / 2 - 3);
		player2 = new cPaddle(w - 2, h / 2 - 3);
	}
	~cGameManager()
	{
		delete ball, player1, player2;
	}

	void ScoreUp(cPaddle * player)
	{
		if(player == player1)
			score1++;
		else if(player == player2)
			score2++;
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Draw()
	{
		system("cls");
		for(int i = 0; i < width + 2; i++)
		{
			std::cout << "\xB2";
		}
		std::cout << std::endl;

		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				int ballX = ball->GetX();
				int ballY = ball->GetY();
				int player1X = player1->GetX();
				int player2X = player2->GetX();
				int player1Y = player1->GetY();
				int player2Y = player2->GetY();

				if(j == 0)
					std::cout << "\xB2";

				if(ballX == j && ballY == i)
					//std::cout << "O";	// ball
					printf("%c", ballChar);
				else if(player1X == j && player1Y == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player1
				else if(player2X == j && player2Y == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player2
				else if(player1X == j && player1Y + 1 == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player1 (extension)
				else if(player1X == j && player1Y + 2 == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player1 (extension)
				else if(player1X == j && player1Y + 3 == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player1 (extension)
				else if(player2X == j && player2Y + 1 == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player2 (extension)
				else if(player2X == j && player2Y + 2 == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player2 (extension)
				else if(player2X == j && player2Y + 3 == i)
					printf("%c", '\xDB');
				//std::cout << "\xDB";	// player2 (extension)
				else
					printf(" ");
					//std::cout << " ";

				if(j == width - 1)
					printf("%c", '\xDB');
					//std::cout << "\xB2";
			}
			printf("\n");
			//std::cout << std::endl;
		}
		for(int i = 0; i < width + 2; i++)
		{
			std::cout << "\xB2";
		}
		std::cout << std::endl;

		std::cout << "Score 1: " << score1 << std::endl;
		std::cout << "Score 2: " << score2 << std::endl;
	}

	void Input()
	{
		ball->Move();

		int ballX = ball->GetX();
		int ballY = ball->GetY();
		int player1X = player1->GetX();
		int player2X = player2->GetX();
		int player1Y = player1->GetY();
		int player2Y = player2->GetY();

		if(_kbhit())
		{
			char currentChar = _getch();
			if(currentChar == up1)	// w
				if(player1Y > 0)
					player1->MoveUp();
			if(currentChar == up2)	// i
				if(player2Y > 0)
					player2->MoveUp();
			if(currentChar == down1)	// s
				if(player1Y + 4 < height)
					player1->MoveDown();
			if(currentChar == down2)	// k
				if(player2Y + 4 < height)
					player2->MoveDown();

			if(ball->GetDirection() == STOP)
			{
				ball->RandomDirection();
			}

			if(currentChar == 'q')
				quit = true;
		}
	}

	void Logic()
	{
		int ballX = ball->GetX();
		int ballY = ball->GetY();
		int player1X = player1->GetX();
		int player2X = player2->GetX();
		int player1Y = player1->GetY();
		int player2Y = player2->GetY();

		// ball hits left paddle
		for(int i = 0; i < 4; i++)
		{
			if(ballX == player1X + 1)
				if(ballY == player1Y + i)
					ball->ChangeDirection((eDir)((rand() % 3) + 4));
		}
			
		// ball hits right paddle
		for(int i = 0; i < 4; i++)
		{
			if(ballX == player2X - 1)
				if(ballY == player2Y + i)
					ball->ChangeDirection((eDir)((rand() % 3) + 1));
		}

		// ball hits bottom wall
		if(ballY == height - 1)
			ball->ChangeDirection(ball->GetDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		// ball hits top wall
		if(ballY == 0)
			ball->ChangeDirection(ball->GetDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		// ball hits right wall
		if(ballX == width - 1)
			ScoreUp(player1);

		// ball hits left wall
		if(ballX == 0)
			ScoreUp(player2);
	}

	void Run()
	{
		while(!quit)
		{
			Sleep(10);
			Draw();
			Input();
			Logic();
		}
	}
};

int main()
{
	cGameManager game(40, 20);
	game.Run();

	return 0;
}