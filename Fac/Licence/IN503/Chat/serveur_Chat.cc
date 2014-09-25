// Chat - Serveur
#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <pwd.h>
#include "sock.h"
#include "sockdist.h"
#include "string.h"

#define LGBUFFER 300
#define LGFILE 10
using namespace std;

int cl(char* s){
  int l=0,i=0;
  while(s[i]!='\0'){
    l++;i++;
  }
  return l+1;
}

int main(int argc, char* argv[], char* env[]) {
  //Initialisation de la boite publique
  Sock brPub(SOCK_STREAM, (short)5000, 0);
  int descbrPub; 

  if(brPub.good()) descbrPub=brPub.getsDesc();
  else {cout<<"pb BR publique"<<endl; exit(1);}

  //Création de la file d'attente, liste de clients (descripteurs, sockaddr et pseudos)
  int li=listen(descbrPub,LGFILE);
  int clients[LGFILE];
  char* pseudos[LGFILE];
  for(int i=0;i<LGFILE;i++) clients[i]=-1;
  struct sockaddr_in brCv[LGFILE];
  socklen_t lgbrCv=sizeof(struct sockaddr_in);
  
  //quelques variables
  fd_set descR;
  int nbsurv=1+descbrPub, current=0; //current est l'indice du prochain clients[i] libre
  int quit=0;

  //Boucle de connection
  while(!quit) {
    FD_ZERO(&descR);
    FD_SET(descbrPub, &descR); FD_SET(STDIN_FILENO, &descR);
    for(int i=0;i<LGFILE;i++)
      if(clients[i]!=-1)
        FD_SET(clients[i], &descR);
      
    int action=select(nbsurv, &descR, NULL,NULL,NULL);
    if(action==-1){
      cout<<"pb select"<<endl;
      exit(2);
    }
    
    //Boite publique (connexion)
    if FD_ISSET(descbrPub, &descR) {
      //La file n'est pas pleine
      if(current<LGFILE) {
        int retourAccept=accept(descbrPub,(struct sockaddr*)&brCv[current], &lgbrCv);
        if(retourAccept==-1){
          cout<<"pb accept"<<endl;
          exit(3);
        }
        else 
          clients[current]=retourAccept;
        cout<<"Connexion acceptée"<<endl;
	
	//Envoie d'un message de connexion
	char buffer[LGBUFFER];
        int retourRecv=recv(clients[current], &buffer, LGBUFFER, 0);
        if(retourRecv==-1) {
          cout<<"pb recv"<<endl;
          exit(4);
        }
        pseudos[current]=buffer;
        strcat(buffer," s'est connecté(e).");
	cout<<buffer<<endl;
        for(int i=0;i<LGFILE;i++)
          if(clients[i]!=-1 && i!=current) {
            int retourSend=sendto(clients[i], buffer, cl(buffer), 0, (sockaddr*) &brCv[i], sizeof(struct sockaddr_in));
            if(retourSend==-1) {
              cout<<"pb send"<<endl;
              exit(5);
            }
	  }
        
        //Mise à jour des paramètres
        nbsurv=1+max(nbsurv, clients[current]);
        int i=0;
        while(i<LGFILE && clients[i]!=-1)
          i++;
        current=i;
      }
      //File pleine
      else 
        cout<<"Demande de connexion refusée"<<endl;
    }
  
    //Test de chaque boite cliente
    for(int k=0;k<LGFILE && clients[k]!=-1;k++) {
      if FD_ISSET(clients[k], &descR) {
        char buffer[LGBUFFER];
        int retourRecv=recv(clients[k], &buffer, LGBUFFER, 0);
        if(retourRecv==-1) {
          cout<<"pb recv"<<endl;
          exit(4);
        }
	if(retourRecv==0) {
	  cout<<pseudos[k]<<endl;  //Ne marche pas je ne sais pas pourquoi...
	  strcpy(buffer,pseudos[k]);
	  strcat(buffer, " s'est déconnecté.");
          close(clients[k]);
          clients[k]=-1;
	}
        cout<<buffer<<endl;
        for(int i=0;i<LGFILE;i++)
          if(clients[i]!=-1 && i!=k) {
            int retourSend=sendto(clients[i], buffer, cl(buffer), 0, (sockaddr*) &brCv[i], sizeof(struct sockaddr_in));
            if(retourSend==-1) {
              cout<<"pb send"<<endl;
              exit(5);
            }
          }
      }
    }

    //Entrée au clavier
    if FD_ISSET(STDIN_FILENO, &descR) {
      char buffer[LGBUFFER];
      cin>>buffer;
      if(strcmp(buffer, "\\quit")==0)
        quit=1;
    }
  }
  
  //Fermeture des boites clients
  for(int i=0;i<LGFILE;i++)
    if(clients[i]!=-1)
      close(clients[i]);

  close(descbrPub);
  return 0;
}
