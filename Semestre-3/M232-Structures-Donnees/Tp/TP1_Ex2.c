#include<stdio.h>
#define max 100
// Structures et variables globales
typedef struct{ 
	int tab[max] ;
	int ar;  
}File;

File F1, F2, F3;

//1-a
void InitialiserFile(File *F){
	F->ar=-1;
}
//1-b
int FileVide(File F){
	return (F.ar==-1);
}
//1-c
int FilePleine(File F){
	return (F.ar>=max-1);
}
//1-d
void Enfiler(File *F,int x){
	if (FilePleine(*F)) printf("File Pleine !");
	else{
		F->ar=F->ar+1; // F->ar ++;
		F->tab[F->ar]=x;
	}
}
//1-e
int Defiler(File *F){
	int x,i;
	if(FileVide(*F)){
		printf("File Vide !"); 
		return -1;	
	}
	else{
		x=F->tab[0]; // element de l'avant
		for(i=0;i<F->ar;i++) 
			F->tab[i]=F->tab[i+1];
		F->ar=F->ar-1; // F->ar --;
		return x;
	}
}
//1-f
int Retirer_max(){
	int mx,x;
	if(!FileVide(F1)){
		mx=Defiler(&F1);
		Enfiler(&F2,mx);
		while(!FileVide(F1)){
			x=Defiler(&F1);
			if(x>mx) mx=x;
			Enfiler(&F2,x);
		}
		while(!FileVide(F2)){
			x=Defiler(&F2);
			if(x!=mx) Enfiler(&F1,x);
		}
		return mx;
	}
	return -1;
}
//1-g
void Trier(){
	int x;
	while(!FileVide(F1)){
		x=Retirer_max();
		Enfiler(&F3,x);
	} 
	while(!FileVide(F3)){
	    x=Defiler(&F3);
		Enfiler(&F1,x); 
	}
}

//2
main(){
	int nbr,x,i;
	InitialiserFile(&F1);
	InitialiserFile(&F2);
	InitialiserFile(&F3);
	printf("Entrer le nombre d elements: ");
	scanf("%d",&nbr);
	for(i=1;i<=nbr;i++){
		printf("Taper l element %d: ",i);
		scanf("%d",&x);
		Enfiler(&F1,x);
	}
	printf("\n--------------------------------------\n");
	printf("Affichage du contenu de la file avant le tri: \n");
	for(i=0;i<nbr;i++) printf(" %d ",F1.tab[i]);
	Trier();
	printf("\n--------------------------------------\n");
	printf("Affichage du contenu de la file apres le tri: \n");
	for(i=0;i<nbr;i++) printf(" %d ",F1.tab[i]);
}
