//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_GENERAL_H
#define SKIPISCINE_GENERAL_H
#include "Domaine.h"

typedef struct t_chargeSommets{
    int num;
    std::string nom;
    int alitude;
}t_chargeSommets;

typedef struct t_chargeTrajet{
    int num;
    std::string nom;
    std::string type;
    int depart;
    int arrivee;
}t_chargeTrajet;

class General {
private:
    Domaine arcs;
public:
    //Constructeur et destructeur
    General();

    ~General() = default;

    //Méthodes

    //Getters & Setters
};


#endif //SKIPISCINE_GENERAL_H
