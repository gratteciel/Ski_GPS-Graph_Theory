//
// Created by mathis on 05/04/2021.
//


#include "../Headers/Domaine.h"

//Constructeur & destructeur
Domaine::Domaine() {
    m_matriceDuree['B'];
    m_matriceDuree['R'];
    m_matriceDuree['D'];


}

Domaine::~Domaine(){
    for(auto s : m_sommets)
        delete s.second;

    for (auto t : m_trajets)
        delete t.second;
}

//Méthodes

void Domaine::initialisation(const t_chargeFichier& fCharge){
    creationSommets(fCharge.sommets);
    creationTrajets(fCharge.trajets);
}


void Domaine::creationSommets(const std::vector<t_chargeSommets>& _som){
    for(const auto s: _som)
        m_sommets[s.num] = new Sommet(s.num,s.nom,s.altitude);
}


void Domaine::creationTrajets(const std::vector<t_chargeTrajet>& _tra){
    for(const auto t: _tra){
        m_trajets[t.num] = new Trajet(t.num,t.nom,t.type,m_sommets[t.depart],m_sommets[t.arrivee],m_matriceDuree);

        m_sommets[t.depart]->setAdjactent(m_trajets[t.num]);

    }
}

bool Domaine::estNombre(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}

void Domaine::afficheTrajets(const char& type, std::string trajetChoisie){
    if(type=='T'){

        bool existe=true;
        if(estNombre(trajetChoisie)){
            if(m_trajets.find(std::stoi(trajetChoisie))!=m_trajets.end())
                m_trajets[std::stoi(trajetChoisie)]->affichage();
            else
                existe=false;
        }
        else{

            int i=0;
            for(const auto& t : m_trajets){
                if(t.second->getNom()==trajetChoisie){
                    t.second->affichage();
                    break;
                }

                i++;
            }
            if(i==m_trajets.size())
                existe=false;

        }

      if(!existe)
            std::cout << "Ce trajet n'existe pas!" <<std::endl;
    }
    else if(type=='N'){
        for(const auto t : m_trajets)
            t.second->affichage();
    }
    else
        for(const auto t : m_trajets){
            if(t.second->getGType() == type)
                t.second->affichage();
        }

    std::cout << std::endl;
}


void Domaine::afficheSommets(const std::string& sommetChoisie){
    if(sommetChoisie=="n")
        for(const auto s : m_sommets)
            s.second->affichage();
    else{
        bool existe =true;
        if(estNombre(sommetChoisie)){
            if(m_sommets.find(std::stoi(sommetChoisie))!=m_sommets.end())
                m_sommets[std::stoi(sommetChoisie)]->affichageComplexe(m_trajets);
            else
                existe =false;
        }else{
            int i=0;
            for(const auto& t : m_sommets){
                if(t.second->getNom()==sommetChoisie){
                    t.second->affichage();
                    break;

                }
                i++;
            }
            if(i==m_sommets.size())
                existe=false;
        }
        if(!existe)
            std::cout << "Ce point n'existe pas!" <<std::endl;
    }
    std::cout << std::endl;

}

