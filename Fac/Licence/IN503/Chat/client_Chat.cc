// Chat - Client
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include "sock.h"
#include "sockdist.h"
#include "string.h"
#include <pwd.h>

#define LGBUFFER 300

using namespace std;

int cl(char* s){
  int l=0,i=0;
  while(s[i]!='\0'){
    l++;i++;
  }
  return l+1;
}

int main(int argc, char* argv[], char* env[]) {
    //Initialisation boite privée
  Sock brLoc(SOCK_STREAM, 0);
  int descbrLoc;

  if(brLoc.good()) descbrLoc=brLoc.getsDesc();
  else {cout<<"pb BR locale"<<endl; exit(1);}

  //Initialisation boite distante (serveur)
  SockDist brPub(argv[1], (short) 5000);
  sockaddr_in* adbrPub=brPub.getAdrDist();
  int lgAdrbrPub=sizeof(struct sockaddr_in);
  
  //Connection et envoi du pseudo
  char* pseudo;
  char new_pseudo;
  cout<<"Voulez-vous entrer un nouveau pseudo ? (Y/N) ";
  cin>>new_pseudo;
  if(new_pseudo=='Y' || new_pseudo=='y') {
    cout<<"Entrez votre nouveau pseudo : ";
    cin>>pseudo;
  }
  else {
    uid_t id=getuid();
    pseudo=getpwuid(id)->pw_name;
  }
  int co=connect(descbrLoc, (sockaddr*) adbrPub, lgAdrbrPub);
  if(co==-1) {cout<<"Connection refusée"<<endl; exit(2);}
  cout<<"Connexion réussie"<<endl;
  
  int retourSend=sendto(descbrLoc, pseudo, cl(pseudo), 0, (sockaddr*) adbrPub, sizeof(struct sockaddr_in));
  if(retourSend==-1) {
    cout<<"pb send"<<endl;
    exit(5);
  }
  
  //quelques variables
  int quit=0;
  fd_set descR;
  int nbsurv=1+max(STDIN_FILENO, descbrLoc);

  //Boucle de connection
  while(!quit) {
    FD_ZERO(&descR);
    FD_SET(STDIN_FILENO, &descR); FD_SET(descbrLoc, &descR);
    
    int action=select(nbsurv, &descR, NULL,NULL,NULL);
    if(action==-1){
      cout<<"pb select"<<endl;
      exit(2);
    }

    //Entrée au clavier
    if FD_ISSET(STDIN_FILENO, &descR) {
      char buffer[LGBUFFER];
      cin.getline(buffer, LGBUFFER);
      if(strcmp(buffer, "\\quit")==0)
        quit=1;
      else {
        int retourSend=sendto(descbrLoc, buffer, cl(buffer), 0, (sockaddr*) adbrPub, sizeof(struct sockaddr_in));
        if(retourSend==-1) {
          cout<<"pb send"<<endl;
          exit(5);
        }
      }
      fflush(STDIN_FILENO);
    }

    //Réception d'un message
    if FD_ISSET(descbrLoc, &descR) {
      char buffer[LGBUFFER];
      int retourRecv=recv(descbrLoc, &buffer, LGBUFFER, 0);
      if(retourRecv==-1) {
        cout<<"pb recv"<<endl;
        exit(4);
      }
      else if(retourRecv==0) {
        cout<<"Le serveur s'est déconnecté"<<endl;
        exit(6);
      }
      cout<<buffer<<endl;
    }
  }

  close(descbrLoc);
  return 0;
}
