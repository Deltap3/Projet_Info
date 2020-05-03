#include "Graphe.h"
#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <bits/stdc++.h>

//Pierre 27/04/2020
bool Graphe::getOri()const  //Getter de l'orientation
{
    return m_ori;
}

//Pierre 27/04/2020
int Graphe::getNbArete()const //Getter du nombre d'aretes total du graphe
{
    return m_nb_arete;
}

//Pierre 27/04/2020
void Graphe::setNbArete(int nb) //Setter du nombre d'aretes total du graphe
{
    m_nb_arete = nb;
}

//Pierre 27/04/2020
int Graphe::getNbSommet()const //Getter du nombre de sommets total du graphe
{
    return m_nb_sommet;
}

//Pierre 27/04/2020
void Graphe::setNbSommet(int nb) //Setter du nombre de sommets total du graphe
{
    m_nb_sommet = nb;
}

//Pierre 27/04/2020
std::vector<Sommet*> Graphe::getSommets()const //Getter du vecteur contenant tous les sommets du graphe
{
    return m_sommets;
}

//Pierre 27/04/2020
std::vector<Arete*> Graphe::getAretes()const //Getter du vecteur contenant toutes les aretes du graphe
{
    return m_aretes;
}

//Pierre 27/04/2020
std::string Graphe::getFileName()const //Getter du nom du fichier de topographie du graphe
{
    return m_fileName;
}

//Pierre 27/04/2020
void Graphe::creation_svg() //Permet de décalrer le fichier SVG avant de dessiner dedans
{
    Svgfile svgout;
    affichage_svg(svgout);
}

//Pierre 01/05/2020
bool Graphe::normalisation() //Permet de demander à l'utilisateur si il veux que les indices soient
{                            //normalises ou non
    std::string choix;
    bool encore;
    bool norm;
    std::cout<<"        Voulez vous que les indices soient normalises ?         "<<std::endl;
    std::cout<<"                            Oui                  > Oui <        "<<std::endl;
    std::cout<<"                            Non                  > Non <        "<<std::endl;
    std::cin>>choix;
    if(choix == "Oui" || choix == "oui")
        norm = true;
    else if(choix == "Non" || choix == "non")
        norm = false;
    else
        encore = normalisation();
    return norm;
}

//Pierre et Jules 30/04/2020
std::vector<std::string> Graphe::couleur(int* choix, bool* norm) //Permet de colorer les sommets en fonction de leurs indices
{
    *norm = normalisation(); //On demande à l'utilisateur s'il veux les indices normalises ou non
    int j = 0;
    std::vector<std::string> colorSommet(m_sommets.size(),"black"); //Ce vecteur contiendra toutes les couleurs que doit prendre chaque sommet
    float maxi = 0,mini = 1000000, k = 0;
    std::cout<<"        Quel indice voulez-vous afficher ?         "<<std::endl;
    std::cout<<"                Indice de Degre         > 0 <      "<<std::endl;
    std::cout<<"           Indice de Vecteur propre     > 1 <      "<<std::endl;
    std::cout<<"              Indice de Proximite       > 2 <      "<<std::endl;
    std::cout<<"            Indice d'intermedialite     > 3 <      "<<std::endl;
    std::cout<<"                Tous les indices        > 4 <      "<<std::endl;
    std::cout<<"> ";
    std::cin>>*choix;                          //Vecteur de couleurs regroupant notre degrade de couleurs allant du moins important au plus important
    std::vector<std::string> toutesCouleur = {"saddlebrown","maroon","firebrick","tomato","salmon","peachpuff","lightgreen","mediumseagreen","limegreen","forestgreen"};
    switch(*choix)
    {
    case 0 : //Indice de degré
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(*norm) //Si les indices sont normalises
            {
                if(m_sommets[i]->getIndiceDegre() > maxi)   //On trouve la valeurs maximale parmis tous les indices du graphe
                    maxi = m_sommets[i]->getIndiceDegre();
                if(m_sommets[i]->getIndiceDegre() < mini)   //et la valeur minimale
                    mini = m_sommets[i]->getIndiceDegre();
            }
            else //Si ils ne sont pas normalises
            {
                if(m_sommets[i]->getIndiceDegreNon() > maxi)
                    maxi = m_sommets[i]->getIndiceDegreNon();
                if(m_sommets[i]->getIndiceDegreNon() < mini)
                    mini = m_sommets[i]->getIndiceDegreNon();
            }
        }
        k = (maxi-mini)/10; //On a une gamme de 10 couleurs donc on cree une constante k
                            //afin de segmenter les differents indice en fonction de leur valeur
                            //par rapport aux autres indices
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
            {
                if(*norm) //Si les indices sont normalises
                {
                    if(m_sommets[i]->getIndiceDegre() > ((j*k) + mini - k*0.0000001)) //Si l'indice appartient au segment numero j
                        colorSommet[i] = toutesCouleur[j];  //Il obtient la couleur numero j de toutesCouleurs
                }
                else //Si ils ne sont pas normalises
                    if(m_sommets[i]->getIndiceDegreNon() > ((j*k) + mini - k*0.0000001))
                        colorSommet[i] = toutesCouleur[j];
            }

        break;
    case 1:  //Indice de vecteur (idem que l'indice precedent mais avec les indices de vecteur)
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getIndiceVect() > maxi)
                maxi = m_sommets[i]->getIndiceVect();
            if(m_sommets[i]->getIndiceVect() < mini)
                mini = m_sommets[i]->getIndiceVect();
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
            {
                if(m_sommets[i]->getIndiceVect() > ((j*k) + mini - k*0.0000001))
                    colorSommet[i] = toutesCouleur[j];
            }
        break;
    case 2:  //Indice de proximité (idem que l'indice precedent mais avec les indices de proximite)
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(*norm)
            {
                if(m_sommets[i]->getIndiceProxi() > maxi)
                    maxi = m_sommets[i]->getIndiceProxi();
                if(m_sommets[i]->getIndiceProxi() < mini)
                    mini = m_sommets[i]->getIndiceProxi();
            }
            else
            {
                if(m_sommets[i]->getIndiceProxiNon() > maxi)
                    maxi = m_sommets[i]->getIndiceProxiNon();
                if(m_sommets[i]->getIndiceProxiNon() < mini)
                    mini = m_sommets[i]->getIndiceProxiNon();
            }
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
            {
                if(*norm)
                {
                    if(m_sommets[i]->getIndiceProxi() > ((j*k) + mini - k*0.0000001))
                        colorSommet[i] = toutesCouleur[j];
                }
                else
                    if(m_sommets[i]->getIndiceProxiNon() > ((j*k) + mini - k*0.0000001))
                        colorSommet[i] = toutesCouleur[j];
            }
        break;
     case 3:  //Indice d'intermediarité (idem que l'indice precedent mais avec les indices d'intermediarite)
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(*norm)
            {
                if(m_sommets[i]->getIndiceInter() > maxi)
                    maxi = m_sommets[i]->getIndiceInter();
                if(m_sommets[i]->getIndiceInter() < mini)
                    mini = m_sommets[i]->getIndiceInter();
            }
            else
            {
                if(m_sommets[i]->getIndiceInterNon() > maxi)
                    maxi = m_sommets[i]->getIndiceInterNon();
                if(m_sommets[i]->getIndiceInterNon() < mini)
                    mini = m_sommets[i]->getIndiceInterNon();
            }
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
            {
                if(*norm)
                {
                    if(m_sommets[i]->getIndiceInter() > ((j*k) + mini - k*0.0000001))
                        colorSommet[i] = toutesCouleur[j];
                }
                else
                    if(m_sommets[i]->getIndiceInterNon() > ((j*k) + mini - k*0.0000001))
                        colorSommet[i] = toutesCouleur[j];
            }
        break;
    case 4 : //Tous les indices (Couleur de l'indice de degré)
        for(size_t i = 0; i < m_sommets.size(); ++i)
        {
            if(*norm)
            {
                if(m_sommets[i]->getIndiceDegre() > maxi)
                    maxi = m_sommets[i]->getIndiceDegre();
                if(m_sommets[i]->getIndiceDegre() < mini)
                    mini = m_sommets[i]->getIndiceDegre();
            }
            else
            {
                if(m_sommets[i]->getIndiceDegreNon() > maxi)
                    maxi = m_sommets[i]->getIndiceDegreNon();
                if(m_sommets[i]->getIndiceDegreNon() < mini)
                    mini = m_sommets[i]->getIndiceDegreNon();
            }
        }
        k = (maxi-mini)/10;
        for(size_t i = 0; i < m_sommets.size(); ++i)
            for(int j = 0; j < 10; ++j)
            {
                if(*norm)
                {
                    if(m_sommets[i]->getIndiceDegre() > ((j*k) + mini - k*0.0000001))
                        colorSommet[i] = toutesCouleur[j];
                }
                else
                    if(m_sommets[i]->getIndiceDegreNon() > ((j*k) + mini - k*0.0000001))
                        colorSommet[i] = toutesCouleur[j];
            }

        break;
    default:
        break;
    }
    return colorSommet; //On retourne le vecteur contenant les couleurs attribues a chaque sommets
}

