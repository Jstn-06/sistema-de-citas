#ifndef CITAS_H
#define CITAS_H

typedef struct {
	int idCita;
	char cedulaPaciente[20]; 
	int codigoMedico;   
	char fecha[11];      
	char hora[6];       
	char estado[20];    
	char observaciones[100];
} Cita;

int generarNuevoIdCita();
void agendarCitaPaciente(char *cedulaPaciente);
void verMisCitasPaciente(char *cedulaPaciente);
void verAgendaMedico(char *codigoMedicoStr);
int verificarDisponibilidadMedico(int codigoMedico, char fecha[], char hora[]);
void atenderCitaMedico(int idCitaAEditar);
void cancelarCita(int idCita);
int estaDentroDeHorario(char *horarioMedico, char *horaCita);

#endif
