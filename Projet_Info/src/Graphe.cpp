#include "Graphe.h"
#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <sstream>


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
    for(int i = 0; i < m_nb_sommet; ++i)
        svgout.addDisk(m_sommets[i]->getCoord_x(),m_sommets[i]->getCoord_y(),5,"blue");
    for(int j = 0; j < m_nb_arete; ++j)
        svgout.addLine(m_aretes[j]->getExtr1()->getCoord_x(),m_aretes[j]->getExtr1()->getCoord_y(),m_aretes[j]->getExtr2()->getCoord_x(),m_aretes[j]->getExtr2()->getCoord_y(),"black");
}

Sommet* Graphe::trouverSommet(int num)
{
    int i=0;
    while(m_sommets[i]->getNumero()!=num)
        ++i;
    return m_sommets[i];
}

Graphe::Graphe(std::string file_name)
{
    std::ifstream fichier{file_name}; //ouverture de fichier
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier";
    }
    else
    {
       std::string ligne_lu; //Variable de lecture
       int nb_ligne=0; //Variable numéro de ligne
       int nb_sommet=0; //Variable nombre de sommet
       int nb_arete=0; //Variable nombre arrete
       while(getline(fichier, ligne_lu))
       {
           std::istringstream iss{ligne_lu};
           if (nb_ligne=0) //lecture ligne oriatation graph
           {
               iss>>m_ori; //0 si non orienté,1 si orienté
           }
           if (nb_ligne=1) //lecture ligne nb sommet
           {
               iss>>m_nb_sommet; //nb sommet
           }
           if (nb_ligne>1 && nb_ligne<(nb_sommet+2)) //lecture des sommets
           {
               Sommet* sommet;
               int nom,num,x,y;
               m_sommets.push_back(sommet);
               iss>>num; //numéro de sommet
               m_sommets.back()->setNumero(num);
               iss>>nom; //nom
               m_sommets.back()->setNom(nom);
               iss>>x; //coord x
               m_sommets.back()->setCoord_x(x);
               iss>>y; //coord y
               m_sommets.back()->setCoord_y(y);
           }
           if (nb_ligne==nb_sommet+2) //lecture nombre d'arrete
           {
               iss>>m_nb_arete; //nb d'arrète
           }
           if(nb_ligne>(nb_sommet+2) && nb_ligne<(nb_sommet+nb_arete+3)) //lecture des arrètes
           {
               Arete* arete;
               int num,ex1,ex2;
               m_aretes.push_back(arete);
               iss>>num; //numéro d'arrète
               m_aretes.back()->setNum(num);
               iss>>ex2; //extrémité 1
               m_aretes.back()->setExtr1(trouverSommet(ex1));
               iss>>ex1; //extrémité 2
               m_aretes.back()->setExtr2(trouverSommet(ex1));
           }
           else
           {
               std::cout << "ERREUR: lecture du fichier";
           }

           ++nb_ligne; //incrémentation néméro de ligne


       }
    }
}

Graphe::~Graphe()
{
    //dtor
}