//Pierre 29-30/04/2020
void Graphe::affichage_svg(Svgfile& svgout)   //S'occupe de toute la partie SVG du programme
{
    svgout.addGrid();
    int choix = 0; //Permet à l'utilisateur de choisir quel indice il veut afficher
    bool norm;  //Permet de savoir si les indices affiches doivent etre normalises ou non
    float fleche_x = 0;
    float fleche_y = 0;
    std::vector<std::string> colorSommet = couleur(&choix,&norm);  //L'utilisateur choisit si les indices seront normalises ou non ainsi que l'indice qu'il souhaite afficher
    std::vector<std::string> toutesCouleur = {"saddlebrown","maroon","firebrick","tomato","salmon","peachpuff","lightgreen","mediumseagreen","limegreen","forestgreen"};
    //Affiche la legende des couleurs des sommets
    for(size_t i = 0; i < toutesCouleur.size();++i)
        svgout.addTriangle(50*i,25,50*i,50,50*(i+1),50,50*(i+1),25,toutesCouleur[i],0,"black");
    svgout.addText(20,20,"Pas Important","black");
    svgout.addText(430,20,"Important","black");
    for(int j = 0; j < m_nb_arete; ++j)  //On affiche d'abord les aretes
    {
        if(m_ori)  //Si il est orinte on cree une fleche
        {
            if(m_aretes[j]->getExtr2()->getCoord_x() < m_aretes[j]->getExtr1()->getCoord_x()) //Si le depart de l'arete est plus haut que l'arrivee en x
            {
                fleche_x = (m_aretes[j]->getExtr2()->getCoord_x())+(1/2*(m_aretes[j]->getExtr1()->getCoord_x() - m_aretes[j]->getExtr2()->getCoord_x()));
                fleche_x = ((fleche_x) + (5/6*(m_aretes[j]->getExtr1()->getCoord_x() - fleche_x)*100))*100;
            }
            else if(m_aretes[j]->getExtr1()->getCoord_x() < m_aretes[j]->getExtr2()->getCoord_x()) //Si le depart de l'arete est plus bas que l'arrivee en x
            {
                fleche_x = (m_aretes[j]->getExtr1()->getCoord_x())+(1/2*(m_aretes[j]->getExtr2()->getCoord_x() - m_aretes[j]->getExtr1()->getCoord_x()));
                fleche_x = ((fleche_x) + (5/6*(m_aretes[j]->getExtr2()->getCoord_x() - fleche_x)*100))*100;
            }
            else if(m_aretes[j]->getExtr1()->getCoord_x() == m_aretes[j]->getExtr2()->getCoord_x()) //Si le depart de l'arete est egal a l'arrivee en x
                fleche_x = m_aretes[j]->getExtr1()->getCoord_x()*100;
            if(m_aretes[j]->getExtr2()->getCoord_y() < m_aretes[j]->getExtr1()->getCoord_y()) //Si le depart de l'arete est plus haut que l'arrivee en y
            {
                fleche_y = (m_aretes[j]->getExtr2()->getCoord_y())+(1/2*(m_aretes[j]->getExtr1()->getCoord_y() - m_aretes[j]->getExtr2()->getCoord_y()));
                fleche_y = ((fleche_y) + (5/6*(m_aretes[j]->getExtr1()->getCoord_y() - fleche_y)*100))*100;
            }
            else if(m_aretes[j]->getExtr1()->getCoord_y() < m_aretes[j]->getExtr2()->getCoord_y()) //Si le depart de l'arete est plus bas que l'arrivee en y
            {
                fleche_y = (m_aretes[j]->getExtr1()->getCoord_y())+(1/2*(m_aretes[j]->getExtr2()->getCoord_y() - m_aretes[j]->getExtr1()->getCoord_y()));
                fleche_y = ((fleche_y) + (5/6*(m_aretes[j]->getExtr2()->getCoord_y() - fleche_y)*100))*100;
            }
            else if(m_aretes[j]->getExtr1()->getCoord_y() == m_aretes[j]->getExtr2()->getCoord_y()) //Si le depart de l'arete est egal a l'arrivee en y
                fleche_y = m_aretes[j]->getExtr1()->getCoord_y()*100;
            //On dessine le triangle
            svgout.addTriangle(m_aretes[j]->getExtr2()->getCoord_x()*100,m_aretes[j]->getExtr2()->getCoord_y()*100,fleche_x-5,fleche_y+5,fleche_x+5,fleche_y-5,"gray",1,"black");
        }
        //On dessine les aretes et on ecrit leur poids
        svgout.addLine(m_aretes[j]->getExtr1()->getCoord_x()*100,m_aretes[j]->getExtr1()->getCoord_y()*100,m_aretes[j]->getExtr2()->getCoord_x()*100,m_aretes[j]->getExtr2()->getCoord_y()*100,"black");
        svgout.addText((m_aretes[j]->getExtr1()->getCoord_x()*100+m_aretes[j]->getExtr2()->getCoord_x()*100)/2,(m_aretes[j]->getExtr1()->getCoord_y()*100+m_aretes[j]->getExtr2()->getCoord_y()*100)/2,m_aretes[j]->getPoids(),"black");
    }
    for(int i = 0; i < m_nb_sommet; ++i) //On affiche ensuite les sommets
    {   //On dessine tous les sommets et on marque leur nom
        svgout.addDisk(m_sommets[i]->getCoord_x()*100,m_sommets[i]->getCoord_y()*100,15,colorSommet[i]);  //On affiche le sommet
        svgout.addText((m_sommets[i]->getCoord_x()*100)-5,(m_sommets[i]->getCoord_y()*100)+5,m_sommets[i]->getNom(),"mediumblue"); //Et son nom
        switch(choix) //On marque ensuite l'indice demandé
        {
        case 0 : //Indice de degré
            if(norm)
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceDegre(),"black");
            else
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceDegreNon(),"black");
            break;
        case 1:  //Indice de vecteur propre
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceVect(),"black");
            break;
        case 2:  //Indice de proximité
            if(norm)
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceProxi(),"black");
            else
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceProxiNon(),"black");
            break;
        case 3:  //Indice di'ntermédiarité
            if(norm)
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceInter(),"black");
            else
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceInterNon(),"black");
            break;
        case 4:  //Tous les indices
            if(norm)
            {
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceDegre(),"black");
                svgout.addText((m_sommets[i]->getCoord_x()*100)+20,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getIndiceVect(),"black");
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)+20,m_sommets[i]->getIndiceProxi(),"black");
                svgout.addText((m_sommets[i]->getCoord_x()*100)-65,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getIndiceInter(),"black");
            }
            else
            {
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)-20,m_sommets[i]->getIndiceDegreNon(),"black");
                svgout.addText((m_sommets[i]->getCoord_x()*100)+20,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getIndiceVect(),"black");
                svgout.addText(m_sommets[i]->getCoord_x()*100,(m_sommets[i]->getCoord_y()*100)+20,m_sommets[i]->getIndiceProxiNon(),"black");
                svgout.addText((m_sommets[i]->getCoord_x()*100)-65,m_sommets[i]->getCoord_y()*100,m_sommets[i]->getIndiceInterNon(),"black");
            }
        default:
            break;
        }

    }
}

