#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"
#include <conio.h>
#include <time.h>

int Cedula_Existente(char cedula_a_buscar[MAX_CEDULA]){
	FILE *datos_guardados = fopen("datos_guardados_usuarios.txt", "r");
	if (datos_guardados == NULL) return 0;
	
	char nombre_prov[MAX_NOMBRE], cedula_prov[MAX_CEDULA], pass_prov[MAX_CONTRASENA], correo_prov[MAX_CORREO], tlf_prov[MAX_TELEFONO];  
	int edad_prov;
	
	while(fscanf(datos_guardados, "%s %d %s %s %s %s", nombre_prov, &edad_prov, cedula_prov, pass_prov, correo_prov, tlf_prov) != EOF){
		if(strcmp(cedula_a_buscar, cedula_prov) == 0){
			printf("La cedula ingresada ya se encuentra registrada.\n");
			fclose(datos_guardados);
			return 1;
		}
	}
	fclose(datos_guardados);
	return 0;
}
	
	int validar_formato_cedula(char cedula_a_verificar[]){
		if (strlen(cedula_a_verificar) != 10) return 0; 
		for (int i = 0; i < 10; i++) {
			if (!isdigit(cedula_a_verificar[i])) return 0; 
		}
		return 1; 
	}
		
		int validar_telefono(char telefono_a_verificar[]){
			if (strlen(telefono_a_verificar) != 10) return 0;
			if (telefono_a_verificar[0] != '0' || telefono_a_verificar[1] != '9') return 0;
			for (int i = 0; i < 10; i++){
				if (!isdigit(telefono_a_verificar[i])) return 0;
			}
			return 1;
		}
			
			int validar_correo(char correo[]){
				char *arroba = strchr(correo, '@');
				if (arroba == NULL) return 0; 
				char *punto = strchr(arroba, '.');
				if (punto == NULL) return 0; 
				if (strlen(punto) <= 1) return 0;
				return 1; 
			}
				
				int validar_nombre(char nombre_a_validar[]){
					if (strlen(nombre_a_validar) < 2) return 0;
					for (int i = 0; i < strlen(nombre_a_validar); i++){
						if (!isalpha(nombre_a_validar[i]) && nombre_a_validar[i] != ' '){
							return 0;
						}
					}
					return 1;
				}
					
					int validar_edad(int edad_a_validar){
						if (edad_a_validar <= 0 || edad_a_validar >= 150) return 0;
						return 1;
					}
						
						int esFechaHoraValida(char *fecha, char *hora) {
							int d, m, a, h, min;
							if (sscanf(fecha, "%d/%d/%d", &d, &m, &a) != 3) return 0; 
							if (a < 2025) return 0;      
							if (m < 1 || m > 12) return 0;
							if (d < 1 || d > 31) return 0;
							if ((m==4 || m==6 || m==9 || m==11) && d > 30) return 0;
							if (m==2) {
								int bisiesto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
								if (d > (bisiesto ? 29 : 28)) return 0;
							}
							if (sscanf(hora, "%d:%d", &h, &min) != 2) return 0;
							if (h < 0 || h > 23) return 0;
							if (min < 0 || min > 59) return 0;
							return 1; 
						}
						
						
						
						void leerContrasenaMask(char *buffer) {
							int i = 0;
							char ch;
							while (1) {
								ch = _getch(); 
								
								if (ch == 13) { 
									buffer[i] = '\0'; 
									break;
								} else if (ch == 8) {
									if (i > 0) {
										i--;
										printf("\b \b"); 
									}
								} else {
									if (i < MAX_CONTRASENA - 1) { 
										buffer[i] = ch;
										i++;
										printf("*");
									}
								}
							}
							printf("\n"); 
						}
						
		int esFechaFutura(char *fecha) {
			int d, m, a;
			time_t t = time(NULL);
			struct tm tiempoLocal = *localtime(&t);
			int anoActual = tiempoLocal.tm_year + 1900;
			int mesActual = tiempoLocal.tm_mon + 1;
			int diaActual = tiempoLocal.tm_mday;
							
			if (sscanf(fecha, "%d/%d/%d", &d, &m, &a) != 3) return 0;
							
			if (a < anoActual) return 0;
			if (a == anoActual) {
			if (m < mesActual) return 0;
			if (m == mesActual) {
			if (d < diaActual) return 0;
			}
			}
			return 1;
			}
