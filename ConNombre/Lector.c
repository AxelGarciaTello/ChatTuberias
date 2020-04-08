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

  tuberiaEscritor=fopen("escritor","r");
  tuberiaLector=fopen("lector","w");

  while (fgets(mensajeRecibido, TAM, tuberiaEscritor) > 0 &&
    strcmp(mensajeRecibido, "Adios\n") != 0){
    printf("Escritor: %s\n", mensajeRecibido);
    printf("Lector:");
    fgets(mensajeEnviado, TAM, stdin);
    fputs(mensajeEnviado, tuberiaLector);
    fclose(tuberiaLector);
    tuberiaLector=fopen("lector","w");
  }

  fclose(tuberiaEscritor);
  fclose(tuberiaLector);
}