//Pierre 27/04/2020
Sommet* Graphe::trouverSommet(int num)
{
    for(size_t i = 0; i < m_sommets.size();++i)
        if(m_sommets[i]->getNumero() == num)
            return m_sommets[i];
}

//Jules 27/04/2020
Graphe::Graphe(std::string file_name)
{
    std::ifstream fichier{file_name}; //ouverture de fichier lecture
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier topo";
    }
    else
    {
       std::string ligne_lu; //Variable de lecture
       int nb_ligne=0; //Variable numero de ligne
       int nb_sommet=0; //Variable nombre de sommet
       int nb_arete=0; //Variable nombre arrete
       while(getline(fichier, ligne_lu))
       {
           std::istringstream iss{ligne_lu};
           if (nb_ligne==0) //lecture ligne oriatation graph
           {
               iss>>m_ori; //0 si non oriente,1 si oriente
           }
           else if (nb_ligne==1) //lecture ligne nb sommet
           {
               iss>>nb_sommet; //nb sommet
               m_nb_sommet = nb_sommet;
           }
           else if (nb_ligne>1 && nb_ligne<(nb_sommet+2)) //lecture des sommets
           {
               Sommet* sommet = new Sommet();
               int num = 0,x = 0,y = 0;
               std::string nom;
               int i = m_sommets.size();
               m_sommets.push_back(sommet);
               iss>>num; //numero de sommet
               m_sommets[i]->setNumero(num);
               iss>>nom; //nom
               m_sommets[i]->setNom(nom);
               iss>>x; //coord x
               m_sommets[i]->setCoord_x(x);
               iss>>y; //coord y
               m_sommets[i]->setCoord_y(y);
           }
           else if (nb_ligne==nb_sommet+2) //lecture nombre d'arrete
           {
               iss>>nb_arete; //nb d'arrete
               m_nb_arete = nb_arete;
           }
           else if(nb_ligne>(nb_sommet+2) && nb_ligne<(nb_sommet+nb_arete+3)) //lecture des arretes
           {
               Arete* arete = new Arete();
               int num,ex1,ex2;
               int i = m_aretes.size();
               m_aretes.push_back(arete);
               iss>>num; //numero d'arrete
               m_aretes[i]->setNum(num);
               iss>>ex1; //extremite 1
               m_aretes[i]->setExtr1(trouverSommet(ex1));
               iss>>ex2; //extremite 2
               m_aretes[i]->setExtr2(trouverSommet(ex2));
           }
           else
           {
               std::cout << "ERREUR: lecture du fichier trop de sommets ou arrète par rapport au nombre anoncé topo"<<std::endl;
           }

           ++nb_ligne; //incrementation numero de ligne
       }
    }
}

