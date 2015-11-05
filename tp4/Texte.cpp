/*
Auteur: Philippe Proulx et Simon Marchi
Date: 2011/03/09
Date derniere modification: 2011/03/11
*/

#include <string>
#include <cstring>
#include "Texte.hpp"

/**
 * Construit une chaîne de texte.
 * 
 * @param texte
 * Contenu de la chaîne de texte.
 * 
 * @param coord
 * Coordonnée du coin en haut à gauche de la chaîne de texte.
 * 
 * @param couleur
 * Couleur de la chaîne de texte.
 */
Texte::Texte(std::string texte, Coord coord, unsigned int couleur)
: Forme(couleur), _texte(texte), _coord(coord), _taille(1)
{
	calculerDimensions();
}

Texte::~Texte()
{

}

/**
 * Trace un pixel de caractère sur un canevas.
 * 
 * @param canevas
 * Canevas sur lequel tracer les pixels.
 * 
 * @param x
 * Position horizontale du pixel.
 * 
 * @param y
 * Position verticale du pixel.
 */
void Texte::assignerPixel(Canevas *canevas, int x, int y) const
{
	for (unsigned int i = 0; i < _taille; i++) {
		for (unsigned int j = 0; j < _taille; j++) {
			canevas->assignerPixel(x + i, y - j, _couleur, 1);
		}
	}
}

/**
 * Dessine la chaîne de texte sur un canevas.
 * 
 * @param canevas
 * Canevas sur lequel dessiner la chaîne de texte.
 */
void Texte::dessiner(Canevas* canevas) const
{
	unsigned int i, j, k = 0;
	const unsigned char* cur_ch;
	unsigned char bits;
	/* Position en haut à gauche du caractère */
	int x = _coord.x;
	int y = _coord.y;
	unsigned int nb_car_h = 0;

	
	/* Pour chaque caractère */
	for (i = 0; i < _texte.size(); ++i) {
		/* Aller chercher la description du caractère */
		cur_ch = _desc[(unsigned char) _texte.at(i)];
		for (j = 0; j < HAUTEUR_CAR; ++j) {
			bits = cur_ch[j];
			for (k = 0; k < LARGEUR_CAR; ++k) {
				if (bits & (1 << (LARGEUR_CAR - k - 1))) {
					assignerPixel(canevas, x + _taille * k, y - _taille * j);
				}
			}
		}
		
		
		/* Position du prochain caractère */
		if (_texte.at(i) == '\n') {
			/* On laisse 1 pixel d'espace */
			y = y - _taille * (HAUTEUR_CAR + 1);
			/* On revient à la ligne */	
			x = _coord.x;
			nb_car_h = 0;
		} else if (_texte.at(i) == '\t') {
			/* On compte le nombre de caractère à ajouter */
			unsigned int ch_add = LARGEUR_TAB - (nb_car_h % LARGEUR_TAB);
			x += (_taille * (LARGEUR_CAR + 1)) * ch_add;			
			nb_car_h += ch_add;
		} else {
			x += _taille * (LARGEUR_CAR + 1);
			nb_car_h++;
		}
	}
}

void Texte::calculerDimensions(void)
{
	unsigned int nb_car_h = 0;
	unsigned int nb_car_h_max = 0;
	unsigned int nb_car_v = 1;
	for (unsigned int i = 0; i < _texte.size(); i++) {
		if (_texte[i] == '\n') {
			nb_car_h_max = std::max(nb_car_h_max, nb_car_h);
			nb_car_h = 0;
			nb_car_v++;
		} else if (_texte[i] == '\t') {
			unsigned int ch_add = LARGEUR_TAB - (nb_car_h % LARGEUR_TAB);
			nb_car_h += ch_add;
		} else {
			nb_car_h++;
		}
	}

	nb_car_h_max = std::max(nb_car_h_max, nb_car_h);
	
	_largeurResultante = nb_car_h_max * (LARGEUR_CAR + 1) * _taille - _taille;
	_hauteurResultante = nb_car_v * (HAUTEUR_CAR + 1) * _taille - _taille;
}

void Texte::assignerTexte(std::string texte)
{
	_texte = texte;
	calculerDimensions();
}

void Texte::assignerCoordonnee(Coord coord)
{
	_coord = coord;
}

void Texte::assignerTaille(unsigned int taille)
{
	_taille = taille;
	calculerDimensions();
}

Coord Texte::obtenirCoordonnee(void) const
{
	return _coord;
}

unsigned int Texte::obtenirLargeurResultante(void) const
{
	return _largeurResultante;
}

