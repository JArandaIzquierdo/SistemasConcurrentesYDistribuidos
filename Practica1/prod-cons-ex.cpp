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
  int j = 0;
  sem_t consumir, producir, tex, turnos; // Declaracion de los semaforos

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

void * productor( void * arg)
{
  int l = (int) arg;
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int elemento = producir_dato();  // Producimos un nuevo dato
    sem_wait(&turnos[l]); // Semanforo para controlar a los productores
    sem_wait (&producir); // Semaforo del productor
    sem_wait (&tex);  // Ya que nos encontramos ante una seccion critica

    //------------------- Seccion critica ---------------------------
    cout << "Dato producido: " << elemento << endl;
    buffer[j] = elemento; // Escribe el dato en la posicion i del buffer
    j++;   // Incrementa la posicion del buffer
    // ------------------ Fin seccion critica ------------------------

    sem_post (&tex); // Decrementamos la seccion critica para que otro proceso pueda entrar
    sem_post (&consumir); // Decrementamos el consumidor
    sem_post (&turnos[(l+1)%2]);
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
      j--;
      elemento = buffer[j];
      //------------------- Fin seccion critica ------------------------

      sem_post (&tex);
      sem_post (&producir);



    consumir_dato (elemento) ;
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{
  // Creacion de la hebras
  pthread_t hebraConsumidor, prod1, prod2;

  // Inicializacion de los semaforos
  sem_init (&consumir,0,0); // Semaforo para el consumidor
  sem_init (&producir,0,num_items); // Semaforo para el productor
  sem_init (&tex,0,1); // Semaforo de exclusion mutua
  sem_init (&turnos[0],0,1); // Semaforo para sincronizacion de productores
  sem_init (&turnos[0],0,0); // Semaforo para sincronizacion de productores

  // Creacion de las hebras
  pthread_create (&hebraConsumidor,NULL, consumidor, NULL);

  // Creacion de hebras productoras
  for(int i=0; i<2; i++)
  {
    pthread_create(&prod[i],NULL, productor, (void*)i);
  }

  // Deja que las hebras terminen de ejecutarse
  pthread_join(hebraConsumidor,NULL);

  // Join de las hebras del productor
  for(int i=0; i<2; i++)
  {
    pthread_join(&prod[i],NULL);
  }

  int turno0, turno1;
  if(rand()%2==0)
    turno1==1;

  // Destruimos los semaforos
  sem_destroy(&consumir);
  sem_destroy(&producir);
  sem_destroy(&tex);
  sem_destroy(&turnos);

   return 0 ;
}
