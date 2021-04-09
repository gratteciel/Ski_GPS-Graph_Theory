//
// Created by ultra gamer on 09/04/2021.
//

#include "../Headers/DonneePseudo.h"

DonneePseudo::DonneePseudo() {

}

void DonneePseudo::lectureFichierProfil() {
    std::ifstream fichier ("../profil.txt");

    if(!fichier)
        throw std::runtime_error( "Impossible d'ouvrir en lecture ");

    while(!fichier.eof())
    {
        std::string pseudo;
        bool estAdmin;
        fichier >> pseudo;
        fichier >> estAdmin;
        m_vecteurProfil.push_back(Profil(pseudo,estAdmin));

    }

}


void DonneePseudo::ajoutProfil(const std::string& pseudo) {

    std::ofstream fichier ("../profil.txt");

    if(!fichier)
        throw std::runtime_error( "Impossible d'ouvrir en ecriture");

    for(const auto& elem: m_vecteurProfil)
    {
        fichier << elem.getProfil().first;
        fichier << elem.getProfil().second;
        fichier << std::endl;
    }
    //ajout d'un nouvel utilisateur qui n'est pas admin
    fichier << pseudo << 0;

}

std::vector<Profil> DonneePseudo::getVecteurProfil() const {
    return m_vecteurProfil;
}