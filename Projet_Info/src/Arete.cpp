#include "Arete.h"

int Arete::getNum()const
{
    return m_numero;
}

int Arete::getExtr1()const
{
    return m_extr1;
}

void Arete::setExtr1(int extr)
{
    m_extr2 = extr;
}

int Arete::getExtr2()const
{
    return m_extr2;
}

void Arete::setExtr2(int extr)
{
    m_extr2 = extr;
}

int Arete::getPoids()const
{
    return m_poids;
}

void Arete::setPoids(int poids)
{
    m_poids = poids;
}


Arete::Arete()
{
    //ctor
}

Arete::~Arete()
{
    //dtor
}