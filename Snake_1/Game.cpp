#include<iostream>
#include<conio.h>
#include<Windows.h>

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
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);


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
	/*cout << "Game rules: " << endl << "use 'W' 'A' 'S' 'D' to control snake's direction, try to eat (F) fruits to get scores" << endl;
	cout << "Every eaten fruit gives you 10 scores. Yor goal is to reach the ammount of 200 scores" << endl;
	cout << "You can walk through the walls and teleport back to the area from the other side of the game field" << endl;
	cout << "But this teleportation isn't for free, it will reduce your ammount of scores by 10 each time you touch the wall" << endl;
	cout << "The reason not to allow your score balance be lower than zero is the Game is over" << endl;
	cout << "By the way, don't touch your tail, it's very dangerous for the hungry snake :) " << endl;*/

	
	cout << endl << "Score: " << score << endl;
	if (score < 0)
	{
		cout << " Game over" << endl;
		system("Pause");
	}
	else if (score > 190)
	{
		cout << " YOU WIN!!! Congratulations" << endl;
		system("Pause");
	}
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
	{
		x = 0;
		score -= 10;
	}
	else if (x < 0)
	{
		x = width - 2;
		score -= 10;
	}


	if (y >= height)
	{
		y = 0;
		score -= 10;
	}
	else if (y < 0)
	{
		y = height - 1;
		score -= 10;
	}

		
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			GameOver = true;
			system("Pause");
		}
			
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