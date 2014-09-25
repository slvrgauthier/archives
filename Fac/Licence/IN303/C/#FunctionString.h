#include <string.h>

char *strcpy (char *s, const char *ct);
//Copie la chaîne ct dans s (y compris le caractère de fin de chaîne), retourne s.

char *strncpy (char *dst, const char *src, size_t n);
//Identique à strcpy en se limitant à n caractères.

char *strcat (char *s, const char *ct);
//Concatène la chaîne ct à la suite de s et retourne s

char *strncat (char *s, const char *ct, size_t n);
//Identique à strcat en se limitant à n caractères.

int strcmp (const char *cs, const char *ct);
//Compare les chaînes cs et ct et renvoi :
//    * Une valeur négative si, lexicalement, cs < ct
//    * Une valeur nulle si cs == ct
//    * Une valeur positive si cs > ct

int strncmp (const char *cs, const char* ct, size_t n);
//Identique à strcmp en se limitant à n caractères.

size_t strlen (const char *cs);
//Retourne le nombre de caractères de cs sans tenir compte du caractère de fin de chaîne.

char *strchr (const char *cs, int c);
//Retourne l'adresse de la première occurrence du caractère c dans la chaîne cs en partant du début de la chaîne.

char *strrchr (const char *cs, int c);
//Identique à strchr en commençant par la fin de cs.

char *strstr (const char *cs, const char *ct);
//Identique à strchr sauf qu'il s'agit de la première occurrence de la sous-chaîne ct.

size_t strspn (const char *cs, const char *ct);
//Cette fonction retourne le nombre de caractères du début de cs appartement à ct.

size_t strcspn (const char *cs, const char *ct);
//C'est l'inverse de la fonction strspn, cette fois, les caractères ne font pas partie de l'ensemble ct.

char *strpbrk (const char *cs, const char *ct);
//Identique à strchr sauf que cette fois, c'est l'ensemble des caractères de ct qui est recherché.

char *strtok (char *cs, const char *ct);
//Cette fonction décompose la chaîne cs en sous-chaîne délimitées par un caractère appartenant à ct. Un appel ultérieur à strtok avec cs égale à NULL, retourne la sous-chaîne suivante ; ct peut être différent à chaque appel.
//La chaîne passée en argument est modifiée par la fonction : elle ajoute un caractère de fin de chaîne à la place du séparateur.



#include <ctype.h>

char tolower(const char c);
//Mettre le caractère c en minuscule.

char toupper(const char c);
//Mettre le caractère c en majuscule.



#include "#FunctionString.h"

char *str_tolower (const char *ct);
//Mettre une chaine en minuscule.

char *str_toupper (const char *ct);
//Mettre une chaine en majuscule.

int str_istr (const char *cs, const char *ct);
//Connaître l'index d'une sous-chaîne

char *str_sub (const char *, unsigned int, unsigned int);
//Extraire une sous-chaine

char **str_split (char *, const char *);
//Découper une chaine

char *str_join (char *, ...);
//Fusionner plusieurs chaines

char *str_remplace (const char *, unsigned int, unsigned int, const char *);
//Remplacer une partie d'une chaine

char *str_strip (const char *);
//Eliminer les espaces superflus
