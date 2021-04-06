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

    if(std::to_string(getNum())[0]!=getNom()[0])
        std::cout << "Point: "  << getNom() << " (" <<getNum() << ") -> " <<getAltitude() <<"m" << std::endl;
    else
        std::cout << "Point: " <<getNom() << " -> " <<getAltitude() << "m" <<std::endl;
}

void Sommet::affichageComplexe(const std::map<int,Trajet*>& _trajets){
    std::cout << "Information detaille du point: " << getNom() << " (" <<getAltitude() <<"m)" << std::endl<<std::endl;

    std::cout << "Les trajets partants de ce point: " << std::endl;
    for(const auto& elem: m_adjacents){
        elem->affichageComplexe(true);
    }

    std::cout <<std::endl<< "Les trajets allant a ce point: " << std::endl;
    for(const auto& elem: _trajets){
       if(elem.second->getSommets().second->getNum()==getNum())
           elem.second->affichageComplexe(false);
    }

}

void Sommet::setAdjactent(Trajet* _trajet){
    m_adjacents.push_back(_trajet);
}


//Getters & Setters

int Sommet::getAltitude() const {
    return m_altitude;
}

