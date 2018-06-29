//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "sprite.hpp"

sprite::sprite(hwlib::glcd_oled_buffered & display, vector2i origin, vector2i size):
display(display),
origin(origin),
size(size),
pos(origin)
{}

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

void sprite::paddle_move(vector2i coords)
{
	if(pos.y+coords.y > 0 && pos.y+size.y+coords.y < 64)
	{
		pos.y += coords.y;
	}
}

void sprite::ball_move(vector2i coords)
{
	pos.x += coords.x;
	pos.y += coords.y;
}

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

bool sprite::bGame_over()
{
	if(pos.x <= 0 || pos.x >= 128-size.x)
	{
		return true;
	}
	
	return false;
}

void sprite::setPos(vector2i moveto)
{
	pos.x = moveto.x;
	pos.y = moveto.y;
}
