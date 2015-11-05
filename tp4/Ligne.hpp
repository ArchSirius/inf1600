#ifndef _LIGNE_HPP
#define _LIGNE_HPP

#include "Forme.hpp"
#include "Coord.hpp"

/**
 * Représente une ligne et permet de tracer une ligne, ou plus précisément un
 * segment de droite.
 */
class Ligne : public Forme
{
public:
    Ligne(Coord c1, Coord c2, unsigned int couleur);
    ~Ligne();
    
    void dessiner(Canevas *canevas) const;
    
    void assignerCoordonnees(Coord c1, Coord c2);
    void assignerEpaisseur(unsigned int epaisseur);
private:
    Coord _c1, _c2;
    unsigned int _epaisseur;
};

#endif // _LIGNE_HPP
