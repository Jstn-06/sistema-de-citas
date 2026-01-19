#ifndef PACIENTES_H
#define PACIENTES_H
#include "validaciones.h" 

#define PACIENTES_MAXIMOS 100

typedef struct {
	char nombre[MAX_NOMBRE];
	char cedula[MAX_CEDULA];            
	char contrasena[MAX_CONTRASENA];  
	int edad;
	char correo[MAX_CORREO];
	char telefono[MAX_TELEFONO];
} datos_pacientes;

extern datos_pacientes lista_pacientes[PACIENTES_MAXIMOS];
extern int cont_pacientes;

void registrar_paciente(); 
void listarPacientes();
void cargarPacientes();

#endif
