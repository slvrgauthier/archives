#include "liste.h"

int Cellule_egal(Cellule c1, Cellule c2){
    typeAssocie ta;
    if(!typeAssocie_estEgal(c1->ta,c2->ta)){
        return 0;
    }
    ta = c1->ta;
    return (ta.fonctionCompare(c1->data,c2->data) == 0);
}

int Cellule_comparer(Cellule c1, Cellule c2){
    typeAssocie ta;
    if(!typeAssocie_estEgal(c1->ta,c2->ta)){
        return 0;
    }
    ta = c1->ta;
    return (ta.fonctionCompare(c1->data,c2->data));
}

Cellule Cellule_cloner(Cellule c){
    Cellule cp = malloc(sizeof(struct Cellule_struct));
    cp->data = c->data;
    cp->next = c->next;
    cp->previous = c->previous;
    cp->used = 0;
    cp->ta = c->ta;
    cp->afficher = c->afficher;
    cp->comparer = c->comparer;
    return cp;
}

Liste Liste_cloner(Liste l){
    Liste lp = Liste_creer(NULL,l->ta);
    Cellule c;
    int i;
    c = l->entry;
    for(i=0;i<l->size;i++){
        Liste_insererFin(lp,c);
        c = c->next;
    }
    return lp;
}

Cellule Cellule_creer(void* data){
    Cellule c;
    c=malloc(sizeof(struct Cellule_struct));
    c->data=data;
    c->previous=NULL;
    c->next=NULL;
    c->used = 0;
    c->ta = associe_int;
    c->afficher = &Cellule_afficher;
    c->comparer = &Cellule_comparer;
    return c;
}

Liste Liste_creer(Cellule c, typeAssocie ta){
    Liste l;
    Cellule cp;
    l=malloc(sizeof(struct Liste_struct));
    // Si c existe
    if(c){
        if(c->used){
            cp = Cellule_cloner(c);
            l->entry = cp;
            l->size = 1;
            l->a = &Liste_a;
            l->premierElement = &Liste_premierElement;
            l->dernierElement = &Liste_dernierElement;
            l->egal = &Liste_egal;
            l->insererDebut = &Liste_insererDebut;
            l->insererFin = &Liste_insererFin;
            l->insererAIndex = &Liste_insererAIndex;
            l->supprimerPremier = &Liste_supprimerPremier;
            l->supprimerDernier = &Liste_supprimerDernier;
            l->supprimerAIndex = &Liste_supprimerAIndex;
            l->vider = &Liste_vider;
            l->sousListe = &Liste_sousListe;
            l->afficher = &Liste_afficher;
            l->ta = ta;
            l->trier = &Liste_trier;

            cp->next = cp;
            cp->previous = cp;
            cp->used = 1;
        }
        else{
            l->entry = c;
            l->size = 1;
            l->a = &Liste_a;
            l->premierElement = &Liste_premierElement;
            l->dernierElement = &Liste_dernierElement;
            l->egal = &Liste_egal;
            l->insererDebut = &Liste_insererDebut;
            l->insererFin = &Liste_insererFin;
            l->insererAIndex = &Liste_insererAIndex;
            l->supprimerPremier = &Liste_supprimerPremier;
            l->supprimerDernier = &Liste_supprimerDernier;
            l->supprimerAIndex = &Liste_supprimerAIndex;
            l->vider = &Liste_vider;
            l->sousListe = &Liste_sousListe;
            l->afficher = &Liste_afficher;
            l->ta = ta;
            l->trier = &Liste_trier;

            c->next = c;
            c->previous = c;
            c->used = 1;
        }
    }
    // Sinon, si Liste_creer(NULL) invoquée
    else{
        l->entry = NULL;
        l->size = 0;
        l->a = &Liste_a;
        l->premierElement = &Liste_premierElement;
        l->dernierElement = &Liste_dernierElement;
        l->egal = &Liste_egal;
        l->insererDebut = &Liste_insererDebut;
        l->insererFin = &Liste_insererFin;
        l->insererAIndex = &Liste_insererAIndex;
        l->supprimerPremier = &Liste_supprimerPremier;
        l->supprimerDernier = &Liste_supprimerDernier;
        l->supprimerAIndex = &Liste_supprimerAIndex;
        l->vider = &Liste_vider;
        l->sousListe = &Liste_sousListe;
        l->afficher = &Liste_afficher;
        l->ta = ta;
        l->trier = &Liste_trier;
    }
    return l;
}

