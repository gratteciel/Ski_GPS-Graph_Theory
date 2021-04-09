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
    std::vector<std::string> m_prefTrajets;
public:
    Profil();
    Profil(std::string _pseudo, bool _estAdmin, const std::vector<std::string>& _prefT);
    Profil(std::string _pseudo, bool _estAdmin);
    //Getters et Setters

    std::pair <std::string,bool> getProfil() const;
    std::vector<std::string> getPrefTrajets() const;
    void setParam(const std::pair<std::string,bool>& _pro);


    void prefTrajetsModification(const std::vector<std::pair<std::string, bool>> &_optiTrajets);
};


#endif //SKIPISCINE_PROFIL_H
