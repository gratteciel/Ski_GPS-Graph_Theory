//
// Created by ultra gamer on 09/04/2021.
//

#include "../Headers/Profil.h"

Profil::Profil() {

}
Profil::Profil(std::string _pseudo, bool _estAdmin, const std::vector<std::string>& _prefT)
      :m_prefTrajets(_prefT)
{
    m_profil.first=_pseudo;
    m_profil.second = _estAdmin;
}

Profil::Profil(std::string _pseudo, bool _estAdmin)

{
    m_profil.first=_pseudo;
    m_profil.second = _estAdmin;
    m_prefTrajets.push_back("TPH");
    m_prefTrajets.push_back("TC");
    m_prefTrajets.push_back("TSD");
    m_prefTrajets.push_back("TS");
    m_prefTrajets.push_back("TK");
    m_prefTrajets.push_back("BUS");

}

///Méthodde permettant de modifier les trajets préférés de l'utilisateur
void Profil::prefTrajetsModification(const std::vector<std::pair<std::string,bool>>& _optiTrajets){
    m_prefTrajets.clear();

    for(auto& elem : _optiTrajets){
        if(elem.second)
            m_prefTrajets.push_back(elem.first);
    }

}

void Profil::setParam(const std::pair<std::string,bool>& _pro){
    m_profil.first=_pro.first;
    m_profil.second=_pro.second;
}
std::pair<std::string,bool> Profil::getProfil() const {
    return m_profil;
}

std::vector<std::string> Profil::getPrefTrajets() const {
    return m_prefTrajets;
}
