#include "typeBase.h"

/**
 * @mainpage Projet: Les Types de base.

 *
 *Description de la bibliothèque : 
 
 Les types disponibles : 
 
 Il y a actuellement 4 types qui ont été implémentés : 
 - Entier (équivalent int)
 - Flottant (équivalent float)
 - Car (équivalent char)
 - String (équivalent char*)
 
 
 Que représente un type ?
 
 Chaque type représente un pointeur sur une structure commune à tous les types (Type). 
 Les types se différencient dans une seconde structure interne.
 L'accès à la valeur stockée dans la variable ne peut se faire directement.
 Dans les fonctions génériques proposées, toutes les variables devront être de type Type.
 *
 *
 *\author VERDIER Frédéric, LAMEIRA Yannick
 */

/**
 * @brief Les constructeurs :
 *Ces constructeurs vont nous permettre de créer une variable avec la syntaxe suivante : 
 < Type> <variable> = <Type>_Creer(<valeur>);                                                                       *
 Ils sont les seules fonctions dépendantes du type (mises à part les fonctions spécifiques à String).
 * @param valeur La valeur à stocker dans la variable.
 * @return valeur déclaré dans son bon type

 */
Entier Entier_Creer(int valeur)
/*Renvoie un Entier dont la valeur stockée est valeur.*/
{
        Entier e=malloc(sizeof(Entier));
        e->type=1;
	e->objet=(entier)malloc(sizeof(entier));
	((entier)e->objet)->val=valeur;
        return e;
}

Flottant Flottant_Creer(float valeur)
/*Renvoie un Flottant dont la valeur stockée est valeur.*/
{
	Flottant f=malloc(sizeof(Flottant));
	f->type=2;
	f->objet=(flottant)malloc(sizeof(flottant));
	((flottant)f->objet)->val=valeur;
	return f;
}
//Autres fonctions à implementer

Car Car_Creer(char valeur)
/*Renvoie un Caractere dont la valeur stockée est valeur.*/
{
	Car c=malloc(sizeof(Car));
	c->type=3;
	c->objet=(car)malloc(sizeof(car));
	((car)c->objet)->val=valeur;
	return c;
}

String String_Creer(char* valeur)
/*Renvoie une Chaine de caractere dont la valeur stockée est valeur.*/
{
	String s=malloc(sizeof(String));
	s->type=4;
	s->objet=(string)malloc(sizeof(string));
	((string)s->objet)->taille=strlen(valeur);
	((string)s->objet)->val=malloc((strlen(valeur)+1)*sizeof(char));
	strcpy(((string)s->objet)->val,valeur);
	return s;
}

/**
 * @brief Les destructeurs :
 *Ces destructeur vont nous permettre de libérer la zone mémoire allouée par une variable a. On utilisera la fonction void Detruire(Type a).                                                                    
 * @param object La variable à détruire.
 */
//Entier
void Detruire(Type object)
/*Libere la memoire allouée par object*/
{
	if(object->type==4)
	{
		free(((string)object->objet)->val);
		((string)object->objet)->val=NULL;
	}
	free(object->objet);
	object->objet = NULL;
	free(object);
	object = NULL;
}

/**
 * @brief Les copies de variables :
 *Pour copier une variable, il faut utiliser void* Clone(Type a).
 Pour cela, on utilisera un switch pour nous permettre de choisir suivant le type de object.
 Exemple : 
 Entier e = Entier_Creer(5);
 Entier e2 = Clone(e);
 * @param object La variable à copier.
 * @return une copie de object, NULL en cas d'erreur.
 */

void* Clone(Type object)
/*Renvoie une copie de object, NULL en cas d'erreur...*/
{
	switch(object->type)
	{
		case 1 : 
			return Entier_Creer(((entier)object->objet)->val);
		break;
		case 2 : 
			return Flottant_Creer(((flottant)object->objet)->val);
		break;
		case 3 : 
			return Car_Creer(((car)object->objet)->val);
		break;
		case 4 : 
			return String_Creer(((string)object->objet)->val);
		break;
		//Autres types à implémenter ici...
		default : 
			printf("Erreur lors du clonage.\n"); 
			return NULL;
		break;
	}
}

/**
 * @brief Les tests d'égalité :
 *La fonction int Egal(Type a, Type b) renvoie 0 si a=b, 1 sinon.
 A noter que si a et b sont de type différent, la fonction renverra 1.
 Exemple : 
 Entier e = Entier_Creer(5);
 Entier e2 = Clone(e);
 Entier e3 = Entier_Creer(4);
 Egal(e, e2); (= 0)
 Egal(e, e3); (= 1)                                                               
 * @param a La variable à gauche de l'égalité à tester.
 * @param b La variable à droite de l'égalité à tester.
 * @return renvoie 0 si égal sinon renvoie 1
 * 
 */

