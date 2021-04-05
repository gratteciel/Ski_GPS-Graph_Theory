//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_SOMMET_H
#define SKIPISCINE_SOMMET_H
#include <iostream>


class Sommet {
private:
    int m_num;
    std::string m_nom;
    int m_altitude;
public:
    //Constructeur et destructeur
    Sommet(int _num, std::string _nom, int _altitude);

    ~Sommet() = default;

    //Méthodes

    //Getters & Setters
};


#endif //SKIPISCINE_SOMMET_H
