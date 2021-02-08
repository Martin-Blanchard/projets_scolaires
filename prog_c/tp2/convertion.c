/* Fichier convertion.c
*convertit un entier donné par l'utilisateur en binaire
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/

#include <stdio.h>
#include <stdlib.h>//Bibliothèques de base

int main()
{
	int a,r,i=15,tableau[15];//Initialisation des variables de base et du tableau qui contiendra l'entier binaire
	printf("Donnez un entier à convertir en binaire ");
	scanf("%d",&a);//Récupération du nombre entré par l'utilisateur
	printf("\n");
	while (i!=-1)
	{
		r=a%2;
		a=a/2;
		tableau[i]=r;
		i--;
	}
	for (i=0;i!=16;i++)
	{
		printf("%d",tableau[i]);
	}
	printf("\n");
	return 0;
}
