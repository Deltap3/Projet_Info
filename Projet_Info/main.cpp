#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    std::cout << "Hello world!" << std::endl;
    return 0;
}

//Jules 27/04/2020 V1 menu console Projet S1 ING2
void Affichage_menu()
{
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "                Commands list                   " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "          > @ID move valeur axis <              " << std::endl;
    std::cout << "             > @ID take object <                " << std::endl;
    std::cout << "            > @ID untake object <               " << std::endl;
    std::cout << "             > play script.txt <                " << std::endl;
    std::cout << "            > load filename.txt <               " << std::endl;
    std::cout << "                 > reload <                     " << std::endl;
    std::cout << "               > ids / noids <                  " << std::endl;
    std::cout << "            > rulers / norulers <               " << std::endl;
    std::cout << "           > anchors / noanchors <              " << std::endl;
    std::cout << "              > undo / do   <                   " << std::endl;
    std::cout << "                  > store <                     " << std::endl;
    std::cout << "                 > restore <                    " << std::endl;
    std::cout << "                  > exit <                      " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
}
// Fin menu console

//Jules 27/04/2020 V1 chargement_topo
void chargement_topo(std::string file_name)
{
    std::ifstream fichier{file_name}; //ouverture de fichier
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier";
    }
    else
    {
       std::string ligne_lu; //Variable de lecture
       int nb_ligne=0; //Variable numéro de ligne
       int nb_sommet=0; //Variable nombre de sommet
       int nb_arrete=0; //Variable nombre arrete
       while(getline(fichier, ligne_lu))
       {
           istringstream iss(ligne_lu);
           if (nb_ligne=0) //lecture ligne oriatation graph
           {
               iss>>; //0 si non orienté,1 si orienté
           }
           if (nb_ligne=1) //lecture ligne nb sommet
           {
               iss>>; //nb sommet
           }
           if (nb_ligne>1 && nb_ligne<(nb_sommet+2)) //lecture des sommets
           {
               iss>>; //numéro de sommet
               iss>>; //nom
               iss>>; //coord x
               iss>>; //coord y
           }
           if (nb_ligne==nb_sommet+2) //lecture nombre d'arrete
           {
               iss>>; //nb d'arrète
           }
           if(nb_ligne>(nb_sommet+2) && nb_ligne<(nb_sommet+nb_arrete+3)) //lecture des arrètes
           {
               iss>>; //numéro d'arrète
               iss>>; //extrémité 1
               iss>>; //extrémité 2
           }
           else
           {
               std::cout << "ERREUR: lecture du fichier";
           }

           ++nb_ligne; //incrémentation néméro de ligne


       }
    }
    return 0;
}
