//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_GENERAL_H
#define SKIPISCINE_GENERAL_H
#include "Domaine.h"



class General {
private:
    Domaine arcs;

public:
    //Constructeur et destructeur
    General(const std::string &nomfichier);
    ~General() = default;
    //Méthodes
    void lecturefichier(const std::string &nomfichier,t_chargeFichier& fCharge);
    //Getters & Setters

};


#endif //SKIPISCINE_GENERAL_H
