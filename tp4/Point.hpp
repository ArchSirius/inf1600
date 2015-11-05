#ifndef _POINT_HPP
#define _POINT_HPP

#include "Forme.hpp"
#include "Coord.hpp"

/**
 * Représente un point et permet de tracer un point.
 */
class Point : public Forme
{
public:
    Point(Coord coord, unsigned int couleur);
    ~Point();
    
    void dessiner(Canevas *canevas) const;
    void assignerCoordonnee(Coord coord);
	void assignerEpaisseur(unsigned int epaisseur);
	void assignerVisible(bool visible); // Devrait etre dans Forme
	
	Coord obtenirCoordonnee(void) const;
	
private:
    Coord _coord;
    unsigned int _epaisseur;
    bool _visible; // Devrait etre dans Forme
};

#endif // _POINT_HPP
