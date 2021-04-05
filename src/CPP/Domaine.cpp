//
// Created by mathis on 05/04/2021.
//

#include "../Headers/Domaine.h"

//Constructeur et destructeur

Domaine::Domaine() {

}

Domaine::~Domaine(){
    for(auto s : m_sommets)
        delete s.second;

    for (auto t : m_trajets)
        delete t.second;
}
