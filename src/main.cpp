//============================================================================
// Name        : Snake.cpp
// Author      : Szymon Miks
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <random>
#include "Game.h"
#include "win_api_colors.h"

using namespace std;

std::default_random_engine rng(std::time(nullptr));

int main() {

	eku::console_color_init();

	auto game = std::make_unique<Game>();
	game->run();

	getch();
	return 0;
}

