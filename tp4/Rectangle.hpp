#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "Forme.hpp"
#include "Ligne.hpp"

/**
 * Représente un rectangle et permet de dessiner un rectangle.
 */
class Rectangle : public Forme
{
    public:
        Rectangle(Coord coin1, Coord coin2, unsigned int couleur);
        ~Rectangle();
        
        void dessiner(Canevas *canevas) const;
        
        void assignerCoordonnees(Coord coin1, Coord coin2);
        void assignerEpaisseur(unsigned int epaisseur);
        void assignerRemplissage(bool remplissage);
        
    private:
        Coord _coin1, _coin2;
        unsigned int _epaisseur;
        bool _remplissage;
};

#endif // _RECTANGLE_HPP
