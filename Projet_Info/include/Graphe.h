#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include "Arete.h"
#include "Sommet.h"
#include <iostream>
#include "svgfile.h"

class Graphe  //Les commentaires de chaques sous programme se trouvent dans le .cpp
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
		void centrProxi();
		void suppr_sommet(int sommet);
		void suppr_arete(int s1,int s2);
		void lecture_topo(std::string file_name);
		std::vector<int> Dijsktra(int Sdepart);
		std::vector<Sommet*> trouverDijstra(int numero);
		int trouverPoids(int first,  int last);
		int trouverEmplacement(int sommet, std::vector<Sommet*>Q);
		std::vector<std::pair<double,const Sommet*>> poidsSuccsTrie(const Sommet* debut)const;
		std::vector<std::string> couleur(int* choix, bool* norm);
		std::vector<std::vector<int>> DijsktraModif(int Sdepart, int Sarrivee);
		void centrInter();
		bool normalisation();
		void printpath(std::vector<int>& path);
		int isNotVisited(int x, std::vector<int>& path);
		void findpaths(int src, int dst, int v);
		std::vector<Sommet*> trouverSuccsIndice(int nb);
		bool connexite();
		void centrDegreArete();
		void centrVectPropreArete();
		std::vector<Arete*> trouverSuccsAretes(Arete* base)const;

        std::vector<Sommet*> getSommets()const;
        std::vector<Arete*> getAretes()const;
        std::string getFileName()const;

        int calculk_connexite();
        void sauvegarde_indice(std::string file_name);
    private:
        bool m_ori;

        int m_nb_arete;
        int m_nb_sommet;

        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::string m_fileName;
};

#endif // GRAPHE_H
