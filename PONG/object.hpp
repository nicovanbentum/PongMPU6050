#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "hwlib.hpp"
#include "vector2i.hpp"

class object
{
private:
	hwlib::glcd_oled_buffered & display;
	
public:
	vector2i origin;
	vector2i size;
	vector2i pos;

	
	object(hwlib::glcd_oled_buffered & display, vector2i origin, vector2i size);
	void draw();
	void move(vector2i coords);
	char bCollides(object & player, object & npc);
	bool bGame_over(object & ball);
	void setPos(vector2i moveto);
};


#endif //OBJECT_HPP