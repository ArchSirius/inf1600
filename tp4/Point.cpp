#include "Point.hpp"

/**
 * Construit un point.
 * 
 * @param coord
 * Coordonnée du point.
 * 
 * @param couleur
 * Couleur du point.
 */
Point::Point(Coord coord, unsigned int couleur)
: Forme(couleur), _coord(coord), _epaisseur(1), _visible(true)
{

}

Point::~Point()
{

}

/**
 * Dessine un point sur un canevas.
 * 
 * @param canevas
 * Canevas sur lequel dessiner le point.
 */
void Point::dessiner(Canevas *canevas) const
{
	if (_visible) {
		canevas->assignerPixel(_coord.x, _coord.y, _couleur, _epaisseur);
	}
}

void Point::assignerCoordonnee(Coord coord)
{
	_coord = coord;
}

void Point::assignerEpaisseur(unsigned int epaisseur)
{
	_epaisseur = epaisseur;
}

void Point::assignerVisible(bool visible)
{
	// Devrait etre dans Forme
	_visible = visible;
}

Coord Point::obtenirCoordonnee(void) const
{
	return _coord;
}

