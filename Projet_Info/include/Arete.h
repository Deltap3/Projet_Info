#ifndef ARETE_H
#define ARETE_H


class Arete
{
    public:
        Arete();
        virtual ~Arete();
        int getNum()const;

        int getExtr1()const;
        void setExtr1(int extr);
        int getExtr2()const;
        void setExtr2(int extr);

        int getPoids()const;
        void setPoids(int poids);

    private:
        int m_numero;
        int m_extr1;
        int m_extr2;
        int m_poids;
};

#endif // ARETE_H
