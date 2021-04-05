//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_SOMMET_H
#define SKIPISCINE_SOMMET_H

#include <vector>
#include "AbstractIdentite.h"
#include "Trajet.h"

class Trajet;

class Sommet : public AbstractIdentite{
private:
    int m_altitude;
    std::vector<const Trajet*> m_adjacents;
public:
    //Constructeur et destructeur
    Sommet(const int& _num, const std::string& _nom, const int& _altitude);
    ~Sommet() = default;
    //Méthodes
    void affichage();
    //Getters & Setters
    int getAltitude() const;

};


#endif //SKIPISCINE_SOMMET_H
