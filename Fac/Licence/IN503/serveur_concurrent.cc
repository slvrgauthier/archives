// TCP - Serveur concurrent
#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <pwd.h>
#include "sock.h"
#include "sockdist.h"
#include "string.h"

using namespace std;

int cl(char* s){
  int l=0,i=0;
  while(s[i]!='\0'){
    l++;i++;
  }
  return l+1;
}

int main(int argc, char* argv[], char* env[]) {
  Sock brPub(SOCK_STREAM, (short)3555, 0);
  int descbrPub; 

  if(brPub.good()) descbrPub=brPub.getsDesc();
  else {cout<<"pb BR publique"<<endl; exit(1);}

  int li=listen(descbrPub,10);
  struct sockaddr_in brCv;
  socklen_t lgbrCv=sizeof(struct sockaddr_in);
  
  while(1) {
    cout<<"Je suis le père de PID "<<getpid()<<" et attends une connexion"<<endl;
    int descbrCv=accept(descbrPub,(struct sockaddr*)&brCv, &lgbrCv);
    cout<<"Je délègue à mon fils le soin de traiter la demande du client"<<endl;

    switch(pid_t fils=fork()) {
      case -1 :
        cout<<"Erreur de fork"<<endl;
        break;
      
      case 0 : {
        cout<<"\tJe suis le fils de PID "<<getpid();
        close(descbrPub);
        char msg[256]="Tiens, bonjour ";
        uid_t buffer;
        int retourRecv=recvfrom(descbrCv, &buffer, sizeof(uid_t), 0, NULL, NULL);
        if(retourRecv == -1) {
          cout<<"erreur recv"<<endl;
        }
        char* nom=getpwuid(buffer)->pw_name;
        strcat(msg, nom);
        int retourSend=sendto(descbrCv, msg, cl(msg), 0, (sockaddr*) &brCv, sizeof(struct sockaddr_in));
        if(retourSend == -1) {
          cout<<"erreur send"<<endl;
        }
        cout<<" et j'ai traité le client \""<<nom<<"\""<<endl;
        cout<<"\t"<<getpid()<<" : je m'endors pour 10s le temps de remarquer les autres connexions..."<<endl;
        sleep(10);
        cout<<"\t"<<getpid()<<" : mon travail est terminé, bye bye !"<<endl;
        exit(0);
        break;
      }
      
      default :
        close(descbrCv);
        break;
    }
  }
  
return 0;
}
