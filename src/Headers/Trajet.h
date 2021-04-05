//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_TRAJET_H
#define SKIPISCINE_TRAJET_H
#include "AbstractIdentite.h"
#include "Sommet.h"

class Sommet;
class Trajet : public AbstractIdentite{
private:
    std::pair<const Sommet*, const Sommet*> m_sommets;

    std::string m_type;
public:
    //Constructeur et destructeur
    Trajet(const int& _num, const std::string& _nom, const std::string& _type, const Sommet* depart, const Sommet* arrivee);
    ~Trajet() = default;
    //Méthodes
    void affichage();
    //Getters & Setters
    std::string getType() const;
};


#endif //SKIPISCINE_TRAJET_H
