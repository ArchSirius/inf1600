#include "Polygone.hpp"
#include "Ligne.hpp"

/**
 * Construit un polygone.
 * 
 * @param coords
 * Vecteur contenant les coordonnées des sommets du polygone.
 * 
 * @param couleur
 * Couleur du polygone.
 */
Polygone::Polygone(const std::vector< Coord >& coords, unsigned int couleur)
: Forme(couleur), _coords(coords), _completer(true), _remplissage(false), _epaisseur(1)
{
	
}

/**
 * Dessine le polygone sur un canevas.
 * 
 * @param
 * Canevas sur lequel dessiner le polygone.
 */
void Polygone::dessiner(Canevas *canevas) const
{
	if (_coords.size() > 0) {
		for (unsigned int i = 0; i < _coords.size() - 1; i++) {
			
			Coord c1 = _coords[i];
			Coord c2 = _coords[i+1];
			Ligne l(c1, c2, _couleur);
			l.assignerEpaisseur(_epaisseur);
			canevas->dessinerForme(&l);
		}

		if (_completer) {
			Coord c1 = _coords.back();
			Coord c2 = _coords.front();
			Ligne l(c1, c2, _couleur);
			l.assignerEpaisseur(_epaisseur);
			canevas->dessinerForme(&l);
		}

		if (_remplissage) {
			tracerRemplissage(canevas);
		}
	}
}

/**
 * Indique si un point se trouve dans le polygone afin d'effectuer le
 * remplissage.
 * 
 * Source de l'algorithme:
 * http://alienryderflex.com/polygon/
 * 
 * @param point
 * Coordonnée du point à vérifier.
 */
bool Polygone::ptDansPolygone(Coord point) const
{
	int j = _coords.size() - 1;
	bool impair = false;

	for (int i = 0; i < (int)_coords.size(); i++) {
		if ((_coords[i].y < point.y && _coords[j].y >= point.y) || 
			(_coords[j].y < point.y && _coords[i].y >= point.y)) {
			if (_coords[i].x + double(point.y - _coords[i].y) / double(_coords[j].y - _coords[i].y) * double(_coords[j].x - _coords[i].x) < point.x) {
				impair = !impair;
			}
		}
		j=i;
	}

	return impair;
}

/**
 * Dessiner l'intérieur du polygone sur un canevas. C'est un code
 * particulièrement non-optimal, mais ça fera pour les besoins du TP.
 * 
 * @param canevas 
 * Canevas sur lequel tracer le remplissage.
 */
void Polygone::tracerRemplissage(Canevas *canevas) const
{
	int xmin, xmax, ymin, ymax;
	xmin = _coords[0].x;
	xmax = _coords[0].x;
	ymin = _coords[0].y;
	ymax = _coords[0].y;
	for (unsigned int i = 1; i < _coords.size(); i++) {
		xmin = std::min(xmin, _coords[i].x);
		xmax = std::max(xmax, _coords[i].x);
		ymin = std::min(ymin, _coords[i].y);
		ymax = std::max(ymax, _coords[i].y);
	}
	
	
	for (int i = xmin; i <= xmax; i++) {
		for (int j = ymin; j <= ymax; j++) {
			if (ptDansPolygone(Coord(i,j))) {
				canevas->assignerPixel(i, j, _couleur, 1);
			}
		}
	}
}

void Polygone::assignerCoordonnees(std::vector< Coord > coords)
{
	_coords = coords;
}

void Polygone::assignerCompleter(bool completer)
{
	_completer = completer;
}

void Polygone::assignerRemplissage(bool remplissage)
{
	_remplissage = remplissage;
}

void Polygone::assignerEpaisseur(unsigned int epaisseur)
{
	_epaisseur = epaisseur;
}

std::vector< Coord >& Polygone::obtenirCoordonnees(void)
{
	return _coords;
}