void Domaine::afficheChangementDuree() {
    std::string choix;
    std::cout << "Voici la liste des temps :" << std::endl;
    std::cout << "Tous les temps sont en secondes" << std::endl;
    //affichage de tous les types

    char categorie;
    float dureeChangement = 0;
    float nouvelleDuree = 0;
    std::cout << "Voici les categories " <<std::endl;
    for (const auto &elem : getMatriceDuree()) {
        std::cout << elem.first << std::endl;
    }
    std::cout << "Veuillez choisir la categorie : ";
    std::cin >> categorie;
    while (categorie != 'R' && categorie != 'B' && categorie != 'D') {
        std::cout << "Mauvaise saisie " << std::endl;
        std::cout << "Veuillez choisir la categorie : ";
        std::cin >> categorie;
    }
    auto it = getMatriceDuree().find(categorie);

        std::cout << "Dans la categorie : " << it->first << std::endl;

    std::string parametre;
    int i=0;



    switch (it->first) {
        /*
        case 'R' :
            for (const auto &elem1 : it->second)
            {
                std::map<std::string,std::vector<int>> temp;
                std::vector<int> temp2;
                std::cout <<" Parametre : "<< i << elem1.first << " avec comme duree de base : " << elem1.second[0] << " et duree pour le denivele :" << elem1.second[1] << std::endl;
                temp2.push_back(elem1.second[0]);
                temp2.push_back(elem1.second[1]);
                temp[elem1.first] = temp2;
                mapAssociation [i] = temp;
                i++;
            }
            std::cout << "Choissisez le parametre : " ;
            std::cin >> parametre;
            while (i > it->second.size()){
                std::cout << "Mauvaise saisie !" << std::endl;
                std::cout << "Choissisez le parametre : " ;
                std::cin >> parametre;
            }
            std::cout << "Vous avez choisi :" << std::endl;
            std::cout  << "Le parametre " << it2->first << " de la categorie " << it->first;
            for (auto& elem : it2->second) {
                std::cout << "Quelle duree voulez vous changer : duree 1 : " << elem.second[0] << "  duree 2 : " << elem.second[1] << std::endl;
                std::cout << "Tapez 1 ou 2 pour choisir la duree: ";
                std::cin >> dureeChangement;
                while (dureeChangement != 1 && dureeChangement != 2) {
                    std::cout << "Mauvaise saisie !" << std::endl;
                    std::cout << "Tapez 1 ou 2 pour choisir la duree: ";
                    std::cin >> dureeChangement;
                }
                std::cout << "Vous avez choisi de changer cette valeur" << elem.second[dureeChangement - 1]
                          << " veuillez mettre la nouvelle valeur : ";
                std::cin >> nouvelleDuree;
                while (nouvelleDuree < 0) {
                    std::cout << "Veuillez mettre un temps positif svp! " << std::endl;
                    std::cout << "Veuillez choisir la nouvelle duree pour ce parametre : ";
                    std::cin >> nouvelleDuree;
                }
                elem.second[dureeChangement - 1] = nouvelleDuree;
            }
            break;
        */
        case 'D':{
            std::vector<std::string> typeD;
            for (const auto &elem1 : it->second)
            {
                typeD.push_back(elem1.first);
                std::cout << i << " parametre : " << elem1.first << " durée pour le 100m: " << (int)elem1.second[0]/60 << "min" << std::endl;
                i++;
            }
            bool fin=true;
            int paramChoisi=0;
            do{
                fin=true;
                int param = entrerUnNombrePositif("Choississez le parametre: ");

                if(param<0 || param>=it->second.size())
                    fin=false;

            }while(!fin);

            std::cout << "Vous avez choisi :" << std::endl;
            std::cout  << "de modifier la duree des pistes " << typeD[paramChoisi] << std::endl;

            std::cout << "Ancienne valeur :" << (int)it->second[typeD[paramChoisi]][0]/60 <<" minutes" << std::endl;



            int param = entrerUnNombrePositif("Nouvelle valeur: ");

            m_matriceDuree['D'][typeD[paramChoisi]][0] = param*60;
            std::cout << m_matriceDuree['D'][typeD[paramChoisi]][0] << std::endl;
            break;
        }

        /*
        case 'B':
            for (const auto &elem1 : it->second)
            {
                std::map<std::string,std::vector<int>> temp;
                std::vector<int> temp2;
                std::cout <<" Parametre : " << i  << " : "<< elem1.first << " duree pour le denivele :" << elem1.second[0] <<std::endl;
                temp2.push_back(elem1.second[0]);
                temp[elem1.first] = temp2;
                mapAssociation [i] = temp;
                i++;
            }
            std::cout << "Choissisez le parametre : " ;
            std::cin >> parametre;
            while (i > it->second.size()){
                std::cout << "Mauvaise saisie !" << std::endl;
                std::cout << "Choissisez le parametre : " ;
                std::cin >> parametre;
            }
            std::cout << "Vous avez choisi :";
            std::cout  << " le parametre " << parametre << " de la categorie " << it->first << std::endl;

            for (auto& elem : it2->second) {
                std::cout << " Vous allez changer cette duree : " << elem.second[0] << std::endl;
                std::cout << "Vous avez choisi de changer cette valeur : " << elem.second[0] << " veuillez mettre la nouvelle valeur : ";
                std::cin >> nouvelleDuree;
                while (nouvelleDuree < 0) {
                    std::cout << "Veuillez mettre un temps positif svp! " << std::endl;
                    std::cout << "Veuillez choisir la nouvelle duree pour ce parametre : ";
                    std::cin >> nouvelleDuree;
                }
                elem.second[0] = nouvelleDuree;
            }
            break;

        default:
            std::cout << "Probleme dans la selection des durees" <<std::endl;
        */
    }

}

