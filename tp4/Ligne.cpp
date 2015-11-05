#include "Ligne.hpp"

#include <cstdlib>

/**
 * Construit une ligne.
 * 
 * @param c1
 * Première extrémité de la ligne.
 * 
 * @param c2
 * Deuxième extrémité de la ligne.
 * 
 * @param couleur
 * Couleur de la ligne.
 */
Ligne::Ligne(Coord c1, Coord c2, unsigned int couleur)
: Forme(couleur), _c1(c1), _c2(c2), _epaisseur(1)
{

}

Ligne::~Ligne()
{

}
#include <cstdio>
/**
 * Dessine une ligne sur un canevas.
 * 
 * Source de l'algorithme:
 * http://en.wikipedia.org/wiki/Bresenham's_line_algorithm#Simplification
 * 
 * @param
 * Canevas sur lequel dessiner la ligne.
 */
void Ligne::dessiner(Canevas *canevas) const
{
	int x1 = _c1.x;
	int x2 = _c2.x;
	int y1 = _c1.y;
	int y2 = _c2.y;
	
	int delta_x = abs(x2 - x1);
	int delta_y = abs(y2 - y1);
	int signe_x, signe_y;
	int diff;
	int diff_2;
	
	signe_x = (x1 < x2) ? 1 : -1;
	signe_y = (y1 < y2) ? 1 : -1;
	
	diff = delta_x - delta_y;
	for (;;) {
		
		canevas->assignerPixel(x1, y1, _couleur, _epaisseur);
		if (x1 == x2 && y1 == y2) {
			break;
		}


		diff_2 = 2 * diff;
		if (diff_2 > -delta_y) {
			diff = diff - delta_y;
			x1 = x1 + signe_x;
		}
		if (diff_2 < delta_x) {
			diff = diff + delta_x;
			y1 = y1 + signe_y;
		}
	}
	
}

void Ligne::assignerCoordonnees(Coord c1, Coord c2)
{
	_c1 = c1;
	_c2 = c2;
}

void Ligne::assignerEpaisseur(unsigned int epaisseur)
{
	_epaisseur = epaisseur;
}
