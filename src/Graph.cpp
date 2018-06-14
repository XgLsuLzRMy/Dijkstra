#include "Graph.hpp"

Graph::Graph(int n_input){
  if(n_input>0){
    Graph::n = n_input;
  }else{
    Graph::n = 0;
  }
  Graph::matrice = null;
  Graph::resetMatrice();
  Graph::nomSommets = null;
  Graph::resetNomSommets();
}

Graph::~Graph(){
  delete [] Graph::matrice;
  delete [] Graph::nomSommets;
}

int Graph::getNombreSommet(){
	return Graph::n;
}

void Graph::resetMatrice(){
  if(Graph::matrice != null){
    delete [] Graph::matrice;
  }
  Graph::matrice = new int*[Graph::n];
  for(int i=0; i<Graph::n; i++){
    Graph::matrice[i] = new int[Graph::n];
    for(int j=0; j<Graph::n; j++){
      Graph::matrice[i][j] = INF;
    }
  }
}

void Graph::resetNomSommets(){
  if(Graph::nomSommets != null){
    delete [] Graph::nomSommets;
  }
  Graph::nomSommets = new char[Graph::n];
  for(int i=0; i<Graph::n; i++){
    Graph::nomSommets[i] = 'A' + i;
  }
}

void Graph::ajouterNomSommet(){
  char* tab = new char[Graph::n];
  for(int i=0; i<Graph::n -1; i++){
    tab[i] = Graph::nomSommets[i];
  }
  tab[Graph::n-1] = Graph::nomSommets[Graph::n-2] + 1;
  delete [] Graph::nomSommets;
  Graph::nomSommets = tab;
}

void Graph::retirerNomSommet(int s){
  char* tab = new char[Graph::n];
  int decal = 0;
  for(int i=0; i<Graph::n+1; i++){
    if(i!=s){
      tab[i-decal] = Graph::nomSommets[i];
    }else{
      decal++;
    }
  }
  
  delete [] Graph::nomSommets;
  Graph::nomSommets = tab;
}

char* Graph::getListeNomSommets(){
	char* res = new char[Graph::n];
	for(int i=0; i<Graph::n; i++){
		//res[i] = Graph::getNomSommet(i+1);
		res[i] = Graph::nomSommets[i];
	}
	return res;
}

