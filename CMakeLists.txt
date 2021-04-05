cmake_minimum_required(VERSION 3.17)
project(skiPiscine)

set(CMAKE_CXX_STANDARD 14)

add_executable(skiPiscine src/main.cpp src/CPP/Domaine.cpp src/Headers/Domaine.h src/CPP/Sommet.cpp src/Headers/Sommet.h src/CPP/General.cpp src/Headers/General.h)