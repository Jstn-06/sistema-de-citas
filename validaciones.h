#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#define MAX_TELEFONO 11
#define MAX_NOMBRE 50
#define MAX_CONTRASENA 50
#define MAX_CORREO 50
#define MAX_CEDULA 11

int Cedula_Existente(char cedula_a_buscar[]);
int validar_formato_cedula(char cedula_a_verificar[]);
int validar_telefono(char telefono_a_verificar[]);
int validar_correo(char correo[]);
int validar_nombre(char nombre_a_validar[]);
int validar_edad(int edad_a_validar);
int esFechaHoraValida(char *fecha, char *hora);
void leerContrasenaMask(char *buffer);
int esFechaFutura(char *fecha);
	
#endif
