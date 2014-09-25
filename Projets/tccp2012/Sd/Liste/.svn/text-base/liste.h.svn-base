/*!	\file liste.h
    \brief fichier .h des structures Cellule et Liste et leur fonctions
*/
#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Ne pas manipuler autrement que le constructeur sous peine de boucle infini ou effet de bord indésirable


/*! \struct typeAssocie
 *  \brief la structure permettant d'associer un type à une Liste ou une Cellule.
 *	\details typeAssocie est une simple interface permettant quelques operations :\n
 *	- L'affichage d'une liste ou d'une cellule sur la sortie standard (par default).\n
 *	- La comparaison de deux cellules.\n
 *	- Le triage d'une liste.\n
 *	Les types primitifs sont dejà implementés voir associe_chaine, associe_int, associe_short, associe_long, associe_float, associe_double, associe_char, associe_void.\n
 *	Si votre liste est heterogene, veuillez utiliser le type : associe_void.\n
 *	Si il vous faut utiliser des types personalisés pour vos listes ou vos cellules, le code basique sera :\n
 *	\code
 *	typeAssocie monTa = typeAssocie_creer(&maFctAffichage,&maFctDeComparaison);
 *	Liste l = Liste_creer(NULL,monTa);
 *	\endcode
 */
struct typeAssocie{
	//! Affiche sur la sortie standard data.
	/*!	\sa \__CHAINE__affiche(), \__INT__affiche(), \__SHORT__affiche(), \__LONG__affiche(), \__CHAR__affiche(), \__DOUBLE__affiche(), \__FLOAT__affiche().
    */
	void (*fonctionAffichage)(void* data);
	//! Compare data1 et data2, renvoie -1 si data1 < data2, 0 si data1 = data2, 1 si data1 > data2.
	/*!	\sa \__CHAINE__compare(), \__INT__compare(), \__SHORT__compare(), \__LONG__compare(), \__CHAR__affiche(), \__DOUBLE__affiche(), \__FLOAT__affiche().
    */
	int (*fonctionCompare)(const void* data1,const void* data2);
	//! Renvoie 1 si la fonction d'affichage et la fonction de comparaison ne sont pas définies, sinon 0.
	int (*estNull)(struct typeAssocie ta);
	//! Renvoie 1 si la structure ta1 et ta2 sont identiques, sinon 0.
    int (*estEgal)(struct typeAssocie ta1, struct typeAssocie ta2);
};

/*!	\typedef typeAssocie
    \brief "struct typeAssocie" simplifié en "typeAssocie".
 */
typedef struct typeAssocie typeAssocie;

/*! \struct Cellule_struct
    \brief la structure Cellule est la representation d'un element d'une liste.
	\details La Cellule est crée via l'appel de la fonction Cellule_creer(void* data).\n
*	Un exemple d'utilisation simple pour creer une cellules contenant un int de valeur 5 :\n
*	\code
*	int valeur = 5;
*	Cellule c = Cellule_creer(&valeur); // c contient la valeur 5, et peux être utilisé dans les listes
*	Cellule_detruire(c); // Ne pas oublier de deallouer la mémoire utilisée
*	\endcode
*/
struct Cellule_struct{
    //! Contenu de la cellule.
    void* data;
    //! Pointeur vers la cellule précedente.
    struct Cellule_struct *previous;
    //! Pointeur vers la cellule suivante.
    struct Cellule_struct *next;
    //! Vaut 1 si cellule est presente dans une liste, sinon 0.
    int used;
    //! Type associe à la cellule (par default int).
    typeAssocie ta;
    //! Fonction d'affichage de la cellule
    /*!	\sa \__CHAINE__affiche(), \__INT__affiche(), \__SHORT__affiche(), \__LONG__affiche(), \__CHAR__affiche(), \__DOUBLE__affiche(), \__FLOAT__affiche().
    */
	void (*afficher)(struct Cellule_struct *c);
    //! Fonction de comparaison de 2 cellules
    /*!	\sa \__CHAINE__compare(), \__INT__compare(), \__SHORT__compare(), \__LONG__compare(), \__CHAR__affiche(), \__DOUBLE__affiche(), \__FLOAT__affiche().
    */
	int (*comparer)(struct Cellule_struct *c1, struct Cellule_struct *c2);
};

/*!	\typedef Cellule
    \brief pointeur vers la structure Cellule.
 */