int Cellule_detruire(Cellule c){
    if (c==NULL){
        return -1;
    }
    else{
        free(c);
        return 0;
    }
}

int Cellule_detruireSiInutilise(Cellule c){
    if (c==NULL){
        return -1;
    }
    else{
        if(!c->used){
            free(c);
            return 0;
        }
        else{
            return 1;
        }
    }
}

int Liste_detruire(Liste l){
    Cellule c, next;
    int i;
    if (l==NULL){
        return -1;
    }
    else{
        // Si l est non vide
        if(l->size){
            c = l->entry;
            for(i=0;i<l->size;i++){
                next = c->next;
                c->used = 0;
                free(c);
                c = next;
            }
        }
        return 0;
    }
}

Cellule Liste_a(Liste l, int index){
    int i;
    Cellule c;
    if(l == NULL){
        return NULL;
    }
    if(l->size>index && (index >= 0)){
        c = l->entry;
        for(i=0;i<index;i++){
            c = c->next;
        }
        return c;
    }
    else{
        return NULL;
    }
}

Cellule Liste_premierElement(Liste l){
    if(l == NULL){
        return NULL;
    }
    return l->entry;
}

Cellule Liste_dernierElement(Liste l){
    if(l == NULL || l->size == 0){
        return NULL;
    }
    return l->entry->previous;
}

int Liste_egal(Liste l1,Liste l2){
    Cellule c1, c2;
    int i;
    if(l1 == NULL || l2 == NULL){
        return (l1 == l2);
    }
    if(l1->size != l2->size){
        return 0;
    }
    c1 = l1->entry;
    c2 = l2->entry;
    for(i=0;i<l1->size;i++){
        if(!Cellule_egal(c1,c2)){
            return 0;
        }
        c1 = c1->next;
        c2 = c2->next;
    }
    return 1;
}

int Liste_insererDebut(Liste l, Cellule c){
    Cellule cp;
    if(l == NULL || c == NULL){
        printf("\n<!> Attention <!> : Vous avez appelé la fonction Liste_insererDebut sur une liste null ou une cellule null.\n");
        return -1;
    }
    l->size += 1;
    if(l->size != 1){
        if(c->used){
            cp = Cellule_cloner(c);
            cp->next = l->entry;
            cp->previous = l->entry->previous;
            l->entry->previous->next = cp;
            l->entry->previous = cp;
            l->entry = cp;
            cp->used = 1;
        }
        else{
            c->next = l->entry;
            c->previous = l->entry->previous;
            l->entry->previous->next = c;
            l->entry->previous = c;
            l->entry = c;
            c->used = 1;
        }
    }
    else{
        if(c->used){
            cp = Cellule_cloner(c);
            l->entry = cp;
            cp->next = cp;
            cp->previous = cp;
            cp->used = 1;
        }
        else{
            l->entry = c;
            c->next = c;
            c->previous = c;
            c->used = 1;
        }
    }
    return 0;
}

int Liste_insererFin(Liste l, Cellule c){
    Cellule cp;
    if(l == NULL || c == NULL){
        printf("\n<!> Attention <!> : Vous avez appelé la fonction Liste_insererFin sur une liste null ou une cellule null.\n");
        return -1;
    }
    l->size += 1;
    if(l->size != 1){
        if(c->used){
            cp = Cellule_cloner(c);
            cp->next = l->entry;
            cp->previous = l->entry->previous;
            l->entry->previous->next = cp;
            l->entry->previous = cp;
            cp->used = 1;
        }
        else{
            c->next = l->entry;
            c->previous = l->entry->previous;
            l->entry->previous->next = c;
            l->entry->previous = c;
            c->used = 1;
        }
    }
    else{
        if(c->used){
            cp = Cellule_cloner(c);
            l->entry = cp;
            cp->next = cp;
            cp->previous = cp;
            cp->used = 1;
        }
        else{
            l->entry = c;
            c->next = c;
            c->previous = c;
            c->used = 1;
        }
    }
    return 0;
}

