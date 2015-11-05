#include "Cercle.hpp"

/**
 * Construit un Cercle.
 * 
 * @param centre
 * Coordonnée du centre du cercle
 * 
 * @param rayon
 * Taille du rayon du cercle
 * 
 * @param couleur
 * Couleur du cercle
 */
Cercle::Cercle(Coord centre, unsigned int rayon, unsigned int couleur)
: Ellipse(centre, rayon, rayon, couleur)
{

}

Cercle::~Cercle()
{

}

unsigned int Cercle::obtenirRayon(void) const
{
	return Ellipse::obtenirRayonX();
}

