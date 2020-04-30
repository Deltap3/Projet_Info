#include "Graphe.h"
#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>

bool Graphe::getOri()const
{
    return m_ori;
}

int Graphe::getNbArete()const
{
    return m_nb_arete;
}

void Graphe::setNbArete(int nb)
{
    m_nb_arete = nb;
}

int Graphe::getNbSommet()const
{
    return m_nb_sommet;
}

void Graphe::setNbSommet(int nb)
{
    m_nb_sommet = nb;
}

std::vector<Sommet*> Graphe::getSommets()const
{
    return m_sommets;
}

std::vector<Arete*> Graphe::getAretes()const
{
    return m_aretes;
}

std::string Graphe::getFileName()const
{
    return m_fileName;
}

void Graphe::creation_svg()
{
    Svgfile svgout;
    affichage_svg(svgout);
}

std::vector<std::string> Graphe::couleur(int* choix)
{
    int j = 0;
    std::vector<std::string> colorSommet(m_sommets.size(),"black");
    float maxi = 0,mini = 1000000, k = 0;
    std::cout<<"        Quel indice voulez-vous afficher ?         "<<std::endl;
    std::cout<<"                Indice de Degre         > 0 <      "<<std::endl;
    std::cout<<"           Indice de Vecteur propre     > 1 <      "<<std::endl;
    std::cout<<"              Indice de Proximite       > 2 <      "<<std::endl;
    std::cout<<"            Indice d'intermedialite     > 3 <      "<<std::endl;
    std::cout<<"> ";
    std::cin>>*choix;
    std::vector<std::string> toutesCouleur = {"saddlebrown","maroon","firebrick","tomato","salmon","peachpuff","lightgreen","mediumseagreen","limegreen","forestgreen"};
    switch(*choix)
    {
    case 0 : //Indice de degré
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getIndiceDegre() > maxi)
                maxi = m_sommets[i]->getIndiceDegre();
            if(m_sommets[i]->getIndiceDegre() < mini)
                mini = m_sommets[i]->getIndiceDegre();
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
                if(m_sommets[i]->getIndiceDegre() > ((j*k) + mini - k*0.0000001))
                    colorSommet[i] = toutesCouleur[j];
        break;
    case 1:  //Indice de vecteur
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getIndiceVect() > maxi)
                maxi = m_sommets[i]->getIndiceVect();
            if(m_sommets[i]->getIndiceVect() < mini)
                mini = m_sommets[i]->getIndiceVect();
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
                if(m_sommets[i]->getIndiceVect() > ((j*k) + mini - k*0.0000001))
                    colorSommet[i] = toutesCouleur[j];
        break;
    case 2:  //Indice de proximité
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getIndiceProxi() > maxi)
                maxi = m_sommets[i]->getIndiceProxi();
            if(m_sommets[i]->getIndiceProxi() < mini)
                mini = m_sommets[i]->getIndiceProxi();
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
                if(m_sommets[i]->getIndiceProxi() > ((j*k) + mini - k*0.0000001))
                    colorSommet[i] = toutesCouleur[j];
        break;
     case 3:  //Indice de intermedialité
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getIndiceInter() > maxi)
                maxi = m_sommets[i]->getIndiceInter();
            if(m_sommets[i]->getIndiceInter() < mini)
                mini = m_sommets[i]->getIndiceInter();
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
                if(m_sommets[i]->getIndiceInter() > ((j*k) + mini - k*0.0000001))
                    colorSommet[i] = toutesCouleur[j];
        break;
    default:
        break;
    }
    return colorSommet;
}

