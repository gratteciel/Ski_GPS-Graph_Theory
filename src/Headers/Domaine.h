//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_DOMAINE_H
#define SKIPISCINE_DOMAINE_H
#include "Sommet.h"
#include "Trajet.h"
#include <map>



class Domaine {
private:
    std::map<int, Sommet*> m_sommets;
    std::map<int, Trajet*> m_trajets;
    int m_ordre; // nombre de sommmets
    int m_taille; // nombre d'aretes

public:
    //Constructeur et destructeur
    Domaine();
    ~Domaine();

    //Méthodes
    void creationSommets(const std::vector<t_chargeSommets>& _som);
    void initialisation(const t_chargeFichier &fCharge);

    //Getters & Setters
    void setOrdre(int _ordre);
    void setTaille(int _taille);
    int getOrdre() const;
    int getTaille() const;


    void creationTrajets(const std::vector<t_chargeTrajet> &_tra);
};


#endif //SKIPISCINE_DOMAINE_H