typedef struct Cellule_struct* Cellule;

/*!	\struct Liste_struct
    \brief la structure Liste est une collection de cellule.
 *	\details La liste est une structure permettant de représenter une liste doublement chainée.\n
 *	Un certain nombre de fonction ont été mise en oeuvre pour vous garantir une facilité d'utilisation :\n
 *	- Constructeur et destructeur.\n
 *	- Recupération de cellule.\n
 *	- Insertion de cellule/liste.\n
 *	- Creation de sous-liste.\n
 *	- Triage.\n
 *	Le code basique pour la creation d'une liste d'entier (int) sera :\n
 *	\code
 *	int valeur = 5;
 *	Liste l = Liste_creer(NULL,associe_int); // Creer une liste d'entier vide
 *	Liste_insererDebut(l, Cellule_creer(&valeur); // Insertion de 5 dans la liste
 *	Liste_detruire(l); // Libere la mémoire de l et de tout les elements qu'elle comporte
 *	\endcode
 */
struct Liste_struct{
    //! Point d'entrée dans la suite des Cellules.
    Cellule entry;
    //! Mémorise la taille ( nombre de cellules) de la liste.
    int size;
    //! Renvoie l'element d'index correspondant.
    /*!	\sa Liste_a()
    */
    Cellule (*a)(struct Liste_struct *l, int index);
    //! Renvoie le premier element.
    /*!	\sa Liste_premierElement()
    */
    Cellule (*premierElement)(struct Liste_struct *l);
    //! Renvoie le dernier element.
    /*!	\sa Liste_dernierElement()
    */
    Cellule (*dernierElement)(struct Liste_struct *l);
    //! Renvoie 1 si les deux listes sont égales sinon 0.
    /*!	\sa Liste_egal()
    */
    int (*egal)(struct Liste_struct *l1, struct Liste_struct *l2);
    // Les fonctions d'insertion font une copie de la cellule passée en argument si celle ci est dejà dans une liste
    /* -------------------------------------  */
    //! Insère une cellule au début de la liste.
    /*!	\sa Liste_insererDebut()
    */
    int (*insererDebut)(struct Liste_struct *l, Cellule c);
    //! Insère une cellule à la fin de la liste.
    /*!	\sa Liste_insererFin()
    */
    int (*insererFin)(struct Liste_struct *l, Cellule c);
    //! Insère une cellule à l'index fourni tel que l.insererAIndex(l,c,1) -> l.a(l,1) == c.
    /*!	\sa Liste_insererAIndex()
    */
    int (*insererAIndex)(struct Liste_struct *l, Cellule c, int index);
    /* -------------------------------------  */
    //! Supprime la première cellule de la liste.
    /*!	\sa Liste_supprimerPremier()
    */
    int (*supprimerPremier)(struct Liste_struct *l);
    //! Supprime la dernière cellule de la liste.
    /*!	\sa Liste_supprimerDernier
    */
    int (*supprimerDernier)(struct Liste_struct *l);
    //! Supprime la cellule à l'index donné.
    /*!	\sa Liste_supprimerAIndex()
    */
    int (*supprimerAIndex)(struct Liste_struct *l, int index);
    //! Vide la liste (Supprime tout les éléments).
    /*!	\sa Liste_vider()
    */
    int (*vider)(struct Liste_struct *l);
    //! Insère la deuxième liste dans la première au début (recopie de la deuxième dans la première).
    /*!	\sa Liste_insererListeDebut()
    */
    int (*insererListeDebut)(struct Liste_struct *l, struct Liste_struct *lAInserer);
    //! Insère la deuxième liste dans la première à la fin (recopie de la deuxième dans la première).
    /*!	\sa Liste_insererListeFin()
    */
    int (*insererListeFin)(struct Liste_struct *l, struct Liste_struct *lAInserer);
    //! Insère la deuxième liste dans la première à l'index (recopie de la deuxième dans la première).
    /*!	\sa Liste_insererListeAIndex()
    */
    int (*insererListeAIndex)(struct Liste_struct *l, struct Liste_struct *lAInserer, int index);
    //! Renvoie la sous-liste, extrai à partir de l'index jusqu'à la fin de la liste.
    /*! \sa Liste_sousListe()
    */
    struct Liste_struct* (*sousListe)(struct Liste_struct *l, int index);
    //! Type Associe à la liste.
    typeAssocie ta;
    //! Affiche la liste grâce au fonction "afficher" de ta, si ta est null, il y'a appelle à afficher de la Cellule.
    /*!	\sa Liste_afficher()
	*/
	void (*afficher)(struct Liste_struct *l);
    //! Trie une liste dans l'ordre croissant, il faut que le type associé soit non-null.
    /*!	\sa Liste_trier()
	*/
	int (*trier)(struct Liste_struct *l);
};

