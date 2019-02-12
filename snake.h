#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

class Snake
{
	private:
		int length;
		pt::Point n1; // pozycja g�owy w�a
		int** nSnake;
		int nWymiar;
		int g;	// kierunek poruszania si� w�a
	public:
		Snake(int nWymiarPlanszy);
		~Snake();
		bool Ruch();
		int GetLength() const {return length;};
		pt::Point GetN1() const {return n1;};
		int** GetSnake() const {return nSnake;};
		void IncraseSnake() {++length;};
};

#endif