int Egal(Type a, Type b)
/*Renvoie 0 si a=b, 1 sinon...*/
{
	if(a->type==b->type)
	{
		switch(a->type)
		{
			case 1 : 
				if(((entier)a->objet)->val==((entier)b->objet)->val)
				{
					return 0;
				}
				else return 1;
			break;
			case 2 : 
				if(((flottant)a->objet)->val==((flottant)b->objet)->val)
				{
					return 0;
				}
				else return 1;
			break;
			case 3 : 
				if(((car)a->objet)->val==((car)b->objet)->val)
				{
					return 0;
				}
				else return 1;
			break;
			case 4 : 
				if(strcmp(((string)a->objet)->val,((string)b->objet)->val)==0)
				{
					return 0;
				}
				else return 1;
			//Autres types à implémenter ici...
			default : 
				return 1;
			break;
		}
	}
	else return 1;
}

/**
 * @brief Les comparaisons :
 *La fonction Compare(Type a, Type b) compare un Type a à un Type B.
 Exemple : 
 Entier e = Entier_Creer(5);
 Entier e1 = Entier_Creer(4);
 Flottant e2 = Flottant_Creer(5.);
 Compare(e,e1); (=-1)
 Compare(e,e2); (=-2  Un message d'erreur est ecrit sur la sortie standard)
 * @param a La variable à gauche de l'inégalité.
 * @param b La variable à droite de l'inégalité.
 * @return -1 si a < b, 0 si a=b, 1 si a > b, et -2 en cas d'érreur.
 * 
 */

int Compare(Type a, Type b)
/*Renvoie 0 si a=b, -1 si a<b, 1 si a>b, -2 en cas d'erreur...*/
{
	if(a->type==b->type)
	{
		switch(a->type)
		{
			case 1 : 
				if(((entier)a->objet)->val==((entier)b->objet)->val)
				{
					return 0;
				}
				else if(((entier)a->objet)->val<((entier)b->objet)->val)
				{
					return -1;
				}
				else
				{
					return 1;
				}
			break;
			case 2 : 
				if(((flottant)a->objet)->val==((flottant)b->objet)->val)
				{
					return 0;
				}
				else if(((flottant)a->objet)->val<((flottant)b->objet)->val)
				{
					return -1;
				}
				else
				{
					return 1;
				}
			break;
			case 3 : 
				if(((car)a->objet)->val==((car)b->objet)->val)
				{
					return 0;
				}
				else if(((car)a->objet)->val<((car)b->objet)->val)
				{
					return -1;
				}
				else
				{
					return 1;
				}
			break;
			case 4 :
				if(strcmp(((string)a->objet)->val,((string)b->objet)->val)==0)
				{
					return 0;
				}
				else if(strcmp(((string)a->objet)->val,((string)b->objet)->val)<0)
				{
					return -1;
				}
				else
				{
					return 1;
				}
			break;
			//Autres types à implémenter ici...
			default : 
				printf("Variables passées en parametre non reconnues...");
				return -2;
			break;
		}
	}
	else
	{ 
		printf("Variables de types differents...");
		return -2;
	}
}
	
/**
 * @brief Affichage:
 *La fonction void Affiche(Type a) affichera dans la sortie standard la valeur stockée dans a.
 Exemple : 
 Entier e = Entier_Creer(5);
 Affiche(e); > 5
 * @param a La variable dont on veut afficher la valeur.
 *
 */	

void Affiche(Type a)
/*Affiche la valeur stockée dans a.*/
{
	switch(a->type)
	{
		case 1 : 
			printf("%d", ((entier)a->objet)->val);
		break;
		case 2 : 
			printf("%f", ((flottant)a->objet)->val);
		break;
		case 3 : 
			printf("%c", ((car)a->objet)->val);
		break;
		case 4 : 
			printf("%s", ((string)a->objet)->val);
		break;
		//Autres types à implémenter ici...
		default : 
			printf("La variable passée en parametre n'est pas reconnue...");
		break;
	}
}

/**
 * @brief Récupérer la valeur:
 *On récupère la valeur : 
 La fonction void* Eval(Type a) renvoie un pointeur vers la valeur stockée dans a.
 Exemple : 
 Entier e = Entier_Creer(5);
 int* v = Eval(e);
 Attention : Modifier v modifiera e.
 * @param a La variable dont on veut récupérer la valeur.
 * @return  pointeur sur la valeur stockée dans la variable.
 *
 */	


void* Eval(Type a)
/*Renvoie un pointeur sur la valeur stockée dans a, NULL en cas d'erreur...*/
{
	switch(a->type)
	{
		case 1 : 
			return &(((entier)a->objet)->val);
		break;
		case 2 : 
			return &(((entier)a->objet)->val);
		break;
		case 3 : 
			return &(((car)a->objet)->val);
		break;
		case 4 : 
			return ((string)a->objet)->val	;
		break;
		//Autres types à implémenter ici...
		default : 
			printf("La variable passée en parametre n'est pas reconnue...");
			return NULL;
		break;
	}
	return NULL;
}
/**
 * @brief Modifie la valeur:
 *La fonction void Modifie(Type a, void* b) modifiera la valeur stockée dans a par la valeur pointée par b.
 Dans le cas ou b est d'un type différent de a, un cast est effectué.
 Exemple : 
 Entier e = Entier_Creer(5);
 char c = 'a';
 Modifie(e, &c); (e vaudra 97)
 * @param a La variable dont on veut modifier la valeur.
 * @param b La nouvelle valeur stockée dans a. 
 * 
 */