/*!	\typedef Liste
    \brief pointeur vers la structure Liste.
 */
typedef struct Liste_struct* Liste;

// Fonction annexe
/*!	\brief Teste l'égalité de deux cellules.
    \param c1,c2 deux cellules à tester
    \return 1 si deux cellules sont égaux, sinon 0.
 */	
int Cellule_egal(Cellule c1, Cellule c2);

/*!	\brief Teste l'égalité deux listes.
    \param l1,l2 deux listes à tester.
    \return 1 si deux listes sont égaux, sinon 0.
 */
int Liste_egal(Liste l1,Liste l2);

/*!	\brief Copie une cellule.
    \return le pointeur vers la copie de la cellule.
    \param c la cellule à copier.
 */
Cellule Cellule_cloner(Cellule c);

/*!	\brief Copie une liste.
    \return le pointeur vers la copie de la liste.
    \param l la liste à copier.
 */
Liste Liste_cloner(Liste l);

/*!	\brief Compare 2 cellules.
    \param c1,c2 2 cellules a comparer.
    \return -2 si c1 et c2 sont de types differents, -1 si c1<c2, 0 si c1=c2, 1 si c1>c2.
*/
int Cellule_comparer(Cellule c1, Cellule c2);

// Constructeurs
/*!	\brief Crée un type associé.
    \param fctAffichage (void *) la fonction affichage propre du type associé.
    \param fctCompare (void *, void *) la fonction comparaison propre du type associé.
    \return le type associe crée.
 */
typeAssocie typeAssocie_creer(void fctAffichage(void *),int fctCompare(const void *,const void *));

/*!	\brief Crée une cellule.
    \param data l'information a insérer dans la cellule.
    \return le pointeur vers la cellule crée.
 */
Cellule Cellule_creer(void* data);

/*!	\brief Crée une liste à partir d'une cellule.
    \param c la cellule que contient la liste.
	\param ta le typeAssocie à la liste.
    \return le pointeur vers la liste crée.
 */
Liste Liste_creer(Cellule c, typeAssocie ta);

// Destructeurs
/*!	\brief Détruit une cellule.
    \param c la cellule à détruire.
    \return -1 si erreur, 0 si la cellule est détruite.
 */
int Cellule_detruire(Cellule c);

/*!	\brief Détruit une cellule inutilisée.
    \param c la cellule à detruire.
	\details La cellule n'est détruite uniquement si elle n'est présente dans aucune liste.
    \return -1 si erreur, 0 si la cellule est détruite.
 */
int Cellule_detruireSiInutilise(Cellule c);

/*!	\brief Détruit une liste.
    \param l la liste à détruire.
    \return -1 si erreur, 0 si la liste est détruite.
 */
int Liste_detruire(Liste l);

// Fonctions
/*!	\brief Accès à une cellule avec une certaine position dans une liste.
    \param l la liste.
    \param index position de la cellule dans la liste.
    \return Le pointeur vers la cellule.
 */
Cellule Liste_a(Liste l, int index);

/*!	\brief Accès au 1er élément de la liste.
    \param l la liste.
    \return Pointeur vers la 1ere cellule.
 */
Cellule Liste_premierElement(Liste l);

/*!	\brief Accès au dernier élément de la liste.
    \param l la liste.
    \return Pointeur vers la dernière cellule.
 */
Cellule Liste_dernierElement(Liste l);

/*!	\brief Insere une cellule au début d'une liste.
    \param l la liste.
    \param c la cellule a insérer dans la liste.
    \return -1 si erreur, 0 si succès.
 */
int Liste_insererDebut(Liste l, Cellule c);

/*!	\brief Insere une cellule à la fin d'une liste.
    \param l la liste.
    \param c la cellule à insérer dans la liste.
    \return -1 si erreur, 0 si succès.
 */
int Liste_insererFin(Liste l, Cellule c);

