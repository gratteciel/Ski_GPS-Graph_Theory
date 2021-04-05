//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_ABSTRACTIDENTITE_H
#define SKIPISCINE_ABSTRACTIDENTITE_H
#include "bibli.h"

class AbstractIdentite {
private:
    int m_num;
    std::string m_nom;
public:
    //Constructeur et destructeur
    AbstractIdentite(const int& num, const std::string& _nom);
    ~AbstractIdentite() = default;
    //Méthodes
    virtual void affichage() = 0; //Méthode pour permettre l'abstraction de la classe
    //Getters & Setters
    int getNum() const;
    std::string getNom() const;
};


#endif //SKIPISCINE_ABSTRACTIDENTITE_H
