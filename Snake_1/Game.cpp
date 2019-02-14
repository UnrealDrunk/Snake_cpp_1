#include<iostream>
#include<conio.h>

using namespace std;

bool GameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, FruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	GameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	FruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;

	for(int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width -1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == FruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
						
				}
				if (!print)
					cout << " ";
			}
			
		}
		cout << endl;
	}

	for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			GameOver = true;
			break;
		
		}
	}


}

void Logic()
{
	int PrevX = tailX[0];
	int PrevY = tailY[0];
	int Prev2X, Prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		Prev2X = tailX[i];
		Prev2Y = tailY[i];
		tailX[i] = PrevX;
		tailY[i] = PrevY;
		PrevX = Prev2X;
		PrevY = Prev2Y;

	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0)
		//GameOver = true;

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			GameOver = true;
	}

	if (x == fruitX && y == FruitY)
	{
		score += 10;
		fruitX = rand() % width;
		FruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();

	}




}