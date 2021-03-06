#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define TAMANIO 100000000     //1000000 o 100000000
#define ini 1                 //inicio del rango de numero aleatorios
#define fin 20                //final del rango de numero aleatorios
#define n_hilos 2             //numero de hilos (no incluye al hilo principal)

int aiVector[TAMANIO] ;
long Suma = 0 ;

struct Dato {
	int a, b ;
	char mensaje[20];
};

void llenar(int iTamanio, int aiVector[]) ;
void mostrarVector(int iTamanio, int aiVector[]) ;
long suma(int aiVector[], struct Dato dato) ;
void *hilo1( void *arg ) ;
void *hilo2( void *arg ) ;

int main(int argc, char *argv[] ) {

	long iSuma = 0;
	int numero ;
	struct timespec inicio, final ;
	struct Dato dato,aux ;

	pthread_t h1, h2 ;

    void *estado1, *estado2 ;

	llenar(TAMANIO,aiVector) ;

	printf("Vector generado con numeros aleatorios entre [ %i - %i ] con tamanio: %i\n",ini, fin,TAMANIO) ;
	//mostrarVector(TAMANIO,aiVector);	//Descomentar si el numero de elementos es peque�o
	printf("Menores por intervalo [a,b]\n") ;

	printf("\tIngrese a: ") ;
	scanf("%d", &dato.a) ;
	aux.a = dato.a ;

	if(dato.a < 1 || dato.a > TAMANIO) {
		printf("\n\tERROR...\n") ;

		exit(1) ;
	}

	printf("\tIngrese b: ") ;
	scanf("%d",&dato.b) ;
	aux.b = dato.b ;

	if(dato.b < dato.a || dato.b > TAMANIO) {
		printf("\n\tERROR...\n") ;

		exit(1) ;
	}

	printf("\n\n------------------------------------------------------------------------------------\n");
	printf("   Sin Hilos\n") ;

	clock_gettime(CLOCK_REALTIME,&inicio) ;
	strcpy( dato.mensaje, "Rango" );
    iSuma = suma(aiVector,dato) ;
    clock_gettime(CLOCK_REALTIME,&final) ;

    printf("\n\tLa Suma en el intervalo [ %i - %i ] es: %i\n",dato.a,dato.b, iSuma) ;
	printf("\t demora: %f milisegundos\n",(float) ( 1000.0*(1.0*final.tv_nsec - inicio.tv_nsec*1.0)*1e-9+ 1.0*final.tv_sec - 1.0*inicio.tv_sec ) ) ;

	printf("------------------------------------------------------------------------------------\n") ;
	printf("   Con Hilos\n") ;

	numero = (dato.b - dato.a + 1)/(n_hilos + 1) ;
	printf("\tEl Incremento es: %i\n", numero) ;

	clock_gettime(CLOCK_REALTIME,&inicio) ;

	//actualizar
	aux.a = dato.a ;
	aux.b = dato.a + numero - 1 ;
	strcpy( aux.mensaje, "Hilo Principal:" );
    Suma = Suma + suma(aiVector,aux) ;

    pthread_create( &h1, NULL, hilo1, &dato) ;
    pthread_create( &h2, NULL, hilo2, &dato) ;
    //unir hilos
    pthread_join( h1, &estado1 ) ;
    pthread_join( h2, &estado2 ) ;

    clock_gettime(CLOCK_REALTIME,&final) ;

    printf( "\tTermine\n" ) ;

	printf("\n\tLa Suma en el intervalo [ %i - %i ] es: %i\n",dato.a,dato.b, Suma) ;
	printf("\t demora: %f milisegundos\n",(float) ( 1000.0*(1.0*final.tv_nsec - inicio.tv_nsec*1.0)*1e-9+ 1.0*final.tv_sec - 1.0*inicio.tv_sec ) ) ;
	printf("------------------------------------------------------------------------------------\n") ;

	return 0 ;
}

void llenar(int iTamanio, int aiVector[]){

	int i ;
	srand((time)NULL) ;
	printf("\tGenerando Vector con tamanio: %i\n",iTamanio) ;
	for(i = 0 ; i < iTamanio ; i++){
		aiVector[i] = rand()%fin + ini ;
	}
}

void mostrarVector(int iTamanio, int aiVector[]){

	int i ;
	for(i = 0 ; i < TAMANIO ; i++){
		printf("Vector[%i] = %i\n",(i+1),aiVector[i]) ;
	}
}

long suma(int aiVector[], struct Dato dato){

	int i, suma = 0 ;
	for(i = dato.a - 1; i < dato.b ; i++){
		suma = suma + aiVector[i];
	}
	printf("  %s  [ %i - %i ] | suma: %i\n",&dato.mensaje,dato.a,dato.b,suma);

	return suma;
}

void *hilo1( void *arg ) {

	int numero,a ;
	struct Dato dato_aux = *(struct Dato *)arg ;
	numero =(dato_aux.b - dato_aux.a + 1)/3 ;
	a = dato_aux.a;
	//actualizar
	dato_aux.a = a + numero ;
	dato_aux.b = a + 2 * numero - 1 ;
	strcpy( dato_aux.mensaje, "Hilo 1:" );
	Suma = Suma + suma(aiVector,dato_aux) ;

	return NULL ;
}

void *hilo2( void *arg ) {

	int numero,a ;
	struct Dato dato_aux = *(struct Dato *)arg ;
	numero =(dato_aux.b - dato_aux.a + 1)/3 ;
	//actualizar
	a = dato_aux.a ;
	dato_aux.a = a + 2 * numero ;
	strcpy( dato_aux.mensaje, "Hilo 2:" );
	Suma = Suma + suma(aiVector,dato_aux) ;

	return NULL ;
}
