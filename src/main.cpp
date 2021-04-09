#include "Headers/General.h"

int main() {
    try{

        int x = 8;
        int y =10;
        Domaine test;
        test.flotMaximal(x,y);
        General projet("../data_arcs.txt");
        projet.boucle();



    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }

    return 0;
}
