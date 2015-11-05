#ifndef _CANEVAS_HPP
#define _CANEVAS_HPP

class Canevas; /* Forme.hpp doit connaître l'existence de Canevas. */

#include "Forme.hpp"
#include "Coord.hpp"

#include <stdexcept>
#include <cstddef>

/** 
 * Représente un Canevas sur lequel on peut dessiner des formes.
 */
class Canevas {
public:
	Canevas(unsigned int w, unsigned int h, unsigned int couleur = 0)  throw (std::bad_alloc);
	~Canevas();
	
	void dessinerForme(Forme *forme);

	void assignerPixel(int x, int y, unsigned int couleur, unsigned int epaisseur);
	void assignerPixel(int x, int y, unsigned int couleur);
	void assignerPixel(Coord coord, unsigned int couleur);
	
	unsigned int obtenirPixel(int x, int y) const;
	unsigned int *obtenirCanevas() const;
	unsigned int obtenirLargeur() const;
	unsigned int obtenirHauteur() const;

private:
	unsigned int *_canevas; // +0
	unsigned int _w; // +4
	unsigned int _h; // +8


	/* Désactiver la copie de Canevas */
	Canevas(const Canevas&); // Pas d'implémentation
	Canevas& operator=(const Canevas&); // Pas d'implémentation
};



/**
 * Assigne une couleur à un carré de pixels de dimension donnée à une position
 * donnée sur le canevas.
 *
 * @param x
 * Position horizontale du pixel à tracer à partir du bas.
 * 
 * @param y
 * Position verticale du pixel à tracer à partir du haut.
 *
 * @param couleur
 * Couleur à assigner aux pixels en format RGB sur les 24 bits de poids faible.
 * 
 * @param epaisseur
 * Dimension du carré de pixels à tracer.
 */
inline void Canevas::assignerPixel(int x, int y, unsigned int couleur, unsigned int epaisseur)
{
	int xgauche = x - epaisseur / 2;
	int yhaut = y - epaisseur / 2;
	int i, j;
	
	for (i = xgauche; i < xgauche + (int)epaisseur; i++) {
		for (j = yhaut; j < yhaut + (int)epaisseur; j++) {
			assignerPixel(i, j, couleur);
		}
	}
}

/**
 * Obtient la couleur d'un pixel d'une position donnée. Si la position fournie 
 * est en dehors du canevas, obtenirPixel retourne 0 (noir).
 * 
 * @return
 * La couleur du pixel en format RGB sur les 24 bits de poids faible.
 */
inline unsigned int Canevas::obtenirPixel(int x, int y) const
{
	if (x > 0 && x < (int)_w && y > 0 && y < (int)_h) {
		return _canevas[y * _w + x];
	} else {
		return 0;
	}
}


/**
 * Retourne la largeur du canevas en pixels.
 * 
 * @return
 * La largeur du canevas en pixels.
 */
inline unsigned int Canevas::obtenirLargeur() const
{
    return _w;
}

/**
 * Retourne la hauteur du canevas en pixels.
 * 
 * @return
 * La hauteur du canevas en pixels.
 */
inline unsigned int Canevas::obtenirHauteur() const
{
    return _h;
}

#endif // _CANEVAS_HPP
