// TCP - Client
#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include "sock.h"
#include "sockdist.h"
#include "string.h"

#define LGBUFFER 1024

using namespace std;

int main(int argc, char* argv[], char* env[]) {
  Sock brLoc(SOCK_STREAM, 0);
  int descbrLoc;

  if(brLoc.good()) descbrLoc=brLoc.getsDesc();
  else {cout<<"pb BR locale"<<endl; exit(1);}

  SockDist brPub(argv[1], (short) 3555);
  sockaddr_in* adbrPub=brPub.getAdrDist();
  int lgAdrbrPub=sizeof(struct sockaddr_in);
  int co=connect(descbrLoc, (sockaddr*) adbrPub, lgAdrbrPub);

  if(co==-1) {cout<<"pb connect"<<endl; exit(2);}
  uid_t msg=getuid();
  char buffer[LGBUFFER];

  int retourSend=sendto(descbrLoc, &msg, sizeof(uid_t), 0, (sockaddr*) adbrPub, sizeof(struct sockaddr_in));
  cout<<"Envoi : "<<msg<<endl;
  int retourRecv1=recvfrom(descbrLoc, &buffer, LGBUFFER, 0, NULL, NULL);
  cout<<"Reçu : "<<buffer<<endl;

return 0;
}
