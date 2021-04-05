#include "Headers/General.h"

int main() {
    try{
        General projet("../data_arcs.txt");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }




    return 0;
}
