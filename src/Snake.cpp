/*
 * Snake.cpp
 *
 *  Created on: 26.04.2017
 *      Author: miXu
 */

#include "Snake.h"
#include <algorithm>
#include <tuple>
#include <iostream>
#include "win_api_colors.h"

Snake::Snake(): najedzony(false)
{
	std::uniform_int_distribution<> dist(0, 3);
	kier = static_cast<kierunek>(dist(rng));

	using namespace std::chrono;
	czas_ruchu = 1s;
}

void Snake::ruch(int plansza_x, int plansza_y) {

	eku::set_text_color(eku::color::yellow);

	if(najedzony) {
		najedzony = false;
		callback_generuj_jedzenie();
	}
	else {
		rysuj(cialo.back(), asci_char::nic);
		cialo.pop_back();
	}

	auto pos = cialo.front();

	if (kier == kierunek::dol) {
		pos.second++;
	}
	else if (kier == kierunek::gora) {
		pos.second--;
	}
	else if (kier == kierunek::lewo) {
		pos.first--;
	}
	else if (kier == kierunek::prawo) {
		pos.first++;
	}

	cialo.push_front(pos);
	przejdz_przez_sciane(plansza_x, plansza_y);

	rysuj(cialo.front(), asci_char::waz);
}

void Snake::update(std::chrono::duration<double> time, int plansza_x, int plansza_y)
{
	ile_minelo += time;
	if(ile_minelo >= czas_ruchu)
	{
		ruch(plansza_x, plansza_y);
		ile_minelo -= czas_ruchu;
	}
}

void Snake::event(kierunek k) {
	if(k == kierunek::gora && kier != kierunek::dol)
	{
		kier = k;
	}
	else if(k == kierunek::dol && kier != kierunek::gora)
	{
		kier = k;
	}
	else if(k == kierunek::lewo && kier != kierunek::prawo)
	{
		kier = k;
	}
	else if(k == kierunek::prawo && kier != kierunek::lewo)
	{
		kier = k;
	}
}

bool Snake::sprawdz(int plansza_x, int plansza_y) {
	przejdz_przez_sciane(plansza_x, plansza_y);

	std::deque<std::pair<int, int>> cialo_temp(cialo);

	std::sort(cialo_temp.begin(), cialo_temp.end(),
		[](const std::pair<int, int> &a, const std::pair<int, int>& b) -> bool {
			if(a.first < b.first) return true;
			if(a.first > b.first) return false;

			return a.second < b.second;
		}
	);

	if(std::adjacent_find(cialo_temp.begin(), cialo_temp.end()) != cialo_temp.end())
		return false;

	return true;
}

void Snake::przejdz_przez_sciane(int plansza_x, int plansza_y) {
	if (cialo.front().first == plansza_x) {
		cialo.front().first = 0;
	}
	if (cialo.front().first == -1) {
		cialo.front().first = plansza_x - 1;
	}
	if (cialo.front().second == plansza_y) {
		cialo.front().second = 0;
	}
	if (cialo.front().second == -1) {
		cialo.front().second = plansza_y - 1;
	}
}

bool Snake::jedzenie(int jedzenie_x, int jedzenie_y) {

	najedzony = (std::tie(jedzenie_x, jedzenie_y) == std::tie(cialo.front().first, cialo.front().second));
	return najedzony;
}

void Snake::ustaw(int plansza_x, int plansza_y) {
	cialo.emplace_front(plansza_x / 2, plansza_y / 2);

	if(kier == kierunek::dol) {
		cialo.emplace_back (plansza_x / 2    , plansza_y / 2 - 1);
		cialo.emplace_front(plansza_x / 2    , plansza_y / 2 + 1);
	}
	else if(kier == kierunek::gora) {
		cialo.emplace_back (plansza_x / 2    , plansza_y / 2 + 1);
		cialo.emplace_front(plansza_x / 2    , plansza_y / 2 - 1);
	}
	else if(kier == kierunek::lewo) {
		cialo.emplace_back (plansza_x / 2 + 1, plansza_y / 2);
		cialo.emplace_front(plansza_x / 2 - 1, plansza_y / 2);
	}
	else if(kier == kierunek::prawo) {
		cialo.emplace_back (plansza_x / 2 - 1, plansza_y / 2);
		cialo.emplace_front(plansza_x / 2 + 1, plansza_y / 2);
	}

	for(const auto p : cialo) {
		rysuj(p, asci_char::waz);
	}

}

int Snake::dlugosc_snake() {
	return cialo.size();
}
