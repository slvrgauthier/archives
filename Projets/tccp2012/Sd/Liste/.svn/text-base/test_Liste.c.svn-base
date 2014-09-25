#include <stdio.h>
#include "liste.h"

void test_Creation_Cellule(){
    printf("Debut du test Cellule_creer()\n");
    printf("------\n");
    printf("Creation d'une Cellule associe a un short* de valeur 5\n");
    short value = 5;
    Cellule c = Cellule_creer(&value);
    c->ta = associe_short;
    printf("Adresse : %p\nValeur : %d\nPrecedant : %p\nSuivant : %p\nNombre d'utilisation : %d\n",&c,*(short*)c->data,c->previous,c->next,c->used);
    printf("------\n");
    printf("Creation d'une Cellule associe a un char* de valeur \"Hello World\"\n");
    char* string = "Hello World";
    Cellule cp = Cellule_creer(&string);
    printf("Adresse : %p\nValeur : %s\nPrecedant : %p\nSuivant : %p\nNombre d'utilisation : %d\n",&cp,*(char**)cp->data,cp->previous,cp->next,cp->used);
    printf("------\n");
    printf("Fin du test Cellule_creer()\n\n");
    Cellule_detruire(c);
    Cellule_detruire(cp);
}

void test_Creation_Liste(){
    printf("Debut du test Liste_creer()\n");
    printf("------\n");
    printf("Creation d'une Cellule associe a un short* de valeur 5 puis creation d'une liste avec cette Cellule\n");
    short value = 5;
    Cellule c = Cellule_creer(&value);
    Liste l = Liste_creer(c,associe_short);
    printf("Pointeur de la cellule : %p\nCellule pointé : %p\n",c,l->entry);
    printf("Taille de la liste : %d\nPointeur vers la fonction a() : %p\n",l->size,l->a);
    printf("Pointeur vers la fonction premierElement() : %p\nPointeur vers la fonction dernierElement() : %p\n",l->premierElement,l->dernierElement);
    printf("Pointeur vers la fonction egal() : %p\nPointeur vers la fonction insererDebut() : %p\n",l->egal,l->insererDebut);
    printf("Pointeur vers la fonction insererFin() : %p\nPointeur vers la fonction insererAIndex() : %p\n",l->insererFin,l->insererAIndex);
    printf("Pointeur vers la fonction supprimerPremier() : %p\nPointeur vers la fonction supprimerDernier() : %p\n",l->supprimerPremier,l->supprimerDernier);
    printf("Pointeur vers la fonction sousListe() : %p\n",l->sousListe);
    printf("------\n");
    printf("Creation d'une Cellule associe a un char* de valeur \"Hello World\" puis creation d'une liste avec cette Cellule\n");
    char* string = "Hello World";
    Cellule cp = Cellule_creer(&string);
    Liste lp = Liste_creer(cp,associe_chaine);
    printf("Pointeur de la cellule : %p\nCellule pointé : %p\n",cp,lp->entry);
    printf("Taille de la liste : %d\nPointeur vers la fonction a() : %p\n",lp->size,lp->a);
    printf("Pointeur vers la fonction premierElement() : %p\nPointeur vers la fonction dernierElement() : %p\n",lp->premierElement,lp->dernierElement);
    printf("Pointeur vers la fonction egal() : %p\nPointeur vers la fonction insererDebut() : %p\n",lp->egal,lp->insererDebut);
    printf("Pointeur vers la fonction insererFin() : %p\nPointeur vers la fonction insererAIndex() : %p\n",lp->insererFin,lp->insererAIndex);
    printf("Pointeur vers la fonction supprimerPremier() : %p\nPointeur vers la fonction supprimerDernier() : %p\n",lp->supprimerPremier,lp->supprimerDernier);
    printf("Pointeur vers la fonction sousListe() : %p\n",lp->sousListe);
    printf("------\n");
    printf("Creation d'une liste vide (initilise a NULL)\n");
    Liste ln = Liste_creer(NULL,associe_void);
    printf("Cellule pointé : %p\n",ln->entry);
    printf("Taille de la liste : %d\nPointeur vers la fonction a() : %p\n",ln->size,ln->a);
    printf("Pointeur vers la fonction premierElement() : %p\nPointeur vers la fonction dernierElement() : %p\n",ln->premierElement,ln->dernierElement);
    printf("Pointeur vers la fonction egal() : %p\nPointeur vers la fonction insererDebut() : %p\n",ln->egal,ln->insererDebut);
    printf("Pointeur vers la fonction insererFin() : %p\nPointeur vers la fonction insererAIndex() : %p\n",ln->insererFin,ln->insererAIndex);
    printf("Pointeur vers la fonction supprimerPremier() : %p\nPointeur vers la fonction supprimerDernier() : %p\n",ln->supprimerPremier,ln->supprimerDernier);
    printf("Pointeur vers la fonction sousListe() : %p\n",ln->sousListe);
    printf("------\n");
    printf("Fin du test Liste_creer()\n\n");
    Liste_detruire(l);
    Liste_detruire(lp);
    Liste_detruire(ln);
}