int Domaine::entrerUnNombrePositif(const std::string& phrase){
    std::string parametre;
    do{
        std::cout << phrase;
        std::cin >> parametre;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while(!estNombre(parametre));
    return std::stoi(parametre);
}

std::map<int,int> Domaine::dijkstra(const int& sInit,std::map<int,int>& poids){
    std::map<int,int> pred;
    std::map<int,bool> marque;

    //initialisation des distances à "l'infini" (valeur maximum d'un INT)
    for(const auto& elem : m_sommets)
        poids[elem.first]=INT_MAX;

    //La distance de sInit à sInit est de 0
    poids[sInit]=0;

    //initialisation des marquages à false (non marqués)
    for(const auto& elem : m_sommets)
        marque[elem.first]=false;



    //Initialisation de la queue
    //parametre 1 : numéro du sommet
    //parametre 2 : duree du sommet par rapport à sInit
    //Comparaison selon le classe Comparaison (selon le parametre 2)
    std::priority_queue<std::pair<int,int> ,std::vector<std::pair<int,int>> ,comparaisonDijkstra> queue;
    queue.push(std::make_pair(sInit,0));

    //initialisation des preds, de base ils sont tous à -1
    for(const auto& elem : m_sommets)
        pred[elem.first]=-1;


    //Tant qu'il reste des sommets dans la queue (veut aussi dire qu'il reste des sommets non marqués)
    while(!queue.empty()){


        int minSom=queue.top().first; //Prend le numéro du sommet avec la plus petite distance de sInit qui est dans la queue
        int distMinSom=queue.top().second; //Prend la distance du sommet jusqu'au sommet sInit

        queue.pop(); //On supprime de la queue le sommet avec la plus petite distance de sInit (on va ensuite le marqué)

        //On marque le sommet avec la plus petite distance depuis le sommet initial non marqué dans la queue
        marque[minSom]=true;

        for(const auto& a : m_sommets[minSom]->getAdjacents()){
            if(!marque[a->getSommets().second->getNum()]){ //Si le sommet adjacent n'est pas marqué

                //Si la distance du sommet actuel avec la plus petite distance de sInit + la distance entre ce sommet et son adjacent
                //est inférieur à la distance de l'adjacent à sInit
                //Alors la distance de l'adjacent à sInit devient "la distance du sommet actuel avec la plus petite distance de sInit + la distance entre ce sommet et son adjacent"
                if(distMinSom+a->getDuree() < poids[a->getSommets().second->getNum()]){
                    poids[a->getSommets().second->getNum()]=distMinSom+a->getDuree();
                    pred[a->getSommets().second->getNum()]=minSom; //Le pred de a est le sommet "minSom"
                    queue.push(std::make_pair(a->getSommets().second->getNum(),poids[a->getSommets().second->getNum()]));//On ajoute a à la priority_queue
                }
            }

        }



    }

    return pred;
}


//Getters & Setters
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

t_mapDuree& Domaine::getMatriceDuree()
{
    return m_matriceDuree;
}


