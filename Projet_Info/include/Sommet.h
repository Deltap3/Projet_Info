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

        void setIndiceDegre(float indice);

    private:
        int m_numero;
        std::string m_nom;

        int m_coord_x;
        int m_coord_y;

        float m_indiceDegre;

};

#endif // SOMMET_H
