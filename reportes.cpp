#include <iostream>
#include <fstream>
#include <cstring>
#include "reportes.h"
#include "pacientes.h"
#include "citas.h"
#include "historial.h"

using namespace std;

// Menú de reportes
void menuReportes()
{
    int opcion;
    do
    {
        cout << "\n===== MENU DE REPORTES =====\n";
        cout << "1. Reporte de pacientes\n";
        cout << "2. Reporte de citas\n";
        cout << "3. Reporte de consultas\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion)
        {
            case 1:
                reportePacientes();
                break;
            case 2:
                reporteCitasDiarias();
                break;
            case 3:
                reporteConsultas();
                break;
            case 4:
                cout << "Saliendo del menú de reportes...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }

    } while(opcion != 4);
}

// Reporte general de pacientes
void reportePacientes()
{
    cargarPacientes();

    if(totalPacientes == 0)
    {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    cout << "\n===== REPORTE DE PACIENTES =====\n";
    cout << "Total de pacientes: " << totalPacientes << "\n";
    cout << "----------------------------------------\n";

    for(int i = 0; i < totalPacientes; i++)
    {
        cout << "ID: " << pacientes[i].idPaciente
             << " | Nombre: " << pacientes[i].nombres << " " << pacientes[i].apellidos
             << " | DNI: " << pacientes[i].dni
             << " | Edad: " << pacientes[i].edad
             << " | Teléfono: " << pacientes[i].telefono
             << "\n";
    }
}

// Reporte diario de citas
void reporteCitasDiarias()
{
    ifstream file("citas.dat", ios::binary);
    if(!file)
    {
        cout << "\nNo hay citas registradas.\n";
        return;
    }

    Cita citas[MAX_CITAS];
    int totalCitas;

    file.read(reinterpret_cast<char*>(&totalCitas), sizeof(int));
    file.read(reinterpret_cast<char*>(citas), sizeof(Cita) * totalCitas);
    file.close();

    cargarPacientes(); // Para relacionar ID paciente

    cout << "\n===== REPORTE DE CITAS =====\n";
    if(totalCitas == 0)
    {
        cout << "No hay citas para hoy.\n";
        return;
    }

    for(int i = 0; i < totalCitas; i++)
    {
        string nombrePaciente = "Desconocido";
        for(int j = 0; j < totalPacientes; j++)
        {
            if(citas[i].idPaciente == pacientes[j].idPaciente)
            {
                nombrePaciente = string(pacientes[j].nombres) + " " + pacientes[j].apellidos;
                break;
            }
        }

        cout << "Cita ID: " << citas[i].idCita
             << " | Paciente: " << nombrePaciente
             << " | Fecha: " << citas[i].fecha
             << " | Hora: " << citas[i].hora
             << " | Motivo: " << citas[i].motivo << "\n";
    }
}

// Reporte de consultas realizadas
void reporteConsultas()
{
    cargarHistorial(); // carga arreglo global consultas[]

    if(totalConsultas == 0)
    {
        cout << "\nNo hay consultas registradas.\n";
        return;
    }

    cargarPacientes();

    cout << "\n===== REPORTE DE CONSULTAS =====\n";

    for(int i = 0; i < totalConsultas; i++)
    {
        string nombrePaciente = "Desconocido";
        for(int j = 0; j < totalPacientes; j++)
        {
            if(consultas[i].idPaciente == pacientes[j].idPaciente)
            {
                nombrePaciente = string(pacientes[j].nombres) + " " + pacientes[j].apellidos;
                break;
            }
        }

        cout << "Consulta ID: " << consultas[i].idConsulta
             << " | Paciente: " << nombrePaciente
             << " | Fecha: " << consultas[i].fecha
             << " | Diagnóstico: " << consultas[i].diagnostico
             << " | Tratamiento: " << consultas[i].tratamiento
             << "\n";
    }
}