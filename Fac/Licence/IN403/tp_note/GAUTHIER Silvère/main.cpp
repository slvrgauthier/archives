#include <iostream>
using namespace std;
#include "personne.h"
#include "file.h"

int main(){
  File fa(10);
  Personne a("A",1),b("B",2),c("C",3),d("D",4),e("E",5),f("F",6),g("G",7),h("H",8),i("I",9),j("J",10),k("K",11),l("L",12),m("M",13),n("N",14),o("O",15),p("P",16),q("Q",17),r("R",18),s("S",19),t("T",20),u("U",21),v("V",22);

  fa.ajouter(a);
  fa.ajouter(b);
  fa.ajouter(c);
  fa.ajouter(d);
  fa.ajouter(e);
  fa.ajouter(f);
  fa.ajouter(g);
  fa.ajouter(h);

  //fa.etats();

  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();

  //fa.etats();

  fa.ajouter(i);
  fa.ajouter(j);
  fa.ajouter(k);

  fa.etats();

  fa.ajouter(l);
  fa.ajouter(m);
  fa.ajouter(n);
  fa.ajouter(o);

  fa.etats();
  fa.ajouter(p);

  fa.etats();

  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();
  fa.retirer();

  fa.etats();

  fa.ajouter(q);
  fa.ajouter(r);
  fa.ajouter(s);
  fa.ajouter(t);
  fa.ajouter(u);
  fa.ajouter(v);

  fa.etats();

return 0;
}
