#ifndef LOGIN_H  
#define LOGIN_H
#include "validaciones.h"

#define MAX_INTENTOS 3
#define ADMIN_USER "admin"
#define ADMIN_PASS "1234"

typedef struct {
	int tipo_usuario;    
	char id_usuario[20]; 
	char nombre_usuario[MAX_NOMBRE];
} SesionActual;

int verificacion_entrada(SesionActual *sesion);

#endif
