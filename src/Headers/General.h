//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_GENERAL_H
#define SKIPISCINE_GENERAL_H
#include "Domaine.h"



class General {
private:
    Domaine arcs;

public:
    //Constructeur et destructeur
    General(const std::string &nomfichier);
    ~General() = default;
    //Méthodes
    void lecturefichier(const std::string &nomfichier,t_chargeFichier& fCharge);
    void interactionDonnee(const std::string& donnee, int& menuActu);
    void boucle();
    void menu1();
    void afficheMenu(const int &menuActu);
    //Getters & Setters

    void interactionDonneeMenu1(const std::string &donnee, int &menuActu);

    void menu2();

    void menu3();

    void interactionDonneeMenu2(const std::string &donnee, int &menuActu);

    void interactionDonneeMenu3(const std::string &donnee, int &menuActu);

    void menu4(const bool& estDijkstra);

    void interactionDonneeMenu4(const std::string &donnee, int &menuActu,const bool& estDijkstra);



    void interactionDonneeMenu6(const std::string &donnee, int &menuActu);

    void menu6();

    void lectureFichierCapacite ();
    void changementValeurFichierCapacite(const std::string nomFichier);
    void menu7();//menu concernant les flots avec lecture du fichier et écriture
    void interactionDonneeMenu7(const std::string& donnee,int& menuActu);
    void interactionDonneeMenu8(const std::string& donnee,int& menuActu);
    void interactionDonneeMenu9(const std::string& donnee,int& menuActu);


    void menu8();
    void menu9();

    void finProgrammeActu();
};


#endif //SKIPISCINE_GENERAL_H
