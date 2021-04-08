//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Sommet.h"

bool trierAdjacentsSelonNumSecondSommet (Trajet* i,Trajet* j) {
    return (i->getSommets().second->getNum()<j->getSommets().second->getNum());
}

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

void Sommet::trierAdjacents(){
    std::sort(m_adjacents.begin(),m_adjacents.end(),trierAdjacentsSelonNumSecondSommet);
}

std::string Sommet::afficheSimple(){
    std::string temp =getNom();
    if(temp!=std::to_string(getNum()))
        temp += " (" + std::to_string(getNum()) +  ")";
   return temp;
}

void Sommet::affichageComplexe(const std::map<int,Trajet*>& _trajets){
    std::cout <<std::endl<< "Information detaille du point: " << getNom() << " (" <<getAltitude() <<"m)" << std::endl<<std::endl;

    std::cout << "Les trajets partants de ce point: " << std::endl;
    for(const auto& elem: m_adjacents){
        elem->affichageComplexe(true);
    }

    std::cout <<std::endl<< "Les trajets allant a ce point: " << std::endl;
    for(const auto& elem: _trajets){
       if(elem.second->getSommets().second->getNum()==getNum())
           elem.second->affichageComplexe(false);
    }
    std::cout << std::endl;
}

void Sommet::setAdjactent(Trajet* _trajet){
    m_adjacents.push_back(_trajet);
}


//Getters & Setters

int Sommet::getAltitude() const {
    return m_altitude;
}

std::vector<Trajet*> Sommet::getAdjacents() const {
    return m_adjacents;
}