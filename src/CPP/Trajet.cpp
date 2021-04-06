//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Trajet.h"

//Constructeur

Trajet::Trajet(const int &_num, const std::string &_nom, const std::string &_type,  Sommet *depart,  Sommet *arrivee, std::map<std::string, std::vector<std::pair<std::string,std::vector<int>>>>& matriceDuree)
      :AbstractIdentite(_num,_nom), m_type(_type)
{
    m_sommets.first=depart;
    m_sommets.second=arrivee;
    m_duree = calculDuree(_nom,_type,depart->getAltitude(),arrivee->getAltitude(),matriceDuree);
}

//Méthodes

void Trajet::affichage(){
    std::cout << "Trajet n'"<<getNum() << ": "<<getNom() <<" (" << returnNomType();

    std::cout << ") allant du point " <<m_sommets.first->getNom() << " a "  << m_sommets.second->getNom() << std::endl;
}

void Trajet::affichageComplexe(const bool& partant){
    std::cout << "n'"<<getNum() << ": "<<getNom() <<" ("<< returnNomType();

    if(partant)
        std::cout << ") allant a "  << m_sommets.second->getNom() << std::endl;
    else
        std::cout << ") partant de "  << m_sommets.first->getNom() << std::endl;
}


std::string Trajet::returnNomType(){

    if(getType().size()==1){

        switch(getType()[0]){
            case 'V':
                return "Piste verte";
                break;
            case 'B':
                return "Piste bleu";
                break;
            case 'R':
                return "Piste rouge";
                break;
            case 'N':
                return "Piste noire";
                break;
        }
    }
    else{
        if(getType()=="KL")
            return "Piste de kilometre lance";
        else if(getType()=="SURF")
            return "Snowpark";
        else if(getType()=="TPH")
            return "Telepherique";
        else if(getType()=="TC")
            return "Telecabine";
        else if(getType()=="TSD")
            return "Telesiege debrayable";
        else if(getType()=="TS")
            return "Telesiege";
        else if(getType()=="TK")
            return "Teleski";
        else if(getType()=="BUS")
            return "Navette";

    }

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


std::pair<Sommet*,Sommet*> Trajet::getSommets() const{
    return m_sommets;
}

void Trajet::setGType(){
    std::string type=getType();

    if(type=="V"||type=="B"||type=="R"||type=="N"||type=="KL"||type=="SURF")
        m_gType='D';
    else if (type[0]=='T')
        m_gType='R';
    else if (type=="BUS")
        m_gType='B';

}

char Trajet::getGType() const{
    return m_gType;
}
