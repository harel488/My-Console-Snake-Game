#include <iostream>
#include <ctime>
#include <conio.h>
#include "point.h"
#include <fstream>

#include <thread>
using namespace std;
#define hight 20
#define width 40

//checking if the point is in the prevPoint array
bool is_prev(point& head, int i, int j)
{
	if (head.x == i && head.y == j)
		return true;
	return false;
}


//the display function- printing the game
void display(point& head, point& fruit, point* v, int size, int snakeSize, int score)
{
	system("cls");
	for (int i = 0; i < hight; i++)
		for (int j = 0; j < width; j++)
		{

			if (i == 0 || i == hight - 1)
			{
				if (j == width - 1)
					cout << "*" << endl;
				else
					cout << "*";
			}
			else
			{
				if (j == 0)
					cout << "*";
				else if (j == width - 1)
					cout << "*" << endl;
				else
				{
					cout << " ";
				}
			}
			if (head.x == i && head.y == j)
			{
				cout << '\b' << "o";
			}
			if (fruit.x == i && fruit.y == j)
			{
				cout << '\b' << "$";
			}
			if (snakeSize > 1)
			{
				for (int t = (size - 1); t > (size - 1) - snakeSize; t--)
				{
					if (is_prev(v[t], i, j))
					{
						cout << '\b' << "o";
					}
				}
			}
		}

	cout << endl << "score: " << score << endl;
}




int main()
{
	cout << "Please use W to up , S to down , D to right , A to left. "  // open massage
		<< endl<<"notice your keyboard is on English mode "
		<<endl<<"Push any key to continue";
	
	while (!_kbhit()) {

	}
	fstream f("highScore.txt");//to save the high score

	
	bool gameOver = false;
	srand((unsigned)time(NULL));
	point head(hight / 2, width / 2);
	point fruit(rand() % (hight - 2) + 1, rand() % (width - 2) + 1);
	int snakeSize = 1;
	int size = 1;
	int score = 0;

	point* prevPoints = new point[1]; //array for all the points that the snake was in
	prevPoints[0] = head;

	char key, prevKey;
	display(head, fruit, prevPoints, size, snakeSize, score);
	key = _getch();
	prevKey = key;
	while (!gameOver)
	{
		if (_kbhit())
		{
			key = _getch();
			if (prevKey == 'w'&&key == 's' || prevKey == 's'&&key == 'w' || prevKey == 'd'&&key == 'a' || prevKey == 'a'&& key == 'd')
				key = prevKey;
			else
				prevKey = key;
		}
		switch (key)
		{
		case 'w':
			--head.x;
			break;
		case 's':
			++head.x;
			break;
		case 'd':
			++head.y;
			break;
		case 'a':
			--head.y;
			break;

		default:
			break;
		}

		if (head.x == 0 || head.x == hight - 1 || head.y == 0 || head.y == width - 1) //if the snake in the wall
			gameOver = true;

		if (snakeSize > 1) // if the snake crash himself
		{
			for (int i = (size - 1); i > ((size - 1) - snakeSize); i--) {
				if (head == prevPoints[i])
					gameOver = true;
			}
		}


		if (head == fruit) //if the snake eat fruit
		{
			fruit.x = rand() % (hight - 2) + 1;
			fruit.y = rand() % (width - 2) + 1;
			++snakeSize;
			score += 5;
		}


		////////////////////////////////////////////
		//adding the last point to prevPoint array
		point*tmp = new point[size + 1];
		for (int i = 0; i < size; i++)
			tmp[i] = prevPoints[i];
		tmp[size] = head;
		size++;
		delete[] prevPoints;
		prevPoints = new point[size];
		for (int i = 0; i < size; i++)
		{
			prevPoints[i] = tmp[i];
		}
		delete[] tmp;

		///////////////////////////////////////////////	

		display(head, fruit, prevPoints, size, snakeSize, score);



	}
	system("cls");
	//////////////////////////////////////////
	// printing the game-over massage and the high score
	int prev_hscore;
	f >> prev_hscore;
	if (score > prev_hscore)
	{
		f.seekg(ios::beg);
		f << score;
		cout << "game-over!" << endl;
		cout << "the new high score is: " << score << endl;
	}
	else
	{
		cout << "game-over!" << endl << "your score is: " << score << endl;
		cout << "the high score is: " << prev_hscore << endl;
	}
	system("pause");
	return 0;
}