//Jules 27/04/2020
void Graphe::lecture_topo(std::string file_name)
{
  std::ifstream fichier{file_name}; //ouverture de fichier lecture
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier topo";
    }
    else
    {
       std::string ligne_lu; //Variable de lecture
       int nb_ligne=0; //Variable numero de ligne
       int nb_sommet=0; //Variable nombre de sommet
       int nb_arete=0; //Variable nombre arrete
       while(getline(fichier, ligne_lu))
       {
           std::istringstream iss{ligne_lu};
           if (nb_ligne==0) //lecture ligne oriatation graph
           {
               iss>>m_ori; //0 si non oriente,1 si oriente
           }
           else if (nb_ligne==1) //lecture ligne nb sommet
           {
               iss>>nb_sommet; //nb sommet
               m_nb_sommet = nb_sommet;
           }
           else if (nb_ligne>1 && nb_ligne<(nb_sommet+2)) //lecture des sommets
           {
               Sommet* sommet = new Sommet();
               int num = 0,x = 0,y = 0;
               std::string nom;
               int i = m_sommets.size();
               m_sommets.push_back(sommet);
               iss>>num; //numero de sommet
               m_sommets[i]->setNumero(num);
               iss>>nom; //nom
               m_sommets[i]->setNom(nom);
               iss>>x; //coord x
               m_sommets[i]->setCoord_x(x);
               iss>>y; //coord y
               m_sommets[i]->setCoord_y(y);
           }
           else if (nb_ligne==nb_sommet+2) //lecture nombre d'arrete
           {
               iss>>nb_arete; //nb d'arrete
               m_nb_arete = nb_arete;
           }
           else if(nb_ligne>(nb_sommet+2) && nb_ligne<(nb_sommet+nb_arete+3)) //lecture des arretes
           {
               Arete* arete = new Arete();
               int num,ex1,ex2;
               int i = m_aretes.size();
               m_aretes.push_back(arete);
               iss>>num; //numero d'arrete
               m_aretes[i]->setNum(num);
               iss>>ex1; //extremite 1
               m_aretes[i]->setExtr1(trouverSommet(ex1));
               iss>>ex2; //extremite 2
               m_aretes[i]->setExtr2(trouverSommet(ex2));
           }
           else
           {
               std::cout << "ERREUR: lecture du fichier trop de sommets ou arrète par rapport au nombre anoncé topo"<<std::endl;
           }

           ++nb_ligne; //incrementation numero de ligne
       }

    }
}

//Jules 27/04/2020
void Graphe::sauvegarde_topo(std::string file_name)
{
    std::ofstream fichier { file_name }; //ouverture fichier ecriture
    if (!fichier)  //Si on n'arrive pas ouvrir le fichier on affiche un message d'erreur
    {
        std::cout << "ERREUR: sauvegarde du fichier topo" << std::endl;
    }
    else //Sinon, on ecrit les donnees dans le fichier
    {
        fichier << m_ori << std::endl; //On ecrit l'orientation du graphe
        fichier << m_nb_sommet<<std::endl; //Son nombre de sommets
        for (int i = 0; i < m_nb_sommet; ++i) //Le numero, le nom et les coordonnees de chaque sommets
        {
            fichier << m_sommets[i]->getNumero() << " " << m_sommets[i]->getNom() << " " << m_sommets[i]->getCoord_x() << " " << m_sommets[i]->getCoord_y() << std::endl;
        }
        fichier << m_nb_arete <<std::endl; //Le nombre d'aretes
        for (int j = 0; j < m_nb_arete; ++j) //Le numero de l'arete et des sommets à ces deux extremites
        {
            fichier << m_aretes[j]->getNum() << " " << m_aretes[j]->getExtr1()->getNumero() << " " << m_aretes[j]->getExtr2()->getNumero() << std::endl;
        }
    }
}

//Jules 27/04/2020
void Graphe::lecture_pond(std::string file_name)
{
    #include <iostream>
    #include <fstream>
    std::ifstream fichier{file_name}; //ouverture de fichier lecture
    if (!fichier)
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier topo";
    }
    else
    {
        std::string ligne_lu; //Variable de lecture
        int nb_ligne=0; //Variable numero de ligne
        int nb_arete=0; //Variable nombre arrete
        while(getline(fichier, ligne_lu))
        {
            std::istringstream iss{ligne_lu};
            if (nb_ligne==0) //lecture ligne nb arrète
            {
               iss>>nb_arete; //nb d'arrete (deja sauvegarde)
               if (nb_arete != m_nb_arete)
               {
                   std::cout << "ERREUR: Le nombre d'arete dans topo est different que dans pond" << std::endl;
               }
            }
            else if (nb_ligne>0 && nb_ligne<(nb_arete+1))
            {
                int num=0;
                float pond=0;
                iss>>num; //Numeros arete (deja sauvgarde)
                iss>>pond;//Lecture poids
                m_aretes[num]->setPoids(pond);
            }
            else
            {
                std::cout << "ERREUR: lecture du fichier trop d'arrete par rapport au nombre annonce pond"<<std::endl;
            }
            ++nb_ligne;
        }
    }

}