void test_Liste_premierElement(){
    printf("Debut du test Liste_premierElement()\n");
    printf("------\n");
    printf("Creation d'une Cellule  c associe a un int* de valeur 5 puis creation d'une liste l avec cette Cellule\n");
    int value = 5;
    short value2 = 10;
    Cellule c = Cellule_creer(&value);
    Liste l = Liste_creer(c,associe_int);
    printf("Cellule_afficher(Liste_premierElement(l)) : ");
    Cellule_afficher(Liste_premierElement(l));
    printf("\n------\n");
    printf("Creation d'une liste vide lp\n");
    Liste lp = Liste_creer(NULL,associe_chaine);
    printf("Cellule_afficher(Liste_premierElement(lp)) : ");
    Cellule_afficher(Liste_premierElement(lp));
    printf("\n------\n");
    printf("Creation d'une liste ln initialise a c, et insertion en fin d'une cellule contenant un short* de valeur 10 (associe au type short)\n");
    Liste ln = Liste_creer(c,associe_void);
    Cellule cl = Cellule_creer(&value2);
    cl->ta = associe_short;
    Liste_insererFin(ln,cl);
    printf("Cellule_afficher(Liste_premierElement(ln)) : ");
    Cellule_afficher(Liste_premierElement(ln));
    printf("\n------\n");
    printf("Fin du test Liste_premierElement()\n\n");
    Liste_detruire(l);
    Liste_detruire(lp);
    Liste_detruire(ln);
}

void test_Liste_dernierElement(){
    printf("Debut du test Liste_dernierElement()\n");
    printf("------\n");
    printf("Creation d'une Cellule  c associe a un int* de valeur 5 puis creation d'une liste l avec cette Cellule\n");
    int value = 5;
    short value2 = 10;
    Cellule c = Cellule_creer(&value);
    Liste l = Liste_creer(c,associe_int);
    printf("Cellule_afficher(Liste_dernierElement(l)) : ");
    Cellule_afficher(Liste_dernierElement(l));
    printf("\n------\n");
    printf("Creation d'une liste vide lp\n");
    Liste lp = Liste_creer(NULL,associe_chaine);
    printf("Cellule_afficher(Liste_dernierElement(lp)) : ");
    Cellule_afficher(Liste_dernierElement(lp));
    printf("\n------\n");
    printf("Creation d'une liste ln initialise a c, et insertion au debut d'une cellule contenant un short* de valeur 10 (associe au type short)\n");
    Liste ln = Liste_creer(c,associe_void);
    Cellule cl = Cellule_creer(&value2);
    cl->ta = associe_short;
    Liste_insererDebut(ln,cl);
    printf("Cellule_afficher(Liste_dernierElement(ln)) : ");
    Cellule_afficher(Liste_dernierElement(ln));
    printf("\n------\n");
    printf("Fin du test Liste_dernierElement()\n\n");
    Liste_detruire(l);
    Liste_detruire(lp);
    Liste_detruire(ln);
}

