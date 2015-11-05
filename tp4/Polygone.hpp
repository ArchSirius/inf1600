#ifndef _POLYGONE_HPP
#define _POLYGONE_HPP

#include "Forme.hpp"
#include "Coord.hpp"
#include <vector>

/**
 * Représente un polygone et permet de tracer un Polygone.
 */
class Polygone : public Forme
{
public:
	Polygone(const std::vector< Coord >& coords, unsigned int couleur);
	void dessiner(Canevas *canevas) const;
	
	void assignerCoordonnees(std::vector< Coord > coords);
	void assignerCompleter(bool completer);
	void assignerRemplissage(bool remplissage);
	void assignerEpaisseur(unsigned int epaisseur);
	
	std::vector< Coord >& obtenirCoordonnees(void);
	
private:
	std::vector< Coord > _coords;
	
	/* Indique si un trait est tracé entre la première et la dernière
	 * coordonnée. */
	bool _completer; 
	bool _remplissage;
	unsigned int _epaisseur;
	
	void tracerRemplissage(Canevas *canevas) const;
	bool ptDansPolygone(Coord point) const;
};

#endif // _POLYGONE_HPP
