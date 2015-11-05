#include "Canevas.hpp"

#include <cstring>
#include <algorithm>

/**
 * Construit un Canevas de taille donnée dont tous les pixels sont
 * initialisés à la couleur spécifiée.
 * 
 * @param w
 * Largeur du Canevas
 * 
 * @param h
 * Hauteur du Canevas
 * 
 * @param couleur
 * Couleur avec laquelle initialiser le Canevas (valeur par défaut: 0 - noir)
 */
Canevas::Canevas(unsigned int w, unsigned int h,  unsigned int couleur) throw (std::bad_alloc)
:  _w(w), _h(h)
{
	_canevas = new unsigned int[h * w];
	
	std::fill_n(_canevas, h * w, couleur);
}

/**
 * Désalloue la mémoire associée au Canevas.
 */
Canevas::~Canevas()
{
    if (_canevas) {
        delete[] _canevas;
    }
}

unsigned int *Canevas::obtenirCanevas() const
{
	return _canevas;
}


