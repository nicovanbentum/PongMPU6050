//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "sprite.hpp"

/// \brief
/// Sprite constructor.
/// \details
/// Constructs a pong sprite (basically a rectangle shape) off a given \p size .
/// Position is determined from the top left of the rectangle.
/// Origin is the objects' original position.
/// needs a hwlib oled display object to write to.
sprite::sprite(hwlib::glcd_oled_buffered & display, vector2i origin, vector2i size):
display(display),
origin(origin),
size(size),
pos(origin)
{}

/// \brief
/// Sprite draw function.
/// \details
/// Write the sprites' pixels to the hwlib display buffer.
void sprite::draw()
{
	for(int i = pos.x; i <= size.x+pos.x; i++)
	{
		for(int j = pos.y; j <= size.y+pos.y; j++)
		{
			display.write( hwlib::location( i, j ), hwlib::black , hwlib::buffering::buffered);
		}
	}
}

/// \brief
/// Sprite move function.
/// \details
/// Add the parameter x and y coordinates to the objects' current position coordinates.
void sprite::move(vector2i coords)
{
	pos.x += coords.x;
	pos.y += coords.y;
}

/// \brief
/// Collision detection.
///	\details
///	returns a char based on what it collided with. an l for level, p for player, n for npc or 0 if nothing.
char sprite::bCollides(sprite & player, sprite & npc)
{
	if(pos.y <= 0 || pos.y >= 64-size.y)
	{
		return 'l'; //'l' as in level collision
	}
	else if(pos.x <= player.pos.x + player.size.x && pos.y >= player.pos.y-size.y && pos.y <= player.pos.y+player.size.y)
	{
		return 'p'; //'p' as in player collision
	}
	else if(pos.x >= npc.pos.x-size.x && pos.y >= npc.pos.y-size.y && pos.y <= npc.pos.y+npc.size.y)
	{
		return 'n'; //'n' as in npc collision
	}else{
		return 0;
	}
}

/// \brief
/// Game over check.
/// \details
/// Checks if the objects' position exceeds the screens' horizontal boundaries.
bool sprite::bGame_over()
{
	if(pos.x <= 0 || pos.x >= 128-size.x)
	{
		return true;
	}
	
	return false;
}

/// \brief
/// Set position function.
/// \details
/// Sets the objects' position coordinates to the \p moveto coordinates.
void sprite::setPos(vector2i moveto)
{
	pos.x = moveto.x;
	pos.y = moveto.y;
}
