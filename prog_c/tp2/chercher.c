/* Fichier chercher.c
*crée deux tableaux de phrases et recherche une phrase donnée à l'intérieur et dit s'il elle l'est ou non.
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>//Inclure la bibliothèque string en vue d'utiliser la fonction strcasecmp

int main()
{
	char phrases[10][50]={"Bravo Niels","Je pirate CPE","Monsieur Doeuf a un fils : John Doeuf","Antho boit un Orangina","Simon aime Caen","Martin est un dieu","Samy joue aux jeux-videos","Gh fait du skate","Daniel fait un marathon","Le programme est compile"}; //On construit notre tableau de 10 phrases
	char phrase_recherche1[50]={"gh fait du skate"};//On entre la phrase recherchée. Modifiez cette variable pour tester.
	int i=0,verif=0;//On initialise le i du for et la variable de vérification pour afficher le bon message final
	for (i=0;i<10;i++)
	{
		if(strcasecmp(phrases[i],phrase_recherche1)==0)//On compare la chaîne recherchée avec toutes les chaînes du tableau. Si elle est bonne,...
		{
			printf("La phrase : \n%s\nest contenue dans le tableau de phrases à la %d-ème place\n",phrase_recherche1,i-1); //.. on affiche un message avec la phrase et sa place. Sinon...
			verif=1;
		}
	}
	if(verif==0)
	{
		printf("La phrase : \n%s\nn'est pas contenue dans le tableau de phrases. Dommage.\n",phrase_recherche1);//...On affiche un message qui dit qu'on ne l'a pas trouvé
	}
	return 0;
}