void Graphe::affichage_svg(Svgfile& svgout)
{
    svgout.addGrid();
    int choix = 0;
    std::vector<std::string> colorSommet = couleur(&choix);
    std::vector<std::string> toutesCouleur = {"saddlebrown","maroon","firebrick","tomato","salmon","peachpuff","lightgreen","mediumseagreen","limegreen","forestgreen"};
    for(size_t i = 0; i < toutesCouleur.size();++i)
        svgout.addTriangle(50*i,25,50*i,50,50*(i+1),50,50*(i+1),25,toutesCouleur[i],0,"black");
    svgout.addText(20,20,"Pas Important","black");
    svgout.addText(430,20,"Important","black");
    for(int i = 0; i < m_nb_sommet; ++i)
    {
        svgout.addDisk(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,15,colorSommet[i]);
        svgout.addText(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getNom(),"mediumblue");
        switch(choix)
        {
        case 0 : //Indice de degré
            svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceDegre(),"black");
            break;
        case 1:  //Indice de vecteur propre
            svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceVect(),"black");
            break;
        case 2:  //Indice de proximité
            svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceProxi(),"black");
            break;
        case 3:  //Indice di'ntermédialité
            svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceInter(),"black");
            break;
        default:
            break;
        }

    }
    for(int j = 0; j < m_nb_arete; ++j)
    {
        svgout.addLine(m_aretes[j]->getExtr1()->getCoord_x()*100,m_aretes[j]->getExtr1()->getCoord_y()*100,m_aretes[j]->getExtr2()->getCoord_x()*100,m_aretes[j]->getExtr2()->getCoord_y()*100,"black");
        svgout.addText((m_aretes[j]->getExtr1()->getCoord_x()*100+m_aretes[j]->getExtr2()->getCoord_x()*100)/2,(m_aretes[j]->getExtr1()->getCoord_y()*100+m_aretes[j]->getExtr2()->getCoord_y()*100)/2,m_aretes[j]->getPoids(),"black");
    }
}

Sommet* Graphe::trouverSommet(int num)
{
    for(size_t i = 0; i < m_sommets.size();++i)
        if(m_sommets[i]->getNumero() == num)
            return m_sommets[i];
}

