//
// Created by mathis on 05/04/2021.
//


#include "../Headers/General.h"


//Constructeur

General::General(const std::string &nomfichier)
        :m_estOptiChemin(false)
{
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
        m_optiTrajets.push_back(std::make_pair(paireDonnee.first,false));
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
    m_optiTrajets.push_back(std::make_pair("BUS",true));
    fichier >> temp;// nombre de remontee

    for (int i = 0; i < temp; ++i) {
        std::pair<std::string,std::vector<int>> paireDonnee;
        int donnee;
        fichier >> paireDonnee.first;
        fichier >> donnee;
        paireDonnee.second.push_back(donnee);
        fichier >> donnee;
        paireDonnee.second.push_back(donnee);
        if(fichier.fail())
            throw std::runtime_error("Probleme lecture pour les montees");
        arcs.getMatriceDuree()['R'][paireDonnee.first]=paireDonnee.second;
        m_optiTrajets.push_back(std::make_pair(paireDonnee.first,true));
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


/// Interaction menu ///
void General::finProgrammeActu(){
    std::cout <<std::endl<< "Appuyez sur entree pour revenir au menu...........";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
            case 7:
                interactionDonneeMenu7(donnee,menuActu);
            case 8:
                interactionDonneeMenu8(donnee,menuActu);
                break;
            case 11:
                interactionDonneeMenu11(donnee,menuActu);
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
                setEstOptiChemin(false);
                break;
            case '6':
                menuActu=7;
                setEstOptiChemin(true);
                break;
            case '7':
                menuActu=11;
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



void General::interactionDonneeMenu4(const std::string& donnee, int& menuActu,const bool& estDijkstra){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':
                menuActu=6;
                break;
            case '1':{
                int s = arcs.entreePoint("Nom ou numero du point initial: ");
                arcs.plusCourtChemin(estDijkstra,getEstOptiChemin(),getOptiTrajets(),s);
                finProgrammeActu();
                break;
            }

            case '2':{
                int s0 = arcs.entreePoint("Nom ou numero du point initial: ");
                int sF = arcs.entreePoint("Nom ou numero du point final: ");
                arcs.plusCourtChemin(estDijkstra,getEstOptiChemin(),getOptiTrajets(),s0,sF);
                finProgrammeActu();
                break;
            }

        }
    }

}

void General::interactionDonneeMenu6(const std::string& donnee, int& menuActu){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':{
                if(getEstOptiChemin())
                    menuActu=7;
                else
                    menuActu=1;
                break;
            }

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

void General::interactionDonneeMenu11(const std::string& donnee,int& menuActu) {

    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':
                menuActu=7;
                break;
            case '1':
                menuActu=8;
                break;
            case '2':
                menuActu=9;
                break;

        }
    }


}
void General::interactionDonneeMenu7(const std::string& donnee, int& menuActu){
    if(donnee.size()==1){
        switch(donnee[0]){
            case '0':
                menuActu=1;
                break;
            case '1':
                modifierOptiTrajets();
                break;
            case '2':
                menuActu=6;
                break;

        }
    }

}

void General::interactionDonneeMenu8(const std::string& donnee,int& menuActu) {





}


/// Affichage Menu ///

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
        case 7:
            menu7();
            break;
        case 8://menu changement capacite Admin
            menu8();
            break;
        case 9://menu calcul de flot
            menu9();
            break;
        case 11://Menu affcihage capacité
            menu11();
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
    std::cout << "6 : Optimisation des vacances -> Plus courts chemin avec selection (4.5)" << std::endl;
    std::cout << "7 : Afficher et modifier les capacites avec les flots (4.6)" << std::endl;
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
    std::string phraseOpti;
    if(getEstOptiChemin())
        phraseOpti="       avec optimisation\n";
    std::cout << "0 : Retour en arriere" << std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;

    if(estDijkstra)
        std::cout <<  "            En temps " << std::endl << " ";
    else
        std::cout <<  "      En nombre de trajets" << std::endl;


    std::cout <<  phraseOpti;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl <<"1 : Tous les plus courts chemin en partant d'un point" << std::endl;
    std::cout << "2 : Plus court chemin entre 2 points" << std::endl;
}

