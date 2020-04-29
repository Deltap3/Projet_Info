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

void Graphe::affichage_svg(Svgfile& svgout)
{
    svgout.addGrid();
    std::string c;
    for(int i = 0; i < m_nb_sommet; ++i)
    {
        switch(trouverSuccs(m_sommets[i]).size())
        {
        case 0 :
            c = "gray";
            break;
        case 1 :
            c = "lightblue";
            break;
        case 2 :
            c = "green";
            break;
        case 3 :
            c = "yellow";
            break;
        case 4 :
            c = "red";
        break;
        default :
            c = "brown";
        }
        svgout.addDisk(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,15,c);
        svgout.addText(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getNom(),"darkblue");
        svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceProxi(),"black");
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
            delete m_sommets[i]; //Degagement de la mémoire supression de l'objet
            m_sommets.erase(m_sommets.begin()+i); //Supression dans le vecteur dans graph
            m_nb_sommet=m_nb_sommet-1;
            indicateur_reussite = 1;
            for (int j = 0; j<m_aretes.size();++j)
            {
                if(m_aretes[j]->getExtr1()->getNumero()==sommet || m_aretes[j]->getExtr2()->getNumero()==sommet )
                {
                    delete m_aretes[j]; //Degagement de la mémoire supression de l'objet
                    m_aretes.erase(m_aretes.begin()+j); //Supression dans le vecteur dans graph
                    m_nb_arete=m_nb_arete-1;
                }
            }
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
}
