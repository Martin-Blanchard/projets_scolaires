/* Fichier circle.c
*affiche l'aire et le périmètre d'un cercle dont le rayon est défini par l'utilisateur
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/
#include <stdio.h> //Bibliothèques classiques
#include <stdlib.h>

int main()
{
	float Rayon,Aire,Perimetre;//Déclaration des variables utiles
	printf("Rentrez le rayon\n");
	scanf("%f",&Rayon);//Demande d'information de la part de l'utilisateur (rayon du cercle)
	Aire=3.141592614*Rayon*Rayon;//Calcul de l'aire
	Perimetre=2*3.141592614*Rayon;//Calcul du périmètre
	printf("Aire = %f\n",Aire);
	printf("Perimetre = %f\n",Perimetre);//Affichage des résultats
	return 0;
}

