//
// Created by ultra gamer on 05/04/2021.
//

#ifndef SKIPISCINE_BIBLI_H
#define SKIPISCINE_BIBLI_H

/*
 * Source pour les couleurs : https://stackoverflow.com/questions/20608058/c-colour-console-text
 */



#include "Fonction.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

#include <cmath>
#include <map>

#include <queue>
#include <limits>
#include <bits/stdc++.h>

typedef struct t_chargeSommets{
    int num;
    std::string nom;
    int altitude;
}t_chargeSommets;
typedef  std::map<char, std::map<std::string,std::vector<int>>> t_mapDuree;

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




struct comparaisonDijkstraOpti
{
    bool operator()(const std::pair<int,std::pair<float,bool>>& a, const std::pair<int,std::pair<float,bool>>& b)
    {

        if(a.second.second && b.second.second)
            return a.second.first > b.second.first;

        if(a.second.second==true)
            return true;
        if(b.second.second==true)
            return false;

        return a.second.first > b.second.first;
    }
};



#endif //SKIPISCINE_BIBLI_H

