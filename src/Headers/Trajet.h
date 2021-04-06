//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_TRAJET_H
#define SKIPISCINE_TRAJET_H

#include "Sommet.h"
#include "AbstractIdentite.h"

class Sommet;

class Trajet : public AbstractIdentite{
private:
    std::pair< Sommet*,  Sommet*> m_sommets;
    char m_gType;
    std::string m_type;
    float m_duree;
public:
    //Constructeur et destructeur
    Trajet(const int& _num, const std::string& _nom, const std::string& _type,  Sommet* depart,  Sommet* arrivee, std::map<std::string, std::vector<std::pair<std::string,std::vector<int>>>>& matriceDuree);
    ~Trajet() = default;
    //Méthodes
    void affichage();
    std::string returnNomType();
    void affichageComplexe(const bool& partant);
    //Getters & Setters
    float calculDuree(const std::string nom, const std::string type, int depart, int arrivee, std::map<std::string, std::vector<std::pair<std::string,std::vector<int>>>>& matriceDuree);
    std::string getType() const;
    float getDuree() const;
    std::pair<Sommet*,Sommet*> getSommets() const;
    void setGType();
    char getGType() const;
};


#endif //SKIPISCINE_TRAJET_H

