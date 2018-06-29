//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "hwlib.hpp"
#include "vector2i.hpp"

/// \brief
/// Sprite class.
/// \details
/// Implements a pong sprite (rectangle shape) based 
/// on a given size and position.
/// Uses adt vector2i to do coordinate calculations.

class sprite
{
private:
	hwlib::glcd_oled_buffered & display;
	
public:
	vector2i origin;
	vector2i size;
	vector2i pos;

	
	sprite(hwlib::glcd_oled_buffered & display, vector2i origin, vector2i size);
	
	
	void draw();
	void paddle_move(vector2i coords);
	void ball_move(vector2i coords);
	char bCollides(sprite & player, sprite & npc);
	bool bGame_over();
	void setPos(vector2i moveto);
};


#endif //OBJECT_HPP