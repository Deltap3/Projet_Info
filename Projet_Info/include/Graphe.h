#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include "Arete.h"
#include "Sommet.h"
#include <iostream>
#include "svgfile.h"

class Graphe
{
    public:
        Graphe(std::string file_name);
        virtual ~Graphe();
        bool getOri()const;

        int getNbArete()const;
        void setNbArete(int nb);
        int getNbSommet()const;
        void setNbSommet(int nb);
		void sauvegarde_topo(std::string file_name);
		void creation_svg();
		void affichage_svg(Svgfile& svgout);
		void lecture_pond(std::string file_name);
        void sauvegarde_pond(std::string file_name);
		Sommet* trouverSommet(int num);
		std::vector<Sommet*> trouverSuccs(Sommet* base)const;
		void centrDegre();
		void centrVectPropre();
		void suppr_sommet(int sommet);
		void suppr_arete(int s1,int s2);
		void lecture_topo(std::string file_name);
		//void Dijsktra(int debut, int fin);
		//void Dijsktra(Sommet* debut);
		//int Dijsktra(int first, int fin);
		std::vector<int> Dijsktra(int Sdepart);
		std::vector<Sommet*> trouverDijstra(int numero);
		int trouverPoids(int first,  int last);
		int trouverEmplacement(int sommet, std::vector<Sommet*>Q);
		std::vector<std::pair<double,const Sommet*>> poidsSuccsTrie(const Sommet* debut)const;

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
