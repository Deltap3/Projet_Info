#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include "Arete.h"
#include "Sommet.h"
#include <iostream>

class Graphe
{
    public:
        Graphe();
        virtual ~Graphe();
        bool getOri()const;

        int getNbArete()const;
        void setNbArete(int nb);
        int getNbSommet()const;
        void setNbSommet(int nb);

        std::vector<Sommet*> getSommets()const;
        std::vector<Arete*> getAretes()const;
        std::string getFileName()const;

    private:
        bool m_ori;

        int m_nb_arete;
        int m_nb_sommet;

        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::string m_fileName;
};

#endif // GRAPHE_H
