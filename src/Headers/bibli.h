//
// Created by ultra gamer on 05/04/2021.
//

#ifndef SKIPISCINE_BIBLI_H
#define SKIPISCINE_BIBLI_H
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cmath>
#include <map>

typedef struct t_chargeSommets{
    int num;
    std::string nom;
    int altitude;
}t_chargeSommets;
typedef  std::map<std::string, std::vector<std::pair<std::string,std::vector<int>>>> mapDuree;

typedef struct t_chargeTrajet{
    int num;
    std::string nom;
    std::string type;
    int depart;
    int arrivee;
}t_chargeTrajet;

typedef struct t_chargeFichier{
    std::vector<t_chargeSommets> sommets;
    std::vector<t_chargeTrajet> trajets;
}t_chargeFichier;



#endif //SKIPISCINE_BIBLI_H

