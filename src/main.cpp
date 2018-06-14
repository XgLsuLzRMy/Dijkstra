#include <iostream>
#include "Graph.hpp"



void afficherTab(int* tab, Graph &g){
  int n = g.tailleTab(tab);
  for(int i=0; i<n; i++){
    std::cout << g.getNomSommet(tab[i]+1) << " ";
  }
  std::cout << "\n";
}

void afficherTab(char* tab, int n){
	for(int i=0; i<n; i++){
		std::cout << tab[i] << " ";
	}
	std::cout << "\n";
}

void afficherTab(int* tab, int n){
	for(int i=0; i<n; i++){
		std::cout << tab[i] << "\t";
	}
	std::cout << "\n";
}

void afficherTabDijkstra(int* poids, char* provenance, Graph &g, char* labels, int taille, char* sommetsFixes, int nbSommetsFixes, int afficherEnTete=0){
	if(afficherEnTete){
		for(int i=0; i<taille; i++){
			std::cout << labels[i] << "\t";
		}
		std::cout << "Fixes\n";
	}
	for(int i=0; i<taille; i++){
		if(poids[i] != INF){
			std::cout << poids[i]; 
		}else{
			std::cout << "INF";
		}
		std::cout << provenance[i] << "\t";
	}
	afficherTab(sommetsFixes, nbSommetsFixes);
}

void echanger(char* tab, int position1, int position2){
	char temp = tab[position1];
	tab[position1] = tab[position2];
	tab[position2] = temp;
}

void echanger(int* tab, int position1, int position2){
	char temp = tab[position1];
	tab[position1] = tab[position2];
	tab[position2] = temp;
}

int appartient(char* tab, char elem, int taille){
	int res = 0;
	for(int i=0; i<taille; i++){
		if(tab[i] == elem){
			res = 1;
			i = taille; // quitter la boucle
		}
	}
	return res;
}

int appartient(int* tab, int elem, int taille){
	int res = 0;
	for(int i=0; i<taille; i++){
		if(tab[i] == elem){
			res = 1;
			i = taille; // quitter la boucle
		}
	}
	return res;
}

int minimum(int* tab, int taille, int* ignore, int tailleIgnore){
	int min = -1;
	for(int i=0; i<taille; i++){
		if(!appartient(ignore, i, tailleIgnore)){
			if(tab[i] != INF){
				if(min==-1){
					min = i;
				}else if(tab[i] < tab[min]){
					min = i;
				}
			}
		}
	}
	return min;
}

int trouver(char* tab, char elem, int taille){
	int res = -1;
	for(int i=0; i<taille; i++){
		if(tab[i] == elem){
			res = i;
			i = taille;
		}
	}
	return res;
}

int* convertirTableauDeNomEnTableauDIndice(char* tableauNom, char* noms, int taille, int tailleNoms){
	int* tableauIndices = new int[taille];
	for(int i=0; i<taille; i++){
		tableauIndices[i] = trouver(noms, tableauNom[i], tailleNoms);
	}
	return tableauIndices;
}

