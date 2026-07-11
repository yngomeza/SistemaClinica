#ifndef CITAS_H
#define CITAS_H

#include "estructuras.h"

//Menú del módulo citas
void menuCitas();

//Registrar una nueva cita
void registrarCita();

//Mostrar citas registradas
void mostrarCitas();

//Buscar una cita
void buscarCita();

//Ordenar citas por fecha
void ordenarCitas();

//Manejo del archivo citas.dat
void guardarCitas();
void cargarCitas();

#endif