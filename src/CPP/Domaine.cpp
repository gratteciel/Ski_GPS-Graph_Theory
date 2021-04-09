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

    for(auto& elem: m_sommets){
        elem.second->trierAdjacents();
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

void Domaine::plusCourtChemin(const bool& estDijkstra,const bool& estOpti,const std::vector<std::pair<std::string,bool>>& optiTrajets, int s0, int sF){
    std::map<int,float> poids;
    std::map<int,int> pred;
    std::vector<std::string> typeAEnlever;

    if(estOpti){
        for(const auto& e : optiTrajets){
            if(e.second)
                typeAEnlever.push_back(e.first);
        }
    }


    if(estDijkstra)
        pred=dijkstraOpti(s0,poids,typeAEnlever);
    else{
        pred=parcoursBFSOpti(s0,typeAEnlever);
        for(const auto& elem : m_sommets)
            poids[elem.first]=-5;
    }

    if(sF!=-5)
        affichePlusCourtChemin(s0,sF,pred,poids[sF],estOpti,optiTrajets);
    else{
        std::cout << std::endl;
        std::cout << "---------------------------------------------------------------------------------------"<<std::endl;
        std::cout << " Point |  Chemin (liste de trajets)"<<std::endl;
        std::cout << " final |  de forme \"nomTrajet\" (\"point intial\"-\"point final\"|\"type\" )"<<std::endl;
        std::cout << "---------------------------------------------------------------------------------------"<<std::endl;
        for(const auto& e : m_sommets){
            if(e.first!=s0)
                affichePlusCourtChemin(s0,e.first,pred,poids[e.first],estOpti,optiTrajets,false);
        }
    }
}

std::string Domaine::convertSecondeHeuresMinS(const float& seconde){

    float minutes = seconde / 60;
    float heure = minutes / 60;

    if(heure!=0)
        return std::to_string(int(heure)) + "h " + std::to_string(int(minutes)%60)
         +  "m " + std::to_string(int(seconde)%60) +"s";
    else{
        if(int(minutes)%60!=0){
            if(int(seconde)%60!=0)
                return std::to_string(int(minutes)%60)
                   +  "m " + std::to_string(int(seconde)%60) +"s";
            else
                return std::to_string(int(minutes)%60)
                       +  "m ";
        }
        else
            return std::to_string(int(seconde)%60) +"s";

    }
}

void Domaine::affichePlusCourtChemin(const int& s0,const int& sF,  std::map<int,int>& pred,const float& poids,const bool& estOpti,const std::vector<std::pair<std::string,bool>>& optiTrajets,const bool& complexe){
    std::vector<int> listeTrajets;
    bool cheminPossible=true;

    getPlusCourtCheminRecursif(pred[sF],pred,s0,listeTrajets,cheminPossible);

    if(!complexe)
    {
        std::cout << "  " << sF;
        if(sF/10<1)
            std::cout << " ";
        std::cout << "   |  ";
    }


    if(cheminPossible){
        if(complexe)
            std::cout << std::endl
                      << "Trajets a parcourir dans l'ordre entre les points " + m_sommets[s0]->afficheSimple() + " et " + m_sommets[sF]->afficheSimple()  + ": " <<std::endl<<std::endl
                      << "   ";


        std::set<std::string> chosesAEviterImpo;
        for(int i=(int)listeTrajets.size()-1; i<listeTrajets.size(); i--){
            //Vérifie si on est pas passé quand meme par un trajet qui est à éviter
            if(estOpti) {
                for(const auto& elem: optiTrajets){

                    if(elem.second && elem.first==m_trajets[listeTrajets[i]]->getType()){//Si on est pas passé sur un trajet a eviter
                        chosesAEviterImpo.insert(m_trajets[listeTrajets[i]]->returnNomType());
                    }
                }
            }


            std::cout << m_trajets[listeTrajets[i]]->getNom()
                      << " ("<<  m_trajets[listeTrajets[i]]->getSommets().first->getNum()
                      << "-" <<m_trajets[listeTrajets[i]]->getSommets().second->getNum()
                      << "|"<<m_trajets[listeTrajets[i]]->getType()
                      << ")";
            if(i!=0)
                std::cout << " -> ";

        }
        if(!chosesAEviterImpo.empty()){ //Si on est passé sur un ou plusieurs trajets a eviter
            std::string phrase;

            int i=0;
            for(const auto& elem : chosesAEviterImpo){
                phrase+=elem;
                if(i!=chosesAEviterImpo.size()-1)
                    phrase+=", ";
                i++;
            }
            if(complexe)
                std::cout << std::endl<<std::endl<<"   Aucun chemin reliant les 2 points ne passant pas par: " << phrase ;
            else
                std::cout << std::endl<<"       |  Aucun chemin reliant les 2 points ne passant pas par: " << phrase ;
        }

        if(poids!=-5){
            if(complexe){
                std::cout <<std::endl;
                std::cout << std::endl<<"   duree: "  << convertSecondeHeuresMinS(poids) << std::endl<<std::endl;
            }
            else
                std::cout << std::endl<<"       |  duree: "  << convertSecondeHeuresMinS(poids) << std::endl;
        }
        else
            std::cout << std::endl;



    }
    else{
        if(complexe)
            std::cout << std::endl;
        std::cout << "Impossible de relier ces 2 points!" << std::endl;
    }
    if(!complexe)
        std::cout << "---------------------------------------------------------------------------------------"<<std::endl;


}

///Sous-programme permmetant d'afficher récursivement les sommets prédécessants pour aller du sommet initial au sommet i
void Domaine::getPlusCourtCheminRecursif(int i, std::map<int,int> pred, const int& initial,std::vector<int>& listeTrajets,bool& cheminPossible){

    if(i==-1)
        cheminPossible=false;

    else
    {
        listeTrajets.push_back(pred[m_trajets[i]->getSommets().second->getNum()]); //On ajoute le trajet à la file
        if(initial!=m_trajets[i]->getSommets().first->getNum()){
            getPlusCourtCheminRecursif(pred[m_trajets[i]->getSommets().first->getNum()], pred,initial,listeTrajets,cheminPossible);

        }
    }
}

void Domaine::afficheInfo(){
    std::map<char, int> traj;

    traj['D']=0;
    traj['R']=0;
    traj['B']=0;
    for(const auto& t: m_trajets)
        traj[t.second->getGType()]+=1;
    std::cout <<"----------------------------------" << std::endl;
    std::cout <<  "    Information sur le domaine   " << std::endl;
    std::cout << "----------------------------------" << std::endl<<std::endl;
    std::cout << "Le domaine skiable possede " << getOrdre() << " points" << std::endl;
    std::cout << "et " << getTaille() << " trajets";
    std::cout << " dont " << traj['D'] << " pistes, " << traj['R']<< " remontees et " << traj['B'] << " navettes" <<std::endl;

}


bool Domaine::changementDuree() {
    std::string choix;
    std::string categorie;
    do{
        std::system("clear || cls");
        std::cout << "Choississez une categorie pour afficher ses valeurs: " << std::endl;
        //affichage de tous les types



        std::cout << "D : Descentes (pistes)" <<std::endl;
        std::cout << "R : Remontee" <<std::endl;
        std::cout << "B : Navette" <<std::endl;
        std::cout << std::endl << "Entrez une des trois lettres: ";
        std::cin >> categorie;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while (categorie != "R" && categorie != "B" && categorie != "D");
    auto it = getMatriceDuree().find(categorie[0]);



    std::string parametre;
    int i=0;

    std::system("clear || cls");





    if(it->first=='D' || it->first=='B'){
        if(!modifDureeBD(categorie))
            return false;

    }


    else if (it->first=='R'){
        std::vector<std::string> typeR;
        std::vector<Trajet> tempTrajets;
        for (const auto &elem1 : it->second) {
            typeR.push_back(elem1.first);
            tempTrajets.push_back(Trajet(elem1.first));
            std::cout <<  i << " : "<< elem1.first << " une duree de base " << (int) elem1.second[0] / 60
                      << "min et une duree sur 100m: " << (int) elem1.second[1] / 60 << "min" << std::endl;
            i++;
        }
        bool fin = true;
        int paramChoisi = 0;




        std::string parametre;
        do{
            std::system("cls || clear");
            std::cout << "--------------------------------------------------------------------------------------"<<std::endl;
            std::cout << "| Parametre  |  Nom de la remontee    -> Temps de base    -> Duree  sur 100m"<<std::endl;

            std::cout << "---------------------------------------------------------------------------------------"<<std::endl;
            i=0;
            for (const auto &elem1 : it->second)
            {

                std::cout <<"|     " << i << "      |  "<< tempTrajets[i].returnNomType() << " -> " << convertSecondeHeuresMinS(elem1.second[1]) << " -> " << convertSecondeHeuresMinS(elem1.second[0]) << " pour 100m" << std::endl;
                i++;
            }

            std::cout << "---------------------------------------------------------------------------------------"<<std::endl<<std::endl;
            fin=true;
            std::cout << "Appuyez sur \"s\" pour revenir au menu ou choississez un parametre pour modifier une valeur: ";
            std::cin >> parametre;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



            if(parametre!="s"){
                if(!estNombre(parametre))
                    fin=false;
                else{
                    if(std::stoi(parametre)<0 || std::stoi(parametre)>=it->second.size())
                        fin=false;
                }

            }
            else
                return false;


        }while(!fin);

        paramChoisi=std::stoi(parametre);


        int param;
        do {
            fin = true;
            std::string phrase2="Vous avez choisi de modifier la duree de: " +  tempTrajets[paramChoisi].returnNomType() +" \n \n"+ "0 : Temps de base = " +convertSecondeHeuresMinS(it->second[typeR[paramChoisi]][1]) + " \n" + "1 : Temps pour 100 metres = " + convertSecondeHeuresMinS(it->second[typeR[paramChoisi]][0]) + "\n" + "Choisissez la valeur que vous voulez modifier: ";



            param = entrerUnNombrePositif(phrase2);

            if(param<0 || param>1)
                fin = false;


        } while (!fin);
        std::string mot;
        if(param==0)
            mot="temps de base";
        else if(param==1)
            mot="temps pour 100 metres";

        std::string phrase = "Vous avez choisi de modifier le " + mot + " de: "+ tempTrajets[paramChoisi].returnNomType() +"\n" + "Ancienne valeur: " + std::to_string((int)it->second[typeR[paramChoisi]][1-param]) + " secondes \n" + "Nouvelle valeur (en secondes): ";


        int nouvelleValeur = entrerUnNombrePositif(phrase);

        m_matriceDuree[categorie[0]][typeR[paramChoisi]][1-param] = nouvelleValeur;
        std::cout << std::endl << "Votre modification a ete pris en compte!" << std::endl;
        std::cout << mot + " de: " << tempTrajets[paramChoisi].returnNomType() <<" : " << convertSecondeHeuresMinS(m_matriceDuree[categorie[0]][typeR[paramChoisi]][1-param])<< std::endl;


    }
    else
        std::cout << "Probleme dans la selection des durees" <<std::endl;

    //Modifie la duree des trajets en fonction de la nouvelle matrice
    for (auto& t: m_trajets)
    {
        t.second->setDuree(t.second->calculDuree(m_matriceDuree));
    }


    return true;

}


bool Domaine::modifDureeBD(const std::string& categorie){
    std::vector<std::string> typeD;
    std::vector<Trajet> tempTrajets;
    std::string mot;

    if(categorie[0]=='D')
        mot="descente";
    else if (categorie[0]=='B')
        mot = "navette";

    int i=0;
    auto it = getMatriceDuree().find(categorie[0]);
    for (const auto &elem1 : it->second)
    {
        typeD.push_back(elem1.first);
        tempTrajets.push_back(Trajet(elem1.first));
        i++;
    }

    bool fin=true;
    int paramChoisi=0;

    std::string parametre;
    do{
        std::system("cls || clear");
        std::cout << "--------------------------------------------------------------------------------------"<<std::endl;
        std::cout << "| Parametre  |  Nom de la "<<mot <<"    -> Duree par default"<<std::endl;

        std::cout << "---------------------------------------------------------------------------------------"<<std::endl;
        i=0;
        for (const auto &elem1 : it->second)
        {
            if(categorie[0]=='B')
                std::cout <<"|     " << i << "      |  "<< elem1.first << "    ->    " << convertSecondeHeuresMinS(elem1.second[0]) << " pour 100m" << std::endl;
            else
                std::cout <<"|     " << i << "      |  "<< tempTrajets[i].returnNomType() << "    ->    " << convertSecondeHeuresMinS(elem1.second[0]) << " pour 100m" << std::endl;
            i++;
        }

        std::cout << "---------------------------------------------------------------------------------------"<<std::endl<<std::endl;
        fin=true;
        std::cout << "Appuyez sur \"s\" pour revenir au menu ou choississez un parametre pour modifier une valeur: ";
        std::cin >> parametre;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



        if(parametre!="s"){
            if(!estNombre(parametre))
                fin=false;
            else{
                if(std::stoi(parametre)<0 || std::stoi(parametre)>=it->second.size())
                    fin=false;
            }

        }
        else
            return false;


    }while(!fin);

    paramChoisi=std::stoi(parametre);


    std::system("clear || cls");
    std::string phrase = "Vous avez choisi de modifier la duree de: " + tempTrajets[paramChoisi].returnNomType() +"\n" + "Ancienne valeur: " + std::to_string((int)it->second[typeD[paramChoisi]][0]) + " secondes \n" + "Nouvelle valeur (en secondes): ";



    int param = entrerUnNombrePositif(phrase);

    m_matriceDuree[categorie[0]][typeD[paramChoisi]][0] = param;
    std::cout << std::endl << "Votre modification a ete pris en compte!" << std::endl;
    if(categorie[0]=='B')
        std::cout << "Duree de " <<  typeD[paramChoisi] <<" : " << convertSecondeHeuresMinS(m_matriceDuree[categorie[0]][typeD[paramChoisi]][0])<< std::endl;
    else
        std::cout << "Duree de " << tempTrajets[paramChoisi].returnNomType() <<" : " << convertSecondeHeuresMinS(m_matriceDuree[categorie[0]][typeD[paramChoisi]][0])<< std::endl;
    return true;
}


int Domaine::entrerUnNombrePositif(const std::string& phrase){
    std::string parametre;
    do{
        std::system("clear || cls");
        std::cout << phrase;
        std::cin >> parametre;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while(!estNombre(parametre));
    return std::stoi(parametre);
}

std::map<int,int> Domaine::dijkstraOpti(const int &sInit, std::map<int, float> &poids,const std::vector<std::string>& typeAEnlever) {
    std::map<int,int> pred;

    std::map<int,char> marque;
    std::map<int,bool> aEnlever;/*----------------*/

    /*----------------*/
    if(!typeAEnlever.empty()){
        for(const auto& elem: m_trajets){
            if(std::find(typeAEnlever.begin(),typeAEnlever.end(),elem.second->getType())!=typeAEnlever.end())
                aEnlever[elem.first]=true;
            else
                aEnlever[elem.first]=false;
        }
    }
    /*----------------*/

    //initialisation des marquages à false (non marqués)
    //initialisation des preds, de base ils sont tous à -1
    for(const auto& elem : m_sommets) {
        pred[elem.first] = -1;
        marque[elem.first] = 'B';
    }
    //inititalisationChemin(pred,marque);

    //initialisation des distances à "l'infini" (valeur maximum d'un FLOAT)
    for(const auto& elem : m_sommets)
        poids[elem.first]=std::numeric_limits<float>::max();;

    //La distance de sInit à sInit est de 0
    poids[sInit]=0;


    //Initialisation de la queue
    //parametre 1 : numéro du sommet
    //parametre 2 : duree du sommet par rapport à sInit
    //parametre 3 : a eviter ou pas
    //Comparaison selon la struct compaisonDijkstra (selon le parametre 2)
    std::priority_queue<std::pair<int,std::pair<float,bool>> ,std::vector<std::pair<int,std::pair<float,bool>>> ,comparaisonDijkstraOpti> queue;
    queue.push(std::make_pair(sInit,std::make_pair(0,false)));


    //Tant qu'il reste des sommets dans la queue (veut aussi dire qu'il reste des sommets non marqués)
    while(!queue.empty()){

        int minSom=queue.top().first; //Prend le numéro du sommet avec la plus petite distance de sInit qui est dans la queue
        float distMinSom=queue.top().second.first; //Prend la distance du sommet jusqu'au sommet sInit
        queue.pop(); //On supprime de la queue le sommet avec la plus petite distance de sInit (on va ensuite le marqué)

        //On marque le sommet avec la plus petite distance depuis le sommet initial non marqué dans la queue
        marque[minSom]='N';


        for(const auto& a : m_sommets[minSom]->getAdjacents()){

                if(marque[a->getSommets().second->getNum()]!='N'){ //Si le sommet adjacent n'est pas marqué
                    bool nePasParcourir=false;

                    if(!typeAEnlever.empty()) {
                        //Si le trajet fait partie des trajets à éviter
                        if (aEnlever[a->getNum()]) {
                            //et que le point adjacent a deja etait marqué
                            //alors on ne parcourt pas -> il existe un trajet moins court MAIS qui n'est pas à éviter
                            if (marque[a->getSommets().second->getNum()] == 'G')
                                nePasParcourir = true;

                            //Mais si l'ancien trajet pour aller à ce point est à éviter aussi
                            //alors on passe quand meme
                            if (aEnlever[pred[a->getSommets().second->getNum()]])
                                nePasParcourir = false;
                        }
                    }

                    if(!nePasParcourir){
                        //Si la distance du sommet actuel avec la plus petite distance de sInit + la distance entre ce sommet et son adjacent
                        //est inférieur à la distance de l'adjacent à sInit

                        //Alors la distance de l'adjacent à sInit devient "la distance du sommet actuel avec la plus petite distance de sInit + la distance entre ce sommet et son adjacent"
                        if(distMinSom+a->getDuree() < poids[a->getSommets().second->getNum()]
                           || (aEnlever[pred[a->getSommets().second->getNum()]] && !aEnlever[a->getNum()]) //Ou le predecesseur est "à enlever" et celui la non
                                ){
                            marque[a->getSommets().second->getNum()]='G';
                            poids[a->getSommets().second->getNum()]=distMinSom+a->getDuree();
                            pred[a->getSommets().second->getNum()]=a->getNum(); //Le pred de a est le trajet entre les 2 points actuels
                            queue.push(std::make_pair(a->getSommets().second->getNum(),std::make_pair(poids[a->getSommets().second->getNum()],aEnlever[a->getNum()])));//On ajoute a à la priority_queue
                        }

                    }

                }


        }
    }


    return pred;
}

///Sous-programme permettant d'effectuer le parcours BFS
///Renvoie le vecteur des prédécesseurs des sommets
std::map<int,int> Domaine::parcoursBFSOpti(const int& _num,const std::vector<std::string>& typeAEnlever){
    //Initialisation des sommets
    std::map<int,int> pred;
    std::map<int,float> ordreDecouverte;
    std::map<int,char> marque;

    //inititalisationChemin(pred,marque);
    for(const auto& elem : m_sommets) {
        pred[elem.first] = -1;
        ordreDecouverte[elem.first] = 0;
        marque[elem.first] = 'B';
    }


    std::map<int,bool> aEnlever;/*----------------*/
    /*----------------*/

    for(const auto& elem: m_trajets){
        if(std::find(typeAEnlever.begin(),typeAEnlever.end(),elem.second->getType())!=typeAEnlever.end())
            aEnlever[elem.first]=true;
        else
            aEnlever[elem.first]=false;
    }

    /*----------------*/

   int decouverte=0;

    //Création de la file vide
    std::priority_queue<std::pair<int,std::pair<float,bool>> ,std::vector<std::pair<int,std::pair<float,bool>>> ,comparaisonDijkstraOpti> queue;


    //enfilerSommetBFS(file,marque,_num);//On enfile s0 (_num : le sommet initial)
    //Création de la file vide

    marque[_num]= 'N';
    queue.push(std::make_pair(_num,std::make_pair(-1,false)));

    while(!queue.empty()){

        int sommetActu= queue.top().first;

        queue.pop();//On défile le prochain sommet de la file
        for(auto a : m_sommets[sommetActu]->getAdjacents()){//Pour tous les sommets adjacents


            if(marque[a->getSommets().second->getNum()]=='B'||marque[a->getSommets().second->getNum()]=='G'){//Si le sommet adjacent n'est pas marqué 'N'


                if(aEnlever[a->getNum()])
                    marque[a->getSommets().second->getNum()]= 'G';
                else
                    marque[a->getSommets().second->getNum()]= 'N';



                pred[a->getSommets().second->getNum()]=a->getNum(); //Le prédecesseur du sommet adjacent devient le trajet allant du sommet actu à ce sommet adjacent
                queue.push(std::make_pair(a->getSommets().second->getNum(),std::make_pair(decouverte,aEnlever[a->getNum()])));
                ordreDecouverte[a->getSommets().second->getNum()]=decouverte;
                decouverte++;
            }
        }

        //s devient exploré (marqué)
        marque[sommetActu]=true;
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
std::vector<std::pair<std::string,int>>& Domaine::getVecteurCapacite(){
    return m_vecteurCapacite;
}

void Domaine::setVecteurCapacite(const std::pair<std::string,int> _pairCapacite)
{

    getVecteurCapacite().push_back(_pairCapacite);
}

