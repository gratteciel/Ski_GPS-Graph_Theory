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
///Sous-programme permettant d'afficher un sommet
void Sommet::affichage() {

    if(std::to_string(getNum())[0]!=getNom()[0])
        std::cout << "Point: "  << getNom() << " (" <<getNum() << ") -> " <<getAltitude() <<"m" << std::endl;
    else
        std::cout << "Point: " <<getNom() << " -> " <<getAltitude() << "m" <<std::endl;
}

///Sous-programme permettant de trier les trajets sortants du sommet
void Sommet::trierSortants(){
    std::sort(m_sortants.begin(),m_sortants.end(),trierAdjacentsSelonNumSecondSommet);
}

///Sous-programme affichant le nom et le numéro entre parenthèse si le nom != numéro
std::string Sommet::afficheSimple(){
    std::string temp =getNom();
    if(temp!=std::to_string(getNum()))
        temp += " (" + std::to_string(getNum()) +  ")";
   return temp;
}

///Sous-programme permettant d'afficher un sommet avec les trajets entrants et sortants
void Sommet::affichageComplexe(const std::map<int,Trajet*>& _trajets){
    std::cout <<std::endl<< "Information detaille du point: " << getNom() << " (" <<getAltitude() <<"m)" << std::endl<<std::endl;


    print("Les trajets partants de ce point: ",color_orange);
    std::cout << std::endl;

    for(const auto& elem: m_sortants){
        elem->affichageComplexe(true);
    }
    std::cout << std::endl;
    print("Les trajets allant a ce point: ",color_orange);
    std::cout << std::endl;

    for(const auto& elem: m_entrants){
        elem->affichageComplexe(true);
    }
    std::cout << std::endl;
}



//Getters & Setters

int Sommet::getAltitude() const {
    return m_altitude;
}

std::vector<Trajet*> Sommet::getSortants() const {
    return m_sortants;
}

std::vector<Trajet*> Sommet::getEntrants() const {
    return m_entrants;
}

void Sommet::setSortant(Trajet* _trajet){
    m_sortants.push_back(_trajet);
}

void Sommet::setEntrant(Trajet* _trajet){
    m_entrants.push_back(_trajet);
}