#ifndef PACIENTES_H
#define PACIENTES_H

#include "estructuras.h"

//Menú del módulo pacientes
void menuPacientes();

//Registro de pacientes
void registrarPaciente();

//Mostrar todos los pacientes
void mostrarPacientes();

//Buscar paciente por ID o DNI
void buscarPaciente();

//Ordenar pacientes
void ordenarPacientes();

//Manejo del archivo pacientes.dat
void guardarPacientes();
void cargarPacientes();

#endif