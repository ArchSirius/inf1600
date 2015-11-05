#include "tp4.hpp"

#include "Point.hpp"
#include "Ligne.hpp"
#include "Rectangle.hpp"
#include "Polygone.hpp"
#include "Ellipse.hpp"
#include "Cercle.hpp"
#include "Texte.hpp"
#include "Couleurs.h"

/* Fonction à appeler à la fin de faireDessin */
void ecrireFrame(const Canevas* c);

/*
Cercle* nouveauCercle(Coord centre, unsigned int rayon, unsigned int couleur) {
	return new Cercle(centre, rayon, couleur);
}
*/
/*
void faireDessin(Forme** formes, unsigned int n) {
	Canevas* canevas = new Canevas(LARGEUR_CANEVAS, HAUTEUR_CANEVAS, COULEUR_CANEVAS);
	for(unsigned int i = 0; i < n; i++){
		canevas->dessinerForme(formes[i]);
	}
	ecrireFrame(canevas);
	delete canevas;
	//canevas = 0;		// pas necessaire
}
*/
/*
void desallouerForme(Forme* forme) {
	delete forme;
	forme = 0;
}
*/
/*
void Canevas::dessinerForme(Forme *forme)
{
	forme->dessiner(this);
}
*/
/*
void Canevas::assignerPixel(int x, int y, unsigned int couleur)
{
	if(x >= 0 && y >= 0 && x < LARGEUR_CANEVAS && y < HAUTEUR_CANEVAS){
		_canevas[x + y * LARGEUR_CANEVAS] = couleur;
	}
}
*/
/*
void Canevas::assignerPixel(Coord coord, unsigned int couleur)
{
	assignerPixel(coord.x, coord.y, couleur);
}
*/