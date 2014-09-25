#include <iostream>
#include <vector>

using namespace std;

//const int n=5;
const int n=6;
const int inf=9999;                    //La valeur infinie.    

void floyd_warshall(int longueur[][n], int dist[][n], int chemin[][n]);
void itineraire(int chemin[][n]);
void fermeturetransitive(int arc[][n], int fermeture[][n]);
void compfortconnexe(int n1, int fermeture[][n]);

int main(){
/*
  //réseau plus grand :
  char villes[41][20]={"Amiens", "Angouleme", "Avignon", "Bayonne", "Bilbao", "Bordeaux", "Bourges", "Brest", "Brive", "Bruxelles", "Caen", "Cahors", "Clermont-Ferrand", "Dijon", "Geneve", "Grenoble", "Lille", "Limoges", "Luxembourg", "Lyon", "Marseille", "Millau", "Montpellier", "Mulhouse", "Nancy", "Nantes", "Nice", "Orleans", "Paris", "Perpignan", "Poitiers", "Reims", "Rennes", "Rodez", "Rouen", "Saint-Etienne", "Strasbourg", "Toulouse", "Tours", "Troyes", "Valence"};
  
  int longueur[41][41];
  for(int i=0;i<41;i++){
    for(int j=0;j<41;j++){
      longueur[i][j]=inf;
    }
    longueur[i][i]=0;
  }
  
  
  longueur[0][34]=120; longueur[0][28]=130;longueur[0][31]=180; longueur[0][16]=140;longueur[1][30]=130;  longueur[1][17]=110; longueur[1][8]=170;  longueur[1][5]=120;longueur[2][40]=140;  longueur[2][22]=90;longueur[2][20]=90;longueur[3][5]=180;  longueur[3][37]=300;longueur[3][4]=70;longueur[4][3]=70;longueur[5][1]=120; longueur[5][8]=200; longueur[5][11]=230; longueur[5][37]=241; longueur[5][3]=180;longueur[6][27]=121; longueur[6][39]=240; longueur[6][13]=250; longueur[6][12]=190; longueur[6][38]=230;longueur[7][32]=240;longueur[8][11]=101; longueur[8][17]=100; longueur[8][1]=170; longueur[8][5]=200; longueur[8][33]=140;longueur[9][16]=110; longueur[9][31]=230; longueur[9][18]=210;longueur[10][34]=130; longueur[10][38]=260; longueur[10][32]=180;longueur[11][21]=180; longueur[11][8]=101; longueur[11][5]=230; longueur[11][37]=110; longueur[11][33]=105;longueur[12][6]=190; longueur[12][19]=210; longueur[12][35]=150; longueur[12][17]=230; longueur[12][33]=270;longueur[13][19]=200; longueur[13][23]=221; longueur[13][24]=220; longueur[13][39]=180; longueur[13][6]=250; longueur[13][14]=200; longueur[14][15]=145; longueur[14][19]=150; longueur[14][13]=200; longueur[15][26]=340; longueur[15][20]=270; longueur[15][40]=90; longueur[15][19]=150; longueur[15][14]=145; longueur[16][0]=140; longueur[16][31]=196; longueur[16][9]=110; longueur[17][30]=120; longueur[17][1]=110; longueur[17][8]=100; longueur[17][12]=230; longueur[18][31]=218; longueur[18][36]=220; longueur[18][9]=210; longueur[18][24]=200; longueur[19][40]=150; longueur[19][35]=80; longueur[19][12]=210; longueur[19][13]=200; longueur[19][14]=150; longueur[19][15]=150; longueur[20][22]=170; longueur[20][2]=90; longueur[20][26]=200; longueur[20][15]=270; longueur[21][37]=190; longueur[21][11]=180; longueur[21][22]=110; longueur[21][33]=60; longueur[22][29]=150; longueur[22][37]=240; longueur[22][21]=110; longueur[22][2]=90; longueur[22][20]=170; longueur[22][40]=200; longueur[23][13]=221; longueur[23][24]=170; longueur[23][36]=120;longueur[24][36]=160; longueur[24][23]=170; longueur[24][13]=220; longueur[24][31]=240; longueur[24][18]=200;longueur[25][32]=110; longueur[25][38]=210; longueur[25][30]=220; longueur[26][20]=200; longueur[26][15]=340; longueur[27][6]=121; longueur[27][39]=200; longueur[27][28]=132; longueur[27][38]=120; longueur[28][0]=130; longueur[28][34]=131; longueur[28][27]=132; longueur[28][39]=181; longueur[28][31]=140; longueur[29][37]=210; longueur[29][22]=150; longueur[30][25]=220; longueur[30][38]=100; longueur[30][17]=120; longueur[30][1]=130; longueur[31][24]=240; longueur[31][28]=140; longueur[31][39]=130; longueur[31][0]=180; longueur[31][16]=196; longueur[31][9]=230; longueur[31][18]=218; longueur[32][10]=180; longueur[32][38]=250; longueur[32][7]=240; longueur[32][25]=110; longueur[33][35]=200; longueur[33][40]=225; longueur[33][21]=60; longueur[33][8]=140; longueur[33][11]=105; longueur[33][12]=270; longueur[34][0]=120; longueur[34][28]=131; longueur[34][10]=130; longueur[35][12]=150; longueur[35][19]=80; longueur[35][40]=120; longueur[35][33]=200; longueur[36][23]=120; longueur[36][24]=160; longueur[36][18]=220;longueur[37][3]=300; longueur[37][5]=241; longueur[37][11]=110; longueur[37][21]=190; longueur[37][22]=240; longueur[37][29]=210;longueur[38][10]=260; longueur[38][32]=250; longueur[38][25]=210; longueur[38][30]=100; longueur[38][27]=120; longueur[38][6]=230;longueur[39][31]=130; longueur[39][28]=181; longueur[39][27]=200; longueur[39][6]=240; longueur[39][13]=180;longueur[40][2]=140; longueur[40][15]=90; longueur[40][35]=120; longueur[40][19]=150; longueur[40][33]=225; longueur[40][22]=200;
*/
  
  //===================================================================
  //   PARTIE 1 :
/*
  int longueur[n][n]={{0,2,inf,4,inf}, //Les longueurs des arcs.
                  {inf,0,2,inf,inf},   //long[i][j]=inf si l'arc ij n'existe pas
                  {inf,inf,0,2,inf},
                  {inf,-3,inf,0,2},
                  {2,inf,inf,inf,0}};                
  int dist[n][n];                      //Le tableau des distances.
  int chemin[n][n];                    //Le tableau de la premiere etape du chemin de i a j.
 
  floyd_warshall(longueur,dist,chemin);
  floyd_warshall(longueur,dist,chemin);
  cout<<"Dist :"<<endl;
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      cout<<dist[i][j]<<" | ";
    }
    cout<<endl;
  }
  cout<<endl<<"Chemin :"<<endl;
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      cout<<chemin[i][j]<<" | ";
    }
    cout<<endl;
  }
  itineraire(chemin);
*/
  
  //===================================================================
  // PARTIE 2 :
  
  int arc[n][n]={{0,0,0,1,0,1},//La matrice d'adjacence du graphe oriente D.
  {1,0,1,1,0,0},
  {0,0,0,1,0,0},
  {0,0,0,0,1,1},
  {0,0,1,0,0,1},
  {0,0,1,0,0,0}};                
  int fermeture[n][n];         // La matrice de la fermeture transitive de D.
  
  fermeturetransitive(arc,fermeture);
  cout<<endl<<"Fermeture :"<<endl;
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      cout<<fermeture[i][j]<<" | ";
    }
    cout<<endl;
  }
  
  compfortconnexe(n,fermeture);
  
  return 0;
}

