#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <vector>

class Sommet  //Les commentaires de chaques sous programme se trouvent dans le .cpp
{
    public:
        Sommet();
        virtual ~Sommet();
        int getNumero()const;
        void setNumero(int num);
        std::string getNom()const;
        void setNom(std::string nom);

        float getCoord_x()const;
        void setCoord_x(float coord);
        float getCoord_y()const;
        void setCoord_y(float coord);

        float getIndiceDegre()const;
        void setIndiceDegre(float indice);
        float getIndiceVect()const;
        void setIndiceVect(float indice);
        float getIndiceProxi()const;
        void setIndiceProxi(float indice);
        float getIndiceInter()const;
        void setIndiceInter(float indice);

        float getIndiceDegreNon()const;
        void setIndiceDegreNon(float indice);
        float getIndiceProxiNon()const;
        void setIndiceProxiNon(float indice);
        float getIndiceInterNon()const;
        void setIndiceInterNon(float indice);


    private:
        int m_numero;
        std::string m_nom;

        int m_coord_x;
        int m_coord_y;

        float m_indiceDegre;
        float m_indiceVect;
        float m_indiceProxi;
        float m_indiceInter;
        float m_indiceDegreNon;
        float m_indiceProxiNon;
        float m_indiceInterNon;

};

#endif // SOMMET_H
