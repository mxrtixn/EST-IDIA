#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Question 1 
typedef struct etudiant{
	int apogee;
	char nom[20]; 
	char prenom[20]; 
	char filiere[5];
	struct etudiant *suivant; 
	struct etudiant *precedent;
}Etudiant;

Etudiant *Debut, *Fin; 
int Taille;

// Question 2-a
void initialiser_liste(){
	Debut=NULL; 
	Fin=NULL;
	Taille=0;
}

// Question 2-b
Etudiant* creer_noeud(int apo, char *nm,char *pr,char *fil){ 
	Etudiant *nouveau;
	if((nouveau = (Etudiant*)malloc(sizeof(Etudiant))) == NULL) return NULL; 
	nouveau->apogee=apo;
	strcpy(nouveau->nom, nm);
	strcpy(nouveau->prenom, pr); 
	strcpy(nouveau->filiere, fil);
	return nouveau;
}
// Question 2-c
void inserer_liste_vide(Etudiant *E){ 
	E->precedent = NULL; 
	E->suivant = NULL;
	Debut = E;
 	Fin = E; 
	Taille = 1; // ou Taille++;
}
// Question 2-d
void inserer_debut(Etudiant *E){ 
	E->precedent = NULL; 
	E->suivant = Debut;  
	Debut->precedent = E;
	Debut = E; 
	Taille ++;
}
// Question 2-e
void inserer_fin(Etudiant *E){  
	E->suivant = NULL; 
	E->precedent = Fin; 
	Fin->suivant = E;
	Fin = E; 
	Taille ++;
}

// Question 2-f
int supprimer_noeud(int pos){ 
	int i;
	Etudiant *supp_element, *courant; 
	if(Taille == 0 || pos < 1) return -1;
	if(pos == 1){ // suppression de 1er élément  
		supp_element = Debut;
		Debut = Debut->suivant; 
		if(Debut == NULL) Fin = NULL; // liste vide 
		else Debut->precedent = NULL;
	}
	else if(pos == Taille){ // suppression du dernier élément 
		supp_element = Fin;  
		Fin->precedent->suivant = NULL;
		Fin = Fin->precedent;
	}
	else{	// suppression ailleurs 
		courant = Debut;
		for(i=1; i<pos; i++) courant = courant->suivant; 
		supp_element = courant; 
		courant->precedent->suivant = courant->suivant; 
		courant->suivant->precedent = courant->precedent;
	}
	free(supp_element); 
	Taille --;
	return 0;
}

// Question 2-g
void afficher_liste(){ /* affichage en avançant */ 
	Etudiant *courant;
	courant = Debut; /* point du départ le 1er élément */ 
	if(Taille==0) printf("Rien a afficher, la liste est vide !\n");
	else{
		printf("| Num |      NOM |   PRENOM |  FIL | \n");
		while(courant != NULL){
			printf("| %3d | %8s | %8s | %4s | \n", courant->apogee, courant->nom, courant->prenom, courant->filiere);
			courant = courant->suivant;
		}
	}
}

// Question 2-h
void detruire_liste(){
	while (Taille > 0)	supprimer_noeud(Taille); // ou bien supprimer_noeud(1);
}

// Question 3
void construire_liste(){	
	int i, NB, apog;
	char last[20], first[20], program[40];
	Etudiant *Etud;
	printf("Entrer le nombre d etudiants: "); 
	scanf("%d", &NB);
	for(i=1; i<=NB; i++){
		printf("Saisie de l etudiant %d: \n", i);
		printf("Numero apogee: "); 
		scanf("%d", &apog);
		printf("Nom: "); 
		scanf("%s",last);
		printf("Prenom: "); 
		scanf("%s",first); 
		printf("Filiere: "); 
		scanf("%s",program);
		Etud = creer_noeud(apog, last, first, program);
		if(Taille==0) inserer_liste_vide(Etud); 
		else{
 			if(strcmp(program,"GI") == 0)	inserer_debut(Etud); // étudiant GI
			else if(strcmp(program,"IDIA") == 0) inserer_fin(Etud); // étudiant IDIA
		}	
	}
}

void echanger_noeuds(Etudiant *E1, Etudiant *E2){
	int tmp;
	char temp[20];
	tmp=E1->apogee; E1->apogee=E2->apogee; E2->apogee=tmp;
	strcpy(temp, E1->nom); strcpy(E1->nom, E2->nom); strcpy(E2->nom, temp);
	strcpy(temp, E1->prenom); strcpy(E1->prenom, E2->prenom); strcpy(E2->prenom, temp);
	strcpy(temp, E1->filiere); strcpy(E1->filiere, E2->filiere); strcpy(E2->filiere, temp);
}

// Question 4 
void trier_liste(){ // Tri par selection
	int tmp;
	char temp[20];
	Etudiant *c, *c1, *c2;
	for(c1=Debut; c1->suivant!=NULL; c1=c1->suivant){  
		c=c1;
		for(c2=c1->suivant; c2!=NULL; c2=c2->suivant){
			if(strcmp(c2->nom, c->nom) < 0) c=c2;
		}
		if(c!=c1) echanger_noeuds(c, c1);
	}
}

//Question 5 
void statistiques(){
	int NbGI = 0, NbIDIA = 0;
	Etudiant *courant; 
	courant = Debut; 
	while(courant != NULL){
		if(strcmp(courant->filiere,"GI") == 0) NbGI ++; 
		else if(strcmp(courant->filiere,"IDIA") == 0) NbIDIA ++;
		courant=courant->suivant;
	}
	printf("----------- Statistiques ----------------\n"); 
	printf("Nombre des etudiants inscrits dans GI : %d \n", NbGI); 
	printf("Nombre des etudiants inscrits dans IDIA : %d \n", NbIDIA);
}
// Question 6
void supprimer_IDIA(){
	Etudiant *cour;
	cour = Debut;
	int index = 1;
	while(cour!=NULL){
		if (strcmp(cour->filiere, "IDIA") == 0){
			cour=cour->suivant;
			supprimer_noeud(index);
		}
		else{
			cour=cour->suivant;
			index ++;
	    }
	}
}

main(){
	initialiser_liste();
	construire_liste();
	printf("------- Etudiants classes par filiere -------------------\n");
	afficher_liste();
	printf("------- Etudiants classes par nom -------------------\n");
	trier_liste();
	afficher_liste();
	statistiques();
	printf("------- Suppression des etudiants de IDIA -----------\n");
	supprimer_IDIA();
	printf("------- Etudiants de GI restants dans la liste ------\n");
	afficher_liste();
	detruire_liste(); 
}