void Graph::afficherMatrice(){
  
  for(int i=0; i<Graph::n; i++){
    std::cout << "\t" << Graph::nomSommets[i];
  }
  std::cout << "\n";
  for(int i=0; i<Graph::n; i++){
    std::cout << Graph::nomSommets[i];
    for(int j=0; j<Graph::n; j++){
      if(Graph::matrice[i][j]!=INF){
        std::cout << "\t" << Graph::matrice[i][j];
      }else{
        std::cout << "\tINF";
      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void Graph::afficherFleches(){
  for(int sommetDepart=0; sommetDepart<Graph::n; sommetDepart++){
    std::cout << "\t------ " << Graph::nomSommets[sommetDepart] << " ------\n";
    for(int sommetArrivee=0; sommetArrivee<Graph::n; sommetArrivee++){
      if(Graph::matrice[sommetArrivee][sommetDepart] != INF){
        std::cout << "\t" << Graph::nomSommets[sommetDepart] << "->" << Graph::nomSommets[sommetArrivee] << ": " << Graph::matrice[sommetArrivee][sommetDepart] << "\n";
      }
    }
  }
  std::cout << "\n";
}

void Graph::modifierFleche(int sommetDepart, int sommetArrivee, int poids, int oriente){
  // on retire 1 car on commence à 0 et non 1
  sommetArrivee--;
  sommetDepart--;
  if(sommetDepart>=0 && sommetDepart<Graph::n && sommetArrivee>=0 && sommetArrivee<Graph::n){
    if(poids>0){  
      Graph::matrice[sommetArrivee][sommetDepart] = poids;
      if(!oriente){
      	Graph::matrice[sommetDepart][sommetArrivee] = poids;
      }
    }else{
      Graph::matrice[sommetArrivee][sommetDepart] = INF;
      if(!oriente){
      	Graph::matrice[sommetDepart][sommetArrivee] = INF;
      }
    }
  }
}

void Graph::modifierFleche(char lettreSommetDepart, char lettreSommetArrivee, int poids, int oriente){
	Graph::modifierFleche(Graph::getNumeroSommet(lettreSommetDepart), Graph::getNumeroSommet(lettreSommetArrivee), poids, oriente);
}

void Graph::retirerSommet(int s){
  s--;
  if(s<Graph::n && s>=0){
    Graph::n--;
    int** matrice2 = new int*[Graph::n];
    for(int i=0; i<Graph::n; i++){
      matrice2[i] = new int[Graph::n];
    }
    
    for(int i=0; i<s; i++){
      for(int j=0; j<s; j++){
        matrice2[i][j] = Graph::matrice[i][j];
      }
    }
    
    for(int i=s+1; i<Graph::n +1; i++){
      for(int j=0; j<s; j++){
        matrice2[i-1][j] = Graph::matrice[i][j];
      }
    }
    
    for(int i=0; i<s +1; i++){
      for(int j=s+1; j<Graph::n+1; j++){
        matrice2[i][j-1] = Graph::matrice[i][j];
      }
    }
    
    for(int i=s+1; i<Graph::n+1; i++){
      for(int j=s+1; j<Graph::n+1; j++){
        matrice2[i-1][j-1] = Graph::matrice[i][j];
      }
    }
    
    delete [] Graph::matrice;
    Graph::matrice = matrice2;
  }
  
  Graph::retirerNomSommet(s);
  
}

void Graph::agrandirMatrice(){
  int** matrice2 = new int*[Graph::n +1];
  for(int i=0; i<Graph::n +1; i++){
    matrice2[i] = new int[Graph::n +1];
    if(i < Graph::n){
      for(int j=0; j<Graph::n; j++){
        matrice2[i][j] = Graph::matrice[i][j];
      }
    }
  }
  
  for(int i=0; i<Graph::n +1; i++){
    matrice2[Graph::n][i] = INF;
    matrice2[i][Graph::n] = INF;
  }
  delete [] Graph::matrice;
  Graph::matrice = matrice2;
  Graph::n++;
  Graph::ajouterNomSommet();
}

int Graph::ajouterSommet(){
  Graph::agrandirMatrice();
  return Graph::n;
}

int Graph::getNumeroSommet(char nomSommet){
  int res = -1;
  int i = 0;
  while(i<Graph::n && res==-1){
    if(Graph::nomSommets[i] == nomSommet){
      res = i+1;
    }
    i++;
  }
  return res;
}

char Graph::getNomSommet(int s){
  s--;
  if(s>=0 && s<Graph::n){
    return Graph::nomSommets[s];
  }else{
    return '$';
  }
}

int* Graph::ajouterATab(int* tab, int x){
  int taille = Graph::tailleTab(tab) + 2;
  int* tab2 = new int[taille];
  for(int i=0; i<taille-2; i++){
    tab2[i] = tab[i];
  }
  tab2[taille-2] = x;
  tab2[taille-1] = FINTAB;
  return tab2;
}

int Graph::tailleTab(int* tab){
  int res = 0;
  if(tab != null){
    int i = 0;
    while(i<=Graph::n && res==0){
      if(tab[i] == FINTAB){
        res = i;
      }
      i++;
    }
  }
  return res;
}

int* Graph::predecesseurs(int s){
  int* res = null;
  int* tmp = null;
  int ok = 0;
  for(int i=0; i<Graph::n; i++){
    if(Graph::matrice[s][i] != INF){
      tmp = Graph::ajouterATab(res, i);
      delete [] res;
      res = tmp;
      ok = 1;
    }
  }
  if(ok == 0){
    res = new int[1];
    res[0] = -1;
  }
  return res;
}

int* Graph::successeurs(int s){
  int* res = null;
  int* tmp = null;
  int ok = 0;
  for(int i=0; i<Graph::n; i++){
    if(Graph::matrice[i][s] != INF){
      tmp = Graph::ajouterATab(res, i);
      delete [] res;
      res = tmp;
      ok = 1;
    }
  }
  if(ok == 0){
    res = new int[1];
    res[0] = -1;
  }
  return res;
}

int Graph::poids(int sommetDepart, int sommetArrivee){
	if(sommetDepart>=0 && sommetDepart<Graph::n &&  sommetArrivee>=0 && sommetArrivee<Graph::n){
		return Graph::matrice[sommetArrivee][sommetDepart];
	}else{
		return -1;
	}
}
