#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citas.h"
#include "medicos.h"
#include "pacientes.h"
#include "validaciones.h"

int estaDentroDeHorario(char *horarioMedico, char *horaCita) {
	int hInicio, hFin, hCita, mCita;
	sscanf(horarioMedico, "%d:%*d-%d:%*d", &hInicio, &hFin);
	sscanf(horaCita, "%d:%d", &hCita, &mCita);
	
	if (hCita >= hInicio && hCita < hFin) {
		return 1;
	}
	return 0;
}


int generarNuevoIdCita() {
	FILE *archivo = fopen("citas.txt", "r");
	int maxId = 1000; 
	int idActual;
	char tempCed[20], tempFecha[15], tempHora[10], tempEst[20], tempObs[100];
	int tempCod;
	
	if (archivo == NULL) return 1001; 
	
	while(fscanf(archivo, "%d %s %d %s %s %s %s", 
				 &idActual, tempCed, &tempCod, 
				 tempFecha, tempHora, tempEst, tempObs) == 7) {
		if (idActual > maxId) {
			maxId = idActual;
		}
	}
	fclose(archivo);
	return maxId + 1;
}

int verificarDisponibilidadMedico(int codigoMedico, char fecha[], char hora[]) {
	FILE *archivo = fopen("citas.txt", "r");
	if (archivo == NULL) return 1; 
	Cita c;
	while(fscanf(archivo, "%d %s %d %s %s %s %s", &c.idCita, c.cedulaPaciente, &c.codigoMedico, c.fecha, c.hora, c.estado, c.observaciones) == 7) {
		if (c.codigoMedico == codigoMedico && strcmp(c.fecha, fecha) == 0 && strcmp(c.hora, hora) == 0) {
			if(strcmp(c.estado, "Cancelada") != 0) {
				fclose(archivo); return 0; // Ocupado
			}
		}
	}
	fclose(archivo); return 1; // Libre
}

void cancelarCita(int idCita) {
	FILE *archivo = fopen("citas.txt", "r");
	FILE *temporal = fopen("temp_citas.txt", "w");
	Cita c;
	int encontrado = 0;
	
	if (!archivo || !temporal) {
		printf("Error al abrir archivos de citas.\n");
		return;
	}
	
	while(fscanf(archivo, "%d %s %d %s %s %s %s", 
				 &c.idCita, c.cedulaPaciente, &c.codigoMedico, 
				 c.fecha, c.hora, c.estado, c.observaciones) == 7) {
		
		if (c.idCita == idCita) {
			if(strcmp(c.estado, "Asignada") == 0) {
				strcpy(c.estado, "Cancelada");
				encontrado = 1;
				printf("Cita ID %d ha sido CANCELADA.\n", idCita);
			} else {
				printf("No se puede cancelar. Estado actual: %s\n", c.estado);
			}
		}
		fprintf(temporal, "%d %s %d %s %s %s %s\n", 
				c.idCita, c.cedulaPaciente, c.codigoMedico, 
				c.fecha, c.hora, c.estado, c.observaciones);
	}
	fclose(archivo);
	fclose(temporal);
	
	if (encontrado) {
		remove("citas.txt");
		rename("temp_citas.txt", "citas.txt");
	} else {
		remove("temp_citas.txt");
		if (!encontrado) printf("ID no encontrado o no cancelable.\n");
		system("pause");
	}
	if (encontrado) system("pause");
}

void agendarCitaPaciente(char *cedulaPaciente) {
	Cita nuevaCita;
	int codigoMedicoDeseado, encontrado = 0;
	char horarioMedicoSel[50];
	int fechaValida = 0, horaValida = 0;
	
	system("cls");
	printf("\n--- AGENDAR CITA ---\n");
	if (cont_medicos == 0) { printf("No hay medicos.\n"); system("pause"); return; }
	
	printf("Medicos Disponibles:\n");
	for(int i=0; i<cont_medicos; i++) {
		if(lista_medicos[i].disponible == 1) 
			printf("%d - Dr. %s (%s)\n", lista_medicos[i].codigo, lista_medicos[i].nombre, lista_medicos[i].horario);
	}
	
	// Bucle para seleccionar Médico válido
	do {
		printf("\nCodigo del medico: "); 
		if(scanf("%d", &codigoMedicoDeseado) != 1) { while(getchar()!='\n'); }
		
		encontrado = 0;
		for(int i=0; i<cont_medicos; i++) { 
			if(lista_medicos[i].codigo == codigoMedicoDeseado) {
				encontrado = 1;
				strcpy(horarioMedicoSel, lista_medicos[i].horario);
			}
		}
		if(!encontrado) printf("Codigo invalido. Intente nuevamente.\n");
	} while(!encontrado);
	
	nuevaCita.codigoMedico = codigoMedicoDeseado;
	strcpy(nuevaCita.cedulaPaciente, cedulaPaciente); 
	
	do {
		printf("Fecha (DD/MM/AAAA): ");
		scanf("%s", nuevaCita.fecha);
		
		if (esFechaHoraValida(nuevaCita.fecha, "00:00") == 0) {
			printf("Formato de fecha invalido. Intente nuevamente.\n");
		} else if (esFechaFutura(nuevaCita.fecha) == 0) {
			printf("Error: La fecha ya paso. Ingrese una fecha futura.\n");
		} else {
			fechaValida = 1; 
		}
	} while(!fechaValida);
	
	do {
		printf("Hora (HH:MM): ");
		scanf("%s", nuevaCita.hora);
		
		// 1. Validar formato básico
		if (esFechaHoraValida(nuevaCita.fecha, nuevaCita.hora) == 0) {
			printf(">> Formato de hora incorrecto. Use HH:MM.\n");
			continue;
		}
		
		// 2. Validar rango del médico
		if (estaDentroDeHorario(horarioMedicoSel, nuevaCita.hora) == 0) {
			printf(">> Fuera de horario. El medico atiende: %s. Intente otra hora.\n", horarioMedicoSel);
			continue;
		}
		
		// 3. Validar disponibilidad 
		if (verificarDisponibilidadMedico(nuevaCita.codigoMedico, nuevaCita.fecha, nuevaCita.hora) == 0) {
			printf(">> HORARIO OCUPADO. El medico ya tiene una cita a las %s. Elija otra hora.\n", nuevaCita.hora);
			continue;
		}
		
		horaValida = 1; 
	} while(!horaValida);
	
	strcpy(nuevaCita.estado, "Asignada");
	strcpy(nuevaCita.observaciones, "Ninguna"); 
	nuevaCita.idCita = generarNuevoIdCita();
	
	FILE *archivo = fopen("citas.txt", "a");
	if (archivo) {
		fprintf(archivo, "%d %s %d %s %s %s %s\n", 
				nuevaCita.idCita, nuevaCita.cedulaPaciente, nuevaCita.codigoMedico, 
				nuevaCita.fecha, nuevaCita.hora, nuevaCita.estado, nuevaCita.observaciones);
		fclose(archivo);
		printf("\n==================================\n");
		printf(" EXITO: Cita agendada.\n");
		printf(" ID de Cita: %d\n", nuevaCita.idCita);
		printf(" Fecha: %s  Hora: %s\n", nuevaCita.fecha, nuevaCita.hora);
		printf("==================================\n");
	} else {
		printf("Error al guardar la cita.\n");
	}
	system("pause");
}

