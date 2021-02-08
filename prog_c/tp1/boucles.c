/* Fichier boucles.c
*affiche un triangle rectangle dont la taille est définie par l'utilisateur avec des boucles for. Les bords sont en '*' et l'intérieur en '#'
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/
#include <stdio.h> //Bibliothèques classiques
#include <stdlib.h>

int main()
{
	int count=0,i=1,c;//Déclaration des variables utiles
	while(count<4){
		printf("Donner la taille du triangle valable ");//On fait en sorte que si l'utilisateur rentre une taille inacceptable, le programme lui redemande jusqu'à ce qu'elle le soit
		scanf("%d",&count);//Demande à l'utilisateur de la taille du triangle
	}
	printf("*\n");//Affichage du sommet
	for (i=1;i < count-1;i++){
		printf("*");//Affichage des côtés gauche
		for (c=i;c!=1;c--){
			printf("#");//Affichage de l'intérieur
		}
		printf("*\n");//Affichage des côtés droits
	}
	for (i=1;i!=count+1;i++){
		printf("*");//Affichage du côté en bas du triangle
	}
	printf("\n");//On fait ça pour que le programme soit esthétique et que le triangle soit bien affiché
	return 0;
}
	
			
			
