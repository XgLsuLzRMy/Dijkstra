#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <iostream>

#define null 0
#define INF 500 // On pourrait mettre un autre nombre ou mettre le nombre maximal pour int par exemple
#define FINTAB -1 // Equivalent de '\0' pour les char* mais ici c'est pour int*. C'est un nombre arbitraire mais qui fonctionne puisqu'on suppose que nous aurons des tableaux de nombres positifs (soit des poids positifs, soit des indices). On pourrait aussi passer la taille du tableau en paramètre mais cette méthode permet à une fonction externe d'utiliser tailleTab(). On aurait pu utiliser taille=sizeof(tab)/sizef(tab[0]) mais cela ne fonctionnait pas

class Graph{
private:
  /*
    \ De  1 2 3
  Vers  
    1     0 3 4
    2     2 0 1
    3     5 7 0
    
    poids = matrice[sommetArrivee][sommetDepart]
  */
  int** matrice;
  char* nomSommets;
  int n;
  void resetMatrice();
  void agrandirMatrice();
  
  void resetNomSommets();
  void ajouterNomSommet();
  void retirerNomSommet(int s);
  
  int* ajouterATab(int* tab, int x);
  
public:
  Graph(int n = 0);
  ~Graph();
  int getNombreSommet();
  char* getListeNomSommets();
  void afficherMatrice();
  void afficherFleches();
  void modifierFleche(int sommetDepart, int sommetArrivee, int poids, int oriente=1); // cree la fleche si elle n'existe pas
  void modifierFleche(char lettreSommetDepart, char lettreSommetArrivee, int poids, int oriente=1);
  int ajouterSommet(); // renvoie le numero du sommet qui a été ajouté
  void retirerSommet(int s);
  int getNumeroSommet(char nomSommet);
  char getNomSommet(int s);
  int* predecesseurs(int s);
  int* successeurs(int s);
  int tailleTab(int* tab);
  int poids(int sommetDepart, int sommetArrivee);
};

#endif
