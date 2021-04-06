//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_DOMAINE_H
#define SKIPISCINE_DOMAINE_H
#include "Sommet.h"
#include "Trajet.h"




class Domaine {
private:
    std::map<int, Sommet*> m_sommets;
    std::map<int, Trajet*> m_trajets;
    int m_ordre; // nombre de sommmets
    int m_taille; // nombre d'aretes
    t_mapDuree m_matriceDuree;


public:
    //Constructeur et destructeur
    Domaine();
    ~Domaine();

    //Méthodes
    void creationSommets(const std::vector<t_chargeSommets>& _som);
    void initialisation(const t_chargeFichier &fCharge);
    void creationTrajets(const std::vector<t_chargeTrajet> &_tra);
    void afficheTrajets(const char& type='N',std::string sommetChoisie="n");
    void afficheSommets(const std::string& sommetChoisie="n");

    //Getters & Setters
    void setOrdre(int _ordre);
    void setTaille(int _taille);
    int getOrdre() const;
    int getTaille() const;
    t_mapDuree& getMatriceDuree();


    bool estNombre(const std::string &str);

    std::map<int, int> dijkstra(const int &sInit, std::map<int, int> &poids);
};


#endif //SKIPISCINE_DOMAINE_H
