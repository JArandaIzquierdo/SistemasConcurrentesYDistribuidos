//Ejercicio Productor - Consumirdor
//Autor: Javier Aranda Izquierdo
#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>

using namespace std ;

// ---------------------------------------------------------------------
// constantes
const unsigned
  num_items  = 40 , // Numero de items a Consumirdor
  tam_vector = 10 ; // Tamaño del vector
  int buffer [tam_vector];  // Buffer
  sem_t consumir, producir, mutex; // Declaracion de los semaforos

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
    sem_wait (&mutex);  // Ya que nos encontramos ante una seccion critica

    //------------------- Seccion critica ---------------------------
    cout << "Dato producido: " << dato << endl;
    buffer[i] = dato; // Escribe el dato en la posicion i del buffer
    i++;   // Incrementa la posicion del buffer
    // ------------------ Fin seccion critica ------------------------
    sem_post (&mutex); // Decrementamos la seccion critica para que otro proceso pueda entrar
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
    while (true)
    {
      sem_wait(&consumidor);
      sem_wait (&mutex);
      i--;
    }



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
  sem_init (&consumidor,0,0);
  sem_init (&producutor,0,num_items);
  sem_init (&mutex,0,1);

  // Creacion de las hebras
  pthread_create (&hebraConsumidor,null, consumidor, (void *)50);
  pthread_create (&hebraProductor,null, producutor, 0;



   return 0 ;
}
