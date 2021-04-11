cmake_minimum_required(VERSION 3.17)
project(skiPiscine)

set(CMAKE_CXX_STANDARD 14)


add_executable(skiPiscine src/main.cpp src/CPP/Domaine.cpp src/Headers/Domaine.h src/CPP/Sommet.cpp src/Headers/Sommet.h src/CPP/General.cpp src/Headers/General.h src/CPP/Trajet.cpp src/Headers/Trajet.h src/CPP/AbstractIdentite.cpp src/Headers/AbstractIdentite.h src/Headers/bibli.h src/CPP/Profil.cpp src/Headers/Profil.h src/CPP/DonneeProfils.cpp src/Headers/DonneeProfils.h src/CPP/Fonction.cpp src/Headers/Fonction.h)


