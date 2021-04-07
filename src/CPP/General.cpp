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

    /// Concernant le remplissage des descentes et des Bus nécéssité de rajouter une ligne vide ///

    fichier >> temp;// nombre de descentes avce les types

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<int>> paireDonnee;
        int donnee = 0;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(donnee);
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les descentes");
        arcs.getMatriceDuree()['D'][paireDonnee.first]=paireDonnee.second;
    }
    fichier >> temp;// nombre de Bus

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<int>> paireDonnee;
        int donnee = 0;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(donnee);
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les Bus");
        arcs.getMatriceDuree()['B'][paireDonnee.first]=paireDonnee.second;
    }

    fichier >> temp;// nombre de remontee

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<int>> paireDonnee;
        std::string donnee=" ";
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(std::stoi(donnee));
        fichier >> donnee;
        paireDonnee.second.push_back(std::stoi(donnee));
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les montees");
        arcs.getMatriceDuree()['R'][paireDonnee.first]=paireDonnee.second;
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
    int menuActu=1;
    std::map<int,float> poids;
    //std::vector<std::string> typeAEnlever;
    //typeAEnlever.push_back("N");

    //std::map<int,int> pred = arcs.dijkstraOpti(3,poids,typeAEnlever);
    while(menuActu!=0){
        std::system("clear || cls");
        afficheMenu(menuActu);
        std::cout <<std::endl<< "Menu n'" ;
        std::string donnee;

        std::cin >> donnee;
        std::system("clear || cls");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        interactionDonnee(donnee,menuActu);

    }
}

void General::interactionDonnee(const std::string &donnee, int &menuActu) {
    if(donnee=="q")
        menuActu=0;
    else{
        switch(menuActu){
            case 1:
                interactionDonneeMenu1(donnee,menuActu);
                break;
            case 2:
                interactionDonneeMenu2(donnee,menuActu);
                break;
            case 3:
                interactionDonneeMenu3(donnee,menuActu);
                break;
            case 4:
                interactionDonneeMenu4(donnee,menuActu,true);
                break;
            case 5:
                interactionDonneeMenu4(donnee,menuActu,false);
                break;
            case 6:
                interactionDonneeMenu6(donnee,menuActu);
                break;
        }
    }

}
void General::interactionDonneeMenu1(const std::string& donnee, int& menuActu){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '1':
                arcs.afficheInfo();
                finProgrammeActu();
                break;
            case '2':
                if(arcs.changementDuree())
                    finProgrammeActu();
                break;
            case '3':
                menuActu=2;
                break;
            case '4':
                menuActu =3;
                break;
            case '5':
                menuActu=6;
                break;
        }
    }

}

void General::interactionDonneeMenu2(const std::string& donnee, int& menuActu){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':
                menuActu=1;
                break;
            case '1':
                arcs.afficheSommets();
                finProgrammeActu();
                break;
            case '2':
                std::string numSommet;
                arcs.afficheSommets(numSommet);
                finProgrammeActu();
                break;
        }
    }

}

void General::interactionDonneeMenu3(const std::string& donnee, int& menuActu){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':
                menuActu=1;
                break;
            case '1':
                arcs.afficheTrajets();
                finProgrammeActu();
                break;
            case '2':
                arcs.afficheTrajets('D');
                finProgrammeActu();
                break;
            case '3':
                arcs.afficheTrajets('R');
                finProgrammeActu();
                break;
            case '4':
                arcs.afficheTrajets('B');
                finProgrammeActu();
                break;
            case '5':
                std::string numTrajet;
                std::cout << "Nom ou numero du trajet: ";
                std::getline (std::cin,numTrajet);
                arcs.afficheTrajets('T',numTrajet);
                finProgrammeActu();
                break;
        }
    }

}

void General::finProgrammeActu(){
    std::cout <<std::endl<< "Appuyez sur entree pour revenir au menu...........";
    char ch = getchar();

}

void General::interactionDonneeMenu4(const std::string& donnee, int& menuActu,const bool& estDijkstra){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':
                menuActu=6;
                break;
            case '1':{
                int s = arcs.entreePoint("Nom ou numero du point initial: ");
                arcs.plusCourtChemin(estDijkstra,s);
                finProgrammeActu();
                break;
            }

            case '2':{
                int s0 = arcs.entreePoint("Nom ou numero du point initial: ");
                int sF = arcs.entreePoint("Nom ou numero du point final: ");
                arcs.plusCourtChemin(estDijkstra,s0,sF);
                finProgrammeActu();
                break;
            }

        }
    }

}



void General::interactionDonneeMenu6(const std::string& donnee, int& menuActu){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':
                menuActu=1;
                break;
            case '1':{
                menuActu=4;
                break;
            }

            case '2':{
                menuActu=5;
                break;
            }

        }
    }

}



void General::afficheMenu(const int& menuActu){
    std::cout << "q : Quitter le programme" <<std::endl;
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
        case 4:
            menu4(true);
            break;
        case 5:
            menu4(false);
            break;
        case 6:
            menu6();
            break;
    }
}

void General::menu1(){
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout <<  "     Domaine skiable des arcs   " << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl <<"1 : A propos du domaine skiable des Arcs" << std::endl;
    std::cout << "2 : Afficher/Modifier les temps par default des trajets (4.1)" << std::endl;
    std::cout << "3 : A propos des points (4.3)" << std::endl;
    std::cout << "4 : A propos des trajets (4.3)" << std::endl;
    std::cout << "5 : Plus courts chemins (4.4)" << std::endl;
}

void General::menu2(){
    std::cout << "0 : Retour en arriere" << std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout <<  "       A propos des points   " << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl <<"1 : Afficher tous les points" << std::endl;
    std::cout << "2 : Information sur 1 point" << std::endl;
}

void General::menu3(){
    std::cout << "0 : Retour en arriere" << std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout <<  "       A propos des trajets   " << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout <<std::endl << "1 : Afficher tous les trajets" << std::endl;
    std::cout << "2 : Afficher toutes les pistes" << std::endl;
    std::cout << "3 : Afficher toutes les remontees" << std::endl;
    std::cout << "4 : Afficher toutes les navettes" << std::endl;
    std::cout << "5 : Information sur 1 trajet" << std::endl;
}

void General::menu4(const bool& estDijkstra){
    std::cout << "0 : Retour en arriere" << std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    if(estDijkstra)
        std::cout <<  "            En temps   " << std::endl;
    else
        std::cout <<  "      En nombre de trajets   " << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl <<"1 : Tous les plus courts chemin en partant d'un point" << std::endl;
    std::cout << "2 : Plus court chemin entre 2 points" << std::endl;
}

void General::menu6(){
    std::cout << "0 : Retour en arriere" << std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout <<  "        Plus court chemin   " << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl <<"1 : Plus court chemin en temps" << std::endl;
    std::cout << "2 : Plus court chemin en nombre de trajets" << std::endl;
}