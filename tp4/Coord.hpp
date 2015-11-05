#ifndef _COORD_HPP
#define _COORD_HPP

#include <iostream>

/**
 * Représente une coordonnée dans le plan dont les coordonnées sotn des entiers
 * signés.
 */
struct Coord
{
	Coord();
	Coord(int xi, int yi);
	
	Coord operator+(const Coord& c) const;
	Coord operator-(const Coord& c) const;
	Coord operator*(const int n) const;
	Coord operator/(const int n) const;
	Coord operator%(const Coord& c) const;
	Coord operator%(const int n) const;
	
	int x, y;
};

std::ostream& operator<<(std::ostream& out, const Coord& c);

#endif // _COORD_HPP
