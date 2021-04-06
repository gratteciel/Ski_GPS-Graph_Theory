//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Trajet.h"

//Constructeur

Trajet::Trajet(const int &_num, const std::string &_nom, const std::string &_type,  Sommet *depart,  Sommet *arrivee, const t_mapDuree& matriceDuree)
      :AbstractIdentite(_num,_nom), m_type(_type)
{
    m_sommets.first=depart;
    m_sommets.second=arrivee;
    setGType();
    m_duree = calculDuree(matriceDuree);
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
    return "bug";

}



//Getters & Setters

std::string Trajet::getType() const {
    return m_type;
}

float Trajet::calculDuree(const t_mapDuree& matriceDuree) {
    int depart= m_sommets.first->getAltitude();
    int arrivee= m_sommets.second->getAltitude();


    if(getGType()=='B')
            return matriceDuree.find('B')->second.find(getNom())->second[0];
    else if(getGType()=='D')
        return (float)matriceDuree.find('D')->second.find(getType())->second[0] * abs(arrivee-depart) / 100;
    else if(getGType()=='R')
        return (float)matriceDuree.find('R')->second.find(getType())->second[0] * abs(arrivee-depart) / 100 + matriceDuree.find('R')->second.find(getType())->second[1];



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
void Trajet::setDuree(float _duree) {
    m_duree = _duree;
}

char Trajet::getGType() const{
    return m_gType;
}

float Trajet::getDuree() const {
    return m_duree;
}

