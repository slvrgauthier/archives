#ifndef GROUPEAMIS_H
#define GROUPEAMIS_H

#include "Personne.h"

class GroupeAmis {
  private :
    Personne personne;
    GroupeAmis* sousgroupe;

  public :
    GroupeAmis();
    GroupeAmis(const Personne&, GroupeAmis*);
    ~GroupeAmis();

    void operator=(const GroupeAmis&);
    void operator+(const GroupeAmis&);
    void operator+(const Personne&);

    bool EstVide()const;
    void ajouter(const Personne&);
    void supprimer(const Personne&);
    void afficher()const;
    bool appartient(const Personne&);
};

#endif