int Liste_insererAIndex(Liste l, Cellule c, int index){
    Cellule cp, cPrev, cNext;
    if(l == NULL || c == NULL){
        printf("\n<!> Attention <!> : Vous avez appele la fonction Liste_insererFin sur une liste null ou une cellule null.\n");
        return -1;
    }
    if((l->size < index) || (index < 0)){
        printf("<!> Attention <!> : Vous avez appele la fonction Liste_insererAIndex avec un index trop grand (ou negatif)(index desire : %d, taille de la liste : %d\n",index,l->size);
        return -1;
    }
    if(index == 0){
        return Liste_insererDebut(l,c);
    }
    if(index == l->size){
        return Liste_insererFin(l,c);
    }
    cPrev = Liste_a(l,index-1);
    cNext = cPrev->next;
    l->size += 1;
    // A Verifie avec des dessins
    if(l->size != 1){
        if(c->used){
            cp = Cellule_cloner(c);
            cPrev->next = cp;
            cp->previous = cPrev;
            cp->next = cNext;
            cNext->previous = cp;
            cp->used = 1;
        }
        else{
            cPrev->next = c;
            c->previous = cPrev;
            c->next = cNext;
            cNext->previous = c;
            c->used = 1;
        }
    }
    else{
        if(c->used){
            cp = Cellule_cloner(c);
            cPrev->next = cp;
            cp->previous = cPrev;
            cp->next = cNext;
            cNext->previous = cp;
            cp->used = 1;
        }
        else{
            cPrev->next = c;
            c->previous = cPrev;
            c->next = cNext;
            cNext->previous = c;
            c->used = 1;
        }
    }
    return 0;
}

int Liste_supprimerPremier(Liste l){
    Cellule c;
    if(l == NULL){
        printf("\n<!> Attention <!> : Vous avez appelé la fonction Liste_supprimerPremier sur une liste null.\n");
        return -1;
    }
    if(l->size < 1){
        printf("\n<!> Attention <!> : Vous avez appelé la fonction Liste_supprimerPremier sur une liste trop courte.\n");
        return -2;
    }
    if(l->size == 1){
        Cellule_detruire(l->entry);
        l->size = 0;
        l->entry = NULL;
        return 0;
    }
    l->size -= 1;
    c = l->entry;
    l->entry = c->next;
    l->entry->previous = c->previous;
    c->previous->next = l->entry;
    Cellule_detruire(c);
    return 0;
}

int Liste_supprimerDernier(Liste l){
    Cellule c;
    if(l == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appelé la fonction Liste_supprimerDernier sur une liste null.\n");
        return -1;
    }
    if(l->size < 1){
        fprintf(stderr,"<!> Attention <!> : Vous avez appelé la fonction Liste_supprimerDernier sur une liste trop courte.\n");
        return -2;
    }
    if(l->size == 1){
        Cellule_detruire(l->entry);
        l->size = 0;
        l->entry = NULL;
        return 0;
    }
    l->size -= 1;
    c = l->entry->previous;
    c->previous->next = l->entry;
    l->entry->previous = c->previous;
    Cellule_detruire(c);
    return 0;
}

int Liste_supprimerAIndex(Liste l, int index){
    Cellule c, cPrev, cNext;
    if(l == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appelé la fonction Liste_supprimerAIndex sur une liste null.\n");
        return -1;
    }
    if(!(index < l->size)){
        fprintf(stderr,"<!> Attention <!> : Vous avez appelé la fonction Liste_supprimerAIndex sur une liste trop courte.\n");
        return -2;
    }
    if(index == l->size-1){
        Liste_supprimerDernier(l);
        return 0;
    }
    if(index == 0){
        Liste_supprimerPremier(l);
        return 0;
    }
    c = Liste_a(l,index);
    cPrev = c->previous;
    cNext = c->next;
    l->size -= 1;
    cPrev->next = cNext;
    cNext->previous = cPrev;
    Cellule_detruire(c);
    return 0;
}

