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
        std::pair<std::string,std::vector<float>> paireDonnee;
        float donnee;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(donnee);
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les descentes");
        arcs.getMatriceDuree()["Descente"].push_back(paireDonnee);
    }
    fichier >> temp;// nombre de montée

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<float>> paireDonnee;
        std::string donnee;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(std::stof(donnee));
        fichier >> donnee;
        paireDonnee.second.push_back(std::stof(donnee));
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les montees");
        arcs.getMatriceDuree()["Montee"].push_back(paireDonnee);
    }
    fichier >> temp;// nombre de Bus

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<float>> paireDonnee;
        float donnee;
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

void General::boucle(){
    int menuActu;
    while(1==1){
        system("cls");
        afficheMenu(menuActu);
        char donnee;
        std::cin >> donnee;
        interactionDonnee(donnee,menuActu);
    }
}

void General::interactionDonnee(const char &donnee, int &menuActu) {
    switch(menuActu){
        case 1:
            interactionDonneeMenu1(donnee,menuActu);
            break;
    }
}
void General::interactionDonneeMenu1(const char& donnee, int& menuActu){
    switch(donnee){
        case '1':
            menuActu=2;
            break;
        case '2':
            menuActu =3;
            break;

    }
}

void General::afficheMenu(const int& menuActu){
    switch(menuActu){
        case 1:
            menu1();
            break;
        case 2:
            menu2();
            break;
        case 3:
            menu3();
            break;
    }
}

void General::menu1(){
    std::cout << "1 : A propos des sommets" << std::endl;
    std::cout << "2 : A propos des trajets" << std::endl;
}

void General::menu2(){
    std::cout << "1 : Afficher tous les sommets" << std::endl;
    std::cout << "2 : Information sur 1 sommet" << std::endl;
}

void General::menu3(){
    std::cout << "1 : Afficher tous les trajets" << std::endl;
    std::cout << "2 : Information sur 1 trajet" << std::endl;
}