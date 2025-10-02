// que imprime este codigo

#include<stdio.h>
int main(){
	int *puntero, i;
	int x[5]= {1,2,3,4,5};
	puntero =x;
	*puntero = 9;
	printf("lo que imprime es: ");
	for(i=0; i<5; i++)
	{
		
		printf("%d, ", x[i]);
	}
	return 0;
}