#include <GL/glut.h>
#include <vector>
#include <algorithm>

#include "tp4.hpp"
#include "Couleurs.h"

#include "Canevas.hpp"

#include "Point.hpp"
#include "Ligne.hpp"
#include "Rectangle.hpp"
#include "Polygone.hpp"
#include "Ellipse.hpp"
#include "Cercle.hpp"
#include "Texte.hpp"

#define PERIODE_AFFICHAGE 16 // ms

struct DonneesFormes {
	Cercle* cercle;
	Polygone* polygone;
	Texte* texte;
	Point* pt1;
	Point* pt2;
	Point* pt3;
	Point* pt4;
	Point* pt5;
};

DonneesFormes formes;
std::vector<Forme*> listeFormes;
bool ferme = true;

/* Fonctions à implémenter */
Cercle* nouveauCercle(Coord centre, unsigned int rayon, unsigned int couleur);
void faireDessin(Forme** formes, unsigned int n);
void desallouerForme(Forme* forme);

/* Fonctions pour créer des formes */
Point* nouveauPoint(Coord coord, unsigned int couleur) {
	return new Point(coord, couleur);
}

Ligne* nouvelleLigne(Coord c1, Coord c2, unsigned int couleur) {
	return new Ligne(c1, c2, couleur);
}

Rectangle* nouveauRectangle(Coord coin1, Coord coin2, unsigned int couleur) {
	return new Rectangle(coin1, coin2, couleur);
}

Polygone* nouveauPolygone(const std::vector< Coord >& coords, unsigned int couleur) {
	return new Polygone(coords, couleur);
}

Ellipse* nouvelleEllipse(Coord centre, unsigned int rayon_x, unsigned int rayon_y, unsigned int couleur) {
	return new Ellipse(centre, rayon_x, rayon_y, couleur);
}

Texte* nouveauTexte(std::string texte, Coord coord, unsigned int couleur) {
	return new Texte(texte, coord, couleur);
}

/* Désalloue toutes les formes */
void desallouerFormes() {
	std::for_each(listeFormes.begin(), listeFormes.end(), desallouerForme);
}

static void display() {
	faireDessin(&listeFormes[0], listeFormes.size());	
}

void ecrireFrame(const Canevas* c)
{
	glRasterPos2i(0,0);
	glDrawPixels(c->obtenirLargeur(), c->obtenirHauteur(), GL_BGRA, GL_UNSIGNED_BYTE, c->obtenirCanevas());
	glutSwapBuffers();
}

static void reshape(int w, int h)
{
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0,w,0,h); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void status(int st)
{

}

static void timer(int value)
{
	/* Code magique pour l'animation */
	glutTimerFunc(PERIODE_AFFICHAGE, timer, 0);
	
	Coord posTxt = formes.texte->obtenirCoordonnee();
	Coord incTxt(-3, 0);
	posTxt = posTxt + incTxt;
	if (posTxt.x < -(int)formes.texte->obtenirLargeurResultante()) {
		posTxt.x = LARGEUR_CANEVAS;
	}
	formes.texte->assignerCoordonnee(posTxt);

	Coord posCercle = formes.cercle->obtenirCentre();
	std::vector<Coord>& coords = formes.polygone->obtenirCoordonnees();
	Coord incX;
	Coord incY;
	if (posCercle.x > LARGEUR_CANEVAS + (int)formes.cercle->obtenirRayon()) {
		incX = Coord( -(LARGEUR_CANEVAS + 2 * (int)formes.cercle->obtenirRayon()) , 0);
	} else {
		incX = Coord(2, 0);
	}
	
	if (coords[1].y <= coords[2].y) {
		ferme = false;
	} else if (coords[1].y - coords[2].y > 60) {
		ferme = true;
	}
	
	incY = (ferme) ? Coord(0, 1) : Coord(0, -1);

	coords[0] = coords[0] + incX;
	coords[1] = coords[1] + incX - incY;
	coords[2] = coords[2] + incX + incY;
	posCercle = posCercle + incX;
	formes.cercle->assignerCentre(posCercle);
	
	formes.pt1->assignerVisible(posCercle.x + 15 < formes.pt1->obtenirCoordonnee().x);
	formes.pt2->assignerVisible(posCercle.x + 15 < formes.pt2->obtenirCoordonnee().x);
	formes.pt3->assignerVisible(posCercle.x + 15 < formes.pt3->obtenirCoordonnee().x);
	formes.pt4->assignerVisible(posCercle.x + 15 < formes.pt4->obtenirCoordonnee().x);
	formes.pt5->assignerVisible(posCercle.x + 15 < formes.pt5->obtenirCoordonnee().x);

	glutPostRedisplay();
}

void initialiserGLUT(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(LARGEUR_CANEVAS, HAUTEUR_CANEVAS);
	glutCreateWindow("INF1600 - TP4");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutWindowStatusFunc(status);
}

void initialiserFormes(void)
{
	formes.texte = nouveauTexte("Ca semble fonctionner !", Coord(100, HAUTEUR_CANEVAS - 10), C_Blue);
	formes.texte->assignerTaille(3);

	formes.cercle = nouveauCercle(Coord(-40,150), 40, C_Yellow);
	formes.cercle->assignerRemplissage(true);

	std::vector<Coord> coords;
	coords.push_back(Coord(-40,150)); coords.push_back(Coord(-40 + 40,150 + 30)); coords.push_back(Coord(-40 + 40,150 - 30));
	formes.polygone = nouveauPolygone(coords, C_Black);
	formes.polygone->assignerRemplissage(true);

	formes.pt1 = nouveauPoint(Coord(105, 150), C_White);
	formes.pt2 = nouveauPoint(Coord(210, 150), C_White);
	formes.pt3 = nouveauPoint(Coord(315, 150), C_White);
	formes.pt4 = nouveauPoint(Coord(420, 150), C_White);
	formes.pt5 = nouveauPoint(Coord(525, 150), C_White);
	formes.pt1->assignerEpaisseur(9);
	formes.pt2->assignerEpaisseur(9);
	formes.pt3->assignerEpaisseur(9);
	formes.pt4->assignerEpaisseur(9);
	formes.pt5->assignerEpaisseur(9);
	
	int n = sizeof(formes) / sizeof(void*);
	
	Forme** f = (Forme**)&formes;
	for (int i = 0; i < n; i++) {
		listeFormes.push_back( f[i] );
	}
}

int main(int argc, char **argv)
{
	initialiserGLUT(argc, argv);
	initialiserFormes();
	atexit(desallouerFormes);
	glutTimerFunc(PERIODE_AFFICHAGE, timer, 0);
	glutMainLoop();
	return 0;
}
