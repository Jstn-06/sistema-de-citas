#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"
#include "pacientes.h" 
#include "medicos.h"
#include "validaciones.h" 

int verificacion_entrada(SesionActual *sesion) {
	char usuario_ing[MAX_CEDULA], contra_ing[MAX_CONTRASENA];
	char nom_tmp[MAX_NOMBRE], ced_tmp[MAX_CEDULA], pass_tmp[MAX_CONTRASENA], correo_tmp[MAX_CORREO], tlf_tmp[MAX_TELEFONO];
	char ced_med_tmp[MAX_CEDULA], nom_med_tmp[MAX_NOMBRE], esp_med_tmp[30], hor_med_tmp[50], pass_med_tmp[MAX_CONTRASENA];
	int edad_tmp, cod_med_tmp, disp_med_tmp;
	int intentos = 0;
	char respuesta_registro; 
	
	while (intentos < MAX_INTENTOS) {
		system("cls");
		
		printf("\n"); 
		printf("==============================================\n");
		printf("          SISTEMA MEDICO - INICIO             \n");
		printf("==============================================\n");
		printf("                                              \n");
		printf("(Intento %d de %d)                      \n", intentos + 1, MAX_INTENTOS);
		printf("                                              \n");
		
		printf("- USUARIO: ");
		scanf("%s", usuario_ing);
		
		printf("- CONTRASENA: ");
		leerContrasenaMask(contra_ing); 
		
		printf("                                              \n");
		printf("==============================================\n");
		
		
		if (strcmp(usuario_ing, ADMIN_USER) == 0 && strcmp(contra_ing, ADMIN_PASS) == 0) {
			sesion->tipo_usuario = 3;
			strcpy(sesion->id_usuario, "0000");
			strcpy(sesion->nombre_usuario, "Administrador");
			return 3;
		}
		
		FILE *f_pac = fopen("datos_guardados_usuarios.txt", "r");
		if (f_pac != NULL) {
			while (fscanf(f_pac, "%s %d %s %s %s %s", nom_tmp, &edad_tmp, ced_tmp, pass_tmp, correo_tmp, tlf_tmp) == 6) {
				if (strcmp(usuario_ing, ced_tmp) == 0 && strcmp(contra_ing, pass_tmp) == 0) {
					sesion->tipo_usuario = 1;
					strcpy(sesion->id_usuario, ced_tmp);
					strcpy(sesion->nombre_usuario, nom_tmp);
					fclose(f_pac); return 1; 
				}
			}
			fclose(f_pac);
		}
		
		FILE *f_med = fopen("datos_medicos.txt", "r");
		if (f_med != NULL) {
			while (fscanf(f_med, "%d %s %s %s %s %s %d", &cod_med_tmp, ced_med_tmp, nom_med_tmp, esp_med_tmp, hor_med_tmp, pass_med_tmp, &disp_med_tmp) == 7) {
				char codigo_str[20];
				sprintf(codigo_str, "%d", cod_med_tmp); 
				if (strcmp(usuario_ing, codigo_str) == 0 && strcmp(contra_ing, pass_med_tmp) == 0) {
					sesion->tipo_usuario = 2;
					strcpy(sesion->id_usuario, codigo_str);
					strcpy(sesion->nombre_usuario, nom_med_tmp);
					fclose(f_med); return 2; 
				}
			}
			fclose(f_med);
		}
		
		printf("\nERROR: Credenciales incorrectas.\n");
		system("pause"); 
		
		system("cls");
		printf("\n==============================================\n");
		printf("     - Usuario nuevo? REGISTRO          \n");
		printf("==============================================\n");
		printf("Desea registrarse como NUEVO PACIENTE? (s/n): ");
		scanf(" %c", &respuesta_registro); 
		
		if (respuesta_registro == 's' || respuesta_registro == 'S') {
			registrar_paciente(); 
			printf("\nIntente iniciar sesion con sus nuevos datos.\n");
			system("pause");
			continue; 
		}
		intentos++;
	}
	return 0; 
}
