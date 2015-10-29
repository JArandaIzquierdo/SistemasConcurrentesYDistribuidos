//Ejercicio Productor - Consumirdor
//Autor: Javier Aranda Izquierdo
#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>

#include <iomanip>
#include <cstdlib>

using namespace std ;

// ---------------------------------------------------------------------
// constantes
const unsigned
  num_items  = 40 , // Numero de items a Consumirdor
  tam_vector = 10 ; // Tamaño del vector
  int buffer [tam_vector];  // Buffer
  int indice = 0;
  sem_t consumir, producir, tex; // Declaracion de los semaforos

// ---------------------------------------------------------------------

// Funcion para profucir datos

unsigned producir_dato()
{
  static int contador = 0 ;
  cout << "Producido: " << contador << endl << flush ;
  return contador++ ;
}
// ---------------------------------------------------------------------

// Funcion para consumir datos

void consumir_dato( int dato )
{
    cout << "Dato recibido: " << dato << endl ;
}
// ---------------------------------------------------------------------

void * productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato = producir_dato();  // Producimos un nuevo dato
    sem_wait (&producir); // Semaforo del productor
    sem_wait (&tex);  // Ya que nos encontramos ante una seccion critica

    //------------------- Seccion critica ---------------------------
    cout << "Dato producido: " << dato << endl;
    buffer[i] = dato; // Escribe el dato en la posicion i del buffer
    i++;   // Incrementa la posicion del buffer
    // ------------------ Fin seccion critica ------------------------
    sem_post (&tex); // Decrementamos la seccion critica para que otro proceso pueda entrar
    sem_post (&consumir); // Decrementamos el consumidor
  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++)
  {
      int elemento;

      sem_wait(&consumir);
      sem_wait (&tex);
      //------------------- Seccion critica ----------------------------
      i--;
      elemento - buffer[indice];
      //------------------- Fin seccion critica ------------------------
      sem_post (&tex);
      sem_post (&producir);



    consumir_dato (dato) ;
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{
  // Creacion de la hebras
  pthread_t hebraConsumidor, hebraProductor;

  // Inicializacion de los semaforos
  sem_init (&consumidor,0,0); // Semaforo para el consumidor
  sem_init (&producutor,0,num_items); // Semaforo para el productor
  sem_init (&tex,0,1); // Semaforo de exclusion mutua

  // Creacion de las hebras
  pthread_create (&hebraConsumidor,NULL, consumidor, NULL;
  pthread_create (&hebraProductor,NULL, producutor, NULL;

  // Deja que las hebras terminen de ejecutarse
  pthread_join(hebraProductor,NULL);
  pthread_join(hebraConsumidor,NULL);

  // Destruimos los semaforos
  sem_destroy(&consumir);
  sem_destroy(&profucir);
  sem_destroy(&tex);

   return 0 ;
}
