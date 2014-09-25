#include "arbre.h"
#include "string.h"

arbre* creerArbre(void* cont)
{
	arbre* A=malloc(sizeof(arbre));
	A->contenu=cont;
	A->fils=NULL;
	A->frere=NULL;
	A->nbpointe=0;

	//	Pointeurs vers les fonctions :
	A->ajouterFrere=_ajouterFrere;
	A->ajouterFils=_ajouterFils;
	A->getFrereNbx=_getFrereNbx;
	A->getFilsNbx=_getFilsNbx;
	A->nbElementsArbre=_nbElementsArbre;
	A->estFeuille=_estFeuille;
	A->detruireArbre=_detruireArbre;
	A->cloneRacine=_cloneRacine;
	A->grefferArbre=_grefferArbre;
	A->grefferFrere=_grefferFrere;
	A->chaine=_chaine;

	return A;
};

arbre* _ajouterFrere(arbre* this,void* cont)
{
	if(this->frere==NULL)
	{
		this->frere=creerArbre(cont);
		//this->frere->nbpointe++;
		return this->frere;
	}
	else
		return this->frere->ajouterFrere(this->frere,cont);
}


arbre* _ajouterFils(arbre* this,void* cont)
{
	if(this->fils==NULL)
	{
		this->fils=creerArbre(cont);
		this->fils->nbpointe++;
		return this->fils;
	}
	else
		return this->fils->ajouterFrere(this->fils,cont);
}

arbre* _getFrereNbx(arbre* this,int nb)
{
	if(nb==0)
		return this;
	if(this->frere==NULL)
		return NULL;
	else
		return this->frere->getFrereNbx(this->frere,nb-1);
}

arbre* _getFilsNbx(arbre* this,int nb)
{
	if(this->fils==NULL)
		return NULL;
	else
		return this->fils->getFrereNbx(this->fils,nb-1);
}

int _nbElementsArbre(arbre* this)
{
	if((this->fils==NULL)&&(this->frere==NULL))
		return 1;
	else if(this->fils==NULL)
		return this->frere->nbElementsArbre(this->frere)+1;
	else if(this->frere==NULL)
		return this->fils->nbElementsArbre(this->fils)+1;
	else
		return this->fils->nbElementsArbre(this->fils)+this->frere->nbElementsArbre(this->frere)+1;
}

int _estFeuille(arbre* this)
{
	if(this->fils==NULL)
		return 1;
	else
		return 0;
}

//A faire: gérer nbpointe dans le detruireArbre
int _detruireArbre(arbre* this)
{
	if(this->nbpointe<=1)
	{
		if((this->fils==NULL)&&(this->frere==NULL))
		{
			free(this);
			this=NULL;
		//	printf("FREE!!!\n");
			return 0;
		}
		else if(this->fils==NULL)
		{
			if((this->frere->detruireArbre(this->frere)==0))
			{
				this->frere=NULL;
				return this->detruireArbre(this);
				this=NULL;
			}
			else
				return 1;
		}
		else if(this->frere==NULL) {
			if((this->fils->detruireArbre(this->fils)==0))
			{
				this->fils=NULL;
				return this->detruireArbre(this);
				this=NULL;
			}
			else
				return 1;
		}
		else
		{
			if((this->frere->detruireArbre(this->frere)==0)&&(this->fils->detruireArbre(this->fils)==0))
			{
				this->fils=NULL;
				this->frere=NULL;
				return this->detruireArbre(this);
				this=NULL;
			}
			else
				return 1;
		}
	}
	else
	{
		this->nbpointe--;
		return 0;
	}
}

//Attention : cloneNoeud() copie les pointeurs, source de segfault lors du detruireArbre()
//Copie non récursive, on modofie donc la fonction pour ne copier que la valeur "contenu". Elimine le problème de detruireArbre().
//Apres ajout d'un compteur du nombre de pointeurs vers le noeud dans la struct, clonenoeud copiera les pointeurs fils mais gardera le père à null: plus simple (le clone d'un arbre est donc une racine)
//A faire: gérer nbpointe dans le clonage
//clonenoeud devient cloneRacine, on ne doit cloner QUE des racines.
arbre* _cloneRacine(arbre* this)
{
	arbre* A=creerArbre(this->contenu);
	A->fils=this->fils;
	if(this->fils!=NULL)
		this->fils->nbpointe++;
	//	Une racine n'a PAS de frere !
	//	A->frere=this->frere;
	//	this->frere>nbpointe++;

	return A;
}

void _grefferArbre(arbre* this,arbre* A)
{
	if(this->fils==NULL)
	{
		this->fils=A;
		this->fils->nbpointe++;
		return;
	}
	else
		return this->fils->grefferFrere(this->fils,A);
}

void _grefferFrere(arbre* this,arbre* A)
{
	if(this->frere==NULL)
	{
		this->frere=A;
	//	this->frere->nbpointe++;
		return;
	}
	else
		return this->frere->grefferFrere(this->frere,A);
}
//La fonction chaine ne décrira qu'un noeud, respectant la description de nos objets (arbre*).
char* _chaine(arbre* this)
{
	char* toString=malloc(1024);
	sprintf(toString, "Noeud de valeur d'addresse : ");
	char tmp[20];
	sprintf(tmp,"%p", &this->contenu);
	strcat(toString, tmp);
	strcat(toString, " (pointé par ");
	sprintf(tmp, "%d", this->nbpointe);
	strcat(toString, tmp);
	strcat(toString, " pointeurs)");
	if(this->frere!=NULL)
	{
		strcat(toString,", frère (direct) : ");
		sprintf(tmp, "%p", this->frere);
		strcat(toString, tmp);
	}
	if(this->fils!=NULL)
	{
		strcat(toString,", fils (direct) : ");
		sprintf(tmp, "%p", this->fils);
		strcat(toString, tmp);
	}
	return toString;
}
