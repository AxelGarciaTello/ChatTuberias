#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define TAM 256

int main(void){
  FILE *tuberiaEscritor;
  FILE *tuberiaLector;
  char mensajeEnviado[TAM];
  char mensajeRecibido[TAM];

  /*Creación de la tubería*/
  if(mkfifo("escritor", S_IWUSR |
                        S_IRUSR |
                        S_IRGRP |
                        S_IROTH
  )!=0){
    printf("Hubo un problema al crear la tuberia del escritor.\n");
  }
  if(mkfifo("lector", S_IWUSR |
                      S_IRUSR |
                      S_IRGRP |
                      S_IROTH
  )!=0){
    printf("Hubo un problema al crear la tuberia del lector.\n");
  }

  tuberiaEscritor=fopen("escritor","w");
  tuberiaLector=fopen("lector","r");

  while(printf("Escritor: ") != 0 &&
    fgets(mensajeEnviado,TAM, stdin) != NULL &&
    fputs(mensajeEnviado, tuberiaEscritor) > 0 &&
    strcmp(mensajeEnviado, "Adios\n") !=0){
      fclose(tuberiaEscritor);
      tuberiaEscritor=fopen("escritor","w");
      fgets(mensajeRecibido, TAM, tuberiaLector);
      printf("Lector: %s\n", mensajeRecibido);
    }

  fclose(tuberiaEscritor);
  fclose(tuberiaLector);
}
