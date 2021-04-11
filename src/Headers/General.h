//
// Created by mathis on 05/04/2021.
//

#ifndef SKIPISCINE_GENERAL_H
#define SKIPISCINE_GENERAL_H
#include "Domaine.h"
#include "Profil.h"
#include "DonneeProfils.h"



class General {
private:
    Domaine arcs;
    Profil* m_profilActif;

    DonneeProfils m_baseUtilisateur;


    bool m_estOptiChemin;
    std::vector<std::pair<std::string,bool>> m_optiTrajets;
public:
    //Constructeur et destructeur
    General(const std::string &nomfichier);
    ~General() =default;
    //Méthodes
    void lecturefichier(const std::string &nomfichier,t_chargeFichier& fCharge);
    void interactionDonnee(const std::string& donnee, int& menuActu);
    void boucle();
    void menu1();
    void afficheMenu(const int &menuActu);
    void interactionDonneeMenu1(const std::string &donnee, int &menuActu);
    void menu2();
    void menu3();
    void interactionDonneeMenu2(const std::string &donnee, int &menuActu);
    void interactionDonneeMenu3(const std::string &donnee, int &menuActu);
    void menu4(const bool& estDijkstra);
    void interactionDonneeMenu4(const std::string& donnee, int& menuActu,const bool& estDijkstra);
    void interactionDonneeMenu6(const std::string &donnee, int &menuActu);
    void menu6();
    void lectureFichierCapacite ();
    void changementValeurFichierCapacite(const std::string nomFichier);
    void menu11();//menu concernant les flots avec lecture du fichier et écriture
    void interactionDonneeMenu11(const std::string& donnee,int& menuActu);
    void interactionDonneeMenu8(const std::string& donnee,int& menuActu);
    void interactionDonneeMenu9(const std::string& donnee,int& menuActu);
    void menu8();
    void menu9();
    void finProgrammeActu(const std::string& phrase = "Appuyez sur entree pour revenir au menu...........");
    void menu7();
    void interactionDonneeMenu7(const std::string &donnee, int &menuActu);
    bool getEstOptiChemin() const;
    void setEstOptiChemin(const bool& _valeur);
    void afficherOptiTrajets();
    void modifierOptiTrajets();
    std::vector<std::pair<std::string, bool>> getOptiTrajets() const;
    void connection();
    void menuAdminAffichage();
    void interactionDonneeAdmin(const std::string &donnee, int &menuActu);

};


#endif //SKIPISCINE_GENERAL_H
