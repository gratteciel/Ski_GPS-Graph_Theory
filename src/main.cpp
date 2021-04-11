#include "Headers/General.h"

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
