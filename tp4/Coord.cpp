#include "Coord.hpp"

/**
 * Constructeur par défaut. Construit une coordonnée de valeur (0,0).
 */
Coord::Coord()
: x(0), y(0)
{
	
}

/**
 * Construit une coordonnée avec les valeurs de composantes spécifiées.
 * 
 * @param xi
 * Valeur initiale pour la composante x.
 * 
 * @param yi
 * Valeur initiale pour la composante y.
 */
Coord::Coord(int xi, int yi)
: x(xi), y(yi)
{

}

/**
 * Additionne deux coordonnées.
 */
Coord Coord::operator+(const Coord& c) const
{
	return Coord(this->x + c.x, this->y + c.y);
}

/**
 * Soustrait deux coordonnées.
 */
Coord Coord::operator-(const Coord& c) const
{
	return Coord(this->x - c.x, this->y - c.y);
}

/**
 * Multiplie une coordonnée par une valeur entière.
 */
Coord Coord::operator*(const int n) const
{
	return Coord(this->x * n, this->y * n);
}

/**
 * Divise une coordonnée par une valeur entière.
 */
Coord Coord::operator/(const int n) const
{
	return Coord(this->x / n, this->y / n);
}


/**
 * Applique l'opérateur modulo entre les coordonnées correspondantes.
 */
Coord Coord::operator%(const Coord& c) const
{
	return Coord(this->x % c.x, this->y % c.y);
}

/**
 * Applique l'opérateur modulo sur les deux coordonnées.
 */
Coord Coord::operator%(const int n) const
{
	return Coord(this->x % n, this->y % n);
}


/**
 * Formatte la coordonnée selon le format "(x,y)" et l'envoit dans un flux de
 * sortie.
 */
std::ostream& operator<<(std::ostream& out, const Coord& c)
{
	out << '(' << c.x << ',' << c.y << ')';
	return out;
}
