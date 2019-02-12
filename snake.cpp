#include "snake.h"
#include <windows.h>
#include <conio.h>

using namespace std;

Snake::Snake(int nWymiarPlanszy)
{
	nSnake = new int*[nWymiarPlanszy*nWymiarPlanszy];
	for (int i = 0; i < nWymiarPlanszy*nWymiarPlanszy; ++i)
		nSnake[i] = new int[2];	//tablica pozycji wê¿a
	length = 3;
	nSnake[0][0] = n1.x = nWymiarPlanszy/2;
	nSnake[0][1] = n1.y = nWymiarPlanszy/2;
	nWymiar = nWymiarPlanszy;
	g = 1;
}

Snake::~Snake()
{
	for (int i = 0; i < nWymiar*nWymiar; ++i)
		delete[] nSnake[i];
	delete[] nSnake;
}

bool Snake::Ruch()
{
	char ch;
	bool chb = false;
	while (kbhit())
	{
		ch = getch();
		chb = true;
		switch(ch)
		{
			case 72:
				if (g != 2)
				{
					--n1.x;
					g = 1;
				}
				else
					chb = false;
				break;
			case 80:
				if (g != 1)
				{
					++n1.x;
					g = 2;
				}
				else
					chb = false;
				break;
			case 75:
				if (g != 4)
				{
					--n1.y;
					g = 3;
				}
				else
					chb = false;
				break;
			case 77:
				if (g != 3)
				{
					++n1.y;
					g = 4;
				}
				else
					chb = false;
				break;
			default:
				chb = false;
		}
	}
	if (!chb) // jeœli nie wciœniêto ¿adnego klawisza lub z³y to w¹¿ ma poruszaæ siê w tym samym kierunku
	{
		if (g == 1)
			--n1.x;
		else if (g == 2)
			++n1.x;
		else if (g == 3)
			--n1.y;
		else if (g == 4)
			++n1.y;
	}	// zmiana pozycji g³owy wê¿a
	for (int i = length; i > 0; --i)
	{
		nSnake[i][0] = nSnake[i-1][0]; // przesuniêcie wê¿a
		nSnake[i][1] = nSnake[i-1][1];
	}
	nSnake[0][0] = n1.x;	//przypisanie nowej pozycji pocz¹tku do tablicy
	nSnake[0][1] = n1.y;
	return true;
}