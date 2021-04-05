//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Sommet.h"

//Constructeur

Sommet::Sommet(const int& _num, const std::string& _nom, const int& _altitude)
       :AbstractIdentite(_num,_nom), m_altitude(_altitude)
{

}

//Méthodes

void Sommet::affichage() {
    std::cout << "Sommet" << std::endl;
}

void Sommet::setAdjactent(Trajet* _trajet){
    m_adjacents.push_back(_trajet);
}


//Getters & Setters

int Sommet::getAltitude() const {
    return m_altitude;
}

