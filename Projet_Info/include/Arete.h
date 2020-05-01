#ifndef ARETE_H
#define ARETE_H
#include "Sommet.h"


class Arete  //Les commentaires de chaques sous programme se trouvent dans le .cpp
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

        float getPoids()const;
        void setPoids(float poids);
        Sommet* m_extr1;
        Sommet* m_extr2;

    private:
        int m_numero;

        float m_poids;
};

#endif // ARETE_H
