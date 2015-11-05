#include "Rectangle.hpp"

#include <algorithm>

/**
 * Construit un rectangle.
 * 
 * @param coin1
 * Coordonnée d'un coin du rectangle.
 * 
 * @param coin2
 * Coordonnée du coin du rectangle opposé à coin1.
 * 
 * @param couleur
 * Couleur du rectangle.
 */
Rectangle::Rectangle(Coord coin1, Coord coin2, unsigned int couleur)
: Forme(couleur), _coin1(coin1), _coin2(coin2), _epaisseur(1), _remplissage(false)
{
	
}

Rectangle::~Rectangle()
{

}

/**
 * Dessine le rectangle sur un canevas.
 * 
 * @param canevas
 * Canevas sur lequel dessiner le rectangle.
 */
void Rectangle::dessiner(Canevas *canevas) const
{
	int x1 = std::min(_coin1.x, _coin2.x);
	int y1 = std::min(_coin1.y, _coin2.y);
	int x2 = std::max(_coin1.x, _coin2.x);
	int y2 = std::max(_coin1.y, _coin2.y);

	// Haut et bas
	for (int i = x1; i <= x2; i++) {
		canevas->assignerPixel(i, y1, _couleur, _epaisseur);
		canevas->assignerPixel(i, y2, _couleur, _epaisseur);
	}
	// Droite et gauche
	for (int j = y1; j <= y2; j++) {
		canevas->assignerPixel(x1, j, _couleur, _epaisseur);
		canevas->assignerPixel(x2, j, _couleur, _epaisseur);
	}

	if (_remplissage) {
		for (int i = x1 + 1; i < x2; i++) {
			for (int j = y1 + 1; j < y2; j++) {
				canevas->assignerPixel(i, j, _couleur, 1);
			}
		}
	}
}

void Rectangle::assignerCoordonnees(Coord coin1, Coord coin2)
{
	_coin1 = coin1;
	_coin2 = coin2;
}

void Rectangle::assignerEpaisseur(unsigned int epaisseur)
{
	_epaisseur = epaisseur;
}

void Rectangle::assignerRemplissage(bool remplissage)
{
	_remplissage = remplissage;
}