void verMisCitasPaciente(char *cedulaPaciente) {
	FILE *archivo = fopen("citas.txt", "r");
	Cita c;
	int encontradas = 0;
	
	system("cls"); printf("--- MIS CITAS ---\n");
	if (archivo == NULL) { printf("Sin citas.\n"); system("pause"); return; }
	
	printf("ID     FECHA       HORA    ESTADO       OBSERVACIONES\n");
	while(fscanf(archivo, "%d %s %d %s %s %s %s", &c.idCita, c.cedulaPaciente, &c.codigoMedico, c.fecha, c.hora, c.estado, c.observaciones) == 7) {
		if (strcmp(c.cedulaPaciente, cedulaPaciente) == 0) {
			printf("%d  %s  %s  %s  %s\n", c.idCita, c.fecha, c.hora, c.estado, c.observaciones);
			encontradas++;
		}
	}
	if(encontradas == 0) printf("No tienes citas.\n");
	fclose(archivo); system("pause");
}

void atenderCitaMedico(int idCitaAEditar) {
	FILE *archivo = fopen("citas.txt", "r");
	FILE *temporal = fopen("temp.txt", "w");
	Cita c;
	int encontrado = 0;
	
	if (!archivo || !temporal) return;
	
	while(fscanf(archivo, "%d %s %d %s %s %s %s", 
				 &c.idCita, c.cedulaPaciente, &c.codigoMedico, c.fecha, c.hora, c.estado, c.observaciones) == 7) {
		if (c.idCita == idCitaAEditar) {
			encontrado = 1;
			printf(">> Ingrese observaciones (Use_guiones_bajos): ");
			scanf("%s", c.observaciones);
			strcpy(c.estado, "Atendida");
			printf("Cita actualizada.\n");
		}
		fprintf(temporal, "%d %s %d %s %s %s %s\n", 
				c.idCita, c.cedulaPaciente, c.codigoMedico, c.fecha, c.hora, c.estado, c.observaciones);
	}
	fclose(archivo); fclose(temporal);
	if (encontrado) { remove("citas.txt"); rename("temp.txt", "citas.txt"); } 
	else remove("temp.txt");
}

void verAgendaMedico(char *codigoMedicoStr) {
	FILE *archivo = fopen("citas.txt", "r");
	Cita c;
	int codigoMed = atoi(codigoMedicoStr), encontradas = 0;
	char nombrePaciente[50];
	
	system("cls"); printf("--- MI AGENDA ---\n");
	if (archivo == NULL) { printf("Sin citas.\n"); system("pause"); return; }
	
	printf("%-6s %-11s %-20s %-10s %-7s %s\n", "ID", "CEDULA", "NOMBRE", "FECHA", "HORA", "ESTADO");
	
	while(fscanf(archivo, "%d %s %d %s %s %s %s", &c.idCita, c.cedulaPaciente, &c.codigoMedico, c.fecha, c.hora, c.estado, c.observaciones) == 7) {
		if (c.codigoMedico == codigoMed) {
			
			strcpy(nombrePaciente, "Desconocido");
			for(int i = 0; i < cont_pacientes; i++) {
				if(strcmp(lista_pacientes[i].cedula, c.cedulaPaciente) == 0) {
					strcpy(nombrePaciente, lista_pacientes[i].nombre);
					break;
				}
			}
			printf("%-6d %-11s %-20s %-10s %-7s %s\n", 
				   c.idCita, c.cedulaPaciente, nombrePaciente, c.fecha, c.hora, c.estado);
			encontradas++;
		}
	}
	
	fclose(archivo);
	
	if(encontradas > 0) {
		int idSel;
		printf("\nID Cita a atender (0 salir): "); 
		if(scanf("%d", &idSel) != 1) { while(getchar()!='\n'); idSel=0; }
		if(idSel != 0) atenderCitaMedico(idSel);
	} else {
		printf("Agenda vacia.\n"); system("pause");
	}
}
