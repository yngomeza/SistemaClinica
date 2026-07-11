#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "estructuras.h"

//Menú del módulo historial médico
void menuHistorial();

//Registrar consulta médica
void registrarConsulta();

//Mostrar historial de un paciente
void mostrarHistorial();

//Buscar consulta
void buscarConsulta();

//Manejo del archivo historial.dat
void guardarHistorial();
void cargarHistorial();

#endif