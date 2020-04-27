#include "Sommet.h"
#include <iostream>
#include <vector>

int Sommet::getNumero()const
{
    return m_numero;
}

int Sommet::getCoord_x()const
{
    return m_coord_x;
}

void Sommet::setCoord_x(int coord)
{
    m_coord_x = coord;
}

int Sommet::getCoord_y()const
{
    return m_coord_y;
}

void Sommet::setCoord_y(int coord)
{
    m_coord_y = coord;
}

std::vector<float> Sommet::getIndice_centr()const
{
    return m_indice_centr;
}

void Sommet::setIndice_centr(std::vector<float> indi_centr)
{
    m_indice_centr = indi_centr;
}

Sommet::Sommet()
{
    //ctor
}

Sommet::~Sommet()
{
    //dtor
}
