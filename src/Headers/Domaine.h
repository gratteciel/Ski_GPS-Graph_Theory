//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_DOMAINE_H
#define SKIPISCINE_DOMAINE_H
#include "Sommet.h"

class Domaine {
private:
    int m_ordre; // nombre de sommmets
    int m_taille; // nombre d'aretes

public:
    //Constructeur et destructeur
    Domaine();

    ~Domaine() = default;

    //Méthodes

    //Getters & Setters
    void setOrdre(int _ordre);
    void setTaille(int _taille);
    int getOrdre() const;
    int getTaille() const;
};


#endif //SKIPISCINE_DOMAINE_H
