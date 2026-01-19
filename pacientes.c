#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pacientes.h"
#include "validaciones.h"

datos_pacientes lista_pacientes[PACIENTES_MAXIMOS];
int cont_pacientes = 0;

void registrar_paciente() {
	FILE *datosguardados_pacientes;
	system("cls");
	
	if (cont_pacientes >= PACIENTES_MAXIMOS) {
		printf("Error: Memoria llena.\n");
		system("pause");
		return;
	}
	
	printf("\n--- REGISTRO DE PACIENTE %d ---\n", cont_pacientes + 1);
	

	do {
		printf("Ingrese su cedula: ");
		scanf("%s", lista_pacientes[cont_pacientes].cedula);

		while(getchar()!='\n');
		
		if (validar_formato_cedula(lista_pacientes[cont_pacientes].cedula) == 0){
			printf("Formato incorrecto.\n");
		}
	} while(validar_formato_cedula(lista_pacientes[cont_pacientes].cedula) == 0);
	
	if (Cedula_Existente(lista_pacientes[cont_pacientes].cedula) == 1){
		system("pause");
		return;
	}
	

	do {
		printf("Ingrese su nombre (sin espacios al inicio): ");
	
		scanf("%[^\n]", lista_pacientes[cont_pacientes].nombre);
		while(getchar()!='\n');
		
		if (validar_nombre(lista_pacientes[cont_pacientes].nombre) == 0){
			printf("Nombre invalido.\n");
		}
	} while(validar_nombre(lista_pacientes[cont_pacientes].nombre) == 0);
	
	do {
		printf("Ingrese su edad: ");
		if (scanf("%d", &lista_pacientes[cont_pacientes].edad) != 1) {
			while(getchar()!='\n');
			lista_pacientes[cont_pacientes].edad = -1;
		} else {
			while(getchar()!='\n');
		}
		if (validar_edad(lista_pacientes[cont_pacientes].edad) == 0) printf("Edad invalida.\n");
	} while(validar_edad(lista_pacientes[cont_pacientes].edad) == 0);

	printf("Ingrese su contrasena: ");
	scanf("%s", lista_pacientes[cont_pacientes].contrasena);
	while(getchar()!='\n');

	do {
		printf("Ingrese su correo: ");
		scanf("%s", lista_pacientes[cont_pacientes].correo);
		while(getchar()!='\n');
		if (validar_correo(lista_pacientes[cont_pacientes].correo) == 0) printf("Correo invalido.\n");
	} while(validar_correo(lista_pacientes[cont_pacientes].correo) == 0);

	do {
		printf("Ingrese su telefono: ");
		scanf("%s", lista_pacientes[cont_pacientes].telefono);
		while(getchar()!='\n');
		if (validar_telefono(lista_pacientes[cont_pacientes].telefono) == 0) printf("Telefono invalido.\n");
	} while(validar_telefono(lista_pacientes[cont_pacientes].telefono) == 0);

	datosguardados_pacientes = fopen("datos_guardados_usuarios.txt", "a");
	if (datosguardados_pacientes != NULL) {
		fprintf(datosguardados_pacientes, "%s %d %s %s %s %s\n",
				lista_pacientes[cont_pacientes].nombre,
				lista_pacientes[cont_pacientes].edad,
				lista_pacientes[cont_pacientes].cedula,
				lista_pacientes[cont_pacientes].contrasena,
				lista_pacientes[cont_pacientes].correo,
				lista_pacientes[cont_pacientes].telefono);
		fclose(datosguardados_pacientes);
		cont_pacientes++;
		printf("Paciente registrado exitosamente.\n");
	} else {
		printf("Error al guardar archivo.\n");
	}
	system("pause");
}

void cargarPacientes(){
	cont_pacientes = 0;
	FILE *f = fopen("datos_guardados_usuarios.txt", "r");
	if (f == NULL) return;
	
	while (fscanf(f, "%s %d %s %s %s %s", 
				  lista_pacientes[cont_pacientes].nombre,
				  &lista_pacientes[cont_pacientes].edad,
				  lista_pacientes[cont_pacientes].cedula,
				  lista_pacientes[cont_pacientes].contrasena,
				  lista_pacientes[cont_pacientes].correo,
				  lista_pacientes[cont_pacientes].telefono) == 6) {
		cont_pacientes++;
		if (cont_pacientes >= PACIENTES_MAXIMOS) break;
	}
	fclose(f);
}
	
	void listarPacientes(){
		system("cls");
		printf("\n--------- LISTA DE PACIENTES ---------\n");
		if (cont_pacientes == 0){
			printf("No hay pacientes registrados.\n");
			system("pause"); return;
		}
		printf("%-20s %-12s %-12s\n", "NOMBRE", "CEDULA", "TELEFONO");
		for (int i = 0; i < cont_pacientes; i++){
			printf("%-20s %-12s %-12s\n", 
				   lista_pacientes[i].nombre, lista_pacientes[i].cedula, lista_pacientes[i].telefono);
		}
		system("pause");
	}
