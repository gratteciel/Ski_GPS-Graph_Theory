//
// Created by ultra gamer on 05/04/2021.
//

#ifndef SKIPISCINE_BIBLI_H
#define SKIPISCINE_BIBLI_H
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <queue>
#include <limits>
#include <bits/stdc++.h>
typedef struct t_chargeSommets{
    int num;
    std::string nom;
    int altitude;
}t_chargeSommets;

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

struct comparaisonDijkstra
{
    bool operator()(const std::pair<int,int>& a, const std::pair<int,int>& b)
    {
        return a.second > b.second;
    }
};

#endif //SKIPISCINE_BIBLI_H

