#include <iostream>
#include <fstream>
#include <sstream>
#include "Graphe.h"

//Jules 27/04/2020 V1 menu console Projet S1 ING2
void Affichage_menu()
{
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "           Commands list           Racourcie    " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "           > Charger_Topo <           > CT <    " << std::endl;
    std::cout << "           > Sauvgarder_Topo <        > ST <    " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "           > Charger_Pond <           > CP <    " << std::endl;
    std::cout << "           > Sauvgarder_Pond <        > SP <    " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "           > Afficher_svg <           > AS <    " << std::endl;
    std::cout << "           > Supprimer_arete <        > SA <    " << std::endl;
    std::cout << "           > Supprimer_sommet <       > SS <    " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "           > Calcul_Degre <           > CaD <   " << std::endl;
    std::cout << "           > Calcul_Vecteur <         > CaV <   " << std::endl;
    std::cout << "           > Calcul_Proximite <       > CaP <   " << std::endl;
    std::cout << "           > Calcul_Intermediarite <  > CaI <   " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "           > Exit <                   > Ext <   " << std::endl;
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

int demander_sommet(std::string phrase)
{
    int sommet = 0;
    std::cout << phrase << std::endl;
    std::cout << "> ";
    return sommet;
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
        if (saisie == "Exit" || saisie == "Ext")
        {
            exit = true;
        }
        else if (saisie == "Charger_Pond" || saisie == "CP" )
        {
            test.lecture_pond(charger_file("Nom du fichier Pond de chargement ?"));
        }
        else if (saisie == "Sauvgarder_Topo" || saisie == "ST" )
        {
            test.sauvegarde_topo(Demander_nom_fichier("Nom du fichier de sauvgarde Topo"));
        }
        else if (saisie == "Sauvgarder_Pond" || saisie == "SP")
        {
            test.sauvegarde_pond(Demander_nom_fichier("Nom du fichier de sauvgarde Pond"));
        }
        //-------------------------------------------------------------------------------------------------------
        else if (saisie == "Afficher_svg" || saisie == "AS")
        {
            std::cout << "Il sera seulement affiche les operations effectue avant cette commande " << std::endl;
            test.creation_svg();
        }
        else if (saisie == "Supprimer_arete" || saisie == "SA")
        {
            int s1;
            int s2;
            s1=demander_sommet("entré le numero de sommet 1 de l'arete");
            s2=demander_sommet("entré le numero de sommet 2 de l'arete");
            test.suppr_arete(s1,s2);
        }
        else if(saisie == "Supprimer_sommet" || saisie == "SS")
        {
            int sommet;
            sommet=demander_sommet("entré le numero de sommet 1 que vous voulez effacer");
            test.suppr_sommet(sommet);
        }
        //--------------------------------------------------------------------------------------------------------
        else if(saisie == "Calcul_Degre" || saisie == "CaD")
        {
            test.centrDegre();
        }
        else if(saisie == "Calcul_Vecteur" || saisie == "CaV")
        {
            test.centrVectPropre();
        }
        else if(saisie == "Calcul_Proximite" || saisie == "CaP")
        {
            test.centrProxi();
        }
        else if(saisie == "Calcul_Intermediarite" || saisie == "CaI")
        {

        }
        else
        {
            std::cout << "saisie invalide, veuillez recommencer ou comtacter le support" << std::endl;
        }


    }
    return 0;
}
