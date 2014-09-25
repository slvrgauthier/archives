// TCP - Serveur
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

  int li=listen(descbrPub,1);
  struct sockaddr_in brCv;
  socklen_t lgbrCv=sizeof(struct sockaddr_in);
  int descbrCv=accept(descbrPub,(struct sockaddr*)&brCv, &lgbrCv);

  char msg[256]="Tiens, bonjour ";
  uid_t buffer;
  int retourRecv=recvfrom(descbrCv, &buffer, sizeof(uid_t), 0, NULL, NULL);
  cout<<"Reçu : "<<buffer<<endl;
  strcat(msg, getpwuid(buffer)->pw_name);
  int retourSend=sendto(descbrCv, msg, cl(msg), 0, (sockaddr*) &brCv, sizeof(struct sockaddr_in));
  cout<<"Envoi : "<<msg<<endl;

return 0;
}
