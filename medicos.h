#ifndef MEDICOS_H
#define MEDICOS_H
#include "validaciones.h"

#define MAX_ESPECIALIDAD 30
#define MAX_HORARIO 50 
#define MEDICOS_MAXIMOS 100

typedef struct {
	int codigo; 
	char cedula[MAX_CEDULA];
	char nombre[MAX_NOMBRE];
	char especialidad[MAX_ESPECIALIDAD];
	char horario[MAX_HORARIO]; 
	char contrasena[MAX_CONTRASENA]; 
	int disponible;
} Datos_Medicos;

extern Datos_Medicos lista_medicos[MEDICOS_MAXIMOS];
extern int cont_medicos;

void registrarMedico();
void listarMedicos();
int existeMedico(int codigo);
void cargarMedicos();

#endif
