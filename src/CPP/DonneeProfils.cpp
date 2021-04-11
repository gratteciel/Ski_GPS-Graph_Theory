//
// Created by ultra gamer on 09/04/2021.
//

#include "../Headers/DonneeProfils.h"



DonneeProfils::DonneeProfils() {
    lectureFichierProfil();
}

DonneeProfils::~DonneeProfils() {
    for(auto elem : m_vecteurProfil)
        delete elem;
}

///Méthode permettant de lire le fichier profil
void DonneeProfils::lectureFichierProfil() {
    std::ifstream fichier ("../profil.txt");

    if(!fichier)
        throw std::runtime_error( "Impossible d'ouvrir en lecture ");

    while(!fichier.eof())
    {
        int nbTrucsEviter=0;
        std::string pseudo;
        std::vector<std::string> prefT;
        bool estAdmin;
        fichier >>pseudo;
        fichier >> estAdmin;
        fichier >> nbTrucsEviter;

        for(int i=0; i<nbTrucsEviter ; i++){
            std::string donnee;
            fichier >> donnee;
            prefT.push_back(donnee);
        }


        m_vecteurProfil.push_back(new Profil(pseudo,estAdmin,prefT));

    }

}


///Méthode retournant vrai si le pseudo en parametre existe, retourne faux sinon
bool DonneeProfils::pseudoExiste(const std::string& pseudoInput){
    for(auto& elem : m_vecteurProfil){
        if(pseudoLowerCase(pseudoInput)==pseudoLowerCase(elem->getProfil().first))
            return true;
    }
    return false;
}


std::string DonneeProfils::pseudoLowerCase(const std::string& donnee){
    std::string pseudo;
    for(const auto& elem : donnee)
    {
        pseudo+= tolower(elem);
    }
    return pseudo;
}

Profil* DonneeProfils::ajoutProfil(const std::string& pseudo) {

    std::ofstream fichier ("../profil.txt");

    if(!fichier)
        throw std::runtime_error( "Impossible d'ouvrir profil.txt  en ecriture");

    for( auto& elem: m_vecteurProfil)
    {
        fichier << elem->getProfil().first;
        fichier << " ";
        fichier << elem->getProfil().second;
        fichier << " ";
        fichier << elem->getPrefTrajets().size();
        for(const auto& elem2: elem->getPrefTrajets()){
            fichier << " ";
            fichier << elem2;
        }

        fichier << std::endl;
    }
    //ajout d'un nouvel utilisateur qui n'est pas admin
    fichier << pseudo << " " << 0  << " " << 6 <<" TPH TC TSD TS TK BUS" ;

    m_vecteurProfil.push_back( new Profil(pseudo,false));
    return m_vecteurProfil.back();

}

void DonneeProfils::reecrireFichierProfil(){
    std::ofstream fichier ("../profil.txt");
    for( auto& elem: m_vecteurProfil)
    {
        fichier << elem->getProfil().first;
        fichier << " ";
        fichier << elem->getProfil().second;
        fichier << " ";
        fichier << elem->getPrefTrajets().size();
        for(const auto& elem2: elem->getPrefTrajets()){
            fichier << " ";
            fichier << elem2;
        }

        fichier << std::endl;
    }
}

Profil* DonneeProfils::getProfil(const std::string& pseudo) {

    for(auto&  elem : m_vecteurProfil)
    {
        if(pseudoLowerCase(pseudo)==pseudoLowerCase(elem->getProfil().first))
            return elem;
    }
    return m_vecteurProfil.back();

}

std::vector<Profil*> DonneeProfils::getVecteurProfil() const {
    return m_vecteurProfil;
}

