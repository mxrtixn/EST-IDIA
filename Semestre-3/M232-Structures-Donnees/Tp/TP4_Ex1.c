#include<stdio.h>
#include<stdlib.h>

typedef struct ElementListe {
	int donnee;
	struct ElementListe *suivant; 
} Element;

/*variables globales*/
int Taille;
Element *Debut;
Element *Fin;

void initialiser_liste(){
	Debut = NULL; 
	Fin = NULL; 
	Taille = 0;
}

void inserer_liste_vide(int d) {
	Element *nouveau;
	nouveau = (Element *)malloc(sizeof(Element));
	nouveau->donnee = d ;
	nouveau->suivant = nouveau; //circulaire
	Debut = nouveau; 
	Fin = nouveau;
	Taille++;
}

void inserer_debut(int d){
	Element *nouveau;
	nouveau = (Element *)malloc(sizeof(Element));
	nouveau->donnee = d ;
	nouveau->suivant = Debut;
	Fin->suivant = nouveau; //circulaire
	Debut = nouveau;
	Taille++;
}

void inserer_fin(int d) {
	Element *nouveau;
	nouveau = (Element *)malloc(sizeof(Element));
	nouveau->donnee = d ;
	Fin->suivant = nouveau; 
	nouveau->suivant = Debut; //circulaire
	Fin=nouveau;
	Taille++;
}

void afficher_liste() {
	Element *courant;
	courant = Debut;
	int i=1;
	if(Taille==0) printf("Rien a afficher, la liste est vide !");
	while (i<=Taille) {
		printf ("%d  ", courant->donnee);
		i++;
		courant=courant->suivant;
	}
	printf("\n");
}

int supprimer_debut() {
	Element *supp;
	if (Taille == 0) return -1;
	supp = Debut;
	Debut = Debut->suivant;
	Fin->suivant = Debut ; //Circulaire
	if (Taille == 1){
		Debut=NULL;
		Fin = NULL;
	}
	free(supp);
	Taille--;
	return 0;
}

int supprimer_fin() {
	int i;
	Element *courant, *supp;
	if (Taille == 0) return -1;
	courant = Debut;
	// placer courant sur l'avant dernier element de la liste
	while(courant->suivant!=Fin) courant=courant->suivant; 
	supp = Fin;
	courant->suivant = Debut;
	Fin=courant;
	if (Taille == 1){
		Debut=NULL;
		Fin=NULL;
	}
	free(supp);
	Taille--;
	return 0;
}

void detruire_liste(){
	while(Taille > 0) supprimer_debut(); // ou supprimer_fin()
}

// decalage par echange des données
void decalage_par_echange(int pas){ 
	int i, j, p, c;
	for(i=1; i<=pas; i++) { 
		Element *courant;
		courant=Debut;  
		p = Debut->donnee;
		for(j=1;j<Taille;j++){
			courant = courant->suivant; 
			c = courant->donnee;
			courant->donnee = p;
			p = c;
		}
		Debut->donnee=p;
	}
}
// decalage par suppression à la fin et insertion au début
void decalage_par_suppression(int pas){ 
	int i, d;
	for(i=1; i<=pas; i++) { 
		d=Fin->donnee;
		supprimer_fin();
		inserer_debut(d);
	}
}

// decalage par changement de début et fin 
void decalage_par_changement(int pas){ 
	int i;
	Element *courant;
	for(i=1; i<=pas; i++) { 
		courant=Debut;
		while(courant->suivant!=Fin) courant=courant->suivant; // place courant sur l'avant dernier element de la liste
		Debut=Fin;
		Fin=courant;
	}
}

void main(){
	int nb, i, data, nbpas;
	initialiser_liste();
	printf("Donner la taille de la liste: "); 
	scanf("%d",&nb);
	for(i=1; i<=nb; i++){
		printf("Saisir un bit : "); scanf("%d", &data);
		if(Taille==0) inserer_liste_vide(data);
		else inserer_fin(data);
	}
	printf("Contenu de la liste avant decalage: \n");
	afficher_liste();
	printf("Entrer le nombre de pas de decalage: "); scanf("%d", &nbpas);
	decalage_par_changement(nbpas);
	printf("Contenu de la liste apres le decalage: \n");
	afficher_liste();
	detruire_liste();
}
