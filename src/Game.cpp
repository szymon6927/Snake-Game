/*
 * Game.cpp
 *
 *  Created on: 26.04.2017
 *      Author: miXu
 */

#include "Game.h"
#include <iostream>
#include <random>
#include <conio.h>
#include "Common.h"
#include "win_api_colors.h"
#include <functional>

Game::Game(): running(true)
{

	wyswietl_logo();
	pobierz_ustawienia();

	for (int i = 0; i < plansza_y; i++) {
		for (int j = 0; j < plansza_x; j++) {
			pole[j][i] = asci_char::nic; //ustawaiamy p jako wolne pole
		}
	}

	system("CLS");
	HideCursor();
	gotoxy(0, 0);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::wyswietl_logo() {
	eku::set_text_color(eku::color::red);

	std::cout << "\t\t" << R"(  _____                _         )" << "\n"
			  << "\t\t" << R"( / ____|              | |   	 )" << "\n"
			  << "\t\t" << R"(| (___   _ __    __ _ | | __ ___ )" << "\n"
			  << "\t\t" << R"( \___ \ | '_ \  / _` || |/ // _ \)" << "\n"
			  << "\t\t" << R"( ____) || | | || (_| ||   <|  __/)" << "\n"
			  << "\t\t" << R"(|_____/ |_| |_| \__,_||_|\_\\___|)" << "\n"
			  << "\n";

	std::cout << " ";
}

void Game::pobierz_ustawienia() {


	using std::cout;
	using std::cin;

	cout << "   BRAK WALIDACJI DANYCH BLEDNE DANE MOGA WPLYNAC NA DZIALANIE GRY !!! \n\n";

	eku::set_text_color(eku::color::yellow);
	cout << "Podaj szerokosc planszy (5 - 35) \n";
	cin >> plansza_x;
	cout << "Podaj wysokosc plnaszy (5 - 20) \n";
	cin >> plansza_y;

	cout << "Podasz szybkosc gry (1 - 20) \n";
	cin >> szybkosc;

	eku::set_text_color(eku::color::green);

	cout << "\n";
	cout << "Podaj klawisze ktorymi chcesz sterowac wezem \n";

	cout << "Ruch w gore \n";
	gora = getch();
	if (gora == 224) {
		gora += getch();
	}
	if (gora == 0) {
		gora -= getch();
	}

	cout << "Ruch w dol \n";
	dol = getch();
	if (dol == 224)
		dol += getch();
	if (dol == 0)
		dol -= getch();

	cout << "Ruch w lewo \n";
	lewo = getch();
	if (lewo == 224) {
		lewo += getch();
	}
	if (lewo == 0) {
		lewo -= getch();
	}

	cout << "Ruch w prawo \n";
	prawo = getch();
	if (prawo == 224) {
		prawo += getch();
	}
	if (prawo == 0) {
		prawo -= getch();
	}
}


void Game::rysuj_plansze() {

	eku::set_text_color(eku::color::red);

	using std::cout;

	cout << static_cast<char>(asci_char::lewy_gorny_rog);
	for (int i = 0; i < plansza_x; i++) {
		cout << static_cast<char>(asci_char::linia_pozioma) << static_cast<char>(asci_char::linia_pozioma);
	}


	cout << static_cast<char>(asci_char::prawy_gorny_rog);
	//lewa ramka
	for (int i = 0; i < plansza_y; i++) {
		cout << "\n" << static_cast<char>(asci_char::linia_pioniwa); //lewa ramka
		for (int j = 0; j < plansza_x; j++) {
			if (pole[j][i] == asci_char::nic) {
				cout << "  ";
			}
			if (pole[j][i] == asci_char::waz) {
				cout << static_cast<char>(asci_char::waz) << static_cast<char>(asci_char::waz);
			}
			if (pole[j][i] == asci_char::jedzenie) {
				cout << static_cast<char>(asci_char::jedzenie) << static_cast<char>(asci_char::jedzenie);
			}
		}

		cout << static_cast<char>(asci_char::linia_pioniwa); //prawa ramka
	}

	cout << "\n";
	//dolna krawedz
	cout << static_cast<char>(asci_char::lewy_dolny_rog);

	for (int i = 0; i < plansza_x; i++) {
		cout << static_cast<char>(asci_char::linia_pozioma) << static_cast<char>(asci_char::linia_pozioma);
	}

	cout << static_cast<char>(asci_char::prawy_dolny_rog);
}

void Game::generuj_jedzenie() {
	std::uniform_int_distribution<> dist_x(0, plansza_x - 1);
	std::uniform_int_distribution<> dist_y(0, plansza_y - 1);

	do {
		jedzenie_x = dist_x(rng);
		jedzenie_y = dist_y(rng);
	}while(pole[jedzenie_x][jedzenie_y] != asci_char::nic);

	pole[jedzenie_x][jedzenie_y] = asci_char::jedzenie;

	eku::set_text_color(eku::color::green);
	rysuj({jedzenie_x, jedzenie_y}, asci_char::jedzenie);
}

void Game::run()
{
	int klawisz;

	//rozpoczecie gry
	std::chrono::steady_clock clock;
	std::chrono::time_point<std::chrono::steady_clock> t1, t2;
	t1 = clock.now();
	std::chrono::duration<double> duration;

	rysuj_plansze();
	snake.ustaw(plansza_x, plansza_y);
	generuj_jedzenie();

	snake.callback_generuj_jedzenie = std::bind(&Game::generuj_jedzenie, this);

	while(running)
	{
		t2 = clock.now();
		duration = t2 - t1;
		t1 = t2;
		update(duration / ( 1.0 / static_cast<double>(szybkosc)));

		if(_kbhit()) { //nacisniety klawisz
			klawisz = getch();
			if (klawisz == 224) {
				klawisz += getch();
			}
			if (klawisz == 0) {
				klawisz -= getch();
			}

			snake.event(przyporzadkowanie(klawisz));
		}

		if(snake.sprawdz(plansza_x, plansza_y) == false) {
			eku::set_text_color(eku::color::aqua);
			gotoxy(plansza_x + 3, plansza_y + 3);
			std::cout << "Koniec gry, twoj wynik to " << snake.dlugosc_snake() << "\n\a";
			running = false;
		}

		if(snake.jedzenie(jedzenie_x, jedzenie_y)) {
			pole[jedzenie_x][jedzenie_y] = asci_char::waz;
		}

	}//koniec nieskonczonej petli
}

kierunek Game::przyporzadkowanie(int klawisz) {
	if(klawisz == gora)
		return kierunek::gora;

	if(klawisz == lewo)
		return kierunek::lewo;

	if(klawisz == prawo)
		return kierunek::prawo;

	return kierunek::dol;
}

void Game::update(std::chrono::duration<double> time) {
	snake.update(time, plansza_x, plansza_y);
}