void Modifie(Type a, void* b)
/*Modifie la valeur stockée dans a par la valeur pointée par b. 
  La valeur de b est castée automatiquement au type de a.*/
{
	int* v1;
	float* v2;
	char* v3;
	switch(a->type)
	{
		case 1 : 
			v1=Eval(a);
			*v1 = *((int*)b);
		break;
		case 2 : 
			v2 = Eval(a);
			*v2 = *((float*)b);
		break;
		case 3 :
			v3 = Eval(a);
			*v3 = *((char*)b);
		break;
		case 4 : 
			v3 = Eval(a);
			v3 = realloc(v3, (strlen((char*)b)+1)*sizeof(char));
			strcpy(v3,(char*)b);
		break;
		//Autres types à implémenter ici...
		default : 
			printf("Le type du premier parametre n'est pas reconnu...");
		break;
	}
}

/**
 * @brief Convertir en String:
 *La fonction String toString(Type a) renvoie un String contenant la valeur stockée dans a.
 Exemple : 
 Entier e = Entier_Creer(5);
 String s = toString(e); (s vaudra "5")
 * @param a La variable à convertir en String.
 * @return un String .
 * 
 */

String toString(Type a)
/*Renvoie la conversion de la valeur stockée dans a en String*/
{
	char s[1024];
	String result;
	switch(a->type)
	{
		case 1 : 
			if(sprintf(s,"%d",((entier)a->objet)->val)>0)
			{
				result = String_Creer(s);
				return result;
			}
			else
			{
				printf("Erreur de conversion");
				return NULL;
			}
		break;
		case 2 : 
			if(sprintf(s, "%f",((flottant)a->objet)->val)>0)
			{
				result = String_Creer(s);
				return result;
			}
			else
			{
				printf("Erreur de conversion");
				return NULL;
			}
		break;
		case 3 : 
			if(sprintf(s, "%c",((car)a->objet)->val)>0)
			{
				result = String_Creer(s);
				return result;
			}
			else
			{
				printf("Erreur de conversion");
				return NULL;
			}
		break;
		case 4 :
			result = Clone(a);
			return result;
		break;
		//Autres types à implémenter ici...
		default : 
			printf("Type du paramètre non reconnu...");
			return NULL;
		break;
	}
	return NULL;
}

/**
 * @brief Concaténation:
 *La fonction void String_Concat(String a, String b) concatène la chaine de caractère contenue dans a et celle contenue dans b et la stock dans a.
 Exemple : 
 String s1 = String_Creer("Salut");
 String s2 = String_Creer(" lecteur !");
 String_Concat(s1,s2);
 Afficher(s1); > Salut lecteur !
 * @param a La variable à gauche de la concaténation dans laquelle on stocke le résultat de la concaténation.
 * @param b La variable à droite de la concaténation.
 * 
 */

void String_Concat(String a, String b)
/*Concatene la valeur de a et celle de b dans a*/
{
	strcat(((string)a->objet)->val,((string)b->objet)->val);
}
/**
 * @brief Connaître la taille du String:
 *Int String_Taille(String a) renvoie la taille de la chaine de caractères contenue dans a.
 Exemple : 
 String s = String_Creer("Coucou");
 int t = String_Taille(s); (t vaudra 6)
 * @param a La variable à analyser.
 * @return taille de la chaine de caractère.
 * 
 */
int String_Taille(String a)
/*Renvoie la taille du tableau char* contenu dans a*/
{
	return ((string)a->objet)->taille;
}
/**
 * @brief Accéder à un caractère d'un String:
 *Char String_At(String a, int i) renvoie le caractère à l'indice i de la chaine de caractères contenue dans a.
 Exemple : 
 String s = String_Creer("Coucou");
 char c = String_At(s, 2); (c vaudra 'u')
 * @param a La variable sur laquelle s'applique la fonction.
 * @param i L'indice du caractère à récupérer dans la chaine de caractères.
 * @return le caractère à la position i stockée dans la chaine de caractères contenue dans a, '\0' en cas d'erreur.
 * 
 */


char String_At(String a, int indice)
/*Renvoie le caractère se trouvant à l'indice indice du tableau contenu dans a*/
{
	if((indice>=0)&&(indice<((string)a->objet)->taille))
	{
		return ((string)a->objet)->val[indice];
	}
	else
	{
		printf("Erreur indice incorrect...");
		return '\0';
	}
}

