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

  /*Creación de las tuberías*/
  if(mkfifo("escritor", S_IWUSR | /*El usuario puede escribir*/
                        S_IRUSR | /*El usuario puede leer*/
                        S_IRGRP | /*El grupo puede leer*/
                        S_IROTH   /*Otros pueden leer*/
  )!=0){
    printf("Hubo un problema al crear la tubería del escritor.\n");
  }
  if(mkfifo("lector", S_IWUSR |
                      S_IRUSR |
                      S_IRGRP |
                      S_IROTH
  )!=0){
    printf("Hubo un problema al crear la tubería del lector.\n");
  }

  /*Abrimos las tuberías como si fueran un fichero*/
  tuberiaEscritor=fopen("escritor", "w");
  tuberiaLector=fopen("lector", "r");

  if(tuberiaEscritor==NULL || tuberiaLector==NULL){
    printf("No se pudo abrir las tuberías.\n");
    exit(0);
  }

  /*
    El proceso Escritor se encarga de leer un mensaje introducido
    por medio del teclado y acto seguido escribirlo en la
    tubería, para que lo reciba el proceso Lector. Después espera una
    respuesta por parte del proceso Lector por medio de la otra tubería.
    Al escribir el mensaje "Adiós\n" acaban los dos procesos.
  */
  while(printf("Escritor: ") != 0 &&
        fgets(mensajeEnviado, TAM, stdin) != NULL &&
        fputs(mensajeEnviado, tuberiaEscritor) > 0 &&
        strcmp(mensajeEnviado, "Adiós\n") !=0){
      /*
        Cerramos la tubería para indicar que terminamos de escribir y
        después la abrimos para volver a escribir en ella.
      */
      fclose(tuberiaEscritor);
      tuberiaEscritor=fopen("escritor", "w");
      /*
        Obtenemos el mensaje escrito por el proceso Lector y lo mostramos
        a pantalla.
      */
      fgets(mensajeRecibido, TAM, tuberiaLector);
      printf("Lector: %s\n", mensajeRecibido);
    }

  /*Cerramos la tuberías*/
  fclose(tuberiaEscritor);
  fclose(tuberiaLector);
}
