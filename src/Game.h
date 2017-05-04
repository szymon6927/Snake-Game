/*
 * Snake.h
 *
 *  Created on: 26.04.2017
 *      Author: miXu
 */

#ifndef GAME_H_
#define GAME_H_

#include "Common.h"
#include "Snake.h"
#include <chrono>

class Game {
public:
	Game();
	~Game();

	void rysuj_plansze();
	void pobierz_ustawienia();
	void generuj_jedzenie();
	void wyswietl_logo();
	void run();

private:
	Snake snake;
	int jedzenie_x, jedzenie_y;
	int plansza_x, plansza_y;
	asci_char pole[45][25];
	int szybkosc;
	// sterowanie
	int gora, dol, lewo, prawo;

	bool running;

	kierunek przyporzadkowanie(int klawisz);
	void update(std::chrono::duration<double> time);
};

#endif /* GAME_H_ */