int Liste_vider(Liste l){
    int i;
    Cellule c, next;
    if(l == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appelé la fonction Liste_vider sur une liste null.\n");
        return -1;
    }
    if(l->size == 0){
        fprintf(stderr,"<!> Attention <!> : Vous avez appelé la fonction Liste_vider sur une liste dejà vide.\n");
        return 0;
    }
    c = l->entry;
    for(i=0;i<l->size;i++){
        next = c->next;
        Cellule_detruire(c);
        c = next;
    }
    l->size = 0;
    l->entry = NULL;
    return 0;
}

Liste Liste_sousListe(Liste l, int index){
    int i;
    Liste ssl = Liste_creer(NULL,l->ta);
    Cellule c;
    if(l == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appele Liste_sousListe sur une liste null.\n");
        return NULL;
    }
    if((l->size < index) || (index < 0)){
        fprintf(stderr,"<!> Attention <!> : Vous avez appele Liste_sousListe avec un index trop grand. (Taille de la liste : %d, index desire : %d.\n",l->size,index);
        return NULL;
    }
    c = Liste_a(l,index);
    Liste_insererFin(ssl,c);
    for(i=index+1;i<l->size;i++){
        c = c->next;
        Liste_insererFin(ssl,c);
    }
    return ssl;
}

int Liste_insererListeDebut(Liste l, Liste lAInserer){
    int i;
    Cellule c;
    if(l == NULL || lAInserer == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appele Liste_insererListeDebut sur au moins une liste NULL.");
        return -1;
    }
    c = lAInserer->entry;
    if(lAInserer->size > 0){
        c = c->previous;
    }
    for(i=0;i<lAInserer->size;i++){
        Liste_insererDebut(l,c);
        c = c->previous;
    }
    return 0;
}

int Liste_insererListeFin(Liste l, Liste lAInserer){
    int i;
    Cellule c;
    if(l == NULL || lAInserer == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appele Liste_insererListeFin sur au moins une liste NULL.");
        return -1;
    }
    c = lAInserer->entry;
    for(i=0;i<lAInserer->size;i++){
        Liste_insererFin(l,c);
        c = c->next;
    }
    return 0;
}

int Liste_insererListeAIndex(Liste l, Liste lAInserer, int index){
    int i;
    Cellule c, cp, next;
    if(l == NULL || lAInserer == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appele Liste_insererListeAIndex sur au moins une liste NULL.");
        return -1;
    }
    if(l->size < index){
        fprintf(stderr,"<!> Attention <!> : Vous avez appele Liste_insererListeAIndex sur au moins une liste trop petite : l->size : %d, index : %d.",l->size,index);
        return -1;
    }
    if(index == 0){
        Liste_insererListeDebut(l, lAInserer);
        return 0;
    }
    if(index == l->size){
        Liste_insererListeFin(l,lAInserer);
        return 0;
    }
    l->size += lAInserer->size;
    next = Liste_a(l,index);
    c = next->previous;
    cp = Cellule_cloner(lAInserer->entry);
    for(i=0;i<lAInserer->size;i++){
        cp->used = 1;
        c->next = cp;
        cp->previous = c;
        c = cp;
        cp = Cellule_cloner(cp->next);
    }
    Cellule_detruire(cp);
    c->next = next;
    next->previous = next;
    return 0;
}

void Liste_afficher(Liste l){
    int i;
    Cellule c;
    if(l == NULL){
        fprintf(stderr,"<!> Attention <!> : Vous avez appele Liste_afficher sur une liste vide.\n");
        return;
    }
    if(l->entry == NULL){
        printf("Liste vide\n");
    }
    if(l->ta.fonctionAffichage == NULL){
        c = l->entry;
        for(i=0;i<l->size;i++){
            Cellule_afficher(c);
            c = c->next;
            if(i != l->size -1){
                printf(" <-> ");
            }
        }
    }
    else{
        c = l->entry;
        for(i=0;i<l->size;i++){
            l->ta.fonctionAffichage(c->data);
            c = c->next;
            if(i != l->size -1){
                printf(" <-> ");
            }
        }
    }
    printf("\n");
}

