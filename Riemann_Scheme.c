/**
* FILE: riemann_corregido.c
* DESCRIPTION:
* 	Implementacion de la suma de Riemann para calcular el area bajo la
*	curva.
* AUTHOR: John Sanabria - john.sanabria@correounivalle.edu.co
* LAST REVISED: 14/04/16
* REFERENCES: http://mathinsight.org/calculating_area_under_curve_riemann_sums
* EDIT: Diego Fernando Ruiz
******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE; // La longitud en el eje 'x'
double numRectxThread = (double)(MAXRECT/MAXTHREAD); // Cuantos rectangulos/hilo
double base_length = 0; // Variable que tiene el ancho de cada rectangulo
double sumTotal = 0; // Variable que tendra la suma total
double partialSums[MAXTHREAD]; // Variable que tien la suma parcial de c/hilo

// Funcion a la que se le calculara la integral, x^2
double function(double x){
	return x * x;
}
// Funcion que calcula el area bajo la curva de un segmento de la curva asignada a un hilo especifico.
void* calcular(void *arg) {
	/* Se recurepa el valor pasado en el parametro a la hora de crear el hilo,
	 * este valor corresponde al numero de lote que le corresponde trabajar a este hilo
	 */
	int id;
	double i;
	id=*(int*)arg;

	/*
	 * Se identifica el donde inicia y donde finaliza el segmento de trabajo para este hilo
	 */
	double loslimit = (double)id/MAXTHREAD; //Limite de inicio en x para este hilo.
	double loslimitUp = (double)(id+1)/MAXTHREAD; //Limite de fin en x para este hilo

	/* Se inicia la posicion de este arreglo que va a contener la suma de todas las areas de
	 * cada rectangulo que hay en el intervalo que le corresponde a este hilo
	 */
	partialSums[id] = 0;

	/* Ciclo para recorrer la porci—n de x correspondiente a este entero
	 * se toma id*numRectxThread para iniciar el iterador y
	 * (id+1)*numRectxThread para finalizar el ciclo.
	 * Con posX = i/MAXRECT se saca el valor de x que se va a evaluar en la funcion
	 * Finalmente, con function(posX) * base_length se haya el area de cada rectangulo y se agrega
	 * posicion del arreglo correspondiente a este hilo
	 */
	for(i=id*numRectxThread; i<=(id+1)*numRectxThread; i++){
		double posX = i/MAXRECT;
		partialSums[id] += function(posX) * base_length;
	}

	printf("El segmento de x para el hilo %d es: [%lf, %lf] y sum: %lf\n", id, loslimit, loslimitUp, partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	/* el arreglo tids almacena el id de cada hilo.
	 * el arreglo taskids almacena el numero de lote de x en el cual le correspondetrabajar al cada hilo creado
	 */
	pthread_t tids[MAXTHREAD];
	int taskids[MAXTHREAD];
	base_length = length/MAXRECT; // esta variable contiene el ancho de cada base de cada rectangulo
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);

	// Creacion de los hilos que calcularan el area bajo la curva
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
		pthread_create(&tids[i], NULL, calcular, &taskids[i]);

	}
	// Ciclo donde se espera el resultado de cada hilo
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(tids[i], NULL);
		sumTotal += partialSums[i];
	}
	printf("Suma total %lf\n",sumTotal);
	pthread_exit(NULL);
}
