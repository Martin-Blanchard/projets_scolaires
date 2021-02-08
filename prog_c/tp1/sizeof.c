/* Fichier sizeof.c
*affiche la taille en octet de chaque type de variable
*auteurs : Simon LENORAIS, Martin BLANCHARD
*/
#include <stdio.h> //Bibliothèques classiques
#include <stdlib.h>


int main()
{
	int a,b,c,d,e,f,g,h,i,j,k,l,m;//Déclaration de toutes les variables
	a=sizeof(char);//Récupération de la taille en octets
	printf("taille char = %i\n",a); //Affichage de cette taille
	j=sizeof(unsigned char);//On réitère cela pour tous les types
	printf("taille unsigned char = %i\n",j);
	b=sizeof(short);
	printf("taille short = %i\n",b);
	k=sizeof(unsigned short);
	printf("taille unsigned short = %i\n",k);
	c=sizeof(int);
	printf("taille int = %i\n",c);
	l=sizeof(unsigned int);
	printf("taille unsigned int = %i\n",l);
	d=sizeof(long int);
	printf("taille long int = %i\n",d);
	e=sizeof(long long int);
	printf("taille long long int = %i\n",e);
	f=sizeof(float);
	printf("taille float = %i\n",f);
	g=sizeof(double);
	printf("taille double = %i\n",g);
	h=sizeof(long double);
	printf("taille long double = %i\n",h);
	i=sizeof(unsigned long);
	printf("taille unsigned long = %i\n",i);
	m=sizeof(unsigned long long);
	printf("taille unsigned long long = %i\n",m);
	return 0;
}
