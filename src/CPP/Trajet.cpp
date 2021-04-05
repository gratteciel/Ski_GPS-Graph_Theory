//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Trajet.h"

//Constructeur

Trajet::Trajet(const int &_num, const std::string &_nom, const std::string &_type, const Sommet *depart, const Sommet *arrivee, int _duree)
      :AbstractIdentite(_num,_nom), m_type(_type), m_duree(_duree)
{
    m_sommets.first=depart;
    m_sommets.second=arrivee;
}

//Méthodes

void Trajet::affichage(){
    std::cout << "Trajet n'"<<getNum() << ": "<<getNom() << std::endl;
}

//Getters & Setters

std::string Trajet::getType() const {
    return m_type;
}

