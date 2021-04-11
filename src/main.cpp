#include "Headers/General.h"

/*
 * Source pour les couleurs : https://stackoverflow.com/questions/20608058/c-colour-console-text
 */

int main() {
    try{
        srand(time(NULL)); //Pour trouver l'horaire aleatoirement
        General projet("../data_arcs.txt");
        projet.connection();
        projet.boucle();


    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }

    return 0;
}
