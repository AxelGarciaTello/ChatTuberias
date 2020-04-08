/*
	Para la implementación de una comunicación bidireccional haremos uso de
	dos tuberías, la primera enviara un mensaje del proceso padre al
	proceso hijo y la segunda del proceso hijo al proceso padre.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX 256

int main(void){
	int tuberia_em_re[2];
	int tuberia_re_em[2];
	int pid;
	char mensaje [MAX];

	/*Creación de las tuberías de comunicación*/
	if(pipe(tuberia_em_re) == -1 || pipe(tuberia_re_em) == -1){
		perror("pipe");
		exit(-1);
	}

	/*Creación del proceso hijo.*/
	if((pid=fork()) == -1){
		perror("fork");
		exit(-1);
	}
	else if (pid == 0){
		/*Código del proceso hijo.*/
		/*
			El proceso hijo (receptor) se encarga de leer un mensaje de la
			tubería y presentarlo en la pantalla, después envía un mensaje
			introducido, por medio del teclado, al proceso padre a través de la
			otra tubería.
			Al recibir el mensaje "Adiós\n", termina el proceso.
		*/
		while(read(tuberia_em_re[0], mensaje, MAX) > 0 &&
			strcmp(mensaje, "Adiós\n") != 0){
			printf("PROCESO HIJO. MENSAJE RECIBIDO: %s\n", mensaje);
			/*Se pide introducir el mensaje a enviar al proceso padre.*/
			printf("PROCESO HIJO. MENSAJE ENVIADO: ");
			fgets(mensaje, sizeof(mensaje), stdin);
			write(tuberia_re_em[1], mensaje, strlen(mensaje)+1);
		}
		/*Cierre de las tuberías y salida del programa*/
		close(tuberia_em_re[0]);
		close(tuberia_em_re[1]);
		close(tuberia_re_em[0]);
		close(tuberia_re_em[1]);
		exit(0);
	}
	else{
		/*Código del proceso padre.*/
		/*
			El proceso padre (emisor) se encarga de leer un mensaje introducido
			por medio del teclado y acto seguido escribirlo en la
			tubería, para que lo reciba el proceso hijo. Después Espera una
			respuesta por parte del proceso hijo por medio de la otra tubería.
			Al escribir el mensaje "Adiós\n" acaban los dos procesos.
		*/
		while(printf("PROCESO PADRE. MENSAJE ENVIADO: ") != 0 &&
			fgets(mensaje, sizeof(mensaje), stdin) != NULL &&
			write(tuberia_em_re[1], mensaje, strlen(mensaje)+1) > 0 &&
			strcmp(mensaje, "Adiós\n") != 0){
				/*Se lee el mensaje del proceso hijo y se imprime.*/
				read(tuberia_re_em[0], mensaje, MAX);
				printf("PROCESO PADRE. MENSAJE RECIBIDO: %s\n", mensaje);
		}
		/*Cierre de las tuberías y salida del programa.*/
		close(tuberia_em_re[0]);
		close(tuberia_em_re[1]);
		close(tuberia_re_em[0]);
		close(tuberia_re_em[1]);
		exit(0);
	}
}
