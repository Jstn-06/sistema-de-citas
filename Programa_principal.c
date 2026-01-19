#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pacientes.h"
#include "login.h"
#include "medicos.h"
#include "citas.h"

void menuPaciente(SesionActual sesion);
void menuMedico(SesionActual sesion);
void menuAdmin(SesionActual sesion);

// Función local para que el administrador pueda eliminar citas por ID
void gestionarCitasAdmin() {
	int idBorrar;
	system("cls");
	printf("--- GESTIONAR CITAS (ADMIN) ---\n");
	printf("Ingrese ID de la cita a cancelar (0 para salir): ");
	if(scanf("%d", &idBorrar) != 1) { while(getchar()!='\n'); idBorrar=0; }
	
	if(idBorrar != 0) {
		cancelarCita(idBorrar);
	}
}

int main() {
	cargarPacientes();
	cargarMedicos();
	SesionActual sesion_actual;
	int resultado_login;
	int sistema_activo = 1; 
	
	while (sistema_activo) {
		system("cls");
		printf("\n===== SISTEMA MEDICO =====\nINICIAR SESION\n");
		
		resultado_login = verificacion_entrada(&sesion_actual);
		
		if (resultado_login == 0) {
			printf("Saliendo del sistema.\n");
			sistema_activo = 0; 
		} else {
			if (resultado_login == 1) menuPaciente(sesion_actual);
			else if (resultado_login == 2) menuMedico(sesion_actual);
			else if (resultado_login == 3) menuAdmin(sesion_actual);
		}
	}
	return 0;
}

void menuPaciente(SesionActual sesion) {
	int op, idCancelar;
	do {
		system("cls");
		printf("=== PACIENTE: %s ===\n", sesion.nombre_usuario);
		printf("1. Agendar Cita\n");
		printf("2. Ver mis Citas\n");
		printf("3. Cancelar Cita\n");
		printf("4. Cerrar Sesion\n");
		printf("Opcion: ");
		scanf("%d", &op);
		switch(op) {
		case 1: 
			agendarCitaPaciente(sesion.id_usuario); 
			break;
		case 2: 
			verMisCitasPaciente(sesion.id_usuario); 
			break;
		case 3:
			// Mostramos primero las citas para que el usuario vea el ID
			verMisCitasPaciente(sesion.id_usuario);
			printf("\nIngrese ID de la cita a cancelar (0 para volver): ");
			if(scanf("%d", &idCancelar)!=1){ while(getchar()!='\n'); idCancelar=0; }
			if(idCancelar != 0) cancelarCita(idCancelar);
			break;
		}
	} while(op != 4);
}

void menuMedico(SesionActual sesion) {
	int op;
	do {
		system("cls");
		printf("=== MEDICO: %s ===\n", sesion.nombre_usuario);
		printf("1. Ver Agenda\n2. Cerrar Sesion\nOp: ");
		scanf("%d", &op);
		if(op == 1) verAgendaMedico(sesion.id_usuario);
	} while(op != 2);
}

void menuAdmin(SesionActual sesion) {
	int op;
	do {
		system("cls");
		printf("=== ADMIN: %s ===\n", sesion.nombre_usuario);
		printf("1. Registrar Medico\n");
		printf("2. Listar Medicos\n");
		printf("3. Listar Pacientes\n");
		printf("4. Registrar Paciente\n");
		printf("5. Cancelar Cita (Gestionar)\n");
		printf("6. Cerrar Sesion\n");
		printf("Op: ");
		scanf("%d", &op);
		switch(op) {
		case 1: registrarMedico(); break;
		case 2: listarMedicos(); break;
		case 3: listarPacientes(); break;
		case 4: registrar_paciente(); break; // El admin ahora puede registrar pacientes
		case 5: gestionarCitasAdmin(); break; // El admin puede cancelar cualquier cita por ID
		}
	} while(op != 6);
}