void floyd_warshall(int longueur[][n], int dist[][n], int chemin[][n]) {
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      if(longueur[i][j]==inf) {
	dist[i][j]=inf;
	chemin[i][j]=-1;
      }
      else {
        dist[i][j]=longueur[i][j];
	chemin[i][j]=j;
      }
    }
  }
  for(int k=0;k<n;k++) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<n;j++) {
	if(dist[i][j]>(dist[i][k]+dist[k][j])) {
	  dist[i][j]=dist[i][k]+dist[k][j];
	  if(longueur[i][k]!=inf){
	    chemin[i][j]=k;
	  }
	  if(chemin[i][j]==-1)
	    chemin[i][j]=chemin[i][k];
	}
      }
    }
  }
}

void itineraire(int chemin[][n]) {
  int x,y;
  cout<<"Entrer le depart : ";
  cin>>x;
  x--;
  cout<<"Entrer la destination : ";
  cin>>y;
  y--;
  if(x>=0 && x<5 && y>=0 && y<5) {
    cout<<"L'itinéraire est : "<<x+1;
    while(x!=y) {
      x=chemin[x][y];
      cout<<" "<<x+1;
    }
    cout<<endl;
  }
  else
    cout<<"Itinériaire inconnu"<<endl;
}

void fermeturetransitive(int arc[][n], int fermeture[][n]) {
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      if(i == j)
	fermeture[i][j] = 1;
      else {
        if(arc[i][j]==0) {
	  fermeture[i][j]=0;
        }
        else {
          fermeture[i][j]=1;
        }
      }
    }
  }
  for(int k=0;k<n;k++) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<n;j++) {
	if(arc[i][k] == 1 && arc[k][j] == 1) {
	  fermeture[i][j] = 1;
	  arc[i][j] = 1;
	}
      }
    }
  }
}

void compfortconnexe(int n1, int fermeture[][n]) {
  cout<<"Les composantes fortement connexes sont :";
  int dv[n];
  for(int i=0;i<n;i++)
    dv[i] = 0;
  for(int i=0;i<n;i++) {
    if(dv[i] == 0) {
      cout<<" {"<<i;
      dv[i] = 1;
      for(int j=i+1;j<n;j++) {
        if(fermeture[i][j] == 1 && fermeture[j][i] == 1) {
	  cout<<","<<j;
	  dv[j] = 1;
	}
      }
      cout<<"}";
    }
  }
  cout<<endl;
}
