//
// Created by ultra gamer on 09/04/2021.
//

#ifndef SKIPISCINE_PROFIL_H
#define SKIPISCINE_PROFIL_H
#include "bibli.h"

class Profil {
private:
    //1er parametre correspond au pseudo et le deuxieme savoir si oui ou non il est admin
    std::pair<std::string,bool> m_profil;
public:
    Profil();
    Profil(std::string _pseudo, bool _estAdmin);

    //Getters et Setters

    std::pair <std::string,bool> getProfil() const;
};


#endif //SKIPISCINE_PROFIL_H