void dijkstra(Graph &graph, char lettreSommetDepart){
	std::cout << "Chemin le plus court en partant de " << lettreSommetDepart << "\n";
	
	// INITIALISATION
	
	int tailleTab = graph.getNombreSommet();
	int* tab = new int[tailleTab]; // Le tableau contenant les poids totaux affichés dans le tableau
	tab[0] = 0; // Le sommet de départ est en position 0 et son poids est de 0 puisque ce sommet est atteint dès le départ
	for(int i=1; i<tailleTab; i++){
		tab[i] = INF; // on initialise à INF
	}
	
	char* provenance = new char[tailleTab]; // le tableau des sommets de provenance. C'est le sommet associé à chaque poids dans le tableau
	char* sommetsFixes = new char[tailleTab]; // le tableau des sommets fixés. Correspond à la derniere colonne du tableau
	int nbSommetsFixes = 0; // le nombre de sommets fixés. Permet d'avoir la condition d'arrêt de l'algorithme (lorsque tous les sommets sont fixés <-> nbSommetsFixes==tailleTab)
	char* labels = graph.getListeNomSommets(); // les noms des sommets. L'ordre des sommets dans le tableau est différent de l'ordre dans le graph donc on a besoin de ce tableau.
	// On pourrait garder le même ordre que dans le graph (cela éviterait ce changement de coordonnées un peu inutil)
	echanger(labels, 0, graph.getNumeroSommet(lettreSommetDepart)-1); // on place le sommet de départ en colonne du tableau 
	
	//afficherTabDijkstra(tab, provenance, graph, labels, tailleTab, sommetsFixes, nbSommetsFixes, 1);
	std::cout << "\n\n";
	
	int* succ = graph.successeurs(graph.getNumeroSommet(lettreSommetDepart)-1); // on récupère les succésseurs du sommet de départ
	int nbSucc = graph.tailleTab(succ); // le nombre de succésseurs
	int poids;
	// On écrit les poids correspondant aux fleches sommetDeDepart->successeur dans le tableau
	// On place les succésseurs directs du sommet de départ en début de tableau (juste après le sommet de départ)
	// Les succésseurs ont donc pour position, dans le tableau, 1, 2, ... d'où i+1
	// Il faut ensuite echanger les position des labels et les provenances pour que ça corresponde
	for(int i=0; i<nbSucc; i++){
		poids = graph.poids(graph.getNumeroSommet(lettreSommetDepart)-1, succ[i]); // on récupère le poids correspondant à la flèche du graphe
		
		tab[i+1] = poids;
		provenance[i+1] = lettreSommetDepart;
		
		echanger(labels, i+1, trouver(labels, graph.getNomSommet(succ[i]+1), tailleTab));
		echanger(provenance, i+1, trouver(labels, graph.getNomSommet(succ[i]+1), tailleTab));
		
	}
	sommetsFixes[0] = lettreSommetDepart; // On fixe le sommet de départ
	nbSommetsFixes++;
	
	afficherTabDijkstra(tab, provenance, graph, labels, tailleTab, sommetsFixes, nbSommetsFixes, 1);
	
	// FIN INITIALISATION
	
	int ok = 0; // booleen pour quitter la boucle while
	int sommetDePoidsLePlusFaible, indiceDuSommetDePoidsLePlusFaibleDansGraph; // On a 2 indices : dans le tableau et dans le graph. Puisque l'on aéfféctué des échanges durant l'initialisation. C'est pourquoi on précise "DansGraph" ou "DansTab"
	int* ignore;
	
	int indSuccDansTab;
	
	// Boucle correspondant à l'application de l'algorithme de Dijkstra
	while(!ok){
		ignore = convertirTableauDeNomEnTableauDIndice(sommetsFixes, labels, nbSommetsFixes, tailleTab); // les indices des sommets ignores c'est à dire les sommets fixés. On a les noms des sommets ignorés/fixés mais on a besoin des leurs indices d'où l'appel à cette fonction
		sommetDePoidsLePlusFaible = minimum(tab, tailleTab, ignore, nbSommetsFixes); // l'indice du sommet de poids le plus faible
		// On fixe ce sommet en l'ajoutant au tableau des sommets fixés
		sommetsFixes[nbSommetsFixes] = labels[sommetDePoidsLePlusFaible];
		nbSommetsFixes++;
		
		indiceDuSommetDePoidsLePlusFaibleDansGraph = graph.getNumeroSommet(labels[sommetDePoidsLePlusFaible])-1; // on convertit l'indice dans le tableau en un indice dans le graph
		
		succ = graph.successeurs(indiceDuSommetDePoidsLePlusFaibleDansGraph); // on récupère les succésseurs du sommet de poids le plus faible
		nbSucc = graph.tailleTab(succ);
		for(int i=0; i<nbSucc; i++){
			poids = graph.poids(indiceDuSommetDePoidsLePlusFaibleDansGraph, succ[i]); // le poids de l'arrête sommetDePoidsLePlusFaible->ième successeur
			
			indSuccDansTab = trouver(labels, graph.getNomSommet(succ[i]+1), tailleTab); // on convertit l'indice dans le graph en un indice dans le tableau
			
			// Si le succésseur avait un poids infini on peut le mettre à jour directement
			if(tab[indSuccDansTab] == INF){
				provenance[indSuccDansTab] = labels[sommetDePoidsLePlusFaible];
				tab[indSuccDansTab] = poids + tab[sommetDePoidsLePlusFaible];
			}else{ // si le poids n'est pas infini alors il faut vérifier si on améliore le poids
				if(tab[indSuccDansTab] > tab[sommetDePoidsLePlusFaible]+poids){
				provenance[indSuccDansTab] = labels[sommetDePoidsLePlusFaible];
				tab[indSuccDansTab] = poids + tab[sommetDePoidsLePlusFaible];
				}
			}
			
		}
		afficherTabDijkstra(tab, provenance, graph, labels, tailleTab, sommetsFixes, nbSommetsFixes); // on affiche la ligne du tableau obtenue après cette itération
		ok = nbSommetsFixes == tailleTab; // on quitte l'algorithme lorsque tous les sommets sont fixés. On pourrait aussi ajouter la condition si appartient(sommetsFixes, sommetDArrivee, nbSommetsFixes) si on avait un sommet d'arrivée défini (et donc passé en paramètre de la fonction dijkstra) ce qui n'est pas le cas ici.
	}
}

int main(){
	std::cout << "Exemples du site http://serge.mehl.free.fr/anx/algo_dij.html\n\n";
  std::cout << "\n=====Exemple 1=====\n";
  Graph g(6);
  g.modifierFleche('A','E', 4);
  g.modifierFleche('B','A', 2);
  g.modifierFleche('B','F', 3);
  g.modifierFleche('C','B', 9);
  g.modifierFleche('C','D', 2);
  g.modifierFleche('C','F', 6);
  g.modifierFleche('D','A', 9);
  g.modifierFleche('D','C', 2);
  g.modifierFleche('D','F', 3);
  g.modifierFleche('E','D', 4);
  g.modifierFleche('F','A', 6);
  g.modifierFleche('F','B', 3);
  g.modifierFleche('F','C', 6);
  //g.afficherFleches();
  dijkstra(g, 'C');
  
  std::cout << "\n\n=====Exemple 2=====\n";
  
  Graph g2(7);
  int oriente = 0;
  g2.modifierFleche('A','C', 3, oriente);
  g2.modifierFleche('A','D', 5, oriente);
  g2.modifierFleche('A','E', 4, oriente);
  g2.modifierFleche('B','C', 5, oriente);
  g2.modifierFleche('B','E', 2, oriente);
  g2.modifierFleche('B','F', 3, oriente);
  g2.modifierFleche('C','D', 1, oriente);
  g2.modifierFleche('C','G', 5, oriente);
  g2.modifierFleche('C','F', 4, oriente);
  g2.modifierFleche('D','G', 4, oriente);
  g2.modifierFleche('F','G', 8, oriente);
  //g2.afficherFleches();
  dijkstra(g2, 'E');
}