//Jules 27/04/2020
void Graphe::sauvegarde_pond(std::string file_name)
{
    std::ofstream fichier {file_name}; //ouverture fichier ecriture
    if (!fichier)
    {
        std::cout << "ERREUR: sauvegarde du fichier pond" << std::endl;
    }
    else
    {
        fichier << m_nb_arete << std::endl;
        for (int i = 0; i < m_nb_arete; ++i)
        {
            fichier << m_aretes[i]->getNum() << " " << m_aretes[i]->getPoids() << std::endl;
        }

    }
}

//Destructeur du graphe
Graphe::~Graphe()
{

}

//Pierre 27/04/2020 modifie par Jules le 30/04/2020
void Graphe::centrDegre() //Permet de calculer l'indice de centralite de degre de tous les sommets
{
    std::vector<float> indice;
    std::vector<float> somme;
    std::string choix;    //Choix de l'utilisateur
    int reponse_valide=0; //Variable servant au blindage du choix de l'utilisateur
    bool norm = normalisation();
    if (m_ori==1)
    {
        while (reponse_valide==0) //Blindage
        {
            std::cout << "Degre d'arrivee > Arr < ou de depart > Dep < ?" << std::endl;
            std::cout << "> ";
            std::cin >> choix;
            if (choix=="Arr" || choix=="Dep")
            {
                reponse_valide=1;
            }
            else
            {
                std::cout << "ERREUR: reponse invalide" << std::endl;
            }
        }
    }
    for(size_t i = 0; i < m_sommets.size();++i) //Pour chaque sommets
    {
        somme.push_back(0);
        indice.push_back(0);
        if (m_ori==0)       //Si le graphe n'est pas oriente
        {
            for(size_t j = 0; j < m_aretes.size();++j)
            {
                if(m_aretes[j]->getExtr1()->getNumero() == m_sommets[i]->getNumero() || m_aretes[j]->getExtr2()->getNumero() == m_sommets[i]->getNumero())
                {
                    somme[i] = somme[i]+1; //On trouve le nombre de successeurs de ce sommet
                }
            }
        }
        else //Si le graphe est oriente
        {
            if (choix=="Dep") //Si l'utilisateur a choisit les degres de depart
            {
                for(size_t j = 0; j < m_aretes.size();++j)
                {
                    if(m_aretes[j]->getExtr1()->getNumero() == m_sommets[i]->getNumero())
                    {
                        somme[i] = somme[i]+1; //On trouve le nombre de successeurs de ce sommet
                    }
                }
            }
            if (choix=="Arr") //Si l'utilisateur a choisit les degres de depart
            {
                for(size_t j = 0; j < m_aretes.size();++j)
                {
                    if(m_aretes[j]->getExtr2()->getNumero() == m_sommets[i]->getNumero())
                    {
                        somme[i] = somme[i]+1; //On trouve le nombre de predecesseurs de ce sommet
                    }
                }
            }
        }
        m_sommets[i]->setIndiceDegre(somme[i]/(m_nb_sommet-1)); //On rentre ces indices dans les donnees de notre graphe
        m_sommets[i]->setIndiceDegreNon(somme[i]);
    }
    //affichage en console
    if(norm)
    {
        std::cout << "Indice de centralite de Degre normalise" << std::endl;
        for(size_t i =0; i<m_sommets.size();++i)
            std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceDegre()<<std::endl;
    }
    else
    {
        std::cout << "Indice de centralite de Degre" << std::endl;
        for(size_t i =0; i<m_sommets.size();++i)
            std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceDegreNon()<<std::endl;
    }

}

//Pierre 28/04/2020
std::vector<Sommet*> Graphe::trouverSuccs(Sommet* base)const //Permet de retourner un vecteur de tous les successeurs d'un sommet
{
    std::vector<Sommet*> succs;
    for(size_t i = 0; i < m_aretes.size(); ++i)
    {
        if(!m_ori)  //Si le graphe n'est pas oriente
            if(m_aretes[i]->getExtr1()->getNumero() == base->getNumero())
                succs.push_back(m_aretes[i]->getExtr2());
        if(m_aretes[i]->getExtr2()->getNumero() == base->getNumero())
            succs.push_back(m_aretes[i]->getExtr1());
    }
    return succs;
}

//Pierre 28/04/2020
void Graphe::centrVectPropre() //Permet de calculer l'indice de centralite de vecteur propre de tous les sommets
{
    std::vector<float> indice;
    std::vector<float> csi;
    float lambda;
    float precedent;
    float somme;
    float difference;
    std::vector<Sommet*>succs;
    for(size_t i = 0; i < m_sommets.size();++i) //Initialisation de toutes les donnees
    {
        somme = 0;
        lambda = 0;
        precedent= 0;
        csi.push_back(0);
        indice.push_back(1);
        m_sommets[i]->setIndiceVect(1);
    }
    do
    {
        precedent = lambda; //On retiens la valeure precedente de lambda pour pouvoir connaitre sa variation
        for(size_t i = 0; i < m_sommets.size();++i)
            csi[i] = 0;
        somme = 0;
        //Calcul Indice Voisins
        for(size_t i = 0; i < m_sommets.size();++i)
        {
            succs = trouverSuccs(m_sommets[i]);
            for(size_t j = 0; j < succs.size();++j)
                csi[i] = csi[i] + succs[j]->getIndiceVect();
        }
        //Calcul Lambda
        for(size_t i = 0; i < m_sommets.size();++i)
        {
            somme = somme + (csi[i]*csi[i]);
        }

        lambda = sqrt(somme);
        //Calcul Indice Vecteur
        for(size_t i = 0; i < m_sommets.size();++i)
        {
            indice[i] = csi[i]/lambda;
            m_sommets[i]->setIndiceVect(indice[i]);
        }
        if(lambda-precedent>0)
            difference = lambda-precedent; //On calcul la variation de lambda
        else
            difference = -(lambda-precedent);
    }while(difference>0.2);
    //affichage en console
    std::cout << "Indice de centralite de Vecteur propre normalise"<<std::endl<<"(il n'existe pas d'indice non normalise pour la centralite de vecteur propre)"<< std::endl;
    for (size_t i =0; i<m_sommets.size();++i)
        std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceVect()<<std::endl;
}

