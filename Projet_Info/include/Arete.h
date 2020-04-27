#ifndef ARETE_H
#define ARETE_H
#include "Sommet.h"


class Arete
{
    public:
        Arete();
        virtual ~Arete();
        int getNum()const;
        void setNum(int num);

        Sommet* getExtr1()const;
        void setExtr1(Sommet* extr);
        Sommet* getExtr2()const;
        void setExtr2(Sommet* extr);

        int getPoids()const;
        void setPoids(int poids);
        Sommet* m_extr1;
        Sommet* m_extr2;

    private:
        int m_numero;

        int m_poids;
};

#endif // ARETE_H
