/*
 * Snake.h
 *
 *  Created on: 26.04.2017
 *      Author: miXu
 */

#include <deque>
#include <utility>
#include <chrono>
#include <functional>
#include "Common.h"

#ifndef SNAKE_H_
#define SNAKE_H_

class Snake {
public:
	Snake();
	~Snake() = default;


	void update(std::chrono::duration<double> time, int plansza_x, int plansza_y);
	void event(kierunek k);
	// false oznacza koniec gry

	bool jedzenie(int jedzenie_x, int jedzenie_y);
	bool sprawdz(int plansza_x, int plansza_y);
	void ustaw(int plansza_x, int plansza_y);
	int dlugosc_snake();

	std::function< void() > callback_generuj_jedzenie;

private:

	void przejdz_przez_sciane(int plansza_x, int plansza_y);
	void ruch(int plansza_x, int plansza_y);

	std::deque<std::pair<int, int>> cialo;
	kierunek kier;
	bool najedzony;
	std::chrono::duration<double> czas_ruchu;
	std::chrono::duration<double> ile_minelo;
};

#endif /* SNAKE_H_ */
