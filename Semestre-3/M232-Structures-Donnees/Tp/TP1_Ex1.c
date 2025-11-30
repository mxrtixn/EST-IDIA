#include<stdio.h>
#define max 100

// Structures de données necessaires
typedef struct{
	int tab[max];
	int sommet;
}Pile;

// Variables globales
Pile P1, P2, P3;
// 1-a)
void InitialiserPile(Pile *P){
	P->sommet=-1;
}
//1-b)
int PileVide(Pile P){
	return (P.sommet<0);
}

//1-c)
int PilePleine(Pile P){
	return (P.sommet>=max-1);
}

//1-d)
void PilePush(Pile *P, int elt){
	if(PilePleine(*P)) printf("Pile pleine !");
	else{
		P->sommet=P->sommet+1; //P->sommet ++;
		P->tab[P->sommet]=elt;
	}
}

//1-e)
int PilePop(Pile *P){
	int x;
	if(PileVide(*P)) printf("Pile vide !");
	else{
		x=P->tab[P->sommet];
		P->sommet=P->sommet-1; // P->sommet --;
	}
	return x;
}

//1-f)
int PileSommet(Pile P){
	return P.sommet;
}

//2)
void Deplacer(){
	int e;
	while(!PileVide(P1)){
		e=PilePop(&P1);
		if(e%2==0) PilePush(&P3, e);
		else PilePush(&P2, e);
	}
	while(!PileVide(P3)){
		e=PilePop(&P3);
		PilePush(&P2, e);
	}
}

//3)
main(){
	int nbr, i, e;
	InitialiserPile(&P1);
	InitialiserPile(&P2);
	InitialiserPile(&P3);
	printf("Entrer le nombre d elements: ");
	scanf("%d", &nbr);
	for(i=1; i<=nbr; i++){
		printf("Entrer element %d: ", i);
		scanf("%d", &e);
		PilePush(&P1, e);
	}
	// Affichage du contenu de P1 avant déplacement
	printf("\nAffichage du contenu de P1 avant traitement: \n");
	for(i=PileSommet(P1); i>=0; i--){
		printf("%d \n", P1.tab[i]);
	} 
	Deplacer();  
	// Affichage du contenu de P2 apres traitement
	printf("\nAffichage du contenu de P2 apres traitement: \n");
	for(i=PileSommet(P2); i>=0; i--){
		printf("%d \n", P2.tab[i]);
	} 
}
