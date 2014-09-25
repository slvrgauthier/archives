#ifndef _ABRBIN_H_
#define _ABRIN_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct arbBin arbBin;
typedef arbBin * ArbBin;

struct arbBin
{
	void * valeur;

	ArbBin filsDroit;
        ArbBin filsGauche;

	int (*nbElemAbr)(ArbBin this);
	int (*estFeuille)(ArbBin this);
	int (*estComplet)(ArbBin this);

	ArbBin (*ajoutNoeud)(ArbBin this, void * m_valeur);	
};

ArbBin creerArbre(void * m_valeur);
void supprRecur(ArbBin this);

int __nbElemAbr(ArbBin this);
int __estFeuille(ArbBin this);
int __estComplet(ArbBin this);

ArbBin __ajoutNoeud(ArbBin this, void * m_valeur);
void afficheArbre(ArbBin this);

#endif