/*!	\brief Insere une cellule dans une certaine place d'une liste.
    \param l la liste.
    \param c la cellule à insérer dans la liste.
    \param index la place pour insérer.
    \return -1 si erreur, 0 si succès.
 */
int Liste_insererAIndex(Liste l, Cellule c, int index);

/*!	\brief Supprime le 1er élément d'une liste.
    \param l la liste.
    \return 0 si succes, -1 si liste nulle, -2 si liste trop courte (taille 0).
 */
int Liste_supprimerPremier(Liste l);

/*!	\brief Supprime le dernier élément d'une liste.
    \param l la liste.
    \return 0 si succes, -1 si liste nulle, -2 si liste trop courte (taille 0).
 */
int Liste_supprimerDernier(Liste l);

/*!	\brief Supprime la cellule a l'index indique dans une liste.
    \param l la liste.
    \param index l'index où on supprime la cellule.
	\return 0 si succes, -1 si liste nulle, -2 si liste trop courte (taille<index).
*/
int Liste_supprimerAIndex(Liste l, int index);

/*!	\brief Vide une liste.
    \param l la liste à vider.
    \return 0 si succès, -1 si la liste est null.
*/
int Liste_vider(Liste l);

/*!	\brief Insere une liste au début d'une autre liste.
    \param l la liste où on insère.
    \param lAInserer la liste à insérer.
    \return -1 si erreur : au moins 1 liste null, 0 si succès.
*/
int Liste_insererListeDebut(Liste l, Liste lAInserer);

/*!	\brief Insere une liste à la fin d'une autre liste.
    \param l la liste où on insère.
    \param lAInserer la liste à insérer.
    \return -1 si erreur : au moins 1 liste nulle, 0 si succès.
*/
int Liste_insererListeFin(Liste l, Liste lAInserer);

/*!	\brief Insere une liste dans d'une autre liste à un index spécifié.
    \param l la liste où on insère.
    \param lAInserer la liste à insérer.
    \param index la position à inserer.
    \return -1 si erreur : au moins 1 liste nulle ou trop courte ( index > taille ), 0 si succès.
*/
int Liste_insererListeAIndex(Liste l, Liste lAInserer, int index);

/*!	\brief Renvoie la sous-liste d'une liste à partir d'une position.
    \param l la liste.
    \param index la position.
    \return Pointeur vers la sous-liste.
 */
Liste Liste_sousListe(Liste l, int index);

/*!	\brief Affiche le contedu d'une liste.
    \param l la liste a afficher.
 */
void Liste_afficher(Liste l);

/*!	\brief Trie une liste.
    \param l la liste à trier.
	\return -1 si liste null ou sans définition de fonction de comparaison, 0 si succès.
 */
int Liste_trier(Liste l);

/*!	\brief Affiche le contenu d'une cellule.
    \param c la cellule à afficher.
 */
void Cellule_afficher(Cellule c);

// --- Fonction pour typeAssocie
/*!	\brief Teste si un type associé est null.
    \param ta type associé à tester.
    \return 1 si nul, sinon 0.
 */
int typeAssocie_estNull(typeAssocie ta);

/*!	\brief Teste l'égalité de 2 types associes.
    \param ta1, ta2 2 types associés à comparer.
    \return 1 s'ils sont egaux, sinon 0.
 */
int typeAssocie_estEgal(typeAssocie ta1,typeAssocie ta2);

/*!	\brief Affiche le contenu d'une chaine de caractères.
    \param ch la chaine à afficher.
 */
void __CHAINE__affiche(void *ch);

/*!	\brief Comparer 2 chaines de caractères.
    \param ch1, ch2 2 chaines à comparer.
    \return 0 si elles sont égales, 1 si ch1 > ch2, -1 si ch1 < ch2.
 */
int __CHAINE__compare(const void *ch1,const void *ch2);

/*!	\brief Affiche le contenu d'un int.
    \param in le int à afficher.
 */
void __INT__affiche(void* in);

/*!	\brief Compare 2 int.
	\param in1, in2 2 int à comparer.
    \return 0 si in1 == in2, 1 si in1 > in2, -1s si in1 < in2.
 */
int __INT__compare(const void *in1, const void *in2);

/*!	\brief Affiche le contenu d'un short.
    \param sh le short à afficher
 */
void __SHORT__affiche(void* sh);

/*!	\brief Comparer 2 short.
    \param sh1, sh2 2 in à comparer.
    \return 0 si sh1 ==  sh2, 1 si sh1 > sh2, -1 si sh1 < sh2.
 */
