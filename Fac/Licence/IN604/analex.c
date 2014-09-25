/*============================================================================
Nom : analex.c  Auteur : Michel Meynard  Prog principal appelant analex()
============================================================================*/
#include <stdio.h>
#include <string.h>
#include "afd.h"		/* Definition de l'AFD et des JETONS */
#include "analex.h"		/* Definition de la fon : int analex() */

int main(){			/* Construction de l'AFD */
  int j;			/* jeton retourne par analex() */
  char *invite="Saisissez un mot reconnu par l'automate, suivi de EOF (CTRL-D) : ";
  creerAfd();			/* Construction de l'AFD a jeton */
  printf("%s",invite);		/* prompt */
  while((j=analex())){		/* analyser tq pas jeton 0 */
    printf("\nRésultat : Jeton = %d ; Lexeme = %s\n%s",j,lexeme,invite);
  }
  return 0;
}
