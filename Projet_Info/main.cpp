#include <iostream>
#include <fstream>
#include <sstream>
#include "Graphe.h"

//Jules 27/04/2020 V1 menu console Projet S1 ING2
void Affichage_menu()
{
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "                Commands list                   " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "             > Charger_Topo <                   " << std::endl;
    std::cout << "             > Sauvgarder_Topo <                " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "             > Charger_Pond <                   " << std::endl;
    std::cout << "             > Sauvgarder_Pond <                " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "             > Afficher_svg <                   " << std::endl;
    std::cout << "             > Supprimer_arete <                " << std::endl;
    std::cout << "             > Supprimer_sommet <               " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "             > Exit <                           " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
}

//Fin affichage menu
std::string Demander_nom_fichier(std::string phrase)
{
    std::string file_name;
    std::cout << phrase << std::endl;
    std::cout << "> ";
    std::cin >> file_name;
    return file_name;
}

std::string charger_file(std::string phrase)
{
    std::string file_name;
    int indicateur_ouverture = 0;
    while(indicateur_ouverture == 0)
    {
        file_name = Demander_nom_fichier(phrase);
        std::ifstream fichier{file_name}; //ouverture de fichier lecture
        if (!fichier)
        {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier topo" << std::endl;
        }
        else
        {
            indicateur_ouverture = 1;
            fichier.close();
        }
    }

    return file_name;
}

int main()
{
    Graphe test(charger_file("Nom du fichier Topo de chargement ?"));
    bool exit = false;
    std::string saisie;
    //Boucle de menu
    while(exit == false)
    {
        Affichage_menu();
        std::cout << "> " ;
        std::cin >> saisie;
        if (saisie == "Exit")
        {
            exit = true;
        }
        else if (saisie == "Charger_Pond" )
        {
            test.lecture_pond(charger_file("Nom du fichier Pond de chargement ?"));
        }
        else if (saisie == "Sauvgarder_Topo" )
        {
            test.sauvegarde_topo(Demander_nom_fichier("Nom du fichier de sauvgarde Topo"));
        }
        else if (saisie == "Sauvgarder_Pond" )
        {
            test.sauvegarde_pond(Demander_nom_fichier("Nom du fichier de sauvgarde Pond"));
        }
        else if (saisie == "Afficher_svg" )
        {
            std::cout << "Il sera seulement affiche les operations effectue avant cette commande " << std::endl;
            test.creation_svg();
        }
    }
    /*Graphe test("graphe_etoile1_topo.txt");
    test.sauvegarde_topo("save.txt");
    test.lecture_pond("graphe_etoile1_pond.txt");
    test.sauvegarde_pond("save2.txt");
    test.centrDegre();
    test.creation_svg();
    test.centrVectPropre();*/
    return 0;
}
