#ifndef VECTOR2I_HPP
#define VECTOR2I_HPP

class vector2i
{
public:
	int x;
	int y;
	
	vector2i(int x, int y):
	x(x),
	y(y)
	{}
	
	vector2i operator+(const vector2i & rhs)
	const {
		return vector2i(x+rhs.x, y+rhs.y);
	}
	
	vector2i operator*(const vector2i & rhs)
	const {
		return vector2i(x*rhs.x, y*rhs.y);
	}
	
	vector2i & operator*=(const vector2i & rhs)
	{
		x*=rhs.x;
		y*= rhs.y;
		return *this;
	}
	
	vector2i & operator*=(const int & rhs)
	{
		x*=rhs;
		y*=rhs;
		return *this;
	}
	
	vector2i operator*(const int & rhs)
	{
		return vector2i(x*rhs, y*rhs);
	}
	
	vector2i operator+(const int & rhs)
	{
		return vector2i(x+rhs, y+rhs);
	}
	
	
};

#endif //VECTOR2I_HPP