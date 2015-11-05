#include "Ellipse.hpp"
#include <cmath>

/**
 * Construit une Ellipse avec les dimensions, la position et la couleur données.
 * 
 * @param centre
 * Coordonnée du centre de l'ellipse
 * 
 * @param rayon_x
 * Longueur du rayon dans l'axe x de l'ellipse (généralement le paramètre a)
 * 
 * @param rayon_y
 * Longueur du rayon dans l'axe y de l'ellipse (généralement le paramètre b)
 * 
 * @param couleur
 * Couleur de l'ellipse
 */
Ellipse::Ellipse(Coord centre, unsigned int rayon_x, unsigned int rayon_y, unsigned int couleur)
: Forme(couleur), _centre(centre), _rayon_x(rayon_x), _rayon_y(rayon_y), _epaisseur(1), _remplissage(false)
{

}

Ellipse::~Ellipse()
{

}

/**
 * Dessine une ellipse sur un Canevas.
 * 
 * Source de l'algorithme:
 * http://www.sunshine2k.de/stuff/Java/Bresenham/Bresenham.html
 * 
 * @param canevas
 * Canevas sur lequel dessiner l'ellipse
 */
void Ellipse::dessiner(Canevas *canevas) const
{
	
	int x, y, e;
	int dx, dy;
	int dernier_x, dernier_y;
	
	int a_carre_2 = 2 * _rayon_x * _rayon_x;
	int b_carre_2 = 2 * _rayon_y * _rayon_y;
	
	x = _rayon_x;
	y = 0;
	
	dx = _rayon_y * _rayon_y * (1 - 2 * _rayon_x);
	dy = _rayon_x * _rayon_x;
	
	e = 0;
	
	dernier_x = b_carre_2 * _rayon_x;
	dernier_y = 0;
	
	while (dernier_x >= dernier_y) {
		tracer(canevas, _centre.x + x, _centre.y + y, false);
		tracer(canevas, _centre.x + x, _centre.y - y, false);
		tracer(canevas, _centre.x - x, _centre.y + y, true);
		tracer(canevas, _centre.x - x, _centre.y - y, true);
		
		y++;
		dernier_y += a_carre_2;
		e += dy;
		dy += a_carre_2;
		if ((2 * e + dx) > 0) {
			x--;
			dernier_x -= b_carre_2;
			e += dx;
			dx += b_carre_2;
		}
	}
	
	y = _rayon_y;
	x = 0;
	
	dy = _rayon_x * _rayon_x * (1 - 2 * _rayon_y);
	dx = _rayon_y * _rayon_y;
	
	e = 0;
	
	dernier_y = a_carre_2 * _rayon_y;
	dernier_x = 0;
	
	while (dernier_x <= dernier_y) {
		tracer(canevas, _centre.x + x, _centre.y + y, false);
		tracer(canevas, _centre.x + x, _centre.y - y, false);
		tracer(canevas, _centre.x - x, _centre.y + y, true);
		tracer(canevas, _centre.x - x, _centre.y - y, true);
		
		x++;
		dernier_x += b_carre_2;
		e += dx;
		dx += b_carre_2;
		if ((2 * e + dy) > 0) {
			y--;
			dernier_y -= a_carre_2;
			e += dy;
			dy += a_carre_2;
		}
	}
}

/**
 * Trace un pixel de l'ellipse. Trace aussi une série de pixels entre ce pixel
 * et l'axe de symétrie vertical de l'ellipse si le remplissage est activé.
 * 
 * @param canevas
 * Canevas sur lequel tracer les pixels.
 * 
 * @param x
 * Composante horizontale de la position du pixel.
 * 
 * @param y
 * Composante verticale de la position du pixel.
 * 
 * @param direction
 * Direction dans laquelle effectuer le remplissage.
 *     true -> droite
 *     false -> gauche
 */
void Ellipse::tracer(Canevas *canevas, int x, int y, bool direction) const
{
	int inc = (direction) ? 1 : -1;
	int i = x;
	
	canevas->assignerPixel(x, y, _couleur, _epaisseur);
	
	if (_remplissage) {
		for (i = x; i != _centre.x; i += inc) {
			canevas->assignerPixel(i, y, _couleur, 1);
		}
		canevas->assignerPixel(i, y, _couleur, 1);
	}
}

void Ellipse::assignerCentre(Coord centre)
{
	_centre = centre;
}

void Ellipse::assignerRayonX(unsigned int rayon_x)
{
	_rayon_x = rayon_x;
}

void Ellipse::assignerRayonY(unsigned int rayon_y)
{
	_rayon_y = rayon_y;
}

void Ellipse::assignerEpaisseur(unsigned int epaisseur)
{
	_epaisseur = epaisseur;
}

void Ellipse::assignerRemplissage(bool remplissage)
{
	_remplissage = remplissage;
}

Coord Ellipse::obtenirCentre(void) const
{
	return _centre;
}

unsigned int Ellipse::obtenirRayonX(void) const
{
	return _rayon_x;
}

unsigned int Ellipse::obtenirRayonY(void) const
{
	return _rayon_y;
}

unsigned int Ellipse::obtenirEpaisseur(void) const
{
	return _epaisseur;
}

bool Ellipse::obtenirRemplissage(void) const
{
	return _remplissage;
}

