#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include "sock.h"
#include "sockdist.h"

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
  Sock brLoc(SOCK_DGRAM, (short)0, 0);
  int descbrLoc; 

  if(brLoc.good()) { 
    descbrLoc=brLoc.getsDesc();
  }
  else { 
    cout<<"pb BR locale"<<endl; 
    exit(1); 
  }

  SockDist brDist("l9", 31469);
  sockaddr_in* adbrDist=brDist.getAdrDist();
  char msg[LGBUFFER];
  char buffer[LGBUFFER];

  while(!(msg[0]=='q' && msg [1]=='u'  && msg[2]=='i' && msg[3]=='t' && msg[4]=='\0')){
    cin>>msg;
    int retourSend=sendto(descbrLoc, msg, cl(msg), 0, (sockaddr*) adbrDist, sizeof(struct sockaddr_in));
    int retourRecv=recvfrom(descbrLoc, &buffer, LGBUFFER, 0, NULL, NULL);
    cout<<buffer<<endl;
  }

return 0;
}