//Jules 29/04/2020
void Graphe::suppr_arete(int s1,int s2)
{
    std::vector<float>avant_indices {0,0,0,0};
    std::vector<std::vector<float>> avant;
    for (int i =0; i < m_sommets.size();++i)
    {
        std::cout<<"Sommet : "<<m_sommets[i]->getNumero()<<"  Degre  "<<m_sommets[i]->getIndiceDegre()<<"  Vecteur  "<<m_sommets[i]->getIndiceVect()<<"  Proximite  "<<m_sommets[i]->getIndiceProxi()<<"  Intermediarite  "<<m_sommets[i]->getIndiceDegre()<<std::endl;
        avant_indices[0] = m_sommets[i]->getIndiceDegre();
        avant_indices[1] = m_sommets[i]->getIndiceVect();
        avant_indices[2] = m_sommets[i]->getIndiceProxi();
        avant_indices[3] = m_sommets[i]->getIndiceInter();
        avant.push_back(avant_indices);
    }
            int indicateur_reusite = 0;
    for (int i =0; i < m_aretes.size();++i)// parcours de toutes les arretes
    {
        if((m_aretes[i]->getExtr1()->getNumero() == s1 && m_aretes[i]->getExtr2()->getNumero() == s2) || (m_aretes[i]->getExtr1()->getNumero() == s2 && m_aretes[i]->getExtr2()->getNumero() == s1))
        { // on teste le sens s1 s2 et s2 s1
            delete m_aretes[i]; //Degagement de la mémoire supression de l'objet
            m_aretes.erase(m_aretes.begin()+i); //Supression dans le vecteur dans graph
            m_nb_arete=m_nb_arete-1;
            indicateur_reusite = 1;
        }
    }
    if (indicateur_reusite == 0) //Numéros de sommet invalide
    {
        std::cout << "ERREUR: numero de sommet invalide" << std::endl;
    }
    this->centrDegre();
    this->centrVectPropre();
    this->centrProxi();
    //this->centrInter();
    for (int i =0; i < m_sommets.size();++i)
    {
        std::cout<<"Sommet : "<<m_sommets[i]->getNumero()<<" Nouveau Degre  "<<m_sommets[i]->getIndiceDegre()<<" Nouveau Vecteur  "<<m_sommets[i]->getIndiceVect()<<" Nouveau Proximite  "<<m_sommets[i]->getIndiceProxi()<<" Nouveau Intermediarite  "<<m_sommets[i]->getIndiceDegre()<<std::endl;
        std::cout<<"Sommet : "<<m_sommets[i]->getNumero() - avant[i][0]<<" Difference Degre  "<<m_sommets[i]->getIndiceDegre() - avant[i][1]<<" Difference Vecteur  "<<m_sommets[i]->getIndiceVect() - avant[i][2]<<" Difference Proximite  "<<m_sommets[i]->getIndiceProxi() - avant[i][3]<<" Difference Intermediarite  "<<m_sommets[i]->getIndiceDegre()<<std::endl;
    }
}

//Jules 29/04/2020
void Graphe::suppr_sommet(int sommet)
{
    std::vector<float>avant_indices {0,0,0,0};
    std::vector<std::vector<float>> avant;
    for (int i =0; i < m_sommets.size();++i)
    {
        std::cout<<"Sommet : "<<m_sommets[i]->getNumero()<<"  Degre  "<<m_sommets[i]->getIndiceDegre()<<"  Vecteur  "<<m_sommets[i]->getIndiceVect()<<"  Proximite  "<<m_sommets[i]->getIndiceProxi()<<"  Intermediarite  "<<m_sommets[i]->getIndiceDegre()<<std::endl;
        avant_indices[0] = m_sommets[i]->getIndiceDegre();
        avant_indices[1] = m_sommets[i]->getIndiceVect();
        avant_indices[2] = m_sommets[i]->getIndiceProxi();
        avant_indices[3] = m_sommets[i]->getIndiceInter();
        avant.push_back(avant_indices);
    }
    int indicateur_reussite = 0;
    for (int i =0; i < m_sommets.size();++i) //parcours de tous les sommets
    {
        if (sommet == m_sommets[i]->getNumero())
        {
            for (int j = 0; j < m_aretes.size();++j)
            {
                if((m_aretes[j]->getExtr1()->getNumero()== sommet) || (m_aretes[j]->getExtr2()->getNumero()==sommet))
                {
                    suppr_arete(m_aretes[j]->getExtr1()->getNumero(),m_aretes[j]->getExtr2()->getNumero());
                    --j; //on delete un élément du vecteur donc toutes les positions du vecteur sont décalées
                }
            }
            delete m_sommets[i]; //Degagement de la mémoire supression de l'objet
            m_sommets.erase(m_sommets.begin()+i); //Supression dans le vecteur dans graph
            m_nb_sommet=m_nb_sommet-1;
            indicateur_reussite = 1;
        }
    }
    if (indicateur_reussite == 0) //Numéros de sommet invalide
    {
        std::cout << "ERREUR: numero de sommet invalide" << std::endl;
    }
    this->centrDegre();
    this->centrVectPropre();
    this->centrProxi();
    this->centrInter();
    for (int i =0; i < m_sommets.size();++i)
        std::cout<<"Sommet : "<<m_sommets[i]->getNumero()<<"  Degre  "<<m_sommets[i]->getIndiceDegre()<<"  Vecteur  "<<m_sommets[i]->getIndiceVect()<<"  Proximite  "<<m_sommets[i]->getIndiceProxi()<<"  Intermediarite  "<<m_sommets[i]->getIndiceDegre()<<std::endl;
}

