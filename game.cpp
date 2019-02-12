#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "game.h"

using namespace std;

Gra::Gra(int nWymiar)
{
	nWymiarPlanszy = nWymiar;
	snake = new Snake(nWymiar);
	plansza = new Plansza;
	gracz = new Gracz;
}

Gra::~Gra()
{
	if (snake)
	{
		delete snake;
	}
	if (plansza)
	{
		delete plansza;
	}
	if (gracz)
	{
		delete gracz;
	}
}

void Gra::Sortowanie(int* aTablicaWynikow, int lewy, int prawy)
{
	int i,j,piwot;
	i = (lewy + prawy) / 2;
	piwot = aTablicaWynikow[i];
	aTablicaWynikow[i] = aTablicaWynikow[prawy];
	for(j = i = lewy; i < prawy; i++)
		if(aTablicaWynikow[i] < piwot)
		{
			swap(aTablicaWynikow[i], aTablicaWynikow[j]);
			j++;
		}
	aTablicaWynikow[prawy] = aTablicaWynikow[j];
	aTablicaWynikow[j] = piwot;
	if(lewy < j - 1) 
		Sortowanie(aTablicaWynikow, lewy, j - 1);
	if(j + 1 < prawy)
		Sortowanie(aTablicaWynikow, j + 1, prawy);
}

bool Gra::StartGry()
{
	if (snake)
	{
		delete snake;
		snake = new Snake(nWymiarPlanszy);
	}
	if (plansza)
	{
		delete plansza;
		plansza = new Plansza;
	}
	if (gracz)
	{
		delete gracz;
		gracz = new Gracz;
	}
	cout << "Podaj imiê gracza: ";
	cin >> gracz->strImie;
	cout << "Podaj poziom trudnoœci: " << endl;
	cout << "1. £atwy" << endl;
	cout << "2. Œredni" << endl;
	cout << "3. Trudny" << endl;
	cin >> nPoziomTrudnosci;
	if (cin.good())
	{
		switch (nPoziomTrudnosci)
		{
			case 1:
				nLiczbaPunktowNaPoziom = 200;
			case 2:
				nLiczbaPunktowNaPoziom = 100;
			case 3:
				nLiczbaPunktowNaPoziom = 20;
		}
	}
	else
	{
		cin.clear();
		cin.sync();
		nLiczbaPunktowNaPoziom = 10;
		nPoziomTrudnosci = 4;
	}
	nPoziom = 1;
	nPunkty = 0;
	plansza->CzyszczeniePlanszy();
	for (int i = 1; i <= snake->GetLength(); ++i)
	{
		snake->GetSnake()[i][1] = snake->GetN1().y+i;
		snake->GetSnake()[i][0] = snake->GetN1().x;
	}
	for (int i = 0; i < snake->GetLength(); ++i)
		plansza->SetSnake(pt::PointMake(snake->GetSnake()[i][1], snake->GetSnake()[i][0]));
	Gra::Losowanie();
	plansza->SetPoint(nPunkt);
	plansza->RysowaniePlanszy();
	return true;
}

bool Gra::Losowanie()
{
	srand (static_cast<unsigned>(time(NULL)));
	nPunkt.x = rand() % nWymiarPlanszy + 1;
	nPunkt.y = rand() % nWymiarPlanszy + 1;
	return true;
}

bool Gra::Ruch()
{
	int a;
	a = plansza->SprawdzeniePlanszy(snake->GetLength(), *snake, nPunkt);
	switch(a)
	{
		case -1:
			return false;
			break;
		case 0:
			return false;
			break;
		case 1:
			nPunkty += 10 * nPoziomTrudnosci;
			snake->IncraseSnake();
			Losowanie();
			break;
		case 2:
			break;
	}
	if (snake->GetLength() >= nWymiarPlanszy*nWymiarPlanszy)
		return true;
	if (nPunkty >= nLiczbaPunktowNaPoziom*nPoziom)
		++nPoziom;
	if (nPoziom >= nLiczbaPoziomow)
		return true;
	plansza->CzyszczeniePlanszy();
	plansza->CzyscPlansze(nPunkt, pt::PointMake(snake->GetSnake()[snake->GetLength()-1][1], snake->GetSnake()[snake->GetLength()-1][0]));
	snake->Ruch();
	plansza->SetPoint(nPunkt);
	for (int i = 0; i < snake->GetLength(); ++i)
		plansza->SetSnake(pt::PointMake(snake->GetSnake()[i][0], snake->GetSnake()[i][1]));
	plansza->AktualizujPlansze(nPunkt, pt::PointMake(snake->GetSnake()[0][1], snake->GetSnake()[0][0]), nPunkty, nPoziom);
	Sleep(500 - nPoziom * 10);
	return true;
}

bool Gra::KoniecGry()
{
	gracz->nLiczbaPunktow = nPunkty;
	fstream Ranking;
	Ranking.open("ranking.txt", ios::in | ios::out);
	int n = 0, a;
	if (Ranking.good())
		Ranking >> n;
	a = n+1;
	Gracz* ranking = new Gracz[a];
	int* aWyniki = new int[a];
	if (Ranking.good())
	{
		for (int i = 0; i < n; ++i)
		{
			if (!Ranking.eof())
			{
				Ranking >> ranking[i].strImie >> ranking[i].nLiczbaPunktow;
				aWyniki[i] = ranking[i].nLiczbaPunktow;
				ranking[i].byl = false;
			}
		}
	}
	ranking[n].byl = false;
	ranking[n].strImie = gracz->strImie;
	aWyniki[n] = ranking[n].nLiczbaPunktow = gracz->nLiczbaPunktow;
	if (a > 1)
		Sortowanie(aWyniki, 0, a);
	Ranking.close();
	Ranking.open("ranking.txt", ios::in | ios::out | ios::trunc);
	Ranking << a << endl;
	for (int i = a; i >= 0; --i)
	{
		for (int j = 0; j < a; ++j)
		{
			if (aWyniki[i] == ranking[j].nLiczbaPunktow && ranking[j].byl == false)
			{
				Ranking << ranking[j].strImie << ' ' << ranking[j].nLiczbaPunktow << endl;
				ranking[j].byl = true;
			}
		}
	}
	Ranking.close();
	delete[] ranking;
	getch();
	return true;
}

bool Gra::Game()
{
	int a = 0;
	for (;a != -1;)
	{
		system("cls");
		cout << "Wybierz opcjê: " << endl;
		cout << "1. Nowa gra." << endl;
		cout << "2. Ranking. " << endl;
		cout << "-1. Wyjœcie. " << endl;
		cin >> a;
		
		
		switch (a)
		{
			case 1:
					bool t;
					StartGry();
					for (;;)
					{
						t = Ruch();
						if (!t)
							break;
					}
					KoniecGry();
				break;
			case 2:
				{
				int n;
				system("cls");
				cout << "RANKING" << endl;
				cout << "--------------" << endl;
				fstream Ranking;
				Ranking.open("ranking.txt", ios::in | ios::out);
				string str;
				if (Ranking.good())
				{
					Ranking >> n;
					Ranking.seekg(2, ios::cur);
					for (int i = 1; i <= 10; ++i)
					{
						cout << i << ". ";
						if (!Ranking.eof())
						{
							getline(Ranking, str);
							cout << str;
						}
						cout << endl;	
					}
				}
				else
					cout << "B³¹d";
				getch();
				Ranking.close();
				break;
				}
			case -1:
				return 0;
		}
		
		
	}
	return true;
}