unsigned int Texte::obtenirHauteurResultante(void) const
{
	return _hauteurResultante;
}
	
unsigned char Texte::_desc[128][7] =
{
// 0
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 1
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 2
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 3
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 4
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 5
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 6
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 7
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 8
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 9
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 10
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 11
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 12
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 13
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 14
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 15
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 16
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 17
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 18
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 19
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 20
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 21
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 22
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 23
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 24
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 25
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 26
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 27
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 28
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 29
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 30
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 31
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 32
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	},

// 33
	{
		0x06, //   11 
		0x06, //   11 
		0x06, //   11 
		0x06, //   11 
		0x00, //      
		0x00, //      
		0x06  //   11 
	},

// 34
	{
		0x1b, // 11 11
		0x09, //  1  1
		0x09, //  1  1
		0x00, //      
		0x00, //      
		0x00, //      
		0x00  //      
	},

// 35
	{
		0x0a, //  1 1 
		0x0a, //  1 1 
		0x1f, // 11111
		0x0a, //  1 1 
		0x1f, // 11111
		0x0a, //  1 1 
		0x0a  //  1 1 
	},

// 36
	{
		0x04, //   1  
		0x0f, //  1111
		0x14, // 1 1  
		0x0e, //  111 
		0x05, //   1 1
		0x1e, // 1111 
		0x04  //   1  
	},

// 37
	{
		0x18, // 11   
		0x18, // 11   
		0x03, //    11
		0x04, //   1  
		0x18, // 11   
		0x03, //    11
		0x03  //    11
	},

// 38
	{
		0x0c, //  11  
		0x12, // 1  1 
		0x14, // 1 1  
		0x08, //  1   
		0x15, // 1 1 1
		0x12, // 1  1 
		0x0d  //  11 1
	},

// 39
	{
		0x0c, //  11  
		0x04, //   1  
		0x04, //   1  
		0x00, //      
		0x00, //      
		0x00, //      
		0x00  //      
	},

// 40
	{
		0x02, //    1 
		0x04, //   1  
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x04, //   1  
		0x02  //    1 
	},

// 41
	{
		0x08, //  1   
		0x04, //   1  
		0x02, //    1 
		0x02, //    1 
		0x02, //    1 
		0x04, //   1  
		0x08  //  1   
	},

// 42
	{
		0x04, //   1  
		0x15, // 1 1 1
		0x0e, //  111 
		0x15, // 1 1 1
		0x04, //   1  
		0x00, //      
		0x00  //      
	},

// 43
	{
		0x00, //      
		0x04, //   1  
		0x04, //   1  
		0x1f, // 11111
		0x04, //   1  
		0x04, //   1  
		0x00  //      
	},

// 44
	{
		0x00, //      
		0x00, //      
		0x00, //      
		0x0c, //  11  
		0x0c, //  11  
		0x04, //   1  
		0x08  //  1   
	},

// 45
	{
		0x00, //      
		0x00, //      
		0x00, //      
		0x1f, // 11111
		0x00, //      
		0x00, //      
		0x00  //      
	},

// 46
	{
		0x00, //      
		0x00, //      
		0x00, //      
		0x00, //      
		0x00, //      
		0x0c, //  11  
		0x0c  //  11  
	},

// 47
	{
		0x01, //     1
		0x02, //    1 
		0x02, //    1 
		0x04, //   1  
		0x08, //  1   
		0x08, //  1   
		0x10  // 1    
	},

// 48
	{
		0x0e, //  111 
		0x11, // 1   1
		0x13, // 1  11
		0x15, // 1 1 1
		0x19, // 11  1
		0x11, // 1   1
		0x0e  //  111 
	},

// 49
	{
		0x04, //   1  
		0x0c, //  11  
		0x14, // 1 1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x1f  // 11111
	},

// 50
	{
		0x0e, //  111 
		0x11, // 1   1
		0x01, //     1
		0x0e, //  111 
		0x10, // 1    
		0x10, // 1    
		0x1f  // 11111
	},

// 51
	{
		0x0e, //  111 
		0x11, // 1   1
		0x01, //     1
		0x06, //   11 
		0x01, //     1
		0x11, // 1   1
		0x0e  //  111 
	},

// 52
	{
		0x02, //    1 
		0x06, //   11 
		0x0a, //  1 1 
		0x12, // 1  1 
		0x1f, // 11111
		0x02, //    1 
		0x02  //    1 
	},

// 53
	{
		0x1f, // 11111
		0x10, // 1    
		0x1e, // 1111 
		0x01, //     1
		0x01, //     1
		0x11, // 1   1
		0x0e  //  111 
	},

