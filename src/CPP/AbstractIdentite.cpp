//
// Created by mathis on 05/04/2021.
//

#include "../Headers/AbstractIdentite.h"

AbstractIdentite::AbstractIdentite(const int& _num, const std::string &_nom)
                :m_num(_num),m_nom(_nom)
{

}

//Getters & Setters
int AbstractIdentite::getNum() const {
    return m_num;
}

std::string AbstractIdentite::getNom() const {
    return m_nom;
}