#include "board.h"
#include <iostream>

using namespace std;

Plansza::Plansza()
{
	 hOut = GetStdHandle( STD_OUTPUT_HANDLE );
}

Plansza::~Plansza()
{

}


void Plansza::gotoxy(int x,int y)
{
	COORD pos={x,y};
	//HANDLE out = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleCursorPosition(hOut, pos);
}

bool Plansza::CzyszczeniePlanszy()
{
	for (int i = 0; i < nWymiarPlanszy; ++i)
		for (int j = 0; j < nWymiarPlanszy; ++j)
			aPlansza[i][j] = FLD_EMPTY;
	return true;
}

bool Plansza::RysowaniePlanszy()
{
	system("cls");
	cout << ' ';
	for (int i = 0; i < nWymiarPlanszy; ++i)
		cout << "-";
	cout << endl;
	for (int i = 0; i < nWymiarPlanszy; ++i)
	{
		cout << '|';
		for (int j = 0; j < nWymiarPlanszy; ++j)
			cout << ' ';
		cout << '|';
		if (i == 5)
			cout << "	PUNKTY";
		else if (i == 7)
			cout << "	POZIOM";
		cout << endl;
	}
	cout << ' ';
	for (int i = 0; i < nWymiarPlanszy; ++i)
		cout << "-";
	return true;
}

void Plansza::CzyscPlansze(pt::Point poi, pt::Point spoi)
{
	gotoxy(poi.x, poi.y);
	cout << ' ';
	gotoxy(spoi.x, spoi.y);
	cout << ' ';
}
void Plansza::AktualizujPlansze(pt::Point poi, pt::Point spoi, int nPunkty, int nPoziom)
{
	gotoxy(poi.x, poi.y);
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << static_cast<char>(FLD_POINT);
	gotoxy(spoi.x, spoi.y);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	cout << static_cast<char>(FLD_SNAKE);
	SetConsoleTextAttribute(hOut, 0x0007);
	gotoxy(nWymiarPlanszy + 4, 7);
	cout << nPunkty;
	gotoxy(nWymiarPlanszy + 4, 9);
	cout << nPoziom;
}

int Plansza::SprawdzeniePlanszy(int nLength, Snake& snake, pt::Point poi)
{
	int j = 0;
	for (int i = 1; i < nLength; ++i)
		if (snake.GetN1().x == snake.GetSnake()[i][0] && snake.GetN1().y == snake.GetSnake()[i][1]) // jeœli w¹¿ wpad³ w siebie zwiêkszamy j
			++j;
	if (snake.GetN1().x <= 0 || snake.GetN1().x > nWymiarPlanszy || snake.GetN1().y <= 0 || snake.GetN1().y > nWymiarPlanszy)	// jeœli w¹¿ wypad³ z planszy
		return 0;
	else if (snake.GetN1().x == poi.y && snake.GetN1().y == poi.x) // jeœli w¹¿ zebra³ punkt
		return 1;
	else if (j > 0)
		return 0;
	else
		return 2;
}