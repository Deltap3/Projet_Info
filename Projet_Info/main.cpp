#include <iostream>
#include <fstream>
#include <sstream>
#include "Graphe.h"

//Jules 27/04/2020 V1 menu console Projet S1 ING2
void Affichage_menu()
{
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "           Commands list           Racourcis    " << std::endl;
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
    std::cout << "           > Calcul_k-connexite <     > KC <    " << std::endl;
    std::cout << "           > Sauvgarder_Ind <         > SI <    " << std::endl;
    std::cout << "           > Connexite <              > CO <    " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "           > Exit <                   > Ext <   " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
}

//Fin affichage menu
//Jules 27/04/2020
std::string Demander_nom_fichier(std::string phrase) //Permet d'obtenir le nom du fichier txt que l'on veut charger
{
    std::string file_name;
    std::cout << phrase << std::endl;
    std::cout << "> ";
    std::cin >> file_name;
    return file_name;
}

//Jules 27/04/2020
std::string charger_file(std::string phrase) //Permet de charger un fichier et de retourner le nom du fichier charge
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

int demander_sommet(std::string phrase) //Permet de demander à l'utilisateur le numero d'un sommet et de renvoyer sa réponse
{
    int sommet = 0;
    std::cout << phrase << std::endl;
    std::cout << "> ";
    std::cin>>sommet;
    return sommet;
}

int main()
{
    Graphe* test = new Graphe(charger_file("Nom du fichier Topo de chargement ?")); //On charge un premier graphe
    bool exit = false;
    std::string saisie;
    //Boucle de menu
    while(exit == false)
    {
        Affichage_menu(); //On affiche le menu
        std::cout << "> " ;
        std::cin >> saisie; //On enregistre la saisie de l'utilisateur
        if (saisie == "Exit" || saisie == "Ext")
        {
            exit = true;
        }
        else if (saisie == "Charger_Topo" || saisie == "CT" ) //On charge un nouveau fichier topologique
        {
            delete test;
            test = new Graphe (charger_file("Nom du fichier Topo de chargement ?"));
        }
        else if (saisie == "Charger_Pond" || saisie == "CP" ) //On charge un nouveau fichier de ponderation
        {
            test->lecture_pond(charger_file("Nom du fichier Pond de chargement ?"));
        }
        else if (saisie == "Sauvgarder_Topo" || saisie == "ST" ) //On sauvegarde la topologie du graphe dans un fichier
        {
            test->sauvegarde_topo(Demander_nom_fichier("Nom du fichier de sauvgarde Topo"));
        }
        else if (saisie == "Sauvgarder_Pond" || saisie == "SP") //On sauvegarde la ponderation du graphe dans un fichier
        {
            test->sauvegarde_pond(Demander_nom_fichier("Nom du fichier de sauvgarde Pond"));
        }
        //-------------------------------------------------------------------------------------------------------
        else if (saisie == "Afficher_svg" || saisie == "AS") //On affiche le graphe dans un fichier SVG
        {
            std::cout << "Il sera seulement affiche les operations effectue avant cette commande " << std::endl;
            test->creation_svg();
        }
        else if (saisie == "Supprimer_arete" || saisie == "SA") //On demande deux sommets à l'utilisateur et on supprime l'arete qui es relies
        {
            int s1;
            int s2;
            s1=demander_sommet("entrer le numero de sommet 1 de l'arete");
            s2=demander_sommet("entrer le numero de sommet 2 de l'arete");
            test->suppr_arete(s1,s2);
        }
        else if(saisie == "Supprimer_sommet" || saisie == "SS") //On demande un sommet à l'utilisateur et on le supprime
        {
            int sommet;
            sommet=demander_sommet("entrer le numero du sommet que vous voulez effacer");
            test->suppr_sommet(sommet);
        }
        //--------------------------------------------------------------------------------------------------------
        else if(saisie == "Calcul_Degre" || saisie == "CaD") //On calcule l'indice de centralite de degre de chaque sommets
        {
            test->centrDegre();
        }
        else if(saisie == "Calcul_Vecteur" || saisie == "CaV") //On calcule l'indice de centralite de vecteur propre de chaque sommets
        {
            test->centrVectPropre();
        }
        else if(saisie == "Calcul_Proximite" || saisie == "CaP") //On calcule l'indice de centralite de proximite de chaque sommets
        {
            test->centrProxi();
        }
        else if(saisie == "Calcul_Intermediarite" || saisie == "CaI") //On calcule l'indice d'intermediarite de degre de chaque sommets
        {
            test->centrInter();
        }
        else if (saisie == "Sauvgarder_Ind" || saisie == "SI" ) //On sauvegarde tous les indices de centralite de chaque sommets
        {
            test->sauvegarde_indice(Demander_nom_fichier("Nom du fichier de sauvgarde Indice"));
        }
        //--------------------------------------------------------------------------------------------------------
        else if (saisie == "Calcul_k-connexite" || saisie == "KC" ) //On calcul la k-connexite du graphe
        {
            int k;
            k = test->calculk_connexite();
            std::cout<<"Le graphe est "<<k<<" connexe"<<std::endl;
        }
        else if (saisie == "Connexite" || saisie == "CO")
        {
            if(test->connexite())
                std::cout<<"Le graphe est connexe"<<std::endl;
            else
                std::cout<<"Le graphe n'est pas connexe"<<std::endl;
        }
        else //Si l'utlisateur saisi autre chose, on lui informe que sa saisie est invalide
        {
            std::cout << "saisie invalide, veuillez recommencer ou contacter le support" << std::endl;
        }
    }
    return 0;
}
