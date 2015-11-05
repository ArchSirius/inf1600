#ifndef _CERCLE_HPP
#define _CERCLE_HPP

#include "Ellipse.hpp"

/**
 * Représente un cercle et permet de dessiner un cercle sur un Canevas.
 * Il ne s'agit que d'un cas particulier de l'ellipse.
 */
class Cercle : public Ellipse
{
public:
    Cercle(Coord centre, unsigned int rayon, unsigned int couleur);
    ~Cercle();
    
    unsigned int obtenirRayon(void) const;
private:
};

#endif // _CERCLE_HPP
