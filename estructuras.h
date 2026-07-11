#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// ESTRUCTURA DE PACIENTE
struct Paciente{
    int idPaciente;
    char nombres[50];
    char apellidos[50];
    char dni[9];
    int edad;
    char telefono[10];
};

// ESTRUCTURA DE CITA
struct Cita{
    int idCita;
    int idPaciente;
    char fecha[11];
    char hora[6];
    char motivo[100];
};

// ESTRUCTURA DE CONSULTA
struct Consulta{
    int idConsulta;
    int idPaciente;
    char fecha[11];
    char diagnostico[150];
    char tratamiento[150];
};

#endif