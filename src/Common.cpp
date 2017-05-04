/*
 * Common.cpp
 *
 *  Created on: 26.04.2017
 *      Author: miXu
 */

#include "Common.h"
#include <windows.h>
#include <iostream>


void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void gotoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

void ShowCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = TRUE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void ustaw_kolor(int kolor)
{
	HANDLE uchwyt;
	uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(uchwyt, kolor);
}

void rysuj(const std::pair<int, int> tile, asci_char znak) {
	gotoxy(tile.first * 2 + 1, tile.second + 1);
	std::cout << static_cast<char>(znak) << static_cast<char>(znak);
}
