#include "Forme.hpp"

/**
 * Construit une forme.
 * 
 * @param couleur
 * Couleur principale de la forme.
 */
Forme::Forme(unsigned int couleur)
: _couleur(couleur)
{

}

Forme::~Forme()
{

}

void Forme::assignerCouleur(unsigned int couleur)
{
	_couleur = couleur;
}

unsigned int Forme::obtenirCouleur(void) const
{
	return _couleur;
}
