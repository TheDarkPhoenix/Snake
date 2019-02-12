#ifndef BOARD_H
#define BOARD_H

#include <windows.h>
#include "point.h"
#include "snake.h"

enum FIELD {FLD_EMPTY = ' ', FLD_SNAKE = '#', FLD_POINT = '$'};

class Plansza
{
	private:

		static const int nWymiarPlanszy = 20;
		FIELD aPlansza[nWymiarPlanszy+1][nWymiarPlanszy+1];
		HANDLE hOut;

	public:

		Plansza();
		~Plansza();

		bool CzyszczeniePlanszy();
		void AktualizujPlansze(pt::Point poi, pt::Point spoi, int nPunkty, int nPoziom);
		void CzyscPlansze(pt::Point poi, pt::Point spoi);
		bool RysowaniePlanszy();
		int SprawdzeniePlanszy(int nLength, Snake& snake, pt::Point poi);
		void gotoxy(int x,int y);

		int GetSize() {return nWymiarPlanszy;};
		void SetPoint(pt::Point poi) {aPlansza[static_cast<int>(poi.y)][static_cast<int>(poi.x)] = FLD_POINT;};
		void SetSnake(pt::Point poi) {aPlansza[static_cast<int>(poi.x)][static_cast<int>(poi.y)] = FLD_SNAKE;};
};

#endif