#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "estructuras.h"

using namespace std;

// Prototipos de funciones del módulo de historial médico

// Menú principal de gestión de historial médico
void menuHistorial();

// Registra una nueva consulta médica
void registrarConsulta();

// Muestra el historial completo de un paciente
void mostrarHistorial();

// Busca una consulta por ID de consulta o ID de paciente
void buscarConsulta();

// Guarda los datos de consultas en el archivo historial.dat
void guardarHistorial();

// Carga los datos de consultas desde el archivo historial.dat
void cargarHistorial();

// Obtiene el siguiente ID disponible para una nueva consulta
int obtenerUltimoIdConsulta();

#endif
