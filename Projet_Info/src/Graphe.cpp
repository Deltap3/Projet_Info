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
    svgout.addGrid();
    for(int i = 0; i < m_nb_sommet; ++i)
    {
        svgout.addDisk(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,15,"lightblue");
        svgout.addText(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getNom(),"black");
    }
    std::cout<<m_aretes[0]->getExtr1()->getCoord_x();
    for(int j = 0; j < m_nb_arete; ++j)
        svgout.addLine(m_aretes[j]->getExtr1()->getCoord_x()*100,m_aretes[j]->getExtr1()->getCoord_y()*100,m_aretes[j]->getExtr2()->getCoord_x()*100,m_aretes[j]->getExtr2()->getCoord_y()*100,"black");
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
           if (nb_ligne==0) //lecture ligne oriatation graph
           {
               iss>>m_ori; //0 si non orienté,1 si orienté
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
               iss>>num; //numéro de sommet
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
               iss>>nb_arete; //nb d'arrète
               m_nb_arete = nb_arete;
           }
           else if(nb_ligne>(nb_sommet+2) && nb_ligne<(nb_sommet+nb_arete+3)) //lecture des arrètes
           {
               Arete* arete = new Arete();
               int num,ex1,ex2;
               int i = m_aretes.size();
               m_aretes.push_back(arete);
               iss>>num; //numéro d'arrète
               m_aretes[i]->setNum(num);
               iss>>ex1; //extrémité 1
               m_aretes[i]->setExtr1(trouverSommet(ex1));
               iss>>ex2; //extrémité 2
               m_aretes[i]->setExtr2(trouverSommet(ex2));
           }
           else
           {
               std::cout << "ERREUR: lecture du fichier"<<std::endl;
           }

           ++nb_ligne; //incrémentation néméro de ligne
       }
    }
}

void Graphe::sauvegarde_topo(std::string file_name)
{
    std::ofstream fichier { file_name }; //ouverture fichier ecriture
    if (!fichier)
    {
        std::cout << "ERREUR: ouverture du fichier" << std::endl;
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

Graphe::~Graphe()
{
    //dtor
}

void Graphe::centrDegre()
{
    std::vector<float> indice;
    std::vector<int> somme;
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