void General::menu6(){
    std::string phraseOpti;
    if(getEstOptiChemin())
        phraseOpti="        avec optimisation \n";
    std::cout << "0 : Retour en arriere" << std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout <<  "        Plus court chemin "  << std::endl;
    std::cout << phraseOpti;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl <<"1 : Plus court chemin en temps" << std::endl;
    std::cout << "2 : Plus court chemin en nombre de trajets" << std::endl;
}


void General::menu11() {
    lectureFichierCapacite();

    std::cout << "Type \t || \t Debit " <<std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    for(int i =0; i < arcs.getVecteurCapacite().size(); i ++)
    {
        std::cout << arcs.getVecteurCapacite()[i].first << "\t || \t" << arcs.getVecteurCapacite()[i].second << std::endl;
        std::cout <<"----------------------------------" << std::endl;
    }

    std::cout << " Tapez 1 pour changer les valeurs ou 2 pour les garder :" ;






}

void General::menu8() {//menu utilisateur changement de débit
    int choixType;
    int nouvelleValeur;
    std::vector<std::pair<std::string,int>> &temp = arcs.getVecteurCapacite();

    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout << "Vous avez choisi de changer les valeurs des capacites" <<std::endl;
    std::cout << "Veuillez choisir le type (numero) de la capacite que vous voulez changer" <<std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Parametre \t || \t Type \t || \t Debit " <<std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    for(int i =0; i < arcs.getVecteurCapacite().size(); i ++)
    {
        std::cout << i+1<<"\t || \t" <<  arcs.getVecteurCapacite()[i].first << "\t || \t" << arcs.getVecteurCapacite()[i].second << std::endl;
        std::cout  <<"----------------------------------" << std::endl;
    }
    do{
        std::cout << "Type : " ;
        std::cin >> choixType;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while(choixType-1<0 || choixType-1 > arcs.getVecteurCapacite().size());
    std::cout << "Vous avez decide de changer cette valeur : " << arcs.getVecteurCapacite()[choixType-1].second << " du type : " << arcs.getVecteurCapacite()[choixType-1].first << std::endl;
    std::cout << "Veuillez modifier cette valeur " << std::endl;
    std::cout  << "Ancienne valeur :" << arcs.getVecteurCapacite()[choixType-1].second <<std::endl;
    std::cout << "Nouvelle valeur :" ;
    std::cin >> nouvelleValeur;
    arcs.getVecteurCapacite()[choixType-1].second = nouvelleValeur;
    changementValeurFichierCapacite("capacite");



}

void General::menu9() {

}

void General::menu10() {
    std::cout << " \t Bonjour voici le menu d'interface " <<std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "Affichage de tous les profils " <<std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;
    std::cout << "Utilisateur n° \t || \t Pseudo" << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;


    for (int i = 0; i < baseUtilisateur.getVecteurProfil().size(); ++i) {
        std::cout << i+1 << "\t || \t " << baseUtilisateur.getVecteurProfil()[i].getProfil().first << std::endl;
        std::cout << "----------------------------------" << std::endl;


    }
    std::cout << "Veuillez choisir le profil (numero)" <<std::endl;
    system("cls");
}





/// Fonction Fichier concernant la capacités ///

void General::changementValeurFichierCapacite(const std::string nomFichier) {

    //ouverture en mode écriture afin d'éffacer le contenu
    // on réecrit le vecteur dans le fichier

    std::ofstream fichier ("../"+nomFichier+".txt");
    if(!fichier)
        throw std::runtime_error( "Impossible d'ouvrir en ecriture ");

    fichier << arcs.getVecteurCapacite().size() <<std::endl;
  for(const auto& elem : arcs.getVecteurCapacite())
      fichier << elem.first << " " << elem.second << std::endl;
}

void General::lectureFichierCapacite() {
    std::ifstream fichier ("../capacite.txt");
    int taille;

    if(!fichier)
        throw std::runtime_error( "Impossible d'ouvrir en lecture ");

    fichier >> taille;

    for(int i = 0 ; i< taille ; i++)
    {
        std::pair <std::string, int> temp;
        fichier >> temp.first;
        fichier >> temp.second;
        arcs.setVecteurCapacite(temp);
    }

}
void General::menu7(){
    std::cout << "0 : Retour en arriere" << std::endl;
    std::cout << std::endl <<"----------------------------------" << std::endl;
    std::cout <<  " Plus court chemin optimisé (4.5)   " << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl <<"1 : Afficher/Modifier l'interet des trajets" << std::endl;
    std::cout << "2 : Faire les plus courts chemins les parametres du \"1\"" << std::endl;

}



void General::afficherOptiTrajets(){


    std::cout << " --------------------------------------------------------------------------------------"<<std::endl;
    std::cout << " Nom du trajet            A eviter?"<<std::endl;
    std::cout << " --------------------------------------------------------------------------------------"<<std::endl;
    for(const auto& elem : m_optiTrajets){
        Trajet temp=Trajet(elem.first);


        std::cout << " "
                  <<temp.returnNomType()
                  <<"         ";

        if(elem.second)
            std::cout << "Oui";
        else
            std::cout << "Non";
        std::cout << std::endl;
    }
    std::cout << std::endl<<std::endl;

}

void General::modifierOptiTrajets(){

    std::string donnee;

    std::string parametre;

    do{
        std::system("cls || clear");
        afficherOptiTrajets();
        std::cout << "Appuyez sur \"s\" pour revenir au menu " << std::endl;
        std::cout <<"Appuyez sur \"m\" pour modifier les valeurs une par une" << std::endl;
        std::cout <<"Appuyez sur \"r\" pour n\'eviter que les remontees et les navettes" << std::endl;
        std::cout <<"Appuyez sur \"p\" pour n\'eviter que les pistes" << std::endl<<std::endl;

        std::cout << "Votre choix: ";
        std::cin >> parametre;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }while(parametre!="s" && parametre!="m"&&parametre!="p" && parametre!="r");

    if(parametre!="s"){
        switch(parametre[0]){
            case 'm':
            {
                for(auto& elem : m_optiTrajets){
                    Trajet temp= Trajet(elem.first);
                    do{
                        std::system("cls || clear");
                        std::cout <<"Souhaitez vous eviter: "<< temp.returnNomType() << "?" << std::endl << std::endl;
                        std::cout <<"Ecrire \"o\" pour \"oui\" ou  \"n\" pour \"non\": ";
                        std::cin >> parametre;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    }while(parametre!="o" && parametre!="n");

                    if(parametre=="o")
                        elem.second=true;
                    else
                        elem.second=false;
                }

            }
                break;
            case 'p':
                for(auto& elem : m_optiTrajets){
                    Trajet temp= Trajet(elem.first);
                    if(temp.getGType()=='R'|| temp.getGType()=='B')
                        elem.second=false;
                    else
                        elem.second=true;
                }

                break;
            case 'r':
                for(auto& elem : m_optiTrajets){
                    Trajet temp= Trajet(elem.first);
                    if(temp.getGType()=='R' || temp.getGType()=='B')
                        elem.second=true;
                    else
                        elem.second=false;
                }

                break;
        }
        std::system("cls || clear");
        std::cout << "Toutes vos modifications ont ete pris en compte!" << std::endl;
        finProgrammeActu();
    }






}

bool General::getEstOptiChemin() const {
    return m_estOptiChemin;
}

std::vector<std::pair<std::string,bool>> General::getOptiTrajets() const {
    return m_optiTrajets;
}

void General::setEstOptiChemin(const bool& _valeur) {
    m_estOptiChemin=_valeur;
}