Graphe::Graphe(std::string file_name)
{
    std::ifstream fichier{file_name}; //ouverture de fichier lecture
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier topo";
    }
    else
    {
       std::string ligne_lu; //Variable de lecture
       int nb_ligne=0; //Variable numero de ligne
       int nb_sommet=0; //Variable nombre de sommet
       int nb_arete=0; //Variable nombre arrete
       while(getline(fichier, ligne_lu))
       {
           std::istringstream iss{ligne_lu};
           if (nb_ligne==0) //lecture ligne oriatation graph
           {
               iss>>m_ori; //0 si non oriente,1 si oriente
           }
           else if (nb_ligne==1) //lecture ligne nb sommet
           {
               iss>>nb_sommet; //nb sommet
               m_nb_sommet = nb_sommet;
           }
           else if (nb_ligne>1 && nb_ligne<(nb_sommet+2)) //lecture des sommets
           {
               Sommet* sommet = new Sommet();
               int num = 0,x = 0,y = 0;
               std::string nom;
               int i = m_sommets.size();
               m_sommets.push_back(sommet);
               iss>>num; //numero de sommet
               m_sommets[i]->setNumero(num);
               iss>>nom; //nom
               m_sommets[i]->setNom(nom);
               iss>>x; //coord x
               m_sommets[i]->setCoord_x(x);
               iss>>y; //coord y
               m_sommets[i]->setCoord_y(y);
           }
           else if (nb_ligne==nb_sommet+2) //lecture nombre d'arrete
           {
               iss>>nb_arete; //nb d'arrete
               m_nb_arete = nb_arete;
           }
           else if(nb_ligne>(nb_sommet+2) && nb_ligne<(nb_sommet+nb_arete+3)) //lecture des arretes
           {
               Arete* arete = new Arete();
               int num,ex1,ex2;
               int i = m_aretes.size();
               m_aretes.push_back(arete);
               iss>>num; //numero d'arrete
               m_aretes[i]->setNum(num);
               iss>>ex1; //extremite 1
               m_aretes[i]->setExtr1(trouverSommet(ex1));
               iss>>ex2; //extremite 2
               m_aretes[i]->setExtr2(trouverSommet(ex2));
           }
           else
           {
               std::cout << "ERREUR: lecture du fichier trop de sommets ou arrète par rapport au nombre anoncé topo"<<std::endl;
           }

           ++nb_ligne; //incrementation numero de ligne
       }
    }
}
void Graphe::lecture_topo(std::string file_name)
{
  std::ifstream fichier{file_name}; //ouverture de fichier lecture
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier topo";
    }
    else
    {
       std::string ligne_lu; //Variable de lecture
       int nb_ligne=0; //Variable numero de ligne
       int nb_sommet=0; //Variable nombre de sommet
       int nb_arete=0; //Variable nombre arrete
       while(getline(fichier, ligne_lu))
       {
           std::istringstream iss{ligne_lu};
           if (nb_ligne==0) //lecture ligne oriatation graph
           {
               iss>>m_ori; //0 si non oriente,1 si oriente
           }
           else if (nb_ligne==1) //lecture ligne nb sommet
           {
               iss>>nb_sommet; //nb sommet
               m_nb_sommet = nb_sommet;
           }
           else if (nb_ligne>1 && nb_ligne<(nb_sommet+2)) //lecture des sommets
           {
               Sommet* sommet = new Sommet();
               int num = 0,x = 0,y = 0;
               std::string nom;
               int i = m_sommets.size();
               m_sommets.push_back(sommet);
               iss>>num; //numero de sommet
               m_sommets[i]->setNumero(num);
               iss>>nom; //nom
               m_sommets[i]->setNom(nom);
               iss>>x; //coord x
               m_sommets[i]->setCoord_x(x);
               iss>>y; //coord y
               m_sommets[i]->setCoord_y(y);
           }
           else if (nb_ligne==nb_sommet+2) //lecture nombre d'arrete
           {
               iss>>nb_arete; //nb d'arrete
               m_nb_arete = nb_arete;
           }
           else if(nb_ligne>(nb_sommet+2) && nb_ligne<(nb_sommet+nb_arete+3)) //lecture des arretes
           {
               Arete* arete = new Arete();
               int num,ex1,ex2;
               int i = m_aretes.size();
               m_aretes.push_back(arete);
               iss>>num; //numero d'arrete
               m_aretes[i]->setNum(num);
               iss>>ex1; //extremite 1
               m_aretes[i]->setExtr1(trouverSommet(ex1));
               iss>>ex2; //extremite 2
               m_aretes[i]->setExtr2(trouverSommet(ex2));
           }
           else
           {
               std::cout << "ERREUR: lecture du fichier trop de sommets ou arrète par rapport au nombre anoncé topo"<<std::endl;
           }

           ++nb_ligne; //incrementation numero de ligne
       }

    }
}

void Graphe::sauvegarde_topo(std::string file_name)
{
    std::ofstream fichier { file_name }; //ouverture fichier ecriture
    if (!fichier)
    {
        std::cout << "ERREUR: sauvegarde du fichier topo" << std::endl;
    }
    else
    {
        fichier << m_ori << std::endl;
        fichier << m_nb_sommet<<std::endl;
        for (int i = 0; i < m_nb_sommet; ++i)
        {
            fichier << m_sommets[i]->getNumero() << " " << m_sommets[i]->getNom() << " " << m_sommets[i]->getCoord_x() << " " << m_sommets[i]->getCoord_y() << std::endl;
        }
        fichier << m_nb_arete <<std::endl;
        for (int j = 0; j < m_nb_arete; ++j)
        {
            fichier << m_aretes[j]->getNum() << " " << m_aretes[j]->getExtr1()->getNumero() << " " << m_aretes[j]->getExtr2()->getNumero() << std::endl;
        }
    }
}

