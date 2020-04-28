#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <vector>

class Sommet
{
    public:
        Sommet();
        virtual ~Sommet();
        int getNumero()const;
        void setNumero(int num);
        std::string getNom()const;
        void setNom(std::string nom);

        int getCoord_x()const;
        void setCoord_x(int coord);
        int getCoord_y()const;
        void setCoord_y(int coord);

        float getIndiceDegre()const;
        void setIndiceDegre(float indice);
        float getIndiceVect()const;
        void setIndiceVect(float indice);

    private:
        int m_numero;
        std::string m_nom;

        int m_coord_x;
        int m_coord_y;

        float m_indiceDegre;
        float m_indiceVect;

};

#endif // SOMMET_H
