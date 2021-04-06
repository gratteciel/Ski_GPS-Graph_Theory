//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Trajet.h"

//Constructeur

Trajet::Trajet(const int &_num, const std::string &_nom, const std::string &_type, const Sommet *depart, const Sommet *arrivee, std::map<std::string, std::vector<std::pair<std::string,std::vector<int>>>>& matriceDuree)
      :AbstractIdentite(_num,_nom), m_type(_type)
{
    m_sommets.first=depart;
    m_sommets.second=arrivee;
    m_duree = calculDuree(_nom,_type,depart->getAltitude(),arrivee->getAltitude(),matriceDuree);
}

//Méthodes

void Trajet::affichage(){
    std::cout << "Trajet n'"<<getNum() << ": "<<getNom() << std::endl;
}

//Getters & Setters

std::string Trajet::getType() const {
    return m_type;
}
float Trajet::calculDuree(const std::string nom, const std::string type, int depart, int arrivee, std::map<std::string, std::vector<std::pair<std::string,std::vector<int>>>>& matriceDuree) {
    for (const auto elem : matriceDuree) {

        for (int i = 0; i < elem.second.size(); ++i) {
            if(elem.first == "Descente" && type == elem.second[i].first){
                return (float)elem.second[i].second[0] * abs(arrivee - depart) / 100;

            }

            else if(elem.first == "Bus" && nom == elem.second[i].first) {
                return (float)elem.second[i].second[0];

            }

            else if(elem.first == "Montee" && type == elem.second[i].first) {
                return (float)elem.second[i].second[0] * abs(arrivee - depart) / 100 + elem.second[i].second[1];

            }


        }
    }
    return 0;

}

