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
  sem_t consumir, producir, mutex;

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
    int dato = producir_dato() ;

    // falta: insertar "dato" en el vector
    // ................

  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato ;

    // falta: leer "dato" desde el vector intermedio
    // .................

    consumir_dato( dato ) ;
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{
  pthread_t hebraConsumidor, hebraProductor;


   return 0 ;
}
