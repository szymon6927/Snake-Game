/*
 * Common.h
 *
 *  Created on: 26.04.2017
 *      Author: miXu
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <random>

void HideCursor();
void gotoxy(int x, int y);
void polskie_litery();
void ShowCursor();
void ustaw_kolor(int kolor);

extern std::default_random_engine rng;

enum class asci_char : int {
	nic = ' ',
	waz = 219,
	jedzenie = 177,
	prawy_dolny_rog = 188,
	prawy_gorny_rog = 187,
	lewy_gorny_rog = 201,
	lewy_dolny_rog = 200,
	linia_pozioma = 205,
	linia_pioniwa = 186
};

enum class kierunek {
	gora,
	dol,
	lewo,
	prawo
};

void rysuj(const std::pair<int, int> tile, asci_char znak);

#endif /* COMMON_H_ */
