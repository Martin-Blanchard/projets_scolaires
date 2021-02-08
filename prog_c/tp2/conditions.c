/* Fichier conditions.c
*affiche 3 tableaux d'entiers inférieurs à 1000. Le premier regroupe ceux divisibles par 2 et 15. Le deuxième ceux divisibles par 103 ou 107. Le troisième ceux divisibles par 7 ou 15 mais pas 3.
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/

#include <stdio.h>
#include <stdlib.h>//On inclut les bibliothèques de base

int main()
{
	int nombres,tableau1[100],tableau2[100],tableau3[500],i1=0,i2=0,i3=0,division,i;//On déclare les tableaux et les indices qui vont les remplir, et aussi la variable qui contiendra l'information "Le nombre est-il dans le tableau i ou non ?".
	for (nombres=0;nombres<=1000;nombres++)//On parcourt les nombres de 1 à 1000.
	{
		division=(nombres%2)|(nombres%15);//On regarde si le nombre est divisible par 2 et 15.
		switch(division)
		{
			case 0:
				tableau1[i1]=nombres;//S'il est divisible par 2 et 15, on le met dans le tableau 1
				i1++;//Et on augmente l'indice du tableau pour copier le prochain nombre qui respecte les conditions dans la case d'après
				break;
				
		}
		division=(nombres%103)&&(nombres%107);//On regarde si le nombre est divisible par 103 ou 107.
		switch(division)
		{
			case 0:
				tableau2[i2]=nombres;//S'il est divisible par 103 ou 107, on le met dans le tableau 2
				i2++;//Et on augmente l'indice du tableau pour copier le prochain nombre qui respecte les conditions
				break;
		}
		division=(nombres%7)&&(nombres%5);//On regarde si le nombre est divisible par 7 ou 5.
		switch(division)
		{
			case 0:
				if (nombres%3!=0)//On regarde s'il n'est pas divisible par 3
				{
					tableau3[i3]=nombres;//Si les conditions sont respectées, on le met dans le tableau 3
					i3++;// Et on augmente l'indice pour copier le prochain nombre qui respecte les conditions
				}
				break;
		}
	}
	printf("Les nombres divisibles par 2 et 15 et inférieurs a 1000 sont : \n");
	for (i=0;i<i1;i++)
	{
		printf("%d\n",tableau1[i]);//Affichage du tableau 1
	}
	printf("Les nombres divisibles par 103 ou 107 et inférieurs a 1000 sont : \n");
	for (i=0;i<i2;i++)
	{
		printf("%d\n",tableau2[i]);//Affichage du tableau 2 
	}
	printf("Les nombres divisibles par 7 ou 5 mais pas 3 et inférieurs a 1000 sont : \n");
	for (i=0;i<i3;i++)
	{
		printf("%d\n",tableau3[i]);//Affichage du tableau 3
	}
	return 0;

}