//Algorithme Dijsktra aide TP3 solution 2 de Mme PALASI
std::vector<int> Graphe::Dijsktra(int Sdepart)
{
    auto cmp = [](std::pair<double,const Sommet*> p1, std::pair<double,const Sommet*> p2)
    {
        return p2.second<p1.second;
    };
    //(Aide TP2 et TP3 Mme PALASI
    std::priority_queue<std::pair<double,const Sommet*>,std::vector<std::pair<double,const Sommet*>>,decltype(cmp)> file(cmp);
    std::vector<int> marquage(m_sommets.size(),0);
    std::vector<int> predecesseur(m_sommets.size(),-1);
    std::vector<int> distance(m_sommets.size(),-1);
    file.push({0,m_sommets[Sdepart]});
    distance[Sdepart] = 0;
    std::pair<double,const Sommet*> premier;
    while(!file.empty())
    {
        premier = file.top();
        file.pop();
        while((!file.empty()) && (marquage[premier.second->getNumero()]))
        {
            premier = file.top();
            file.pop();
        }
        for(auto succs : poidsSuccsTrie(premier.second))
        {
            if((marquage[succs.second->getNumero()] == 0) && (distance[premier.second->getNumero()] + succs.first < distance[succs.second->getNumero()]) || (distance[succs.second->getNumero()] == -1))
            {
                distance[succs.second->getNumero()] = distance[premier.second->getNumero()] + succs.first;
                predecesseur[succs.second->getNumero()] = premier.second->getNumero();
                file.push({distance[succs.second->getNumero()],succs.second});
            }
        }
    }
    return distance;
}

//Pierre 29/04/2020
std::vector<std::pair<double,const Sommet*>> Graphe::poidsSuccsTrie(const Sommet* debut)const
{  //Permet de retrouner un vecteur de pair contenant le sommet et le poids pour y aller trie par ordre croissant de tous les successeurs d'un sommet
    std::vector<std::pair<double,const Sommet*>>poidsSuccs;
    for(size_t i = 0; i < m_aretes.size(); ++i)
    {
        if(m_aretes[i]->getExtr1()->getNumero() == debut->getNumero())
            poidsSuccs.push_back(std::make_pair(m_aretes[i]->getPoids(),m_aretes[i]->getExtr2()));
        else if(m_aretes[i]->getExtr2()->getNumero() == debut->getNumero())
            poidsSuccs.push_back(std::make_pair(m_aretes[i]->getPoids(),m_aretes[i]->getExtr1()));
    }
    std::sort(poidsSuccs.begin(),poidsSuccs.end());
    return poidsSuccs;
}

//Pierre 29/04/2020
void Graphe::centrProxi() //Permet de calculer l'indice de centralite de proximite de tous les sommets
{
    std::vector<int> resultat(m_sommets.size(),0);
    float somme = 0;
    bool norm = normalisation();
    for(size_t i = 0; i < m_sommets.size(); ++i)
    {
        resultat = Dijsktra(i);
        for(size_t j = 0; j < resultat.size(); ++j)
            somme = somme + resultat[j];
        m_sommets[i]->setIndiceProxi((m_sommets.size()-1)/(somme));
        m_sommets[i]->setIndiceProxiNon(1/somme);
        somme = 0;
    }
    //affichage en console
    if(norm)
    {
        std::cout << "Indice de centralite de Proximite normalise" << std::endl;
        for (size_t i =0; i<m_sommets.size();++i)
            std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceProxi()<<std::endl;
    }
    else
    {
        std::cout << "Indice de centralite de Proximite" << std::endl;
        for (size_t i =0; i<m_sommets.size();++i)
            std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceProxiNon()<<std::endl;
    }
}

//Jules 29/04/2020
void Graphe::sauvegarde_indice(std::string file_name)
{
    std::ofstream fichier {file_name}; //ouverture fichier ecriture
    if (!fichier)
    {
        std::cout << "ERREUR: sauvegarde du fichier Indice" << std::endl;
    }
    else
    {
        fichier << "(Num Deg Vec Pro Int) Normalise" << std::endl;
        for (int i = 0; i < m_nb_sommet; ++i)
            fichier << m_sommets[i]->getNumero() << "   " << m_sommets[i]->getIndiceDegre()<< "   " << m_sommets[i]->getIndiceVect()<< "   " << m_sommets[i]->getIndiceProxi()<< "   " << m_sommets[i]->getIndiceDegre() << std::endl;
        fichier << "Num Deg Vec Pro Int" << std::endl;
        for (int i = 0; i < m_nb_sommet; ++i)
            fichier << m_sommets[i]->getNumero() << "   " << m_sommets[i]->getIndiceDegreNon()<< "   " << m_sommets[i]->getIndiceVect()<< "   " << m_sommets[i]->getIndiceProxiNon()<< "   " << m_sommets[i]->getIndiceDegreNon() << std::endl;

    }
}

//Pierre 30/04/2020
std::vector<std::vector<int>> Graphe::DijsktraModif(int Sdepart, int Sarrivee) //Dijkstra modifie afin de pouvoir realiser l'indice d'intermediarite
{
    auto cmp = [](std::pair<double,const Sommet*> p1, std::pair<double,const Sommet*> p2)
    {
        return p2.second<p1.second;
    };
    //(Aide TP2 et TP3 Mme PALASI modifié
    std::priority_queue<std::pair<double,const Sommet*>,std::vector<std::pair<double,const Sommet*>>,decltype(cmp)> file(cmp);
    std::vector<int> marquage(m_sommets.size(),0);
    std::vector<int> predecesseur(m_sommets.size(),-1);
    std::vector<std::vector<int>> resultat;
    std::vector<int> distance(m_sommets.size(),-1);
    file.push({0,m_sommets[Sdepart]});
    distance[Sdepart] = 0;
    std::pair<double,const Sommet*> premier;
    while((!file.empty()) || (marquage[Sarrivee] == 0))
    {
        premier = file.top();
        file.pop();
        while((!file.empty()) && (marquage[premier.second->getNumero()] == 1))
        {
            premier = file.top();
            file.pop();
        }
        marquage[premier.second->getNumero()] = 1;
        for(auto succs : poidsSuccsTrie(premier.second))
        {
            if((marquage[succs.second->getNumero()] == 0))
            {
                if(((distance[premier.second->getNumero()] + succs.first) == distance[succs.second->getNumero()]))
                    resultat.push_back(predecesseur);
                if((distance[premier.second->getNumero()] + succs.first < distance[succs.second->getNumero()]) || (distance[succs.second->getNumero()] == -1))
                {
                    distance[succs.second->getNumero()] = distance[premier.second->getNumero()] + succs.first;
                    predecesseur[succs.second->getNumero()] = premier.second->getNumero();
                    if((distance[succs.second->getNumero()] != -1))
                        resultat.push_back(predecesseur);
                    file.push({distance[succs.second->getNumero()],succs.second});
                }
            }
        }
    }
    return resultat;
}

