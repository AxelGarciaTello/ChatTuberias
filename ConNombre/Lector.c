/*
	Para la implementación de una comunicación bidireccional haremos uso de
	dos tuberías, la primera enviara un mensaje del proceso Escritor al
	proceso Lector y la segunda del proceso Lector al proceso Escritor.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define TAM 256

int main(void){
  FILE *tuberiaEscritor;
  FILE *tuberiaLector;
  char mensajeEnviado[TAM];
  char mensajeRecibido[TAM];

  /*Abrimos las tuberías como si fueran un fichero*/
  tuberiaEscritor=fopen("escritor", "r");
  tuberiaLector=fopen("lector", "w");

  if(tuberiaEscritor==NULL || tuberiaLector==NULL){
      printf("No se pudo abrir las tuberías.\n");
      exit(0);
  }

  /*
    El proceso Lector se encarga de leer un mensaje de la
    tubería y presentarlo en la pantalla, después envía un mensaje
    introducido, por medio del teclado, al proceso Escritor a través de
    la otra tubería.
    Al recibir el mensaje "Adiós\n", termina el proceso.
  */
  while(fgets(mensajeRecibido, TAM, tuberiaEscritor) > 0 &&
         strcmp(mensajeRecibido, "Adiós\n") != 0){
    /*
      Obtenemos el mensaje escrito por el proceso Escritor y lo mostramos
      a pantalla.
    */
    printf("Escritor: %s\n", mensajeRecibido);
    printf("Lector:");
    /*Enviamos el mensaje ingresado por el teclado al Escritor*/
    fgets(mensajeEnviado, TAM, stdin);
    fputs(mensajeEnviado, tuberiaLector);
    /*
      Cerramos la tubería para indicar que terminamos de escribir y
      después la abrimos para volver a escribir en ella.
    */
    fclose(tuberiaLector);
    tuberiaLector=fopen("lector", "w");
  }

  /*Cerramos la tuberías*/
  fclose(tuberiaEscritor);
  fclose(tuberiaLector);
}