// 54
	{
		0x0e, //  111 
		0x10, // 1    
		0x10, // 1    
		0x1e, // 1111 
		0x11, // 1   1
		0x11, // 1   1
		0x0e  //  111 
	},

// 55
	{
		0x1f, // 11111
		0x01, //     1
		0x02, //    1 
		0x04, //   1  
		0x08, //  1   
		0x08, //  1   
		0x08  //  1   
	},

// 56
	{
		0x0e, //  111 
		0x11, // 1   1
		0x11, // 1   1
		0x0e, //  111 
		0x11, // 1   1
		0x11, // 1   1
		0x0e  //  111 
	},

// 57
	{
		0x0e, //  111 
		0x11, // 1   1
		0x11, // 1   1
		0x0f, //  1111
		0x01, //     1
		0x01, //     1
		0x0e  //  111 
	},

// 58
	{
		0x00, //      
		0x00, //      
		0x0c, //  11  
		0x0c, //  11  
		0x00, //      
		0x0c, //  11  
		0x0c  //  11  
	},

// 59
	{
		0x00, //      
		0x00, //      
		0x0c, //  11  
		0x00, //      
		0x0c, //  11  
		0x04, //   1  
		0x08  //  1   
	},

// 60
	{
		0x02, //    1 
		0x04, //   1  
		0x08, //  1   
		0x10, // 1    
		0x08, //  1   
		0x04, //   1  
		0x02  //    1 
	},

// 61
	{
		0x00, //      
		0x00, //      
		0x1f, // 11111
		0x00, //      
		0x00, //      
		0x1f, // 11111
		0x00  //      
	},

// 62
	{
		0x10, // 1    
		0x08, //  1   
		0x04, //   1  
		0x02, //    1 
		0x04, //   1  
		0x08, //  1   
		0x10  // 1    
	},

// 63
	{
		0x0e, //  111 
		0x11, // 1   1
		0x01, //     1
		0x02, //    1 
		0x04, //   1  
		0x00, //      
		0x04  //   1  
	},

// 64
	{
		0x0e, //  111 
		0x11, // 1   1
		0x01, //     1
		0x0d, //  11 1
		0x15, // 1 1 1
		0x15, // 1 1 1
		0x0e  //  111 
	},

// 65
	{
		0x0e, //  111 
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x1f, // 11111
		0x11, // 1   1
		0x11  // 1   1
	},

// 66
	{
		0x1e, // 1111 
		0x11, // 1   1
		0x11, // 1   1
		0x1e, // 1111 
		0x11, // 1   1
		0x11, // 1   1
		0x1e  // 1111 
	},

// 67
	{
		0x0e, //  111 
		0x11, // 1   1
		0x10, // 1    
		0x10, // 1    
		0x10, // 1    
		0x11, // 1   1
		0x0e  //  111 
	},

// 68
	{
		0x1e, // 1111 
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x1e  // 1111 
	},

// 69
	{
		0x1f, // 11111
		0x10, // 1    
		0x10, // 1    
		0x1e, // 1111 
		0x10, // 1    
		0x10, // 1    
		0x1f  // 11111
	},

// 70
	{
		0x1f, // 11111
		0x10, // 1    
		0x10, // 1    
		0x1e, // 1111 
		0x10, // 1    
		0x10, // 1    
		0x10  // 1    
	},

// 71
	{
		0x0e, //  111 
		0x11, // 1   1
		0x10, // 1    
		0x10, // 1    
		0x13, // 1  11
		0x11, // 1   1
		0x0f  //  1111
	},

// 72
	{
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x1f, // 11111
		0x11, // 1   1
		0x11, // 1   1
		0x11  // 1   1
	},

// 73
	{
		0x0e, //  111 
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x0e  //  111 
	},

// 74
	{
		0x07, //   111
		0x02, //    1 
		0x02, //    1 
		0x02, //    1 
		0x02, //    1 
		0x12, // 1  1 
		0x0c  //  11  
	},

// 75
	{
		0x11, // 1   1
		0x12, // 1  1 
		0x14, // 1 1  
		0x18, // 11   
		0x14, // 1 1  
		0x12, // 1  1 
		0x11  // 1   1
	},

// 76
	{
		0x10, // 1    
		0x10, // 1    
		0x10, // 1    
		0x10, // 1    
		0x10, // 1    
		0x10, // 1    
		0x1f  // 11111
	},

// 77
	{
		0x11, // 1   1
		0x1b, // 11 11
		0x1f, // 11111
		0x15, // 1 1 1
		0x11, // 1   1
		0x11, // 1   1
		0x11  // 1   1
	},

