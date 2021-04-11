//
// Created by ultra gamer on 09/04/2021.
//

#ifndef SKIPISCINE_DONNEEPROFILS_H
#define SKIPISCINE_DONNEEPROFILS_H
#include "bibli.h"
#include "Profil.h"

class DonneeProfils {
private:
    std::vector<Profil*> m_vecteurProfil;

public:
    DonneeProfils();
    ~DonneeProfils();
    void lectureFichierProfil();
    Profil* ajoutProfil(const std::string& pseudo);

    std::vector<Profil*> getVecteurProfil() const;

    bool pseudoExiste(const std::string& pseudoInput);

    std::string pseudoLowerCase(const std::string &donnee);

    Profil *getProfil(const std::string &pseudo);

    void reecrireFichierProfil();
};


#endif //SKIPISCINE_DONNEEPROFILS_H
