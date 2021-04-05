//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_SOMMET_H
#define SKIPISCINE_SOMMET_H


#include "AbstractIdentite.h"
#include "Trajet.h"

class Trajet;

class Sommet : public AbstractIdentite{
private:
    int m_altitude;
    std::vector<Trajet*> m_adjacents;
public:
    //Constructeur et destructeur
    Sommet(const int& _num, const std::string& _nom, const int& _altitude);
    ~Sommet() = default;
    //Méthodes
    void affichage();
    void setAdjactent(Trajet *_trajet);
    //Getters & Setters
    int getAltitude() const;


    void affichageComplexe(const std::map<int,Trajet*>& _trajet);
};


#endif //SKIPISCINE_SOMMET_H