// 78
	{
		0x11, // 1   1
		0x19, // 11  1
		0x1d, // 111 1
		0x17, // 1 111
		0x13, // 1  11
		0x11, // 1   1
		0x11  // 1   1
	},

// 79
	{
		0x0e, //  111 
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x0e  //  111 
	},

// 80
	{
		0x1e, // 1111 
		0x11, // 1   1
		0x11, // 1   1
		0x1e, // 1111 
		0x10, // 1    
		0x10, // 1    
		0x10  // 1    
	},

// 81
	{
		0x0e, //  111 
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x15, // 1 1 1
		0x12, // 1  1 
		0x0d  //  11 1
	},

// 82
	{
		0x1e, // 1111 
		0x11, // 1   1
		0x11, // 1   1
		0x1e, // 1111 
		0x12, // 1  1 
		0x11, // 1   1
		0x11  // 1   1
	},

// 83
	{
		0x0e, //  111 
		0x11, // 1   1
		0x10, // 1    
		0x0e, //  111 
		0x01, //     1
		0x11, // 1   1
		0x0e  //  111 
	},

// 84
	{
		0x1f, // 11111
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04  //   1  
	},

// 85
	{
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x0e  //  111 
	},

// 86
	{
		0x11, // 1   1
		0x11, // 1   1
		0x1b, // 11 11
		0x0a, //  1 1 
		0x0e, //  111 
		0x04, //   1  
		0x04  //   1  
	},

// 87
	{
		0x11, // 1   1
		0x11, // 1   1
		0x15, // 1 1 1
		0x15, // 1 1 1
		0x1f, // 11111
		0x0a, //  1 1 
		0x0a  //  1 1 
	},

// 88
	{
		0x11, // 1   1
		0x11, // 1   1
		0x0a, //  1 1 
		0x04, //   1  
		0x0a, //  1 1 
		0x11, // 1   1
		0x11  // 1   1
	},

// 89
	{
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x0e, //  111 
		0x04, //   1  
		0x04, //   1  
		0x04  //   1  
	},

// 90
	{
		0x1f, // 11111
		0x01, //     1
		0x02, //    1 
		0x04, //   1  
		0x08, //  1   
		0x10, // 1    
		0x1f  // 11111
	},

// 91
	{
		0x0e, //  111 
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x0e  //  111 
	},

// 92
	{
		0x10, // 1    
		0x08, //  1   
		0x08, //  1   
		0x04, //   1  
		0x02, //    1 
		0x02, //    1 
		0x01  //     1
	},

// 93
	{
		0x0e, //  111 
		0x02, //    1 
		0x02, //    1 
		0x02, //    1 
		0x02, //    1 
		0x02, //    1 
		0x0e  //  111 
	},

// 94
	{
		0x04, //   1  
		0x0a, //  1 1 
		0x11, // 1   1
		0x00, //      
		0x00, //      
		0x00, //      
		0x00  //      
	},

// 95
	{
		0x00, //      
		0x00, //      
		0x00, //      
		0x00, //      
		0x00, //      
		0x00, //      
		0x1f  // 11111
	},

// 96
	{
		0x0c, //  11  
		0x06, //   11 
		0x00, //      
		0x00, //      
		0x00, //      
		0x00, //      
		0x00  //      
	},

// 97
	{
		0x00, //      
		0x00, //      
		0x0d, //  11 1
		0x13, // 1  11
		0x11, // 1   1
		0x13, // 1  11
		0x0d  //  11 1
	},

// 98
	{
		0x10, // 1    
		0x10, // 1    
		0x16, // 1 11 
		0x19, // 11  1
		0x11, // 1   1
		0x19, // 11  1
		0x16  // 1 11 
	},

// 99
	{
		0x00, //      
		0x00, //      
		0x0e, //  111 
		0x11, // 1   1
		0x10, // 1    
		0x11, // 1   1
		0x0e  //  111 
	},

// 100
	{
		0x01, //     1
		0x01, //     1
		0x0d, //  11 1
		0x13, // 1  11
		0x11, // 1   1
		0x13, // 1  11
		0x0d  //  11 1
	},

// 101
	{
		0x00, //      
		0x00, //      
		0x0e, //  111 
		0x11, // 1   1
		0x1f, // 11111
		0x10, // 1    
		0x0f  //  1111
	},

// 102
	{
		0x06, //   11 
		0x09, //  1  1
		0x08, //  1   
		0x08, //  1   
		0x1c, // 111  
		0x08, //  1   
		0x08  //  1   
	},

