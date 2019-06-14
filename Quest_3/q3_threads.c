#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 100

// tentativa de implementação com duas funções estava dando Segmentation fault
/*int eh_primo(int n){
	int i;
	if(n == 1 || n == 0)
		return 0;
	for(i = 2; i < n; i++){
		if(n%i == 0)
			return 0;
	}
	return 1;
}*/
int count = 0;

void *print_primos(void *arg){
	int i, j, from, notPrimo;
	int *to;
	to = (int *)(arg);
	from = *to - 1000;
	for(i = from; i < *to; i++){
		notPrimo = 0;
		for(j = 2; j < (i/2); j++){
			if(i == 1 || i == 0)
				break;
			if(i%j == 0)
				notPrimo++;
				break;
		}
		if(notPrimo == 0){
			printf("thread %ld, valor: %d\n", *to/1000, i);
			
		}
	}

}

int main(){

	pthread_t threads[NUM_THREADS];

	int j;
	int to[NUM_THREADS]; //até onde quero que essa thread calcule
	int ini = 1000; //vai andar numa janela de 10000

	for(j=0; j<NUM_THREADS; j++){ //criando minhas 10 threads
		to[j] = ini; 
		pthread_create(&threads[j], NULL, print_primos, (void *)(&to[j]));
		ini = ini + 1000; //
	}
	for(j = 0; j < NUM_THREADS; j++){
		pthread_join(threads[j], NULL);
	}

	exit(0);
}

