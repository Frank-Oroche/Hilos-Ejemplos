#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void imprimir( char *nombre ) {
  int i;
  for( i=0; i<100; i++ ){
    printf( "%s: %3i \n", nombre, i );
  }
  return;
}

void * hilo1( void *arg ) {
  imprimir( "Hilo1" );
  return NULL;
}

void * hilo2( void *arg ) {
  imprimir( "Hilo2" ); 
  return NULL;
}


int main(int argc, char *argv[] ) {

    pthread_t h1, h2;
    void *estado1, *estado2;

    printf( "Iniciando hilo principal\n" );
    pthread_create( &h1, NULL, hilo1, NULL );
    pthread_create( &h2, NULL, hilo2, NULL );
    imprimir( "PADRE" ); 
    pthread_join( h2, &estado2 );
    pthread_join( h1, &estado1 );
    printf( "Termine\n" );
}