// 103
	{
		0x00, //      
		0x00, //      
		0x0f, //  1111
		0x11, // 1   1
		0x0f, //  1111
		0x01, //     1
		0x0e  //  111 
	},

// 104
	{
		0x10, // 1    
		0x10, // 1    
		0x16, // 1 11 
		0x19, // 11  1
		0x11, // 1   1
		0x11, // 1   1
		0x11  // 1   1
	},

// 105
	{
		0x00, //      
		0x04, //   1  
		0x00, //      
		0x0c, //  11  
		0x04, //   1  
		0x04, //   1  
		0x0e  //  111 
	},

// 106
	{
		0x02, //    1 
		0x00, //      
		0x06, //   11 
		0x02, //    1 
		0x02, //    1 
		0x0a, //  1 1 
		0x04  //   1  
	},

// 107
	{
		0x10, // 1    
		0x10, // 1    
		0x12, // 1  1 
		0x14, // 1 1  
		0x18, // 11   
		0x14, // 1 1  
		0x12  // 1  1 
	},

// 108
	{
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x08, //  1   
		0x06  //   11 
	},

// 109
	{
		0x00, //      
		0x00, //      
		0x1a, // 11 1 
		0x15, // 1 1 1
		0x15, // 1 1 1
		0x15, // 1 1 1
		0x11  // 1   1
	},

// 110
	{
		0x00, //      
		0x00, //      
		0x16, // 1 11 
		0x19, // 11  1
		0x11, // 1   1
		0x11, // 1   1
		0x11  // 1   1
	},

// 111
	{
		0x00, //      
		0x00, //      
		0x0e, //  111 
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x0e  //  111 
	},

// 112
	{
		0x00, //      
		0x00, //      
		0x1e, // 1111 
		0x11, // 1   1
		0x1e, // 1111 
		0x10, // 1    
		0x10  // 1    
	},

// 113
	{
		0x00, //      
		0x00, //      
		0x0f, //  1111
		0x11, // 1   1
		0x0f, //  1111
		0x01, //     1
		0x01  //     1
	},

// 114
	{
		0x00, //      
		0x00, //      
		0x16, // 1 11 
		0x18, // 11   
		0x10, // 1    
		0x10, // 1    
		0x10  // 1    
	},

// 115
	{
		0x00, //      
		0x00, //      
		0x0f, //  1111
		0x10, // 1    
		0x0e, //  111 
		0x01, //     1
		0x1e  // 1111 
	},

// 116
	{
		0x00, //      
		0x08, //  1   
		0x08, //  1   
		0x1c, // 111  
		0x08, //  1   
		0x0a, //  1 1 
		0x04  //   1  
	},

// 117
	{
		0x00, //      
		0x00, //      
		0x11, // 1   1
		0x11, // 1   1
		0x11, // 1   1
		0x13, // 1  11
		0x0d  //  11 1
	},

// 118
	{
		0x00, //      
		0x00, //      
		0x11, // 1   1
		0x11, // 1   1
		0x0a, //  1 1 
		0x0a, //  1 1 
		0x04  //   1  
	},

// 119
	{
		0x00, //      
		0x00, //      
		0x11, // 1   1
		0x15, // 1 1 1
		0x15, // 1 1 1
		0x0a, //  1 1 
		0x0a  //  1 1 
	},

// 120
	{
		0x00, //      
		0x00, //      
		0x11, // 1   1
		0x0a, //  1 1 
		0x04, //   1  
		0x0a, //  1 1 
		0x11  // 1   1
	},

// 121
	{
		0x00, //      
		0x00, //      
		0x11, // 1   1
		0x11, // 1   1
		0x0f, //  1111
		0x01, //     1
		0x0e  //  111 
	},

// 122
	{
		0x00, //      
		0x00, //      
		0x1f, // 11111
		0x02, //    1 
		0x04, //   1  
		0x08, //  1   
		0x1f  // 11111
	},

// 123
	{
		0x03, //    11
		0x02, //    1 
		0x02, //    1 
		0x0c, //  11  
		0x02, //    1 
		0x02, //    1 
		0x03  //    11
	},

// 124
	{
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04, //   1  
		0x04  //   1  
	},

// 125
	{
		0x18, // 11   
		0x08, //  1   
		0x08, //  1   
		0x06, //   11 
		0x08, //  1   
		0x08, //  1   
		0x18  // 11   
	},

// 126
	{
		0x00, //      
		0x09, //  1  1
		0x15, // 1 1 1
		0x12, // 1  1 
		0x00, //      
		0x00, //      
		0x00  //      
	},

// 127
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00
	}

};
