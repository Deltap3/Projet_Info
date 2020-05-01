#include "Sommet.h"
#include <iostream>
#include <vector>

//Pierre 27/04/2020
int Sommet::getNumero()const //Getter du numero du sommet
{
    return m_numero;
}

//Pierre 27/04/2020
void Sommet::setNumero(int num) //Setter du numero du sommet
{
    m_numero = num;
}

//Pierre 27/04/2020
std::string Sommet::getNom()const //Getter du nom du sommet
{
    return m_nom;
}

//Pierre 27/04/2020
void Sommet::setNom(std::string nom) //Setter du nom du sommet
{
    m_nom = nom;
}

//Pierre 27/04/2020
float Sommet::getCoord_x()const //Getter de la coordonnee en x du sommet
{
    return m_coord_x;
}

//Pierre 27/04/2020
void Sommet::setCoord_x(float coord) //Setter de la coordonnee en x du sommet
{
    m_coord_x = coord;
}

//Pierre 27/04/2020
float Sommet::getCoord_y()const //Getter de la coordonnee en x du sommet
{
    return m_coord_y;
}

//Pierre 27/04/2020
void Sommet::setCoord_y(float coord) //Setter de la coordonnee en x du sommet
{
    m_coord_y = coord;
}

//Pierre 27/04/2020
float Sommet::getIndiceDegre()const //Getter de l'indice de centralite de degre du sommet
{
    return m_indiceDegre;
}

//Pierre 27/04/2020
void Sommet::setIndiceDegre(float indice) //Setter de l'indice de centralite de degre du sommet
{
    m_indiceDegre = indice;
}

//Pierre 27/04/2020
float Sommet::getIndiceVect()const //Getter de l'indice de centralite de vecteur propre du sommet
{
    return m_indiceVect;
}

//Pierre 27/04/2020
void Sommet::setIndiceVect(float indice) //Setter de l'indice de centralite de vecteur propre du sommet
{
    m_indiceVect = indice;
}

//Pierre 27/04/2020
float Sommet::getIndiceProxi()const //Getter de l'indice de centralite de proximite du sommet
{
    return m_indiceProxi;
}

//Pierre 27/04/2020
void Sommet::setIndiceProxi(float indice) //Setter de l'indice de centralite de proximite du sommet
{
    m_indiceProxi = indice;
}

//Pierre 27/04/2020
float Sommet::getIndiceInter()const //Getter de l'indice de centralite d'intermediarite du sommet
{
    return m_indiceInter;
}

//Pierre 27/04/2020
void Sommet::setIndiceInter(float indice) //Setter de l'indice de centralite d'intermediarite du sommet
{
    m_indiceInter = indice;
}

//Pierre 27/04/2020
float Sommet::getIndiceDegreNon()const //Idem que les getter et setter precedents mais sur les indices non normalises
{
    return m_indiceDegreNon;
}

//Pierre 27/04/2020
void Sommet::setIndiceDegreNon(float indice)
{
    m_indiceDegreNon = indice;
}

//Pierre 27/04/2020
float Sommet::getIndiceProxiNon()const
{
    return m_indiceProxiNon;
}

//Pierre 27/04/2020
void Sommet::setIndiceProxiNon(float indice)
{
    m_indiceProxiNon = indice;
}

//Pierre 27/04/2020
float Sommet::getIndiceInterNon()const
{
    return m_indiceInterNon;
}

//Pierre 27/04/2020
void Sommet::setIndiceInterNon(float indice)
{
    m_indiceInterNon = indice;
}

//Pierre 27/04/2020
Sommet::Sommet()
{
    m_nom = 'A';
    m_numero = 0;
}

//Pierre 27/04/2020
Sommet::~Sommet()
{

}