void Cellule_afficher(Cellule c){
    if(c == NULL){
        printf("Cellule NULL");
    }
    else{
        if(c->ta.fonctionAffichage == NULL){
            printf("Aucun affichage disponible");
        }
        else{
            c->ta.fonctionAffichage(c->data);
        }
    }
}

int Liste_trier(Liste l){
    void** T;
    Cellule c;
    typeAssocie ta;
    int i, size;
    if(l == NULL){
        fprintf(stderr,"<!> Attention <!>, vous avez invoquez Liste_trier sur une liste NULL");
        return -1;
    }
    if(l->ta.fonctionCompare == NULL){
        fprintf(stderr,"<!> Attention <!>, vous avez invoquez Liste_trier sur une liste qui n'a pas de définition sur comment comparer ces elements");
        return -1;
    }
    if(l->size == 0){
        return 0;
    }
    ta = l->ta;
    size = l->size;
    T = malloc(sizeof(void*)*size);
    c = l->entry;
    for(i=0;i<size;i++){
        T[i] = c->data;
        c = c->next;
    }
    qsort(T,size,sizeof(void*),ta.fonctionCompare);
    Liste_vider(l);
    for(i=0;i<size;i++){
        Liste_insererFin(l,Cellule_creer(T[i]));
    }
    free(T);
    return 0;
}

/* --- Definition de different type associé frequent --- */

typeAssocie typeAssocie_creer(void fctAffichage(void *),int fctCompare(const void *, const void *)){
    typeAssocie res;
    res.fonctionAffichage = fctAffichage;
    res.fonctionCompare = fctCompare;
    res.estNull = typeAssocie_estNull;
    res.estEgal = typeAssocie_estEgal;
    return res;
}

int typeAssocie_estNull(typeAssocie ta){
    return ((ta.fonctionAffichage == NULL) && (ta.fonctionCompare == NULL));
}

int typeAssocie_estEgal(typeAssocie ta1, typeAssocie ta2){
    return ((ta1.fonctionAffichage == ta2.fonctionAffichage) && (ta2.fonctionCompare == ta2.fonctionCompare));
}

/* --- Type predefini --- */
void __CHAINE__affiche(void* ch){
    printf("%s",*(char**)ch);
}

int __CHAINE__compare(const void* ch1,const void* ch2){
    return strcmp(*(char**)ch1,*(char**)ch2);
}

void __INT__affiche(void* in){
    printf("%d",*(int*)in);
}

int __INT__compare(const void* in1,const void* in2){
    int const *pa = in1;
    int const *pb = in2;

    return *pa - *pb;
}

void __SHORT__affiche(void* sh){
    printf("%d",*(short*)sh);
}

int __SHORT__compare(const void* sh1,const void* sh2){
    short const *pa = sh1;
    short const *pb = sh2;

    return *pa - *pb;
}

void __LONG__affiche(void* lo){
    printf("%ld",*(long*)lo);
}

int __LONG__compare(const void* lo1,const void* lo2){
    long const *pa = lo1;
    long const *pb = lo2;

    return *pa - *pb;
}

void __FLOAT__affiche(void* fl){
    printf("%f",*(float*)fl);
}

int __FLOAT__compare(const void* fl1,const void* fl2){
    float const *pa = fl1;
    float const *pb = fl2;

    return *pa - *pb;
}

void __DOUBLE__affiche(void* dou){
    printf("%f",*(float*)dou);
}

int __DOUBLE__compare(const void* dou1,const void* dou2){
    double const *pa = dou1;
    double const *pb = dou2;

    return *pa - *pb;
}

void __CHAR__affiche(void* ch){
    printf("%c",*(char*)ch);
}

int __CHAR__compare(const void* ch1,const void* ch2){
    char const *pa = ch1;
    char const *pb = ch2;

    return *pa - *pb;
}

/* ------------ */
