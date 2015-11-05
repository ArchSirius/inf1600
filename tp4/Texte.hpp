#ifndef _TEXTE_HPP
#define _TEXTE_HPP

#include "Forme.hpp"
#include "Coord.hpp"

/**
 * Représente une chaîne de texte et permet de tracer une chaîne de texte.
 */
class Texte : public Forme
{
public:
	static const unsigned int LARGEUR_CAR = 5;
	static const unsigned int HAUTEUR_CAR = 7;
	static const unsigned int LARGEUR_TAB = 8;
	
	Texte(std::string texte, Coord coord, unsigned int couleur);
	~Texte();
	
	void dessiner(Canevas* canevas) const;
	
	void assignerTexte(std::string texte);
	void assignerCoordonnee(Coord coord);
	void assignerTaille(unsigned int taille);
	Coord obtenirCoordonnee(void) const;
	unsigned int obtenirLargeurResultante(void) const;
	unsigned int obtenirHauteurResultante(void) const;

private:
	void assignerPixel(Canevas *canevas, int x, int y) const;
	void calculerDimensions(void);

	std::string _texte;
	Coord _coord;
	unsigned int _taille;
	unsigned int _largeurResultante;
	unsigned int _hauteurResultante;
	
	static unsigned char _desc[128][7];
};

#endif // _TEXTE_HPP
