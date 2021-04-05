//
// Created by mathis on 05/04/2021.
//

#include "../Headers/General.h"


//Constructeur

General::General(const std::string &nomfichier) {
    t_chargeFichier fCharge;
    lecturefichier(nomfichier,fCharge);
    arcs.initialisation(fCharge);

}


//Méthodes

void General::lecturefichier(const std::string &nomfichier,t_chargeFichier& fCharge) {

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
        fichier >> tempSommet.altitude;
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les sommets");
        fCharge.sommets.push_back(tempSommet);
    }
    fichier >> temp;// nombre de descentes avce les types

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<int>> paireDonnee;
        int donnee;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(donnee);
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les descentes");
        arcs.getMatriceDuree()["Descente"].push_back(paireDonnee);
    }
    fichier >> temp;// nombre de montée

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<int>> paireDonnee;
        std::string donnee;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(std::stoi(donnee));
        fichier >> donnee;
        paireDonnee.second.push_back(std::stoi(donnee));
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les montees");
        arcs.getMatriceDuree()["Montee"].push_back(paireDonnee);
    }
    fichier >> temp;// nombre de Bus

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<int>> paireDonnee;
        int donnee;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(donnee);
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les Bus");
        arcs.getMatriceDuree()["BUS"].push_back(paireDonnee);
    }



    fichier >> temp; // nombre d'arcs dans le graphe
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

        fCharge.trajets.push_back(tempTrajet);

    }

}
