#include "Arete.h"
#include "Sommet.h"

//Pierre 27/04/2020
int Arete::getNum()const //Getter du numero de l'arete
{
    return m_numero;
}

//Pierre 27/04/2020
void Arete::setNum(int num) //Setter du numero de l'arete
{
    m_numero = num;
}

//Pierre 27/04/2020
Sommet* Arete::getExtr1()const //Getter d'un pointeur sur le sommet qui est l'extremite 1 de l'arete
{
    return m_extr1;
}

//Pierre 27/04/2020
void Arete::setExtr1(Sommet* extr) //Setter d'un pointeur sur le sommet qui est l'extremite 1 de l'arete
{
    m_extr1 = extr;
}

//Pierre 27/04/2020
Sommet* Arete::getExtr2()const //Getter d'un pointeur sur le sommet qui est l'extremite 2 de l'arete
{
    return m_extr2;
}

//Pierre 27/04/2020
void Arete::setExtr2(Sommet* extr) //Setter d'un pointeur sur le sommet qui est l'extremite 1 de l'arete
{
    m_extr2 = extr;
}

//Pierre 27/04/2020
float Arete::getPoids()const //Getter d'u poids de l'arete
{
    return m_poids;
}

//Pierre 27/04/2020
void Arete::setPoids(float poids) //Setter d'u poids de l'arete
{
    m_poids = poids;
}

//Pierre 27/04/2020
float Arete::getIndiceDegre()const //Getter de l'indice de centralite de degre du sommet
{
    return m_indiceDegre;
}

//Pierre 27/04/2020
void Arete::setIndiceDegre(float indice) //Setter de l'indice de centralite de degre du sommet
{
    m_indiceDegre = indice;
}

//Pierre 27/04/2020
float Arete::getIndiceVect()const //Getter de l'indice de centralite de vecteur propre du sommet
{
    return m_indiceVect;
}

//Pierre 27/04/2020
void Arete::setIndiceVect(float indice) //Setter de l'indice de centralite de vecteur propre du sommet
{
    m_indiceVect = indice;
}

//Pierre 27/04/2020
float Arete::getIndiceDegreNon()const //Idem que les getter et setter precedents mais sur les indices non normalises
{
    return m_indiceDegreNon;
}

//Pierre 27/04/2020
void Arete::setIndiceDegreNon(float indice)
{
    m_indiceDegreNon = indice;
}



//Pierre 27/04/2020
Arete::Arete() //Constrcuteur d'une arete
{
    m_poids = 0;
}

//Pierre 27/04/2020
Arete::~Arete() //Destrcuteur d'une arete
{

}
