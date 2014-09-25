#include "string.h"
using namespace std;

class Article{
  public:
    int ref;
    float prix;
    string nom;
    bool promo;
    int reduc[4];

    Article();
    Article(int,float,string,bool);

    int getRef();
    void setRef(int);
    float getPrix();
    void setPrix(float);
    string getNom();
    void setNom(string);
    bool getPromo();
    void setPromo(bool);

    void saisie();
    void afficher();
};
