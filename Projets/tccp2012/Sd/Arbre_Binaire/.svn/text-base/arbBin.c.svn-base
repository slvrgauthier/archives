#include "arbBin.h"

ArbBin creerArbre(void * m_valeur)
{
	ArbBin arbre = malloc(sizeof(arbBin));

	arbre->valeur = m_valeur;

	arbre->filsDroit = NULL;
	arbre->filsGauche = NULL;

	arbre->nbElemAbr = __nbElemAbr;
	arbre->estFeuille = __estFeuille;
	arbre->estComplet = __estComplet;

	arbre->ajoutNoeud = __ajoutNoeud;

	return arbre;
}

int __nbElemAbr(ArbBin this)
{
	if(this->estFeuille(this))
	{
		return 1;
	}
	else if(this->filsDroit == NULL)
	{
		return 1 + this->nbElemAbr(this->filsGauche);
	}
	else if(this->filsGauche == NULL)
	{
		return 1 + this->nbElemAbr(this->filsDroit);
	}
	else
	{
		return 2 + this->nbElemAbr(this->filsGauche) + this->nbElemAbr(this->filsDroit);
	}
}

int __estFeuille(ArbBin this)
{
	if(this->filsDroit == NULL && this->filsGauche == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void supprRecur(ArbBin this)
{
	if(this->estFeuille(this))
	{
 		free(this);
		this = NULL;
	}
	else
	{
		if(this->filsGauche != NULL && this->filsDroit == NULL)
		{
			supprRecur(this->filsGauche);

			free(this);

			this->filsGauche = NULL;
			this = NULL;
		}
		else if(this->filsGauche == NULL && this->filsDroit != NULL)
		{
			supprRecur(this->filsDroit);
 
			free(this);

			this->filsDroit = NULL;
			this = NULL;
		}
		else
		{
			supprRecur(this->filsGauche);
			supprRecur(this->filsDroit);

			free(this);

			this->filsDroit = NULL;
			this->filsGauche = NULL; 
			this = NULL;
		}
	}
}

ArbBin __ajoutNoeud(ArbBin this, void * m_valeur)
{
	if(this->estFeuille(this))
	{
		this->filsGauche = creerArbre(m_valeur);
		return this->filsGauche;
	}
	else if(this->filsGauche != NULL && this->filsDroit == NULL)
	{
		this->filsDroit = creerArbre(m_valeur);
		return this->filsDroit;
	}
	else if(this->filsDroit != NULL && this->filsGauche == NULL)
	{
		this->filsGauche = creerArbre(m_valeur);
		return this->filsGauche;
	}
	else
	{
		printf("Erreur : Le noeud %d n'a pas de fils libre pour %d.\n", this->valeur, m_valeur);
		return NULL;
	}
}

int __estComplet(ArbBin this)
{
	if(this->filsGauche != NULL && this->filsDroit != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void afficheArbre(ArbBin this)
{
	//Dans l'attente d'une solution, considérons que les noeuds contiennent des int

	if(this != NULL)
	{
		printf("Je ne suis pas nul.\n");
		if(this->estFeuille(this))
		{ 
			printf("%d\t", this->valeur);
		}
		else if(this->filsGauche != NULL && this->filsDroit == NULL)
		{
			printf("%d\n", this->valeur);
			afficheArbre(this->filsGauche);
		}
		else if(this->filsGauche == NULL && this->filsDroit != NULL)
		{
			printf("%d", this->valeur);
			afficheArbre(this->filsDroit);
		}
		else
		{
			printf("%d\n", this->valeur);
			afficheArbre(this->filsGauche);
			afficheArbre(this->filsDroit);
		} 
	}
	else
	{
		printf("L'arbre est vide.\n");
	}
}
