#include "Sommet.h"
#include <iostream>
#include <vector>

int Sommet::getNumero()const
{
    return m_numero;
}

void Sommet::setNumero(int num)
{
    m_numero = num;
}

std::string Sommet::getNom()const
{
    return m_nom;
}

void Sommet::setNom(std::string nom)
{
    m_nom = nom;
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

float Sommet::getIndiceDegre()const
{
    return m_indiceDegre;
}

void Sommet::setIndiceDegre(float indice)
{
    m_indiceDegre = indice;
}

float Sommet::getIndiceVect()const
{
    return m_indiceVect;
}

void Sommet::setIndiceVect(float indice)
{
    m_indiceVect = indice;
}

float Sommet::getIndiceProxi()const
{
    return m_indiceProxi;
}

void Sommet::setIndiceProxi(float indice)
{
    m_indiceProxi = indice;
}

Sommet::Sommet()
{
    m_nom = 'A';
    m_numero = 0;
}

Sommet::~Sommet()
{
    //dtor
}
