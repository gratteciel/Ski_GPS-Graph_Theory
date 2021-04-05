//
// Created by mathis on 05/04/2021.
//

#include "../Headers/General.h"



General::General(const std::string &nomfichier) {
    lecturefichier(nomfichier);
}

void General::lecturefichier(const std::string &nomfichier) {
    std::vector<t_chargeSommets> vecteurSommets;
    std::vector <t_chargeTrajet> vecteurTrajets;
    std::ifstream fichier (nomfichier);
    int temp = 0;

    if(!fichier)
        throw std::runtime_error( "Impossible d'ouvrir en lecture ");


    fichier >> temp ; // nombre de sommets dans le graphe
    arcs.setOrdre(temp);

    if(fichier.fail())
        throw std::runtime_error("Probleme de lecture de l'ordre du graphe");

    for(int i = 0 ; i < arcs.getOrdre(); i++)
    {
        t_chargeSommets tempSommet;
        fichier >> tempSommet.num ;
        fichier >> tempSommet.nom ;
        fichier >> tempSommet.alitude;
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les sommets");
        vecteurSommets.push_back(tempSommet);
    }

    fichier >> temp; // nombre d'arêtes dans le graphe
    arcs.setTaille(temp);
    if ( fichier.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    for (int i = 0; i < arcs.getTaille(); ++i) {
        t_chargeTrajet tempTrajet;
        fichier >> tempTrajet.num;
        fichier >>tempTrajet.nom;
        fichier >> tempTrajet.type;
        fichier >> tempTrajet.depart;
        fichier >> tempTrajet.arrivee;
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture nom d'une sommet");

        vecteurTrajets.push_back(tempTrajet);

    }





}
