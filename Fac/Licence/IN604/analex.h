/*============================================================================
Nom : analex.h  Auteur : Michel Meynard  D�finition de la fon : analex()
retourne un entier n�gatif si erreur, positif si OK, 0 si fin de fichier
le filtrage est permis g�ce aux jetons n�gatifs
============================================================================*/
char lexeme[1024];		/* lex�me courant de taille maxi 1024 */

int analex(){			/* reconna�t un mot sur l'entr�e standard */
  int  etat=EINIT;		/* unique �tat initial */
  int efinal=-1;		/* pas d'�tat final d�j� vu */
  int lfinal=0;			/* longueur du lex�me final */
  int c;char sc[2];int i;	/* caract�re courant */
  lexeme[0]='\0';		/* lexeme en var globale (pour le main)*/
  while ((c=getchar())!=EOF && TRANS[etat][c]!=-1){ /* Tq on peut avancer */
    sprintf(sc,"%c",c);		/* transforme le char c en chaine sc */
    strcat(lexeme,sc);		/* concat�nation */
    etat=TRANS[etat][c];	/* Avancer */
    if (JETON[etat]){		/* si �tat final */
      efinal=etat;		/* s'en souvenir */
      lfinal=strlen(lexeme);	/* longueur du lexeme egalement */
    } /* fin si */     
  } /* fin while */
  if (JETON[etat]){		/* �tat final */
    ungetc(c,stdin);		/* rejeter le car non utilis� */
    return (JETON[etat]<0 ? analex() : JETON[etat]);/* ret le jeton ou boucle*/
  }
  else if (efinal>-1){		/* on en avait vu 1 */
    ungetc(c,stdin);		/* rejeter le car non utilis� */
    for(i=strlen(lexeme)-1;i>=lfinal;i--)
      ungetc(lexeme[i],stdin);	/* rejeter les car en trop */
    lexeme[lfinal]='\0';	/* voici le lexeme reconnu */
    return (JETON[efinal]<0 ? analex() : JETON[efinal]);/* ret jeton ou boucle*/
  }
  else if (strlen(lexeme)==0 && c==EOF)
    return 0;			/* cas particulier */
  else if (strlen(lexeme)==0){
    lexeme[0]=c;lexeme[1]='\0';	/* retourner (c,c) */
    return c;
  }
  else {
    ungetc(c,stdin);		/* rejeter le car non utilis� */
    for(i=strlen(lexeme)-1;i>=1;i--)
      ungetc(lexeme[i],stdin);	/* rejeter les car en trop */
    return lexeme[0];
  }
}
