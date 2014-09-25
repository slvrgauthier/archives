#include <cstdlib>
#include <iostream>
#include <netdb.h>

using namespace std;

int main(int argc, char* argv[], char* env[]) {

struct hostent* h=gethostbyname(argv[1]);

cout<<"Nom : "<<h->h_name<<endl;
cout<<"Alias : "<<h->h_aliases<<endl;
cout<<"Type d'adresse : "<<h->h_addrtype<<endl;
cout<<"Longueur de l'adresse : "<<h->h_length<<endl;
cout<<"Adresses : ";
int j=0;
while(h->h_addr_list[j]!=NULL) {
  if(j!=0)
    cout<<"           ";
  for(int i=0;i<h->h_length-1;i++)
    cout<<(int)((unsigned char)h->h_addr_list[j][i])<<".";
  cout<<(int)((unsigned char)h->h_addr_list[j][h->h_length-1])<<endl;
  j++;
}

return 0;
}

/*
Ex 5 : 
On remarque que www.lirmm.fr et janela.lirmm.fr sont dans le même réseau (par le nom de domaine comme par l'adresse ip).
Le nom officiel de imag.fr est rillet.imag.fr.
J'obtiens la même adresse IP avec "getent hosts i10".(i10 étant la machine sur laquelle je travaille)
Certains appels comme inet_ntoa qui convertit directement l'adresse binaire en nombres et points auraient étés utiles pour alléger la syntaxe de notre programme, le rendant plus simple à lire.

Avec toutes les commandes nslookup, dig et host, on obtient exactement les même adresses IP qu'avec notre programme.
*/

