#include "typeBase.h"

int main()
{
	printf("Bienvenue sur l'interface test des types de base...\n");
	printf("\nTest des constructeurs : \n");
	Entier a = Entier_Creer(4);
	Flottant b = Flottant_Creer(4.2);
	Car cc = Car_Creer('c');
	String s = String_Creer("Coucou");
	printf("(Entier) %d (= 4)\n", ((entier)a->objet)->val);
	printf("(Flottant) %f (=4.2)\n", ((flottant)b->objet)->val);
	printf("(Car) %c (=c)\n", ((car)cc->objet)->val);
	printf("(String) %s (=Coucou)\n", ((string)s->objet)->val);
	
	printf("\nTest de destructeur : \n");
	Entier t = Entier_Creer(5);
	String ss = String_Creer("Coucou");
	printf("(Entier) %d (>0) \n", ((entier)t->objet)->val);
	printf("(String) %s (>0) \n", ((string)ss->objet)->val);
	Detruire(t);
	Detruire(ss);
	//printf("%d (=?) \n", ((entier)t->objet)->val);     //Note : Test de la destruction de l'objet
	//printf("%s (=?) \n", ((string)ss->objet)->val);    //Note : Test de la destruction de l'objet
	
	printf("\nTest de Clone() : \n");
	Entier c = Clone(a);
	String s1 = Clone(s);
	printf("%d (=4)\n",((entier)c->objet)->val);
	printf("%s (=Coucou)\n",((string)s1->objet)->val);
	
	printf("\nTest de Egal() : \n");
	int e=Egal(a, c);
	printf("%d (=0) \n",e);
	e=Egal(a,b);
	printf("%d (=1) \n",e); 
	Entier d = Entier_Creer(3);
	e=Egal(a,d);
	printf("%d (=1) \n",e);
	e=Egal(s,s1);
	printf("%d (=0) \n",e);
	
	printf("\nTest de Compare() : \n");
	e=Compare(a, c);
	printf("%d (=0) \n",e);
	e=Compare(a,b);
	printf("%d (=-2) \n",e);
	e=Compare(a, d);
	printf("%d (=1) \n",e);
	Entier g=Entier_Creer(6);
	e=Compare(a,g);
	printf("%d (=-1) \n",e);
	String s2=String_Creer("Coucouuuuu");
	e=Compare(s,s2);
	printf("%d (=-1) \n",e);
	
	printf("\nTest de Eval() : \n");
	int *a1 = Eval(a);
	float *b1 = Eval(b);
	char* s3 = Eval(s);
	printf("%d (=4)\n", *a1);
	printf("%f (=4.2)\n", *b1);
	printf("%s (=Coucou)\n",s3);
	
	printf("\nTest de Modifie() : \n");
	*a1 = 12;
	Entier a2 = Entier_Creer(4);
	Modifie(a2, a1);
	printf("%d (=12)\n",((entier)a2->objet)->val);
	char* a3 = "slotting";
	Modifie(a2, a3);
	printf("%d (=?)\n",((entier)a2->objet)->val);
	float a4=4.2;
	Modifie(a2, &a4);
	printf("%d (=?)\n",((entier)a2->objet)->val);
	double a5 = 12;
	Modifie(a2, &a5);
	printf("%d (=0)\n",((entier)a2->objet)->val);
	char a6 = 'a';
	Modifie(a2, &a6);
	printf("%d (=97)\n",((entier)a2->objet)->val);
	char* s4="Cocon";
	String s5 = String_Creer("Coucou");
	Modifie(s5,s4);
	printf("%s (=Cocon)\n",((string)s5->objet)->val);
	
	printf("\nTest de Affiche() : \n");
	Affiche(a);
	printf(" (Le nombre 4 doit apparaitre avant ceci)\n");
	Affiche(b);
	printf(" (Le nombre 4.2 doit apparaitre avant ceci)\n");
	Affiche(cc);
	printf(" (La lettre c doit apparaitre avant ceci)\n");
	Affiche(s);
	printf(" (Le mot Coucou doit apparaitre avant ceci)\n");
	
	printf("\nTest de toString() : \n");
	String s6;
	s6 = toString(a);
	Affiche(s6);
	printf(" (Le nombre 4 doit apparaitre avant ceci)\n");
	s6 = toString(b);
	Affiche(s6);
	printf(" (Le nombre 4.2 doit apparaitre avant ceci)\n");
	s6 = toString(cc);
	Affiche(s6);
	printf(" (La lettre c doit apparaitre avant ceci)\n");
	s6 = toString(s);
	Affiche(s6);
	printf(" (Le mot Coucou doit apparaitre avant ceci)\n");
	
	printf("\nTest de Concatene() : \n");
	String_Concat(s6,s);
	Affiche(s6);
	printf(" (Le mot CoucouCoucou doit apparaitre avant ceci)\n");
	String_Concat(s6,s6);
	Affiche(s6);
	printf(" (Le mot CoucouCoucouCoucouCoucou doit apparaitre avant ceci)\n");
	
	printf("\nTest de String_At() : \n");
	char ccc = String_At(s, 2);
	printf("%c (=u)\n",ccc);
	
	printf("\nTest de String_Taille() : \n");
	int taille = String_Taille(s);
	printf("%d (=6)\n",taille);
	
	return 0;
}