void test_Liste_a(){
    printf("Debut du test Liste_a()\n");
    printf("------\n");
    printf("Creation d'une Cellule  c associe a un int* de valeur 5 puis creation d'une liste l avec cette Cellule\n");
    printf("Puis insertion en fin de l les valeurs : 10 15 20\n");
    int value = 5, v2 = 10, v3 = 15, v4 = 20;
    Cellule c = Cellule_creer(&value);
    Liste l = Liste_creer(c,associe_int);
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_insererFin(l,Cellule_creer(&v4));
    printf("Cellule_afficher(Liste_a(l,0)) : ");
    Cellule_afficher(Liste_a(l,0));
    printf("\nCellule_afficher(Liste_a(l,1)) : ");
    Cellule_afficher(Liste_a(l,1));
    printf("\nCellule_afficher(Liste_a(l,2)) : ");
    Cellule_afficher(Liste_a(l,2));
    printf("\nCellule_afficher(Liste_a(l,3)) : ");
    Cellule_afficher(Liste_a(l,3));
    printf("\nCellule_afficher(Liste_a(l,4)) : ");
    Cellule_afficher(Liste_a(l,4));
    printf("\nCellule_afficher(Liste_a(l,-2)) : ");
    Cellule_afficher(Liste_a(l,-2));
    printf("\n------\n");
    Liste_detruire(l);
}

void test_Liste_insertionDebut(){
    printf("Debut du test Liste_insertionDebut()\n");
    printf("------\n");
    printf("Creation d'une Cellule  c associe a un int* de valeur 5 puis creation d'une liste l avec cette Cellule\n");
    printf("Puis insertion au debut de l les valeurs : 10 15 20, enfin affichage de la liste\n");
    int value = 5, v2 = 10, v3 = 15, v4 = 20;
    Cellule c = Cellule_creer(&value);
    Liste l = Liste_creer(c,associe_int);
    Liste_insererDebut(l,Cellule_creer(&v2));
    Liste_insererDebut(l,Cellule_creer(&v3));
    Liste_insererDebut(l,Cellule_creer(&v4));
    Liste_afficher(l);
    printf("\n------\n");
    Liste_detruire(l);
}

void test_Liste_insertionFin(){
    printf("Debut du test Liste_insertionFin()\n");
    printf("------\n");
    printf("Creation d'une Cellule  c associe a un int* de valeur 5 puis creation d'une liste l avec cette Cellule\n");
    printf("Puis insertion a la fin de l les valeurs : 10 15 20, enfin affichage de la liste\n");
    int value = 5, v2 = 10, v3 = 15, v4 = 20;
    Cellule c = Cellule_creer(&value);
    Liste l = Liste_creer(c,associe_int);
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_insererFin(l,Cellule_creer(&v4));
    Liste_afficher(l);
    printf("\n------\n");
    Liste_detruire(l);
}

void test_Liste_insertionAIndex(){
    printf("Debut du test Liste_insertionAIndex()\n");
    printf("------\n");
    printf("Creation d'une Cellule  c associe a un int* de valeur 5 puis creation d'une liste l avec cette Cellule\n");
    int value = 5, v2 = 10, v3 = 15, v4 = 20, v5 = 25, v6 = 30;
    Cellule c = Cellule_creer(&value);
    Liste l = Liste_creer(c,associe_int);
    printf("Insertion de 10 a l'emplacement 1 et affichage de la liste\n");
    Liste_insererAIndex(l,Cellule_creer(&v2),1);
    Liste_afficher(l);
    printf("Insertion de 15 a l'emplacement 0 et affichage de la liste\n");
    Liste_insererAIndex(l,Cellule_creer(&v3),0);
    Liste_afficher(l);
    printf("Insertion de 20 a l'emplacement 2 et affichage de la liste\n");
    Liste_insererAIndex(l,Cellule_creer(&v4),2);
    Liste_afficher(l);
    printf("Insertion de 25 a l'emplacement 50 et affichage de la liste\n");
    Liste_insererAIndex(l,Cellule_creer(&v5),50);
    Liste_afficher(l);
    printf("Insertion de 30 a l'emplacement -5 et affichage de la liste\n");
    Liste_insererAIndex(l,Cellule_creer(&v6),-5);
    Liste_afficher(l);
    printf("\n------\n");
    Liste_detruire(l);
}

