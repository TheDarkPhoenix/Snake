#ifndef GAME_H
#define GAME_H

#include <string>
#include "board.h"
#include "point.h"
#include "snake.h"

enum MOVE {MV_UP = 'w', MV_DOWN = 's', MV_LEFT = 'a', MV_RIGHT = 'd'};

class Gra
{
	private:
		struct Gracz
		{
			std::string strImie;
			int nLiczbaPunktow;
			bool byl;
		};
		int nWymiarPlanszy;
		pt::Point nPunkt;
		int nPunkty;
		int nPoziom;
		int nPoziomTrudnosci;
		MOVE Klawisz;
		const static int nLiczbaPoziomow = 600;
		int nLiczbaPunktowNaPoziom;
		Gracz* gracz;
		Snake* snake;
		Plansza* plansza;

	public:
		Gra(int nWymiar);
		~Gra();
		bool Losowanie();
		bool StartGry();
		bool Ruch();
		bool KoniecGry();
		bool Game();
		int GetLevel() {return nPoziom;};
		int GetPoints() {return nPunkty;};
		pt::Point GetPoint() {return nPunkt;};
		void Sortowanie(int* aTablicaWynikow, int lewy, int prawy);
};

#endif