void Graphe::lecture_pond(std::string file_name)
{
    #include <iostream>
    #include <fstream>
    std::ifstream fichier{file_name}; //ouverture de fichier lecture
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier topo";
    }
    else
    {
        std::string ligne_lu; //Variable de lecture
        int nb_ligne=0; //Variable numero de ligne
        int nb_arete=0; //Variable nombre arrete
        while(getline(fichier, ligne_lu))
        {
            std::istringstream iss{ligne_lu};
            if (nb_ligne==0) //lecture ligne nb arrète
            {
               iss>>nb_arete; //nb d'arrete (deja sauvegarde)
               if (nb_arete != m_nb_arete)
               {
                   std::cout << "ERREUR: Le nombre d'arete dans topo est different que dans pond" << std::endl;
               }
            }
            else if (nb_ligne>0 && nb_ligne<(nb_arete+1))
            {
                int num=0;
                float pond=0;
                iss>>num; //Numeros arete (deja sauvgarde)
                iss>>pond;//Lecture poids
                m_aretes[num]->setPoids(pond);
            }
            else
            {
                std::cout << "ERREUR: lecture du fichier trop d'arrete par rapport au nombre annonce pond"<<std::endl;
            }
            ++nb_ligne;
        }
    }

}

void Graphe::sauvegarde_pond(std::string file_name)
{
    std::ofstream fichier {file_name}; //ouverture fichier ecriture
    if (!fichier)
    {
        std::cout << "ERREUR: sauvegarde du fichier pond" << std::endl;
    }
    else
    {
        fichier << m_nb_arete << std::endl;
        for (int i = 0; i < m_nb_arete; ++i)
        {
            fichier << m_aretes[i]->getNum() << " " << m_aretes[i]->getPoids() << std::endl;
        }

    }
}


Graphe::~Graphe()
{

}

void Graphe::centrDegre()
{
    std::vector<float> indice;
    std::vector<float> somme;
    int oriente = getOri();
    std::string choix;
    int reponse_valide=0;
    if (oriente==1)
    {
        while (reponse_valide==0)
        {
        std::cout << "degré arrive > Arr < ou depart > Dep < ?" << std::endl;
        std::cout << "> ";
        std::cin >> choix;
        if (choix=="Arr" || choix=="Dep")
        {
            reponse_valide=1;
        }
        else
        {
            std::cout << "ERREUR: reponse invalide" << std::endl;
        }

        }
    }
    for(size_t i = 0; i < m_sommets.size();++i)
    {
        somme.push_back(0);
        indice.push_back(0);
        if (oriente==0)
        {
            for(size_t j = 0; j < m_aretes.size();++j)
            {
                if(m_aretes[j]->getExtr1()->getNumero() == m_sommets[i]->getNumero() || m_aretes[j]->getExtr2()->getNumero() == m_sommets[i]->getNumero())
                {
                    somme[i] = somme[i]+1;
                }
            }
        }
        if (oriente==1)
        {
            if (choix=="Dep")
            {
                for(size_t j = 0; j < m_aretes.size();++j)
                {
                    if(m_aretes[j]->getExtr1()->getNumero() == m_sommets[i]->getNumero())
                    {
                        somme[i] = somme[i]+1;
                    }
                }
            }
            if (choix=="Arr")
            {
                for(size_t j = 0; j < m_aretes.size();++j)
                {
                    if(m_aretes[j]->getExtr2()->getNumero() == m_sommets[i]->getNumero())
                    {
                        somme[i] = somme[i]+1;
                    }
                }
            }
        }
        m_sommets[i]->setIndiceDegre(somme[i]/(m_nb_sommet-1));
    }
    //affichage en console
    std::cout << "Indice de Degre" << std::endl;
    for (size_t i =0; i<m_sommets.size();++i)
    {
        std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceDegre()<<std::endl;
    }
}
std::vector<Sommet*> Graphe::trouverSuccs(Sommet* base)const
{
    std::vector<Sommet*> succs;
    for(size_t i = 0; i < m_aretes.size(); ++i)
    {
        if(m_aretes[i]->getExtr1()->getNumero() == base->getNumero())
            succs.push_back(m_aretes[i]->getExtr2());
        else if(m_aretes[i]->getExtr2()->getNumero() == base->getNumero())
            succs.push_back(m_aretes[i]->getExtr1());
    }
    return succs;
}

