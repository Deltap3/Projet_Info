#include "Graphe.h"
#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <utility>
#include <algorithm>


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
    for(int i = 0; i < m_nb_sommet; ++i)
    {
        svgout.addDisk(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,15,"lightblue");
        svgout.addText(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getNom(),"darkblue");
        svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceDegre(),"blue");
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
    for(size_t i = 0; i < m_sommets.size();++i)
    {
        somme.push_back(0);
        indice.push_back(0);
        for(size_t j = 0; j < m_aretes.size();++j)
        {
            if(m_aretes[j]->getExtr1()->getNumero() == m_sommets[i]->getNumero() || m_aretes[j]->getExtr2()->getNumero() == m_sommets[i]->getNumero())
            {
                somme[i] = somme[i]+1;
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

void Graphe::Dijsktra(int first, int last)
{
    std::vector<double>marque((int)m_sommets.size(),0);
    std::vector<double> distance((int)m_sommets.size(),-1);
    std::vector<std::pair<double,Sommet*>>poidSuccs;
    std::vector<Sommet*>succs;
    Sommet* debut = trouverSommet(first);
    Sommet* fin = trouverSommet(last);
    succs=trouverSuccs(debut);
    for(size_t i = 0; i < succs.size();++i)
        poidSuccs.push_back(std::make_pair(0,nullptr));
    poidSuccs = poidsSuccsTrie(debut);
    distance[debut->getNumero()] = 0;
    marque[debut->getNumero()] = 1;
    do
    {

    }while(marque[fin->getNumero()] == 1);
}

void Graphe::Dijsktra(Sommet* debut)
{
    std::vector<double>marque((int)m_sommets.size(),0);
    std::vector<double> distance((int)m_sommets.size(),-1);
    distance[debut->getNumero()] = 0;
    marque[debut->getNumero()] = 1;
    int fin = 1;
    do
    {

    }while(fin!=m_sommets.size());
}

std::vector<std::pair<double,Sommet*>> Graphe::poidsSuccsTrie(Sommet* debut)const
{
    std::vector<std::pair<double,Sommet*>>poidsSuccs;
    for(size_t i = 0; i < m_aretes.size(); ++i)
    {
        if(m_aretes[i]->getExtr1()->getNumero() == debut->getNumero())
            poidsSuccs.push_back(std::make_pair(m_aretes[i]->getPoids(),m_aretes[i]->getExtr2()));
        else if(m_aretes[i]->getExtr2()->getNumero() == debut->getNumero())
            poidsSuccs.push_back(std::make_pair(m_aretes[i]->getPoids(),m_aretes[i]->getExtr1()));
    }
    std::sort(poidsSuccs.begin(),poidsSuccs.end());
    for(size_t i = 0; i<poidsSuccs.size();++i)
        std::cout<<"sommet  "<<poidsSuccs[i].first<<" poids   "<<poidsSuccs[i].second->getNom()<<std::endl;
    return poidsSuccs;
}



