/*
 ============================================================================
 Name        : PracticaSoHilos.c
 Author      : Diego fernando Ruiz
 Version     :
 Copyright   : Your copyright notice
 Description : Creaci—n de Hilos in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



void *creacionHilos(void*);

int main(int argc, char *argv[]) {
	if(argc != 2){
		printf("Parametros incorrectos\n");
		return EXIT_FAILURE;
	}
	int i;
	int hilos = atoi(argv[1]);
	if(hilos < 1){
		printf("Debes ingresar un numero de hilos mayor o igual a 1\n");
		return EXIT_SUCCESS;
	}
	pthread_t tids[hilos];
	if(hilos == 1){
		pthread_create(&tids[0], NULL, creacionHilos, NULL);
		pthread_join(tids[0], NULL);
	}else {
		//Aca se crea todos los hilos y se les pone el trabajo
		for(i=0; i<hilos; i++){
			pthread_create(&tids[0], NULL, creacionHilos, NULL);
		}
		//Aca se recolectan los trabajos de los hilos.
		for(i=0; i<hilos; i++){
			pthread_join(tids[i], NULL);
		}
	}
	return EXIT_SUCCESS;
}

void *creacionHilos(void* null){
	pthread_t thread_id = pthread_self();
	printf("hola %d \n", (int) (thread_id));
	pthread_exit(NULL);
}
