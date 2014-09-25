
#ifndef _TYPEBASE_
#define _TYPEBASE_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Définition des types*/
typedef struct Type* Type;
/**
 * 
 * \brief Strutures de Type Entier : 
 * Cette strutures va nous permettre de créer les types Entier . Ce type sera appelé par un int égal à 1. 
 */
typedef struct Type* Entier;	//type = 1
/**
 * 
 * \brief Strutures de Type Flottant : 
 * Cette strutures va nous permettre de créer les types Flottant . Ce type sera appelé par un int égal à 2. 
 */
typedef struct Type* Flottant;	//type = 2	
/**
 * 
 * \brief Strutures de Type Car : 
 * Cette strutures va nous permettre de créer les types Car . Ce type sera appelé par un int égal à 3. 
 */
typedef struct Type* Car;	//type = 3
/**
 * 
 * \brief Strutures de Type String : 
 * Cette strutures va nous permettre de créer les types String . Ce type sera appelé par un int égal à 4. 
 */
typedef struct Type* String;	//type = 4


typedef struct entier* entier;
typedef struct flottant* flottant;
typedef struct car* car;
typedef struct string* string;


struct Type
/*Structure générique à tous les types*/
{
	int type;
	void* objet;
};

struct entier
/*Structure representant un Entier*/
{
        int val;       //Pointeur sur la valeur a stocker.
};

struct flottant
/*Structure representant un Flottant*/
{
	float val;
};

//Autres types à implémenter ici...

struct car
/*Structure representant un caractère*/
{
	char val;
	
};

struct string
/*Structure representant une chaine de caractère*/
{
	char* val;
	int taille;
};


Entier Entier_Creer(int valeur);       //Constructeur d'un Entier
Flottant Flottant_Creer(float valeur);	//Constructeur d'un Flottant
//Autres constructeurs pour les autres types à implémenter ici...
Car Car_Creer(char valeur);
String String_Creer(char* valeur);

/*Fonctions generiques : fonctionne pour tous les types.*/
void Detruire(Type objet);          //Libère la mémoire allouée par objet
void* Clone(Type objet);       //Renvoie le pointeur d'une copie de la structure pointée par le paramètre
int Egal(Type a, Type b);    //Renvoie 0 si a=b, 1 sinon
int Compare(Type a, Type b);	//Renvoie -1 si a<b, 0 si a=b, 1 si a>b, -2 en cas d'erreur
void Affiche(Type objet);     //Affiche sur la sortie standard la valeur et le type de la structure pointée par objet
void* Eval(Type objet);		//Renvoie un pointeur sur la valeur stockée par objet
void Modifie(Type objet, void* val);
String toString(Type a);	//Renvoie la valeur stockée dans a sous forme de String
void String_Concat(String a, String b);	//Concatene la valeur de a et celle de b dans a
int String_Taille(String a);	//Renvoie la taille de la chaine de caractères contenue dans a
char String_At(String a, int indice);	//Renvoie le caractère contenu dans la chaine de caractère de a à la position indice

#endif
