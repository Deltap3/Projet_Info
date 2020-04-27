#include "Graphe.h"
#include "Arete.h"
#include "Sommet.h"
#include <iostream>
#include "svgfile.h"

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
        svgout.addDisk(m_sommets[i]->getCoord_x(),m_sommets[i]->getCoord_y(),5,"blue")
    for(int j = 0; j < m_nb_arete; ++j)
        svgout.addLine(m_aretes[i]->m_extr1->getCoord_x(),m_aretes[i]->m_extr1->getCoord_y(),m_aretes[i]->m_extr2->getCoord_x(),m_aretes[i]->m_extr2->getCoord_(),"black")
}

Graphe::Graphe()
{
    //ctor
}

Graphe::~Graphe()
{
    //dtor
}
