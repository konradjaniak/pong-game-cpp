#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

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
		srand(time(NULL));
	}

	void Reset()
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void changeDirection(eDir d)
	{
		direction = d;
	}

	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
	}

	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }
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

int main()
{
	cBall c(0, 0);
	std::cout << c << std::endl;
	c.randomDirection();
	std::cout << c << std::endl;
	c.Move();
	std::cout << c << std::endl;
	c.randomDirection();
	c.Move();
	std::cout << c << std::endl;
	c.randomDirection();
	c.Move();
	std::cout << c << std::endl;

	return 0;
}