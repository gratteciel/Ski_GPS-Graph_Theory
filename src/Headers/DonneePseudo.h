//
// Created by ultra gamer on 09/04/2021.
//

#ifndef SKIPISCINE_DONNEEPSEUDO_H
#define SKIPISCINE_DONNEEPSEUDO_H
#include "bibli.h"
#include "Profil.h"

class DonneePseudo {
private:
    std::vector<Profil> m_vecteurProfil;

public:
    DonneePseudo();
    void lectureFichierProfil();
    void ajoutProfil(const std::string& pseudo);

    std::vector<Profil> getVecteurProfil() const;

};


#endif //SKIPISCINE_DONNEEPSEUDO_H
