#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool vectIn(int x, int y, vector<int> voisins[]) {
  for(int i=0;i<voisins[x].size();i++)
    if(voisins[x].at(i)==y)
      return true;
  return false;
}

void pointrandom(int n, int point[][2]) {
  srand(time(NULL));
  for(int i=0;i<n;i++) {
    point[i][0]=rand()%612;
    point[i][1]=rand()%792;
  }
}
    
void voisinstrandom(int n, int m, vector<int> voisins[]);
void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]);
void ecritureniveaux(int n, int niveau[]);
void parcoursprofondeur(int n, vector<int> voisins[], int debut[], int fin[], int niveau[], int pere[]);
void AffichageGraphique(int type, int n, int point[][2], int pere[]);

int main(){
  int n;             //Le nombre de sommets.
  int m;             // Le nombre d'aretes.
  cout << "Entrer le nombre de sommets: ";
  cin >> n;
  cout << "Entrer le nombre d'aretes: ";
  cin >> m;
  int point[n][2];
  vector<int> voisins[n];	// Les listes des voisins. 
  int pere[n];            // L'arbre en largeur.
  for(int i=0;i<n;i++)
    pere[i]=-1;
  int ordre[n];           // L'ordre de parcours.
  int niveau[n];          // Le niveau du point.
  
  int debut[n];
  int fin[n];

  pointrandom(n,point);
  voisinstrandom(n,m,voisins);
  cout<<"PARCOURS en LARGEUR :"<<endl;
  parcourslargeur(n,voisins,niveau,ordre,pere);
  ecritureniveaux(n,niveau);
  AffichageGraphique(0,n,point,pere);
  cout<<endl<<"PARCOURS en PROFONDEUR :"<<endl;
  parcoursprofondeur(n,voisins,debut,fin,niveau,pere);
  ecritureniveaux(n,niveau);
  AffichageGraphique(1,n,point,pere);
  //Remarque : la différence entre les deux postscripts est faible mais existe

return 0;
}

void voisinstrandom(int n, int m, vector<int> voisins[]) {
  srand(time(NULL));
  int x, y, i=0;
  while(i<m) {
    x=rand()%n; y=rand()%n;
    if(x!=y && !(vectIn(x,y,voisins))) {
      voisins[x].push_back(y);
      voisins[y].push_back(x);
      i++;
    }
  }
}

void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]) {
  for(int i=0;i<n;i++)
    niveau[i]=0;
  
  int dv[n]; vector<int> AT;
  for(int i=0;i<n;i++)
    dv[i]=0;
  dv[0]=ordre[0]=1; pere[0]=niveau[0]=0;
  AT.push_back(0); int t=2;
  
  while(!AT.empty()) {
    int v=AT.front(); AT.erase(AT.begin());
    for(int i=0;i<voisins[v].size();i++) {
      int x=voisins[v].at(i);
      if(dv[x]==0) {
	dv[x]=1;
	AT.push_back(x);
	ordre[x]=t; t++;
	pere[x]=v;
	niveau[x]=niveau[v]+1;
      }
    }
  }
}

void ecritureniveaux(int n, int niveau[]) {
  int niv[n]; int isole=0;
  niv[0]=1;
  for(int i=1;i<n;i++)
    niv[i]=0;
  for(int i=1;i<n;i++) {
    if(niveau[i]==0)
      isole++;
    else
      niv[niveau[i]]++;
  }
  for(int i=0;i<n;i++)
    if(niv[i]!=0)
      cout<<"Il y a "<<niv[i]<<" sommets au niveau "<<i<<"."<<endl;
  cout<<"Il y a "<<isole<<" sommets qui ne sont pas dans la composante de 0."<<endl;
}

void parcoursprofondeur(int n, vector<int> voisins[], int debut[], int fin[], int niveau[], int pere[]) {  
  for(int i=0;i<n;i++)
    niveau[i]=0;
  
  int dv[n]; vector<int> AT;
  for(int i=0;i<n;i++)
    dv[i]=0;
  dv[0]=debut[0]=1; pere[0]=niveau[0]=0;
  AT.push_back(0); int t=2;
  
  while(!AT.empty()) {
    int x=AT.back();
    if(voisins[x].empty()) {
      AT.pop_back();
      fin[x]=t; t++;
    }
    else {
      int y=voisins[x].back(); voisins[x].pop_back();
      if(dv[y]==0) {
	dv[y]=1;
	AT.push_back(y);
	debut[y]=t; t++;
	pere[y]=x;
	niveau[y]=niveau[x]+1;
      }
    }
  }
  
}

void AffichageGraphique(int type, int n, int point[][2], int pere[]) { 
  ofstream output;                           
  if(type==0)
    output.open("arbreLargeur.ps",ios::out);
  else
    output.open("arbreProfondeur.ps",ios::out);
  output << "%!PS-Adobe-3.0" << endl;
  output << "%%BoundingBox: 0 0 612 792" << endl;
  output << endl;  
  for(int i=0;i<n;i++) {
    output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << "stroke"<<endl;
    output << endl;
  }
  output << endl;
  for(int i=0;i<n-1;i++) {
    output << point[i][0] << " " << point[i][1] << " moveto" << endl;
    if(pere[i] != -1)
      output << point[pere[i]][0] << " " << point[pere[i]][1] << " lineto" << endl;
    output << "stroke" << endl;
    output << endl;
  }
}