void Graphe::centrVectPropre()
{
    std::vector<float> indice;
    std::vector<float> csi;
    float lambda;
    float precedent;
    float somme;
    float difference;
    std::vector<Sommet*>succs;
    for(size_t i = 0; i < m_sommets.size();++i)
    {
        somme = 0;
        lambda = 0;
        precedent= 0;
        csi.push_back(0);
        indice.push_back(1);
        m_sommets[i]->setIndiceVect(1);
    }
    do
    {
        precedent = lambda;
        for(size_t i = 0; i < m_sommets.size();++i)
            csi[i] = 0;
        somme = 0;
        //Calcul Indice Voisins
        for(size_t i = 0; i < m_sommets.size();++i)
        {
            succs = trouverSuccs(m_sommets[i]);
            for(size_t j = 0; j < succs.size();++j){
                csi[i] = csi[i] + succs[j]->getIndiceVect();}
        }
        //Calcul Lambda
        for(size_t i = 0; i < m_sommets.size();++i)
            somme = somme + (csi[i]*csi[i]);
        lambda = sqrt(somme);
        //Calcul Indice Vecteur
        for(size_t i = 0; i < m_sommets.size();++i)
        {
            indice[i] = csi[i]/lambda;
            m_sommets[i]->setIndiceVect(indice[i]);
        }
        if(lambda-precedent>0)
            difference = lambda-precedent;
        else
            difference = -(lambda-precedent);
    }while(difference>0.2);
    //affichage en console
    std::cout << "Indice de Vecteur propre" << std::endl;
    for (size_t i =0; i<m_sommets.size();++i)
    {
        std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceVect()<<std::endl;
    }

}

void Graphe::suppr_arete(int s1,int s2)
{
    int indicateur_reusite = 0;
    for (int i =0; i < m_aretes.size();++i)// parcours de toutes les arretes
    {
        if((m_aretes[i]->getExtr1()->getNumero() == s1 && m_aretes[i]->getExtr2()->getNumero() == s2) || (m_aretes[i]->getExtr1()->getNumero() == s2 && m_aretes[i]->getExtr2()->getNumero() == s1))
        { // on teste le sens s1 s2 et s2 s1
            delete m_aretes[i]; //Degagement de la mémoire supression de l'objet
            m_aretes.erase(m_aretes.begin()+i); //Supression dans le vecteur dans graph
            m_nb_arete=m_nb_arete-1;
            indicateur_reusite = 1;
        }
    }
    if (indicateur_reusite == 0) //Numéros de sommet invalide
    {
        std::cout << "ERREUR: numero de sommet invalide" << std::endl;
    }

}

void Graphe::suppr_sommet(int sommet)
{
    int indicateur_reussite = 0;
    for (int i =0; i < m_sommets.size();++i) //parcours de tous les sommets
    {
        if (sommet == m_sommets[i]->getNumero())
        {
            for (int j = 0; j < m_aretes.size();++j)
            {
                if((m_aretes[j]->getExtr1()->getNumero()== sommet) || (m_aretes[j]->getExtr2()->getNumero()==sommet))
                {
                    suppr_arete(m_aretes[j]->getExtr1()->getNumero(),m_aretes[j]->getExtr2()->getNumero());
                    --j; //on delete un élément du vecteur donc toutes les positions du vecteur sont décalées
                }
            }
            delete m_sommets[i]; //Degagement de la mémoire supression de l'objet
            m_sommets.erase(m_sommets.begin()+i); //Supression dans le vecteur dans graph
            m_nb_sommet=m_nb_sommet-1;
            indicateur_reussite = 1;
        }
    }
    if (indicateur_reussite == 0) //Numéros de sommet invalide
    {
        std::cout << "ERREUR: numero de sommet invalide" << std::endl;
    }
}

