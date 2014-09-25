#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include "sock.h"
#include "sockdist.h"

using namespace std;

int main(int argc, char* argv[], char* env[]) {
  Sock brLoc(SOCK_DGRAM, (short)0, 0);
  int descbrLoc; 
  sockaddr_in adbrLoc; 
  socklen_t lenbrLoc=sizeof(struct sockaddr_in);

  if(brLoc.good()) { 
    descbrLoc=brLoc.getsDesc();
    int log=getsockname(descbrLoc, (struct sockaddr*) &adbrLoc, &lenbrLoc);

    if (log==0)
      cout<<"BR : "<<ntohs(adbrLoc.sin_port)<<endl;
    else 
      cout<<"pb getsockname"<<endl;
  }
  else { 
    cout<<"pb BR locale"<<endl; 
    exit(1); 
  }
  
return 0;
}
