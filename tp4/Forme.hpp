#ifndef _FORME_HPP
#define _FORME_HPP

class Forme; /* Canevas.hpp doit connaître l'existence de Forme. */

#include "Canevas.hpp"

class Forme
{
    public:
        Forme(unsigned int couleur);
        virtual ~Forme();
        
        /*
         * Méthode virtuelle pure que les différentes formes doivent implémenter
         */
        virtual void dessiner(Canevas *canevas) const = 0;
        
        void assignerCouleur(unsigned int couleur);
        unsigned int obtenirCouleur(void) const;
        
    protected:
		unsigned int _couleur;
};

#endif // _FORME_HPP
