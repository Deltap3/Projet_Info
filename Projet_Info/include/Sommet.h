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

        int getCoord_x()const;
        void setCoord_x(int coord);
        int getCoord_y()const;
        void setCoord_y(int coord);

        std::vector<float> getIndice_centr()const;
        void setIndice_centr(std::vector<float> indi_centr);

    private:
        int m_numero;

        int m_coord_x;
        int m_coord_y;

        std::vector<float> m_indice_centr;
};

#endif // SOMMET_H
