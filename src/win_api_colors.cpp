#include "win_api_colors.h"

namespace eku
{

// global variables
HANDLE std_con_out;
bool color_protect = false;
color text_color, back_color, def_text_color, def_back_color;

void update_colors()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(std_con_out, &csbi);
	text_color = static_cast<color>(csbi.wAttributes & 15);
	back_color = static_cast<color>((csbi.wAttributes & 0xf0) >> 4);
}

void set_color(color text, color background)
{
	if (color_protect && text_color == background)
		return;

	text_color = text;
	back_color = background;
	WORD wAttributes = (static_cast<unsigned>(back_color) << 4) | static_cast<unsigned>(text_color);
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

void set_text_color(color text)
{
	if (color_protect && text_color == back_color)
		return;

	text_color = text;
	WORD wAttributes = (static_cast<unsigned>(back_color) << 4) | static_cast<unsigned>(text_color);
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

void set_back_color(color background)
{
	if (color_protect && text_color == background)
		return;

	back_color = background;
	WORD wAttributes = (static_cast<unsigned>(back_color) << 4) | static_cast<unsigned>(text_color);
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

void console_color_init()
{
	std_con_out = GetStdHandle(STD_OUTPUT_HANDLE);
	update_colors();
	def_text_color = text_color;
	def_back_color = back_color;
}

} // namespace eku
