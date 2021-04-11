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
    int m_taille; // nombre d'arcs
    t_mapDuree m_matriceDuree;
    float m_horaire;
    std::map<std::string,int> m_vecteurCapacite;


public:
    //Constructeur et destructeur
    Domaine();
    Domaine(const t_mapDuree& m_matriceDuree, const std::map<std::string,int>& m_vecteurCapacite,const float& horaire);
    ~Domaine();

    //Méthodes
    void creationSommets(const std::vector<t_chargeSommets>& _som);
    void initialisation(const t_chargeFichier &fCharge);
    void creationTrajets(const std::vector<t_chargeTrajet> &_tra);
    void afficheTrajets(const char& type='N',std::string sommetChoisie="n");
    void afficheSommets(const std::string& sommetChoisie="n");
    bool estNombre(const std::string &str);
    void plusCourtChemin(const bool& estDijkstra,const bool& estOpti,const std::vector<std::pair<std::string,bool>>& optiTrajets, int s0, int sF=-5, const bool& estGrapheEcart=false);
    void affichePlusCourtChemin(const int& s0,const int& sF,  std::map<int,int>& pred,const float& poids,const bool& estOpti,const std::vector<std::pair<std::string,bool>>& optiTrajets,const bool& complexe=true,const bool& estGrapheEtat=false);
    void getPlusCourtCheminRecursif(int i, std::map<int,int> pred, const int& initial,std::vector<int>& listePoints,bool& cheminPossible);
    std::string convertSecondeHeuresMinS(const float& seconde);
    int returnPointId(const std::string &entree);
    bool changementDuree();
    int entreePoint(const std::string &phrase);
    void afficheInfo();
    void afficherCapaciteFlot(const bool& estAdmin);
    void interactionCapaciteFlot(const bool& estAdmin);
    int entrerUnNombrePositif(const std::string &phrase);
    void reecrireFichierCapacite();
    std::map<int,std::pair<int,bool>> BFSFord(const int& initial,const int& final,std::map<int,int>& sigma);
    bool modifDureeBD(const std::string &categorie);
    std::map<int,int> dijkstraOpti(const int &sInit, std::map<int, float> &poids,const std::vector<std::string>& typeAEnlever = std::vector<std::string>(), const bool& estGrapheEcart=false);
    std::map<int,int> parcoursBFSOpti(const int& _num,const std::vector<std::string>& typeAEnlever= std::vector<std::string>(),const bool& estGrapheEcart=false);
    void modifCapaciteAdmin();
    std::map<int,bool> fordFulkerson(const int& initial,const int& final);
    bool chaineAugmentante(const int& initial,const int& final,std::map<int,std::pair<int,bool>>& pred,std::map<int,int>& sigma);
    void getPlusCourtCheminBFSFord(int i,int ancienI,std::map<int, std::pair<int, bool>>& pred, const int &initial,
                                   std::vector<std::pair<int,bool>>& listeTrajets, bool &cheminPossible);
    void calculFlotMaximal(const int& final,int& flotMax);
    bool afficheGrapheEcart();
    void algosQuatreSix(const int &initial, const int &final);
    void horaire();
    float initialisationHoraire();
    float getHoraire();
    void creationGrapheEcart(const std::map<int, Trajet*>& _trajets,std::map<int,bool>& trajetsParcouru);
    void finProgrammeActu(const std::string &phrase);
    //Getters & Setters
    void ajoutSommet(Sommet* som);
    void setOrdre(int _ordre);
    void setTaille(int _taille);
    int getOrdre() const;
    int getTaille() const;
    t_mapDuree& getMatriceDuree();
    std::map<std::string,int>& getVecteurCapacite();
    void setVecteurCapacite(const std::pair<std::string,int> _vecteurCapacite);
    std::map<int, Sommet *>& getSommets();
    std::map<int, Trajet *>& getTrajets();





    /// Concernant les horaires ///


    void calculFlotMaximal(const int &initial, const int &final);

};


#endif //SKIPISCINE_DOMAINE_H
