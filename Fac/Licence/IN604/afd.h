/*============================================================================
Nom : afd.h     Auteur : Michel Meynard | Definition d'un AFD
============================================================================*/
#define EINIT 0
#define E0 1
#define E0x 2
#define Ehexa 3
#define Eocta 4
#define Eint 5
#define Efloat 6
#define EfloatE 7
#define EfloatEs 8
#define Efloatexp 9
#define Ei 10
#define Eif 11
#define Ee 12
#define Eel 13
#define Eels 14
#define Eelse 15
#define Et 16
#define Eth 17
#define Ethe 18
#define Ethen 19
#define Ethr 20
#define Ethro 21
#define Ethrow 22
#define Es 23
#define Ess 24
#define Ecom1 26
#define Ese 25
#define Ecom2 27
#define Eid 28

#define NBETAT 29

#define INT 300
#define OCTA 301
#define HEXA 302
#define FLOAT 303
#define IF 304
#define ELSE 305
#define THEN 306
#define THROW 307
#define ID 308

int TRANS[NBETAT][256];		/* table de transition : etat suivant */
int JETON[NBETAT];		/* final (1) ou non (0) ? */

void intervalle(int edeb, int efin, int cardeb, int carfin) {
  for(int c=cardeb ; c<=carfin ; c++)
    TRANS[edeb][c]=efin;
}

int creerAfd(){			/* Construction de l'AFD */
  int i;int j;			/* variables locales */
  for (i=0;i<NBETAT;i++){
    for(j=0;j<256;j++) TRANS[i][j]=-1; /* init vide */
    JETON[i]=0;			/* init tous etats non finaux */
  }
  /* Transitions de l'AFD */
  //nombres
  TRANS[EINIT]['0']=E0 ; TRANS[EINIT]['.']=Efloat ; intervalle(EINIT,Eint,'1','9');
  TRANS[E0]['.']=Efloat ; TRANS[E0]['x']=E0x ; intervalle(E0,Eocta,'1','7');
  intervalle(E0x,Ehexa,'1','9') ; intervalle(E0x,Ehexa,'A','F');
  intervalle(Ehexa,Ehexa,'0','9') ; intervalle(Ehexa,Ehexa,'A','F');
  intervalle(Eocta,Eocta,'0','7');
  intervalle(Eint,Eint,'0','9') ; TRANS[Eint]['.']=Efloat;
  intervalle(Efloat,Efloat,'0','9') ; TRANS[Efloat]['e']=TRANS[Efloat]['E']=EfloatE;
  intervalle(EfloatE,Efloatexp,'1','9') ; TRANS[EfloatE]['+']=TRANS[EfloatE]['-']=EfloatEs;
  intervalle(EfloatEs,Efloatexp,'1','9');
  intervalle(Efloatexp,Efloatexp,'0','9');
  //identificateurs
  intervalle(EINIT,Eid,'a','z') ; intervalle(EINIT,Eid,'A','Z');
  intervalle(Eid,Eid,'a','z') ; intervalle(Eid,Eid,'A','Z') ; intervalle(Eid,Eid,'0','9') ; TRANS[Eid]['_']=Eid;
  intervalle(Ei,Eid,'a','z') ; intervalle(Ei,Eid,'A','Z') ; intervalle(Ei,Eid,'0','9') ; TRANS[Ei]['_']=Eid;
  intervalle(Eif,Eid,'a','z') ; intervalle(Eif,Eid,'A','Z') ; intervalle(Eif,Eid,'0','9') ; TRANS[Eif]['_']=Eid;
  intervalle(Ee,Eid,'a','z') ; intervalle(Ee,Eid,'A','Z') ; intervalle(Ee,Eid,'0','9') ; TRANS[Ee]['_']=Eid;
  intervalle(Eel,Eid,'a','z') ; intervalle(Eel,Eid,'A','Z') ; intervalle(Eel,Eid,'0','9') ; TRANS[Eel]['_']=Eid;
  intervalle(Eels,Eid,'a','z') ; intervalle(Eels,Eid,'A','Z') ; intervalle(Eels,Eid,'0','9') ; TRANS[Eels]['_']=Eid;
  intervalle(Eelse,Eid,'a','z') ; intervalle(Eelse,Eid,'A','Z') ; intervalle(Eelse,Eid,'0','9') ; TRANS[Eelse]['_']=Eid;
  intervalle(Et,Eid,'a','z') ; intervalle(Et,Eid,'A','Z') ; intervalle(Et,Eid,'0','9') ; TRANS[Ethen]['_']=Eid;
  intervalle(Eth,Eid,'a','z') ; intervalle(Eth,Eid,'A','Z') ; intervalle(Eth,Eid,'0','9') ; TRANS[Ethen]['_']=Eid;
  intervalle(Ethe,Eid,'a','z') ; intervalle(Ethe,Eid,'A','Z') ; intervalle(Ethe,Eid,'0','9') ; TRANS[Ethen]['_']=Eid;
  intervalle(Ethen,Eid,'a','z') ; intervalle(Ethen,Eid,'A','Z') ; intervalle(Ethen,Eid,'0','9') ; TRANS[Ethen]['_']=Eid;
  intervalle(Ethr,Eid,'a','z') ; intervalle(Ethr,Eid,'A','Z') ; intervalle(Ethr,Eid,'0','9') ; TRANS[Ethrow]['_']=Eid;
  intervalle(Ethro,Eid,'a','z') ; intervalle(Ethro,Eid,'A','Z') ; intervalle(Ethro,Eid,'0','9') ; TRANS[Ethrow]['_']=Eid;
  intervalle(Ethrow,Eid,'a','z') ; intervalle(Ethrow,Eid,'A','Z') ; intervalle(Ethrow,Eid,'0','9') ; TRANS[Ethrow]['_']=Eid;
  //mots clefs
  TRANS[EINIT]['i']=Ei ; TRANS[Ei]['f']=Eif;
  TRANS[EINIT]['e']=Ee ; TRANS[Ee]['l']=Eel ; TRANS[Eel]['s']=Eels ; TRANS[Eels]['e']=Eelse;
  TRANS[EINIT]['t']=Et ; TRANS[Et]['h']=Eth ; TRANS[Eth]['e']=Ethe ; TRANS[Ethe]['n']=Ethen;
                                               TRANS[Eth]['r']=Ethr ; TRANS[Ethr]['o']=Ethro ; TRANS[Ethro]['w']=Ethrow;
  //blancs
  

  /* Etats finaux */
  JETON[E0]=JETON[Eint]=INT;
  JETON[Eocta]=OCTA;
  JETON[Ehexa]=HEXA;
  JETON[Efloat]=JETON[Efloatexp]=FLOAT;

  JETON[Eif]=IF;
  JETON[Eelse]=ELSE;
  JETON[Ethen]=THEN;
  JETON[Ethrow]=THROW;

  JETON[Eid]=JETON[Ei]=JETON[Ee]=JETON[Eel]=JETON[Eels]=JETON[Et]=JETON[Eth]=JETON[Ethe]=JETON[Ethr]=JETON[Ethro]=ID;
}
