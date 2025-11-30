#include<stdio.h>
#include<stdlib.h>
typedef struct ElementListe{
	int donnee;
	struct ElementListe *precedent;
	struct ElementListe *suivant; 
	}Element;
int Taille;
Element *Debut, *Fin;

//Initialisation de la liste
void initialiser_liste(){
	Debut = NULL;
	Fin = NULL;
	Taille = 0; 
}
//Insertion dans une liste vide
int inserer_liste_vide(int d){
	Element *nouveau;
	if ((nouveau = (Element*) malloc(sizeof(Element))) == NULL) return -1;
	nouveau->donnee = d;
	nouveau->precedent = nouveau; //Circulaire
	nouveau->suivant = nouveau; //Circulaire
	Debut = nouveau;
	Fin = nouveau;
	Taille++;
	return 0;
}
//Insertion au debut de la liste
int inserer_debut(int d){
	Element *nouveau;
	if ((nouveau = (Element*) malloc(sizeof(Element))) == NULL) return -1;
	nouveau->donnee=d;
	nouveau->suivant = Debut;
	Debut->precedent = nouveau;
	nouveau->precedent = Fin; //Circulaire
	Fin->suivant = nouveau; //Circulaire
	Debut = nouveau;
	Taille++;
	return 0;
}
//Insertion a la fin de la liste
int inserer_fin(int d){
	Element *nouveau;
	if ((nouveau = (Element*) malloc(sizeof(Element))) == NULL) return -1;
	nouveau->donnee=d;
	nouveau->precedent = Fin;
	Fin->suivant = nouveau;
	nouveau->suivant = Debut; //Circulaire
	Debut->precedent=nouveau; //Circulaire
	Fin = nouveau;
	Taille++;
	return 0;
}
//Insertion avant un element de la liste de position pos
int inserer_avant(int d, int pos){
	int i;
	Element *nouveau, *courant;
	if ((nouveau = (Element*) malloc(sizeof(Element))) == NULL) return -1;
	nouveau->donnee=d;
	courant = Debut;
	for(i = 1; i < pos; ++i) courant = courant->suivant;
	courant->precedent->suivant = nouveau;
	nouveau->precedent = courant->precedent;
	nouveau->suivant = courant;
	courant->precedent = nouveau;
	if(pos==1){
		Debut = nouveau; 
		Debut->precedent = Fin; Fin->suivant = Debut; //Circulaire
	}
	Taille++;
	return 0;
}
//Insertion apres un element de la liste de position pos
int inserer_apres(int d, int pos){
	int i;
	Element *nouveau, *courant;
	if ((nouveau = (Element*) malloc(sizeof(Element))) == NULL) return -1;
	nouveau->donnee = d;
	courant = Debut;
	for(i = 1; i < pos; ++i) courant = courant->suivant;
	nouveau->suivant = courant->suivant;
	courant->suivant->precedent = nouveau;
	nouveau->precedent = courant;
	courant->suivant = nouveau;
	if(pos==Taille){
		Fin=nouveau; 
		Fin->suivant = Debut; Debut->precedent = Fin; //Circulaire
	}
	Taille++;
	return 0;
}
//Suppression d'un element dans la liste
int supprimer(int pos){
	int i;
	Element *supp_element, *courant;
	if(Taille == 0) return -1;
	if(pos == 1) { // suppression du 1er element 
		supp_element = Debut; Debut = Debut->suivant;
		if(Taille==1){ 
			Debut=NULL; Fin=NULL;
		}
		else{
			Fin->suivant=Debut; Debut->precedent = Fin; //Circulaire
		}
	}
	else if(pos == Taille){ // suppression du dernier element 
			supp_element = Fin;
			Fin = Fin->precedent;
			Fin->suivant = Debut; //Circulaire
			Debut->precedent = Fin; //Circulaire
		}
		else{ // suppression ailleurs 
			courant = Debut;
			for(i=1; i<pos; ++i) courant = courant->suivant;
			supp_element = courant;
			courant->precedent->suivant = courant->suivant;
			courant->suivant->precedent = courant->precedent;
		}
	free(supp_element);
	Taille--;
	return 0;
}
//Afficher la liste entiere
afficher_liste(){ // affichage en avançant 
	Element *courant;
	int i;
	courant = Debut; 
	for(i=1; i<=Taille; i++) {
		printf(" %d ", courant->donnee);
		courant = courant->suivant; 
	}
}
//Destruction de la liste
detruire_liste() {
	while (Taille > 0) supprimer(1); // ou supprimer(Taille);
}
//Nombre de zeros
int nombreZeros(int a){
	int b=0,c;
	c=a;
	while(c/10!=0){
		b++;
		c=c/10;
	}
	return(b);
}
//Multiplication par a=10^b
void multiplication(int mult){
	int b=0,i;
	b=nombreZeros(mult);
	for(i=1;i<=b;i++) inserer_fin(0);
}
//Division par a=10^b
void division(int div){
	int b=0,i;
	b=nombreZeros(div);
	for(i=1;i<=b;i++) supprimer(Taille); // suppression à la fin
}

main(){
	int nb, a, pas, i, m, d;
	initialiser_liste();
	printf(" Donner la taille de la liste: "); scanf("%d",&nb);
	for(i=1;i<=nb;i++){
		printf(" Saisir un chiffre : "); scanf("%d",&a);
		if(Taille==0) inserer_liste_vide(a);
		else inserer_fin(a);
	}
	printf("\n -------------- Affichage de la liste: \n");
	afficher_liste();
	printf("\n Entrer le multiplicateur: "); scanf("%d",&m);
	multiplication(m);
	printf("\n -------------- Resultat de la multiplication: \n");
	afficher_liste();
	printf("\n Entrer le diviseur: "); scanf("%d",&d);
	division(d);
	printf("\n -------------- Resultat de la division: \n");
	afficher_liste();
	detruire_liste();
}
