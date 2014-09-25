/** @file arbin.h 
 * @brief en-t�te d�finissant les structures, types, fonctions sur les arbres 
 * binaires d'entiers.
 * @author Meynard Michel
*/
#ifndef _ARBINH
#define _ARBINH

#ifndef NULL
#define NULL 0
#endif 

/*----------------------- Types Unions Structures ---------------------------*/

/** type pointeur sur la racine de l'arbre binaire d'entiers */
typedef struct Noeudbin * Arbin; 

/** type noeud d'un arbre binaire d'entiers */
typedef struct Noeudbin {
    int val ;
    Arbin fg;
    Arbin fd ;
} Noeudbin ;

/*---------------------------FONCTIONS----------------------------------------*/

/** macro fonction cr�ant un Arbin vide (retourne pointeur nul) */
#define creerarbin() (NULL)	

/** macro fonction retournant le sous-arbre gauche d'un Arbin
 *@param a un Arbin
 *@return le sous-arbre gauche de a 
*/
#define sag(a) ((a)->fg)	

/** macro fonction retournant le sous-arbre droit d'un Arbin
 *@param a un Arbin
 *@return le sous-arbre droit de a 
*/
#define sad(a) ((a)->fd)	/* retourne le sous-arbre droit de a */

/** macro fonction  testant si un Arbin est vide 
 *@param  a un Arbin
 *@return vrai si a est vide, faux sinon
*/
#define videa(a) (a==NULL)

/** macro fonction retournant la racine d'un Arbin
 *@param a un Arbin
 *@return l'entier situ� � la racine
*/
#define racine(a) ((a)->val)

/** @remark Ces 5 pseudo-fonctions (macros) sont definies quel 
 * que soit le type de l'Arbin (entier, car, arbre,...) 
*/

/** fonction rempla�ant le sag(pere) par filsg et vidant l'ancien sag. Attention,
 * op�ration MODIFIANTE !
 *@param pere un Arbin
 *@param filsg l'Arbin qu'il faut greffer � la place du sag actuel de pere
 */
void greffergauche(Arbin pere, Arbin filsg); 

/** fonction rempla�ant le sad(pere) par filsd et vidant l'ancien sag. Attention,
 * op�ration MODIFIANTE !
 *@param pere un Arbin
 *@param filsd l'Arbin qu'il faut greffer � la place du sad actuel de pere
 */
void grefferdroite(Arbin pere, Arbin filsd); 

/** fonction construisant un nouvel Arbin � partir d'une valeur enti�re qui 
 * deviendra la racine et de deux sous arbres.
 *@param rac l'entier racine
 *@param g un Arbin qui devient sag
 *@param d un Arbin qui devient sad
 *@return l'Arbin construit
 */
Arbin construire(int rac, Arbin g, Arbin d);


/** fonction copiant (clone) la structure d'un Arbin
 *@param a un Arbin
 *@return l'Arbin copi� 
 */
Arbin copiera(Arbin a);

/** fonction vidant un Arbin (d�sallocation). Attention, op�ration MODIFIANTE !
 *@param pa un pointeur sur Arbin
 */
void videra(Arbin * pa);

/** fonction affichant un Arbin de mani�re indent�e. Attention, racine(a) est 
 * affich�e comme un char
 *@param a l'Arbin � afficher
 */
void affichera(Arbin a);


#endif /* _ARBINH */
