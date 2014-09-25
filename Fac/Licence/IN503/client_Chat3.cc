// Chat - Client
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
  Sock brLoc(SOCK_STREAM, 0);
  int descbrLoc;

  if(brLoc.good()) descbrLoc=brLoc.getsDesc();
  else {cout<<"pb BR locale"<<endl; exit(1);}

  SockDist brPub(argv[1], (short) 3500);
  sockaddr_in* adbrPub=brPub.getAdrDist();
  int lgAdrbrPub=sizeof(struct sockaddr_in);
  int co=connect(descbrLoc, (sockaddr*) adbrPub, lgAdrbrPub);

  if(co==-1) {cout<<"pb connect"<<endl; exit(2);}
  int quit=0;
  fd_set descR;
  int nbsurv=max(STDIN_FILENO, STDOUT_FILENO);


while(!quit) {
  FD_ZERO(&descR);
  FD_SET(STDIN_FILENO, &descR); FD_SET(STDOUT_FILENO, &descR);
  int action=select(nbsurv, &descR, NULL,NULL,NULL);
  if FD_ISSET(STDIN_FILENO, &descR) {
    char buffer[LGBUFFER];
    cin>>buffer;
    cout<<"OK!"<<endl;
    if(strcmp(buffer, "quit"))
      quit=1;
    else
      int retourSend=sendto(descbrLoc, buffer, cl(buffer), 0, (sockaddr*) adbrPub, sizeof(struct sockaddr_in));
  }

  if FD_ISSET(STDOUT_FILENO, &descR) {
    char buffer[LGBUFFER];
    int retourRecv=recv(descbrLoc, &buffer, LGBUFFER, 0);
    cout<<buffer<<endl;
  }
}

close(descbrLoc);
return 0;
}
