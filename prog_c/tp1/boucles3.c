/* Fichier boucles2.c
*affiche un triangle rectangle dont la taille est définie par l'utilisateur avec des do... while. Les bords sont en '*' et l'intérieur en '#'
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/
#include <stdio.h> //Bibliothèques classiques
#include <stdlib.h>

int main()
{
	int count,i=1,c;//Déclaration des variables utiles
	while(count<4){//On fait en sorte que si l'utilisateur rentre une taille inacceptable, le programme lui redemande jusqu'à ce qu'elle le soit
		printf("Donner la taille du triangle valable ");
		scanf("%d",&count);//Demande à l'utilisateur de la taille du triangle
	}
	printf("*\n");//Affichage du sommet
	printf("**\n");//Affichage du segment suivant
	do{
		printf("*");//Affichage des côtés gauche
		c=i;//ON met c=i pour définir le bon nombre de # à afficher selon le nombre d'itérations du premier do..While
		do{
			printf("#");//Affichage de l'intérieur
			c--;
		}while (c!=0);
		printf("*\n");//Affichage des côtés droits
		i++;
	}while (i < count-2);
	i=1;//On remet i à 1 pour refaire un while
	do{
		printf("*");//Affichage du côté en bas du triangle
		i++;
	}while (i!=count+1);
	printf("\n");//On fait ça pour que le programme soit esthétique et que le triangle soit bien affiché
	return 0;
}//Nous avons dans ce cas dû ajuster les conditions des do...while car la première itération ne tient pas compte de la condition et s'effectue quoi qu'il arrive
