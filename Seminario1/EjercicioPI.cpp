#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include "fun_tiempo.h"

using namespace std;
	
	const unsigned long m=10; //número de muestras
	const unsigned long n=5; // número de hebras
	double resultado_parcial[n]; //vector de resultados parciales

double f(double x)
{
	return 4.0/(1+x*x);
}

double calcular_integral_secuencial( )
{ 
	struct timespec inicio = ahora();
	double suma = 0.0 ; // inicializar suma
	for( unsigned long i = 0 ; i < m ; i++ ) // para cada i entre 0 y m− 1
		suma += f( ((i+0.5)/m )); //añadir f (xi ) a la suma actual
	struct timespec fin = ahora();
	cout << "Tiempo Secuencial: " << duracion( &inicio, &fin) << " seg." << endl;
	return suma/m ;	// devolver valor promedio de f
	
	
}

void * funcion_hebra( void *ih_void) //función que ejecuta cada hebra
{
	unsigned long ih = (unsigned long) ih_void; //índice de cada hebra
   	double sumap = 0.0;
	//cálculo de la suma parcial
	for(unsigned long i = ih; i < m; i+=n){
		sumap += f( ((i+0.5)/m));
	}
	resultado_parcial[ih] = sumap;
}

double calcular_integral_concurrente()
{
	struct timespec inicio = ahora();
	double Sum;
	//crear y lanzar n hebras, cada una ejecuta "funcion_concurrente"
	pthread_t id_hebra[n];
	for(unsigned i = 0; i < n; i++){
		pthread_create( &(id_hebra[i]),NULL,funcion_hebra,(void *) i);
	}
	//esperar (join) a que termine cada hebra, sumar su resultado
	for(unsigned i = 0; i < n; i++){
		unsigned long resultado;
		pthread_join(id_hebra[i], (void **) (&resultado));
		//devolver resultado completo
		Sum += resultado_parcial[i];		
	}
	struct timespec fin = ahora();
	cout << "Tiempo Concurrente " << duracion( &inicio, &fin) << " seg." << endl;
	return Sum/m;

}

int main(int argc, char* argv[]){


	cout << "Integral secuencial " << calcular_integral_secuencial() << endl;

	cout << "Integral concurrente " << calcular_integral_concurrente() << endl;
	

}