//Pierre 30/04/2020
void Graphe::centrInter() //Permet de calculer l'indice de centralite d'intermedirite de tous les sommets
{
    //Initialisation
    float somme = 0, n_pcc = 0, n_pcc_i = 0;
    bool norm = normalisation();
    std::vector<std::vector<int>> touspcc;
    std::vector<int>temp(m_sommets.size(),0);
    for(size_t i = 0; i < m_sommets.size(); ++i)
            touspcc.push_back(temp);
    //Calcul de l'indice
    for(size_t i = 0; i < m_sommets.size(); ++i)
    {
        n_pcc_i = 0;
        for(size_t j = 0; j < m_sommets.size(); ++j)
        {
            for(size_t k = 0; k < m_sommets.size(); ++k)
            {
                touspcc = DijsktraModif(j,k);
                n_pcc = touspcc.size();
                for(size_t l = 0; l < touspcc.size(); ++l)
                    for(size_t m = 0; m < touspcc[l].size(); ++m)
                        if((touspcc[l][m] == m_sommets[i]->getNumero()))
                            n_pcc_i++;
            }
            somme = somme + (n_pcc_i/n_pcc);
            n_pcc = 0;
            n_pcc_i = 0;
        }
        m_sommets[i]->setIndiceInterNon(somme);
        m_sommets[i]->setIndiceInter((2*somme)/((m_sommets.size()*m_sommets.size())-(3*m_sommets.size())+2));
        somme = 0;
    }
    //affichage en console
    if(norm)
    {
        std::cout << "Indice de centralite d'Intermedialite normalise" << std::endl;
        for (size_t i =0; i<m_sommets.size();++i)
            std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceInter()<<std::endl;
    }
    else
    {
        std::cout << "Indice de centralite d'Intermedialite" << std::endl;
        for (size_t i =0; i<m_sommets.size();++i)
            std::cout << m_sommets[i]->getNumero()<<" : "<< m_sommets[i]->getIndiceInterNon()<<std::endl;
    }
}

//Jules 30/04/2020
int Graphe::calculk_connexite()
{
    int k_connex = 100000000;
    int k_connexnew = 100000000;
    int commun=0;
    std::vector<std::vector<int>> resultat;
    std::vector<int>marq(m_sommets.size(),0);//marquage des sommets
    for(size_t i = 0;i < m_sommets.size(); ++i)//Pour tous couples de sommets Si et Sj
    {
        for(size_t j = 0; j < m_sommets.size(); ++j)
        {
            if (i != j) //Sommets dijoints
            {
                resultat = DijsktraModif(i,j);
                k_connexnew = 100000000;
                for (size_t x = 0; x < resultat.size(); ++x)
                {
                    commun = 0;
                    for (size_t y = 1;y < ((resultat[x].size())-1);++y )
                    {
                        if (marq[resultat[x][y]] == 0)
                        {
                            marq[resultat[x][y]] = 1;
                        }
                        else
                        {
                            ++commun;
                        }
                    }
                    if (commun == 0)
                    {
                        if(k_connexnew = 100000000)
                        {
                            k_connexnew = 0;
                        }
                        ++k_connexnew;
                    }
                }
            }
            if(k_connexnew < k_connex)
            {
                k_connex = k_connexnew;
            }
            k_connexnew = 100000000;
        }
    }
    return k_connex;
}

std::vector<Sommet*> Graphe::trouverSuccsIndice(int nb) //Permet de retourner un vecteur de tous les successeurs d'un sommet
{
    Sommet* base = new Sommet();
    for(size_t i = 0; i < m_sommets.size();++i)
        if(m_sommets[i]->getNumero() == nb)
            base = m_sommets[i];
    std::vector<Sommet*> succs;
    for(size_t i = 0; i < m_aretes.size(); ++i)
    {
        if(!m_ori)  //Si le graphe n'est pas oriente
            if(m_aretes[i]->getExtr1()->getNumero() == base->getNumero())
                succs.push_back(m_aretes[i]->getExtr2());
        if(m_aretes[i]->getExtr2()->getNumero() == base->getNumero())
            succs.push_back(m_aretes[i]->getExtr1());
    }
    return succs;
}

void Graphe::printpath(std::vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        std::cout << path[i] << " ";
    std::cout<<"coucou" << std::endl;
}

// utility function to check if current
// vertex is already present in path
int Graphe::isNotVisited(int x, std::vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}

// utility function for finding paths in graph
// from source to destination
void Graphe::findpaths(int src, int dst, int v)
{
    // create a queue which stores
    // the paths
    std::queue<std::vector<int> > q;

    // path vector to store the current path
    std::vector<std::vector<int>> resultat;
    std::vector<int> path;
    path.push_back(src);
    q.push(path);
    while (!q.empty())
    {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];

        // if last vertex is the desired destination
        // then print the path
        std::cout<<"last "<<last<<"  dst  "<<dst<<std::endl;
        if (last == dst)
        {
            printpath(path);
            resultat.push_back(path);
        }
        std::vector<Sommet*> succs  = trouverSuccsIndice(last);
        std::cout<<"succs"<<succs.size()<<std::endl;
        for (size_t i = 0; i < succs.size(); i++)
            std::cout<<"succs"<<i<<" : "<<succs[i]->getNom()<<std::endl;
        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (size_t i = 0; i < succs.size(); i++)
        {std::cout<<"3"<<std::endl;
            if (isNotVisited(succs[i]->getNumero(), path))
            {
                std::vector<int> newpath(path);
                newpath.push_back(succs[i]->getNumero());
                q.push(newpath);
            }
        }
    }
}

bool Graphe::connexite()
{
    std::vector<int> chemin(m_sommets.size(),0);
    for(size_t i = 0; i < m_sommets.size(); ++i)
    {
        chemin = Dijsktra(i);
        for(size_t j = 0; j < m_sommets.size(); ++j)
            if(chemin[j] == -1)
                return false;
    }
    return true;
}