int __SHORT__compare(const void* sh1,const void* sh2);

/*!	\brief Affiche le contenu d'un long.
    \param lo le long à afficher.
 */
void __LONG__affiche(void* lo);

/*!	\brief Comparer 2 long.
    \param lo1, lo2 2 long à comparer.
    \return 0 si lo1 == lo2, 1 si lo1 > lo2, -1 si lo1 < lo2.
 */
int __LONG__compare(const void* lo1,const void* lo2);

/*!	\brief Affiche le contenu d'un float.
    \param fl le float à afficher.
 */
void __FLOAT__affiche(void* fl);

/*!	\brief Compare 2 float.
    \param fl1, fl2 2 float à comparer.
    \return 0 si fl1 == fl2, 1 si fl1 > fl2, -1 si fl1 < fl2.
 */
int __FLOAT__compare(const void* fl1,const void* fl2);

/*!	\brief Affiche le contenu d'un double.
    \param dou le double à afficher.
 */
void __DOUBLE__affiche(void* dou);

/*!	\brief Compare 2 double.
    \param dou1, dou2 2 double à comparer.
    \return 0 si dou1 == dou2, 1 si dou1 > dou2, -1 si dou1 < dou2.
 */
int __DOUBLE__compare(const void* dou1,const void* dou2);

/*!	\brief Afficher le contenu d'un char.
    \param ch le char à afficher.
 */
void __CHAR__affiche(void* ch);

/*!	\brief Comparer 2 char.
    \param ch1, ch2 2 double à comparer.
    \return 0 si ch1 == ch2, 1 si ch1 > ch2, -1 si ch1 < ch2.
 */
int __CHAR__compare(const void* ch1,const void* ch2);

//! Type associe predefini representant une chaine de caractere.
static const typeAssocie associe_chaine = {__CHAINE__affiche,__CHAINE__compare,typeAssocie_estNull,typeAssocie_estEgal};
//! Type associe predefini representant un int.
static const typeAssocie associe_int = {__INT__affiche,__INT__compare,typeAssocie_estNull,typeAssocie_estEgal};
//! Type associe predefini representant un short.
static const typeAssocie associe_short = {__SHORT__affiche,__SHORT__compare,typeAssocie_estNull,typeAssocie_estEgal};
//! Type associe predefini representant un long.
static const typeAssocie associe_long = {__LONG__affiche,__LONG__compare,typeAssocie_estNull,typeAssocie_estEgal};
//! Type associe predefini representant un float.
static const typeAssocie associe_float = {__FLOAT__affiche,__FLOAT__compare,typeAssocie_estNull,typeAssocie_estEgal};
//! Type associe predefini representant un double.
static const typeAssocie associe_double = {__DOUBLE__affiche,__DOUBLE__compare,typeAssocie_estNull,typeAssocie_estEgal};
//! Type associe predefini representant un char.
static const typeAssocie associe_char = {__CHAR__affiche,__CHAR__compare,typeAssocie_estNull,typeAssocie_estEgal};
//! Type associe predefini representant un type indefini.
static const typeAssocie associe_void = {NULL,NULL,typeAssocie_estNull,typeAssocie_estEgal};

/*!	Renvoie la valeur d'une cellule selon son type associe.
*/
#define CELLULE_VALEUR(Cellule) \
    !memcmp(&(Cellule->ta),&(associe_int),sizeof(typeAssocie)) ? *(int*)Cellule->data : \
    !memcmp(&(Cellule->ta),&(associe_short),sizeof(typeAssocie)) ? *(short*)Cellule->data : \
    !memcmp(&(Cellule->ta),&(associe_long),sizeof(typeAssocie)) ? *(long*)Cellule->data : \
    !memcmp(&(Cellule->ta),&(associe_float),sizeof(typeAssocie)) ? *(float*)Cellule->data : \
    !memcmp(&(Cellule->ta),&(associe_double),sizeof(typeAssocie)) ? *(double*)Cellule->data : \
    !memcmp(&(Cellule->ta),&(associe_char),sizeof(typeAssocie)) ? *(char*)Cellule->data : 0\

/*! Ne compile pas :
!memcmp(&(Cellule->ta),&(associe_chaine),sizeof(typeAssocie)) ? *(float*)Cellule->data :
------ */

#endif // LISTE_H
