//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Trajet.h"

//Constructeur

Trajet::Trajet(const int &_num, const std::string &_nom, const std::string &_type,  Sommet *depart,  Sommet *arrivee)
      :AbstractIdentite(_num,_nom), m_type(_type)
{
    m_sommets.first=depart;
    m_sommets.second=arrivee;
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
