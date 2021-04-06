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

        int point = entreePoint("Nom ou numero du point: ");
        m_sommets[point]->affichageComplexe(m_trajets);
    }
    std::cout << std::endl;

}

int Domaine::entreePoint(const std::string& phrase){
    int s0Int=-2;
    std::string s0;
    do{
        if(s0Int==-1)
            std::cout << "Ce point n'existe pas!" <<std::endl;
        std::cout << phrase;

        std::cin >> s0;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        s0Int = returnPointId(s0);
    }while(s0Int==-1);
    return s0Int;
}

int Domaine::returnPointId(const std::string& entree){

    if(estNombre(entree)){
        if(m_sommets.find(std::stoi(entree))!=m_sommets.end())
            return std::stoi(entree);

    }else{

        for(const auto& t : m_sommets){
            if(t.second->getNom()==entree){
                return t.second->getNum();
            }

        }

    }
    return -1;
}

void Domaine::plusCourtChemin(int s0, int sF){

    std::map<int,int> poids;

    std::map<int,int> pred=dijkstra(s0,poids);
    if(sF!=-5)
        affichePlusCourtChemin(s0,sF,pred,poids[sF]);

    else{
        std::cout << std::endl;
        std::cout << "---------------------------------------------------------------------------------------"<<std::endl;
        std::cout << " Point |       Chemin (liste de trajets)"<<std::endl;
        std::cout << " final |       de forme \"nomTrajet\" (allant du \"sommet intial\" au  \"sommet final\" )"<<std::endl;
        std::cout << "---------------------------------------------------------------------------------------"<<std::endl;
        for(const auto& e : m_sommets){
            if(e.first!=s0)
                affichePlusCourtChemin(s0,e.first,pred,poids[e.first],false);
        }
    }
}

std::string Domaine::convertSecondeHeuresMinS(const int& seconde){
    int minutes = seconde / 60;
    int heure = minutes / 60;

    if(heure!=0)
        return std::to_string(int(heure)) + "h " + std::to_string(int(minutes%60))
         +  "m " + std::to_string(int(seconde%60)) +"s.";
    else{
        if(minutes!=0){
            return std::to_string(int(minutes%60))
                   +  "m " + std::to_string(int(seconde%60)) +"s.";
        }
        else
            return std::to_string(int(seconde%60)) +"s.";

    }
}

void Domaine::affichePlusCourtChemin(const int& s0,const int& sF, const std::map<int,int>& pred,const int& poids,const bool& complexe){
    std::queue<int> listePoints;

    getPlusCourtCheminRecursif(sF,pred,s0,listePoints);
    listePoints.push(sF);
    if(complexe)
        std::cout << std::endl << "Trajets a parcourir dans l'ordre entre les points " + m_sommets[s0]->afficheSimple() + " et " + m_sommets[sF]->afficheSimple()  + ": " <<std::endl<<std::endl << "   ";
    else{
        std::cout << "  " << sF;
        if(sF/10<1)
            std::cout << " ";
        std::cout << "   |  ";
    }



    while(listePoints.size()!=1){
        int actu = listePoints.front();
        listePoints.pop();
        for(const auto& elem: m_sommets[actu]->getAdjacents()){
            if(elem->getSommets().second->getNum()==listePoints.front()){
                std::cout << elem->getNom() << " ("<<  actu << "-" <<listePoints.front() << ")";
                if(listePoints.size()!=1)
                    std::cout << " -> ";
                break;
            }
        }

    }
    if(complexe){
        std::cout <<std::endl;
        std::cout << std::endl<<"   duree= "  << convertSecondeHeuresMinS(poids) << std::endl<<std::endl;
    }
    else{
        std::cout << std::endl<<"       |  duree= "  << convertSecondeHeuresMinS(poids) << std::endl;
        std::cout << "---------------------------------------------------------------------------------------"<<std::endl;
    }

}

///Sous-programme permmetant d'afficher récursivement les sommets prédécessants pour aller du sommet initial au sommet i
void Domaine::getPlusCourtCheminRecursif(int i, std::map<int,int> pred, const int& initial,std::queue<int>& listePoints){
    if(initial!=i){
        getPlusCourtCheminRecursif(pred[i], pred,initial,listePoints);
        listePoints.push(pred[i]); //On ajoute le point à la file
    }
}

void Domaine::afficheInfo(){
    std::map<char, int> traj;

    traj['D']=0;
    traj['R']=0;
    traj['B']=0;
    for(const auto& t: m_trajets)
        traj[t.second->getGType()]+=1;

    std::cout << "Le domaine skiable possede " << getOrdre() << " points" << std::endl;
    std::cout << "et " << getTaille() << " trajets";
    std::cout << " dont " << traj['D'] << " pistes, " << traj['R']<< " remontees et " << traj['B'] << " navettes" <<std::endl;

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
    //Comparaison selon la struct compaisonDijkstra (selon le parametre 2)
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

