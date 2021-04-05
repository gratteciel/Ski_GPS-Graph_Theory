//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_DOMAINE_H
#define SKIPISCINE_DOMAINE_H
#include "Sommet.h"
#include "Trajet.h"
#include <map>


class Domaine {
private:
    std::map<int, Sommet*> m_sommets;
    std::map<int, Trajet*> m_trajets;
public:
    //Constructeur et destructeur
    Domaine();
    ~Domaine();

    //Méthodes

    //Getters & Setters
};


#endif //SKIPISCINE_DOMAINE_H
