/* Fichier boucles2.c
*affiche un triangle rectangle dont la taille est définie par l'utilisateur avec des boucles while. Les bords sont en '*' et l'intérieur en '#'
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/
#include <stdio.h> //Bibliothèques classiques
#include <stdlib.h>

int main()
{
	int count,i=1,c;//Déclaration des variables utiles
	while(count<4){
		printf("Donner la taille du triangle valable ");//On fait en sorte que si l'utilisateur rentre une taille inacceptable, le programme lui redemande jusqu'à ce qu'elle le soit
		scanf("%d",&count);//Demande à l'utilisateur de la taille du triangle
	}
	printf("*\n");//Affichage du sommet
	while (i < count-1){
		printf("*");//Affichage des côtés gauche
		c=i;//ON met c=i pour définir le bon nombre de # à afficher selon le nombre d'itérations du premier while
		while (c!=1){
			printf("#");//Affichage de l'intérieur
			c--;
		}
		printf("*\n");//Affichage des côtés droits
		i++;
	}
	i=1;//On remet i à 1 pour refaire un while
	while (i!=count+1){
		printf("*");//Affichage du côté en bas du triangle
		i++;
	}
	printf("\n");//On fait ça pour que le programme soit esthétique et que le triangle soit bien affiché
	return 0;
}
