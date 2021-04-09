//
// Created by ultra gamer on 09/04/2021.
//

#include "../Headers/Profil.h"

Profil::Profil() {

}
Profil::Profil(std::string _pseudo, bool _estAdmin)

{
    m_profil.first=_pseudo;
    m_profil.second = _estAdmin;


}

std::pair<std::string,bool> Profil::getProfil() const {
    return m_profil;
}