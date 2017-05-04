#ifndef WIN_API_COLORS_H_
#define WIN_API_COLORS_H_

/*
 * Header file to color text and background in windows console applications
 * Global variables: text_color, back_color, def_text_color, def_back_color, color_protect
 *
 * Note: you MUST call ONCE console_color_init() before doing any related actions
 *
 * Note: set colors remain as long as you don't explicitly change them (changing streams does not affect colors)
 *
 * Note: call set_color(def_text_color, def_back_color) to restore defaults
 *
 * Example usage
 * 1. use the given functions
 *    eku::set_background_color(eku::color::yellow);
 * 2. use standard stream templates which allow operator chaining (only text color is supported here)
 *    std::cout << "some text" << eku::color::cyan << "text in different color" << eku::...
 */

#ifndef _WIN32
#error This file supports only Windows compilation
#endif

#include <windows.h>
#include <iosfwd>

namespace eku
{

enum class color : WORD
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};

// Standard Output Handle
extern HANDLE std_con_out;

// If color_protect is true, background and text colors will never be the same
// Any operation trying to set the same background and text color will have no effect
extern bool color_protect;

/*
 * text_color     - current text color
 * back_color     - current background color
 * def_text_color - default text color
 * def_back_color - default background color
 */
extern color text_color, back_color, def_text_color, def_back_color;

void update_colors();
void set_color(color text_color, color back_color);
void set_text_color(color text_color);
void set_back_color(color back_color);
void console_color_init();

template <class elem, class traits> inline
std::basic_ostream<elem, traits>& operator<<(std::basic_ostream<elem, traits>& os, color col)
{
	os.flush();
	set_text_color(col);
	return os;
}

template <class elem, class traits> inline
std::basic_istream<elem, traits>& operator>>(std::basic_istream<elem, traits>& is, color col)
{
	std::basic_ostream<elem, traits>* p = is.tie();

	if(p)
		p->flush();

	set_text_color(col);
	return is;
}

} //namespace eku

#endif //WIN_API_COLORS_H_
