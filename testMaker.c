//programa gerador de testes
//compilar gcc testMaker.c -o testMaker
//rodar ./testMaker >test.txt

#include <stdio.h>
#include <time.h>

#define MAX 1000000

int main(){
	int i, x;

	printf("%d\n", 1);
	printf("%d\n",MAX );	
	for (i = MAX; i > 0; i--){
		printf("%d ", i);
	}
	printf("\n%d", 0);
}
