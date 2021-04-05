//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Domaine.h"

Domaine::Domaine() {

}

void Domaine::setOrdre(int _ordre) {
    m_ordre = _ordre;
}
void Domaine::setTaille(int _taille) {
    m_taille = _taille;
}
int Domaine::getOrdre() const {
    return m_ordre;
}

int Domaine::getTaille() const {
    return m_taille;
}