void test_Liste_insertionListeDebut(){
    printf("Debut du test Liste_insertionListeDebut()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 3, 4, 5 et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_insererFin(l,Cellule_creer(&v4));
    Liste_insererFin(l,Cellule_creer(&v5));
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int contenant 1, 2 et affichage de celle ci\n");
    Liste ln = Liste_creer(NULL,associe_int);
    Liste_insererFin(ln,Cellule_creer(&v1));
    Liste_insererFin(ln,Cellule_creer(&v2));
    Liste_afficher(ln);
    printf("Insertion au debut de la liste l la liste ln et affichage des deux listes\n");
    Liste_insererListeDebut(l,ln);
    printf("l : ");
    Liste_afficher(l);
    printf("ln : ");
    Liste_afficher(ln);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
}

void test_Liste_insertionListeFin(){
    printf("Debut du test Liste_insertionListeFin()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 1, 2, 3 et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v1));
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int contenant 1, 2 et affichage de celle ci\n");
    Liste ln = Liste_creer(NULL,associe_int);
    Liste_insererFin(ln,Cellule_creer(&v4));
    Liste_insererFin(ln,Cellule_creer(&v5));
    Liste_afficher(ln);
    printf("Insertion a la fin de la liste l la liste ln et affichage des deux listes\n");
    Liste_insererListeFin(l,ln);
    printf("l : ");
    Liste_afficher(l);
    printf("ln : ");
    Liste_afficher(ln);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
}

void test_Liste_insertionListeAIndex(){
    printf("Debut du test Liste_insertionListeFin()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 1, 4, 5 et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v1));
    Liste_insererFin(l,Cellule_creer(&v4));
    Liste_insererFin(l,Cellule_creer(&v5));
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int contenant 2, 3 et affichage de celle ci\n");
    Liste ln = Liste_creer(NULL,associe_int);
    Liste_insererFin(ln,Cellule_creer(&v2));
    Liste_insererFin(ln,Cellule_creer(&v3));
    Liste_afficher(ln);
    printf("Insertion a l'index 1 de la liste l la liste ln et affichage des deux listes\n");
    Liste_insererListeAIndex(l,ln,1);
    printf("l : ");
    Liste_afficher(l);
    printf("ln : ");
    Liste_afficher(ln);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
}

void test_Cellule_egal(){
    printf("Debut du test Cellule_egal()\n");
    printf("------\n");
    printf("Creation de char* Hello1 = \"Hello\"\nCreation de char* Hello2 = \"Hello\"\nCreation de char* hello = \"hello\"\nCreation de char* Cquatre = 4\nCreation de int* Iquatre = 4\n");
    char* Hello1 = "Hello";
    char* Hello2 = "Hello";
    char* hello = "hello";
    char* Cquatre = "4";
    int Iquatre = 4;
    printf("Creation des Cellules associes respectif c1, c2, c3, c4, c5 et definition de leur typeAssocie respectif\n");
    Cellule c1 = Cellule_creer(&Hello1);
    Cellule c2 = Cellule_creer(&Hello2);
    Cellule c3 = Cellule_creer(&hello);
    Cellule c4 = Cellule_creer(&Cquatre);
    Cellule c5 = Cellule_creer(&Iquatre);
    c1->ta = associe_chaine;
    c2->ta = associe_chaine;
    c3->ta = associe_chaine;
    c4->ta = associe_chaine;
    c5->ta = associe_int;
    printf("--- Test ---\n");
    printf("Cellule_egal(c1,c2) -> %d\n",Cellule_egal(c1,c2));
    printf("Cellule_egal(c1, c3) -> %d\n",Cellule_egal(c1, c3));
    printf("Cellule_egal(c4, c5) -> %d\n",Cellule_egal(c4, c5));
    printf("------\n");
    printf("Fin du test Cellule_egal()\n\n");
    Cellule_detruire(c1);
    Cellule_detruire(c2);
    Cellule_detruire(c3);
    Cellule_detruire(c4);
    Cellule_detruire(c5);
}

void test_Liste_egal(){
    printf("Debut du test Liste_egal()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 1, 2, 3et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v1));
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int contenant 1, 2 et affichage de celle ci\n");
    Liste ln = Liste_creer(NULL,associe_int);
    Liste_insererFin(ln,Cellule_creer(&v1));
    Liste_insererFin(ln,Cellule_creer(&v2));
    Liste_afficher(ln);
    printf("Test de l'egalite de l et ln : ");
    printf("%d\n",Liste_egal(l,ln));
    printf("Insertion en fin de ln de la valeur 4 et affichage\n");
    Liste_insererFin(ln,Cellule_creer(&v4));
    Liste_afficher(ln);
    printf("Test de l'egalite de l et ln : ");
    printf("%d\n",Liste_egal(l,ln));
    printf("Suppression a la fin de ln et insertion en fin de la valeur 3 et affichage\n");
    Liste_supprimerDernier(ln);
    Liste_insererFin(ln,Cellule_creer(&v3));
    Liste_afficher(ln);
    printf("Test de l'egalite de l et ln : ");
    printf("%d\n",Liste_egal(l,ln));
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
}

void test_Liste_supprimerDebut(){
    printf("Debut du test Liste_supprimerDebut()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 2, 3, et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_afficher(l);
    printf("Suppression au debut et reaffichage\n");
    Liste_supprimerPremier(l);
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int contenant 1 et affichage de celle ci\n");
    Liste ln = Liste_creer(NULL,associe_int);
    Liste_insererFin(ln,Cellule_creer(&v1));
    Liste_afficher(ln);
    printf("Suppression au debut et reaffichage\n");
    Liste_supprimerPremier(ln);
    Liste_afficher(ln);
    printf("Creation d'une liste lp associe au type int vide\n");
    Liste lp = Liste_creer(NULL,associe_int);
    printf("Suppression au debut et affichage\n");
    Liste_supprimerPremier(lp);
    Liste_afficher(lp);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
    Liste_detruire(lp);
}

void test_Liste_supprimerFin(){
    printf("Debut du test Liste_supprimerFin()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 2, 3, et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_afficher(l);
    printf("Suppression a la fin et reaffichage\n");
    Liste_supprimerDernier(l);
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int contenant 1 et affichage de celle ci\n");
    Liste ln = Liste_creer(NULL,associe_int);
    Liste_insererFin(ln,Cellule_creer(&v1));
    Liste_afficher(ln);
    printf("Suppression a la fin et reaffichage\n");
    Liste_supprimerDernier(ln);
    Liste_afficher(ln);
    printf("Creation d'une liste lp associe au type int vide\n");
    Liste lp = Liste_creer(NULL,associe_int);
    printf("Suppression a la fin et affichage\n");
    Liste_supprimerDernier(lp);
    Liste_afficher(lp);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
    Liste_detruire(lp);
}

void test_Liste_supprimerAIndex(){
    printf("Debut du test Liste_supprimerAIndex()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 2, 3, 4, et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_insererFin(l,Cellule_creer(&v4));
    Liste_afficher(l);
    printf("Suppression a l'index' 1 et reaffichage\n");
    Liste_supprimerAIndex(l,1);
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int contenant 1 et affichage de celle ci\n");
    Liste ln = Liste_creer(NULL,associe_int);
    Liste_insererFin(ln,Cellule_creer(&v1));
    Liste_afficher(ln);
    printf("Suppression a l'index 2 et reaffichage\n");
    Liste_supprimerAIndex(ln,2);
    Liste_afficher(ln);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
}

void test_Liste_vider(){
    printf("Debut du test Liste_vider()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 2, 3, 4 et affichage de celle ci\n");
    int v2 = 2, v3 = 3, v4 = 4;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_insererFin(l,Cellule_creer(&v4));
    Liste_afficher(l);
    printf("Vidage et reaffichage\n");
    Liste_vider(l);
    Liste_afficher(l);
    printf("Creation d'une liste ln associe au type int vide\n");
    Liste ln = Liste_creer(NULL,associe_int);
    printf("Vidage et reaffichage\n");
    Liste_vider(ln);
    Liste_afficher(ln);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
}

void test_Liste_ssListe(){
    printf("Debut du test Liste_sousListe()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int contenant 1, 2, 3, et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v1));
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v3));
    printf("Creation d'une liste ln qui recoit la sous liste de l issu de l'index 1 et affichage de l puis de ln\n");
    Liste ln = Liste_sousListe(l,1);
    Liste_afficher(l);
    Liste_afficher(ln);
    printf("Creation d'une liste lp qui recoit la sous liste de ln issu de l'index 2 et affichage de ln puis de lp\n");
    Liste lp = Liste_sousListe(ln,2);
    Liste_afficher(ln);
    Liste_afficher(lp);
    printf("\n------\n");
    Liste_detruire(l);
    Liste_detruire(ln);
    Liste_detruire(lp);
}

void test_Liste_trier(){
    printf("Debut du test Liste_trier()\n");
    printf("------\n");
    printf("Creation d'une liste l associe au type int avec quelques valeurs et affichage de celle ci\n");
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7;
    Liste l = Liste_creer(NULL,associe_int);
    Liste_insererFin(l,Cellule_creer(&v3));
    Liste_insererFin(l,Cellule_creer(&v5));
    Liste_insererFin(l,Cellule_creer(&v2));
    Liste_insererFin(l,Cellule_creer(&v4));
    Liste_insererFin(l,Cellule_creer(&v6));
    Liste_insererFin(l,Cellule_creer(&v7));
    Liste_insererFin(l,Cellule_creer(&v1));
    printf("Triage de l puis reaffichage\n");
    Liste_trier(l);
    Liste_afficher(l);
    printf("Ne marche pas mais trie a l'envers");
    printf("Creation d'une liste ln associe au type char contenant z, a, h, b et affichage de celle ci\n");
    char c1 = 'z', c2 = 'a', c3 = 'h', c4 = 'b';
    Liste ln = Liste_creer(NULL,associe_char);
    Liste_insererFin(ln,Cellule_creer(&c1));
    Liste_insererFin(ln,Cellule_creer(&c2));
    Liste_insererFin(ln,Cellule_creer(&c3));
    Liste_insererFin(ln,Cellule_creer(&c4));
    Liste_afficher(ln);
    printf("Triage de ln puis reaffichage\n");
    Liste_trier(ln);
    Liste_afficher(ln);
    printf("Ne marche pas");
    printf("Creation d'une liste lc associe au type chaine avec quelques valeurs et affichage de celle ci\n");
    char* z1 = "abc", *z2 = "bac", *z3 = "cab", *z4 = "cba", *z5 = "zed";
    Liste lc = Liste_creer(NULL,associe_chaine);
    Liste_insererFin(lc,Cellule_creer(&z2));
    Liste_insererFin(lc,Cellule_creer(&z1));
    Liste_insererFin(lc,Cellule_creer(&z5));
    Liste_insererFin(lc,Cellule_creer(&z4));
    Liste_insererFin(lc,Cellule_creer(&z3));
    Liste_afficher(lc);
    printf("Triage de lc puis reaffichage\n");
    Liste_trier(lc);
    Liste_afficher(lc);
    printf("\n------\n");
    //Liste_detruire(l);
    Liste_detruire(ln);
}

int main(void){
    int choix = 1;
    while(choix){
        printf("Choix d'un test :\n");
        printf("0 : Quitter le programme\n");
        printf("1 : Test des constructeurs\n");
        printf("|-10 : Test du constructeur de Cellule\n");
        printf("|-11 : Test du constructeur de Liste\n");
        printf("2 : Test des accesseurs\n");
        printf("|-20 : Test de l'accesseur premier element\n");
        printf("|-21 : Test de l'accesseur dernier element\n");
        printf("|-22 : Test de l'accesseur d'element par index\n");
        printf("3 : Test des fonctions d'insertions\n");
        printf("|-30 : Test de l'insertion au debut\n");
        printf("|-31 : Test de l'insertion a la fin\n");
        printf("|-32 : Test de l'insertion d'un element par index\n");
        printf("|-33 : Test de l'insertion d'une liste au debut d'une liste\n");
        printf("|-34 : Test de l'insertion d'une liste a la fin d'une liste\n");
        printf("|-35 : Test de l'insertion d'une liste par index d'une liste\n");
        printf("4 : Test des fonctions de suppression\n");
        printf("|-40 : Test de la suppression au debut\n");
        printf("|-41 : Test de la suppression a la fin\n");
        printf("|-42 : Test de la suppression d'un element par index\n");
        printf("|-43 : Test du vidage d'une liste\n");
        printf("5 : Test des fonctions de comparaison\n");
        printf("|-50 : Test de l'egalite de deux cellules\n");
        printf("|-51 : Test de l'egalite de deux listes\n");
        printf("6 : Test des fonctions annexes\n");
        printf("|- 60 : Test de la creation d'une sous liste\n");
        printf("|- 61 : Test du triage d'une liste\n");
        printf("Faites votre choix : ");
        fflush(stdout);
        scanf("%d",&choix);
        fflush(stdin); // Si l'utilisateur rentre n'importe quoi au clavier, on evite de boucler...
        printf("\n-----------------\n");
        switch(choix){
        case 0:
            break;
        case 1:
            test_Creation_Cellule();
            test_Creation_Liste();
            break;
        case 10:
            test_Creation_Cellule();
            break;
        case 11:
            test_Creation_Liste();
            break;
        case 2:
            test_Liste_premierElement();
            test_Liste_dernierElement();
            test_Liste_a();
            break;
        case 20:
            test_Liste_premierElement();
            break;
        case 21:
            test_Liste_dernierElement();
            break;
        case 22:
            test_Liste_a();
            break;
        case 3:
            test_Liste_insertionDebut();
            test_Liste_insertionFin();
            test_Liste_insertionAIndex();
            test_Liste_insertionListeDebut();
            test_Liste_insertionListeFin();
            test_Liste_insertionListeAIndex();
            break;
        case 30:
            test_Liste_insertionDebut();
            break;
        case 31:
            test_Liste_insertionFin();
            break;
        case 32:
            test_Liste_insertionAIndex();
            break;
        case 33:
            test_Liste_insertionListeDebut();
            break;
        case 34:
            test_Liste_insertionListeFin();
            break;
        case 35:
            test_Liste_insertionListeAIndex();
            break;
        case 4:
            test_Liste_supprimerDebut();
            test_Liste_supprimerFin();
            test_Liste_supprimerAIndex();
            test_Liste_vider();
            break;
        case 40:
            test_Liste_supprimerDebut();
            break;
        case 41:
            test_Liste_supprimerFin();
            break;
        case 42:
            test_Liste_supprimerAIndex();
            break;
        case 43:
            test_Liste_vider();
            break;
        case 5:
            test_Cellule_egal();
            test_Liste_egal();
            break;
        case 50:
            test_Cellule_egal();
            break;
        case 51:
            test_Liste_egal();
            break;
        case 6:
            test_Liste_ssListe();
            test_Liste_trier();
            break;
        case 60:
            test_Liste_ssListe();
            break;
        case 61:
            test_Liste_trier();
            break;
        default:
            printf("Saisi incorrect\n");
            break;
        }
    }
    return 0;
}

