#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "medicos.h"
#include "validaciones.h" 

Datos_Medicos lista_medicos[MEDICOS_MAXIMOS];
int cont_medicos = 0;

void cargarMedicos() {
	cont_medicos = 0;
	FILE *archivo = fopen("datos_medicos.txt", "r");
	if (archivo == NULL) return;
	
	while (fscanf(archivo, "%d %s %s %s %s %s %d", 
				  &lista_medicos[cont_medicos].codigo,
				  lista_medicos[cont_medicos].cedula,
				  lista_medicos[cont_medicos].nombre,
				  lista_medicos[cont_medicos].especialidad,
				  lista_medicos[cont_medicos].horario,
				  lista_medicos[cont_medicos].contrasena, 
				  &lista_medicos[cont_medicos].disponible) == 7) { 
		cont_medicos++;
		if (cont_medicos >= MEDICOS_MAXIMOS) break;
	}
	fclose(archivo);
}

int existeMedico(int codigo) {
	for (int i = 0; i < cont_medicos; i++) {
		if (lista_medicos[i].codigo == codigo) return 1;
	}
	return 0;
}

void listarMedicos() {
	system("cls");
	printf("\n--- LISTA DE MEDICOS ---\n");
	if (cont_medicos == 0) {
		printf("No hay medicos.\n"); system("pause"); return;
	}
	printf("%-10s %-20s %-15s\n", "CODIGO", "NOMBRE", "HORARIO");
	for (int i = 0; i < cont_medicos; i++) {
		if (lista_medicos[i].disponible == 1) {
			printf("%-10d %-20s %-15s\n", 
				   lista_medicos[i].codigo, lista_medicos[i].nombre, lista_medicos[i].horario);
		}
	}
	system("pause");
}

void registrarMedico() {
	int opcion_horario, codigo_temp, validado = 0; 
	system("cls");
	if (cont_medicos >= MEDICOS_MAXIMOS) return;
	
	do {
		printf("\n--- ALTA MEDICO ---\nIngrese Codigo (6 digitos): ");
		if (scanf("%d", &codigo_temp) != 1) { while(getchar() != '\n'); codigo_temp = 0; }
		
		if (codigo_temp >= 100000 && codigo_temp <= 999999) {
			if (existeMedico(codigo_temp)) { printf("Codigo repetido.\n"); } 
			else { lista_medicos[cont_medicos].codigo = codigo_temp; validado = 1; }
		} else { printf("Debe ser de 6 digitos.\n"); }
	} while (validado == 0);
	
	validado = 0; 
	do {
		printf("Cedula: "); scanf("%s", lista_medicos[cont_medicos].cedula);
		if (validar_formato_cedula(lista_medicos[cont_medicos].cedula)) validado = 1;
		else printf("Cedula invalida.\n");
	} while(validado == 0);
	
	printf("Nombre: "); scanf("%s", lista_medicos[cont_medicos].nombre);
	printf("Especialidad: "); scanf("%s", lista_medicos[cont_medicos].especialidad);
	
	printf("Horario (1. 8-12, 2. 13-17, 3. 17-21): ");
	scanf("%d", &opcion_horario);
	if(opcion_horario==1) strcpy(lista_medicos[cont_medicos].horario, "08:00-12:00");
	else if(opcion_horario==2) strcpy(lista_medicos[cont_medicos].horario, "13:00-17:00");
	else strcpy(lista_medicos[cont_medicos].horario, "17:00-21:00");
	
	printf("Contrasena: "); scanf("%s", lista_medicos[cont_medicos].contrasena);
	lista_medicos[cont_medicos].disponible = 1; 
	
	FILE *f = fopen("datos_medicos.txt", "a");
	if (f) {
		fprintf(f, "%d %s %s %s %s %s %d\n", 
				lista_medicos[cont_medicos].codigo, lista_medicos[cont_medicos].cedula,
				lista_medicos[cont_medicos].nombre, lista_medicos[cont_medicos].especialidad,
				lista_medicos[cont_medicos].horario, lista_medicos[cont_medicos].contrasena, 
				lista_medicos[cont_medicos].disponible);
		fclose(f);
		cont_medicos++;
		printf("Medico registrado.\n");
	}
	system("pause");
}
