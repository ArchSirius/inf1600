#ifndef _ELLIPSE_HPP
#define _ELLIPSE_HPP

#include "Forme.hpp"
#include "Coord.hpp"

/**
 * Représente une ellipse et permet de dessiner une ellipse sur un Canevas.
 */
class Ellipse : public Forme
{
public:
	Ellipse(Coord centre, unsigned int rayon_x, unsigned int rayon_y, unsigned int couleur);
	~Ellipse();
	
	void dessiner(Canevas *canevas) const;

	void assignerCentre(Coord centre);
	void assignerRayonX(unsigned int rayon_x);
	void assignerRayonY(unsigned int rayon_y);
	void assignerEpaisseur(unsigned int epaisseur);
	void assignerRemplissage(bool remplissage);
	
	Coord obtenirCentre(void) const;
	unsigned int obtenirRayonX(void) const;
	unsigned int obtenirRayonY(void) const;
	unsigned int obtenirEpaisseur(void) const;
	bool obtenirRemplissage(void) const;

private:
	void tracer(Canevas *canevas, int x, int y, bool direction) const;

	Coord _centre;
	unsigned int _rayon_x, _rayon_y;
	unsigned int _epaisseur;
	bool _remplissage;
};

#endif // _ELLIPSE_HPP
