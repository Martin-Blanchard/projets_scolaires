/* Fichier operators.c
*affiche les résultats de tous les opérateurs arithmétiques et logiques sur a et b
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/
#include <stdio.h> //Bibliothèques classiques
#include <stdlib.h>

int main()
{
	int a=16,b=3;//Déclaration de a et b
	printf("a+b = %i\n",a+b);
	printf("a-b = %i\n",a-b);
	printf("a*b = %i\n",a*b);
	printf("a/b = %i\n",a/b);
	printf("reste de a par b = %i\n",a%b);
	printf("NON a = %i\n",!a);
	printf("NON b = %i\n",!b);
	printf("a ET b = %i\n",a&&b);
	printf("a OU b = %i\n",a||b);//Affichage du résultat de chaque opération
	return 0;
}
	
	