//Algorithme Dijsktra aide TP3 solution 2 de Mme PALASI
std::vector<int> Graphe::Dijsktra(int Sdepart)
{
    auto cmp = [](std::pair<double,const Sommet*> p1, std::pair<double,const Sommet*> p2)
    {
        return p2.second<p1.second;
    };
    //(Aide TP2 et TP3 Mme PALASI
    std::priority_queue<std::pair<double,const Sommet*>,std::vector<std::pair<double,const Sommet*>>,decltype(cmp)> file(cmp);
    std::vector<int> marquage(m_sommets.size(),0);
    std::vector<int> predecesseur(m_sommets.size(),-1);
    std::vector<int> distance(m_sommets.size(),-1);
    file.push({0,m_sommets[Sdepart]});
    distance[Sdepart] = 0;
    std::pair<double,const Sommet*> premier;
    while(!file.empty())
    {
        premier = file.top();
        file.pop();
        while((!file.empty()) && (marquage[premier.second->getNumero()]))
        {
            premier = file.top();
            file.pop();
        }
        for(auto succs : poidsSuccsTrie(premier.second))
        {
            if((marquage[succs.second->getNumero()] == 0) && (distance[premier.second->getNumero()] + succs.first < distance[succs.second->getNumero()]) || (distance[succs.second->getNumero()] == -1))
            {
                distance[succs.second->getNumero()] = distance[premier.second->getNumero()] + succs.first;
                predecesseur[succs.second->getNumero()] = premier.second->getNumero();
                file.push({distance[succs.second->getNumero()],succs.second});
            }
        }
    }
    return distance;
}

std::vector<std::pair<double,const Sommet*>> Graphe::poidsSuccsTrie(const Sommet* debut)const
{
    std::vector<std::pair<double,const Sommet*>>poidsSuccs;
    for(size_t i = 0; i < m_aretes.size(); ++i)
    {
        if(m_aretes[i]->getExtr1()->getNumero() == debut->getNumero())
            poidsSuccs.push_back(std::make_pair(m_aretes[i]->getPoids(),m_aretes[i]->getExtr2()));
        else if(m_aretes[i]->getExtr2()->getNumero() == debut->getNumero())
            poidsSuccs.push_back(std::make_pair(m_aretes[i]->getPoids(),m_aretes[i]->getExtr1()));
    }
    std::sort(poidsSuccs.begin(),poidsSuccs.end());
    return poidsSuccs;
}

void Graphe::centrProxi()
{
    std::vector<int> resultat(m_sommets.size(),0);
    float somme = 0;
    for(size_t i = 0; i < m_sommets.size(); ++i)
    {
        resultat = Dijsktra(i);
        for(size_t j = 0; j < resultat.size(); ++j)
            somme = somme + resultat[j];
        m_sommets[i]->setIndiceProxi((m_sommets.size()-1)/(somme));
        somme = 0;
    }
    //affichage en console
    std::cout << "Indice de centre Proximite" << std::endl;
    for (size_t i =0; i<m_sommets.size();++i)
    {
        std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceProxi()<<std::endl;
    }
}

void Graphe::sauvegarde_indice(std::string file_name)
{
    std::ofstream fichier {file_name}; //ouverture fichier ecriture
    if (!fichier)
    {
        std::cout << "ERREUR: sauvegarde du fichier Indice" << std::endl;
    }
    else
    {
        fichier << "Num Deg Vec Pro Int" << std::endl;
        for (int i = 0; i < m_nb_sommet; ++i)
        {
            fichier << m_sommets[i]->getNumero() << "   " << m_sommets[i]->getIndiceDegre()<< "   " << m_sommets[i]->getIndiceVect()<< "   " << m_sommets[i]->getIndiceProxi()<< "   " << m_sommets[i]->getIndiceDegre() << std::endl;
        }
    }
}

