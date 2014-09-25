// Apprifix - Serveur
#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include "sock.h"
#include "sockdist.h"
#include "string.h"

#define LGBUFFER 1024

using namespace std;

int cl(char* s){
  int l=0,i=0;
  while(s[i]!='\0'){
    l++;i++;
  }
  return l+1;
}

int main(int argc, char* argv[], char* env[]) {
  Sock brLoc(SOCK_DGRAM, (short)3555, 0);
  int descbrLoc; 

  if(brLoc.good()) { 
    descbrLoc=brLoc.getsDesc();
  }
  else { 
    cout<<"pb BR locale"<<endl; 
    exit(1); 
  }

  SockDist brDist("h16", 3000);
  sockaddr_in* adbrDist=brDist.getAdrDist();
  char* msg="Message bien reçu : ";
  char buffer[LGBUFFER];

  while(strcmp(buffer,"quit")!=0){
    int retourRecv=recvfrom(descbrLoc, &buffer, LGBUFFER, 0, NULL, NULL);
    cout<<"Approlix : "<<buffer<<endl;
    int retourSend=sendto(descbrLoc, msg, cl(msg), 0, (sockaddr*) adbrDist, sizeof(struct sockaddr_in));
    cout<<"Apprifix : "<<msg<<buffer<<endl;
  }

return 0;
}
