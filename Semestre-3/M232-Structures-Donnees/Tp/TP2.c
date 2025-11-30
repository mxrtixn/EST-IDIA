#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct etudiant{
    char *Nom;
    char *Prenom;
    float Note;
    struct etudiant *Suivant;
    }Etudiant;

typedef struct{
    Etudiant *Debut;
    int Nb_etudiants;
    }Liste;

void Initialiser_Liste(Liste *L){
	L->Debut=NULL;
  	L->Nb_etudiants=0;
}

Etudiant* Creer_Etudiant(char *nom,char *prenom ,float note){
   Etudiant *E;
   if ((E=(Etudiant *)malloc(sizeof(Etudiant)))==NULL) return NULL;
   if ((E->Nom=(char *)malloc(20*sizeof(char)))==NULL) return NULL;
   if ((E->Prenom=(char *)malloc(20*sizeof(char)))==NULL) return NULL;

   strcpy(E->Nom,nom);
   strcpy(E->Prenom,prenom);

void Inserer_Debut(Liste *L,Etudiant *E){
  	if(L->Nb_etudiants==0)
		L->Debut=E;
  	else{
    	E->Suivant=L->Debut;
	   	L->Debut=E;
	}
	L->Nb_etudiants++;
}

void Inserer_Fin(Liste *L,Etudiant *E){
	Etudiant *Courant;
   	if(L->Nb_etudiants==0) L->Debut=E;
	else{
        Courant=L->Debut;
        while(Courant->Suivant!=NULL)
		      Courant=Courant->Suivant;
        Courant->Suivant=E;
	}
	L->Nb_etudiants++;
}

void Afficher_Liste(Liste L){
	Etudiant *Courant;
	Courant=L.Debut;
  	while(Courant!=NULL){
    	printf("%s  %s a eu la note %.2f \n", Courant->Nom, Courant->Prenom, Courant->Note);
    	Courant=Courant->Suivant;
  	}
}

void Detruire_Liste(Liste *L){
	Etudiant *Supp;
	while(L->Debut!=NULL){
    	Supp=L->Debut;
      	L->Debut=L->Debut->Suivant;
      	free(Supp->Nom);
      	free(Supp->Prenom);
      	free(Supp);
      	L->Nb_etudiants--;
   	}
}

void Diviser_Liste (Liste L, Liste *L1, Liste *L2) {
	Etudiant *s, *p;
   	p=L.Debut;
   	if(p==NULL) printf("la Liste est vide ! \n");
   	else{
    	while(p!=NULL){
			s=Creer_Etudiant(p->Nom, p->Prenom ,p->Note);
            if(s->Note>=10) Inserer_Fin(L1, s);
            else Inserer_Fin(L2, s);
            p=p->Suivant;
        }
	}
}

void Echanger_Etudiants(Etudiant *E1, Etudiant *E2){
  	float n;
  	char *t;
  	t=E1->Nom; E1->Nom=E2->Nom; E2->Nom=t;
  	t=E1->Prenom; E1->Prenom=E2->Prenom; E2->Prenom=t;
  	n=E1->Note; E1->Note=E2->Note; E2->Note=n;
}

void Trier_selection(Liste *L){
	Etudiant *p, *q, *t;
   	p=L->Debut;
   	while(p!=NULL){
    	q=p->Suivant;
      	t=p;
      	while(q!=NULL){
         	if(q->Note > t->Note){
		   		t=q;
		 	}
         	q=q->Suivant;
      	}
      	if(t!=p) Echanger_Etudiants(t,p);
      	p=p->Suivant;
   	}
}

// Deuxième version de la fonction du tri
void Trier_selection2(Liste *L){
	Etudiant *p, *q, *t;
   	float maxnote;
   	for(p=L->Debut; p->Suivant!=NULL; p=p->Suivant){
    	t=p;
      	for(q=p->Suivant; q!=NULL; q=q->Suivant){
         	if(q->Note > t->Note) t=q;
      	}
      	if(t!=p) Echanger_Etudiants(t,p);
   	}
}

main(){
  	int i, n;
	float note;
  	char nom[30], prenom[30];
  	Liste *Classe, *Admis, *Non_Admis;
  	Etudiant *E;

  	Classe=(Liste *)malloc(sizeof(Liste));
  	Initialiser_Liste(Classe);
  	Admis=(Liste *)malloc(sizeof(Liste));
  	Initialiser_Liste(Admis);
  	Non_Admis=(Liste *)malloc(sizeof(Liste));
  	Initialiser_Liste(Non_Admis);

  	printf("Donner le nombre d etudiants de la classe: ");
  	scanf("%d",&n);
  	for(i=0;i<n;i++){
     	printf("Saisir les donnees de l etudiant %d :\n",i+1);
     	printf("Nom    : "); getchar();
	 	gets(nom);
     	printf("Prenom : ");
	 	gets(prenom);
     	printf("Note   : ");
	 	scanf("%f",&note);
     	E=Creer_Etudiant(nom,prenom,note);
     	Inserer_Fin(Classe, E);
	}
  	printf("Liste de la Classe : -----------------\n");
  	Afficher_Liste(*Classe);

  	Diviser_Liste(*Classe,Admis,Non_Admis) ;
  	printf("Liste des Admis:-------------------- \n");
  	Afficher_Liste(*Admis);
  	printf("Liste des Non Admis:---------------- \n");
  	Afficher_Liste(*Non_Admis);

  	printf("Liste des Admis par ordre de merite:---------\n");
  	Trier_selection(Admis);
  	Afficher_Liste(*Admis);

  	Detruire_Liste(Classe);
  	Detruire_Liste(Admis);
  	Detruire_Liste(Non_Admis);
}
