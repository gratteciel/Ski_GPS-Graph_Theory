//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Domaine.h"

//Constructeur & destructeur
Domaine::Domaine() {
    m_matriceDuree["BUS"];
    m_matriceDuree["Montee"];
    m_matriceDuree["Descente"];


}



Domaine::~Domaine(){
    for(auto s : m_sommets)
        delete s.second;

    for (auto t : m_trajets)
        delete t.second;
}

//Méthodes

void Domaine::initialisation(const t_chargeFichier& fCharge){
    creationSommets(fCharge.sommets);
    creationTrajets(fCharge.trajets);
}


void Domaine::creationSommets(const std::vector<t_chargeSommets>& _som){
    for(const auto s: _som)
        m_sommets[s.num] = new Sommet(s.num,s.nom,s.altitude);
}
float Domaine::calculDuree(std::string type,int depart, int arrivee)
{
    for(const auto elem : m_matriceDuree)
    {
        for (int i = 0; i < elem.second.size(); ++i) {

            if(type == elem.second[i].first){
                if (elem.first == "BUS")
                {
                    return elem.second[i].second[0];

                }
                else {
                    if (elem.second[i].second.size() == 0 ){
                        return  ( (elem.second[i].second[0] * abs(depart-arrivee))  / 100 ) ;
                    }
                    else
                    {
                        return (((elem.second[i].second[0] * abs(depart-arrivee))  / 100 ) + elem.second[i].second[1] ) ;
                    }
                }
            }

        }
    }

}


void Domaine::creationTrajets(const std::vector<t_chargeTrajet>& _tra){
    for(const auto t: _tra){
        m_trajets[t.num] = new Trajet(t.num,t.nom,t.type,m_sommets[t.depart],m_sommets[t.arrivee],calculDuree(t.type,t.depart,t.arrivee));
        m_sommets[t.depart]->setAdjactent(m_trajets[t.num]);
    }
}

//Getters & Setters
void Domaine::setOrdre(int _ordre) {
    m_ordre = _ordre;
}
void Domaine::setTaille(int _taille) {
    m_taille = _taille;
}
int Domaine::getOrdre() const {
    return m_ordre;
}

int Domaine::getTaille() const {
    return m_taille;
}

std::map<std::string, std::vector<std::pair<std::string,std::vector<int>>>>& Domaine::getMatriceDuree()
{
    return m_matriceDuree;
}