std::vector<std::vector<int>> Graphe::DijsktraModif(int Sdepart, int Sarrivee)
{
    auto cmp = [](std::pair<double,const Sommet*> p1, std::pair<double,const Sommet*> p2)
    {
        return p2.second<p1.second;
    };
    //(Aide TP2 et TP3 Mme PALASI
    std::priority_queue<std::pair<double,const Sommet*>,std::vector<std::pair<double,const Sommet*>>,decltype(cmp)> file(cmp);
    std::vector<int> marquage(m_sommets.size(),0);
    std::vector<int> predecesseur(m_sommets.size(),-1);
    std::vector<std::vector<int>> resultat;
    std::vector<int> distance(m_sommets.size(),-1);
    int npcc = 0;
    file.push({0,m_sommets[Sdepart]});
    distance[Sdepart] = 0;
    std::pair<double,const Sommet*> premier;
    while((!file.empty()) || (marquage[Sarrivee] == 0))
    {
        premier = file.top();
        file.pop();
        while((!file.empty()) && (marquage[premier.second->getNumero()] == 1))
        {
            premier = file.top();
            file.pop();
        }
        marquage[premier.second->getNumero()] = 1;
        for(auto succs : poidsSuccsTrie(premier.second))
        {
            if((marquage[succs.second->getNumero()] == 0))
            {
                resultat.push_back(predecesseur);
                if((distance[premier.second->getNumero()] + succs.first < distance[succs.second->getNumero()]) || (distance[succs.second->getNumero()] == -1))
                {
                    distance[succs.second->getNumero()] = distance[premier.second->getNumero()] + succs.first;
                    predecesseur[succs.second->getNumero()] = premier.second->getNumero();
                    file.push({distance[succs.second->getNumero()],succs.second});
                }
            }
        }
    }
    return resultat;
}

void Graphe::centrInter()
{
    std::cout<<"0"<<std::endl;
    float somme = 0, n_pcc = 0, n_pcc_i = 0;
    std::vector<std::vector<int>> touspcc;
    std::vector<int>temp(m_sommets.size(),0);
    for(size_t i = 0; i < m_sommets.size(); ++i)
            touspcc.push_back(temp);
    std::cout<<"1"<<std::endl;
    for(size_t i = 0; i < m_sommets.size(); ++i)
    {
        for(size_t j = 0; j < m_sommets.size(); ++j)
        {
            for(size_t k = 0; k < m_sommets.size(); ++k)
            {std::cout<<"2"<<std::endl;
                touspcc = DijsktraModif(j,k);std::cout<<"3"<<std::endl;
                n_pcc = touspcc.size();
                for(size_t l = 0; l < touspcc.size(); ++l)
                    for(size_t m = 0; m < touspcc[l].size(); ++m)
                        if(touspcc[l][m] == m_sommets[i]->getNumero())
                            n_pcc_i++;
            }
            somme = somme + (n_pcc_i/n_pcc);
            n_pcc = 0;
            n_pcc_i = 0;
        }
        m_sommets[i]->setIndiceInter((2*somme)/((m_sommets.size()*m_sommets.size())-(3*m_sommets.size())+2));
        somme = 0;
    }
}

int Graphe::calculk_connexite()
{
    int k_connex=100000000;
    int k_connexnew=0;
    int commun=0;
    std::vector<std::vector<int>> resultat;
    std::vector<int>marq(m_sommets.size(),0);//marquage des sommets 
    for(size_t i = 0;i < m_sommets.size(); ++i)//Pour tous couples de sommets Si et Sj
    {
        for(size_t j = 0; j < m_sommets.size(); ++j)
        {
            if (i != j) //Sommets dijoints
            {
                resultat = DijsktraModif(i;j);
                k_connexnew=0;
                for (size_t x = 0;x<resultat.size(),++x)
                {
                    commun =0;
                    for (size_t y = 1;y<((resultat[x].size)-1);++y )
                    {
                        if (marq[resultat[x][y]]==0)
                        {
                            marq[resultat[x][y]]=1;
                        }
                        else
                        {
                            ++commun;
                        }
                    }
                    if (commun==0)
                    {
                        ++k_connexnew;
                    } 
                }

            }
            if(k_connexnew<k_connex)
            {
                k_connex=k_connexnew;
            }
            k_connexnew=0;
        }
    }
    return k_connex;
}
