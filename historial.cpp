#include <iostream>
#include <cstring>
#include <fstream>
#include "historial.h"
#include "pacientes.h"

using namespace std;

// Constante que define el número máximo de consultas
#define MAX_CONSULTAS 100

// Declaración de variables externas del módulo pacientes
extern Paciente pacientes[];
extern int totalPacientes;

// Arreglo global para almacenar las consultas en memoria
Consulta consultas[MAX_CONSULTAS];
// Variable global que lleva el conteo de consultas registradas
int totalConsultas = 0;

/*
 * FUNCIÓN: cargarHistorial
 * PROPÓSITO: Carga los datos de consultas desde el archivo binario historial.dat
 * PROCESO: Abre el archivo en modo lectura binaria, lee el total de consultas
 *          y luego los datos de cada consulta en el arreglo global
 */
void cargarHistorial() {
    // Abrir archivo en modo binario para lectura
    ifstream archivo("historial.dat", ios::binary);
    
    // Verificar si el archivo existe y se abrió correctamente
    if (archivo) {
        // Leer primero el total de consultas almacenadas
        archivo.read(reinterpret_cast<char*>(&totalConsultas), sizeof(totalConsultas));
        // Leer los datos de todas las consultas
        archivo.read(reinterpret_cast<char*>(consultas), sizeof(Consulta) * totalConsultas);
        // Cerrar el archivo
        archivo.close();
        cout << "Historial cargado correctamente.\n";
    } else {
        cout << "No se encontró archivo de historial. Se creará uno nuevo.\n";
    }
}

/*
 * FUNCIÓN: guardarHistorial
 * PROPÓSITO: Guarda los datos de consultas en el archivo binario historial.dat
 * PROCESO: Abre el archivo en modo escritura binaria, escribe el total de
 *          consultas y luego los datos de cada consulta del arreglo global
 */
void guardarHistorial() {
    // Abrir archivo en modo binario para escritura
    ofstream archivo("historial.dat", ios::binary);
    
    // Verificar si el archivo se abrió correctamente
    if (archivo) {
        // Escribir el total de consultas
        archivo.write(reinterpret_cast<char*>(&totalConsultas), sizeof(totalConsultas));
        // Escribir los datos de todas las consultas
        archivo.write(reinterpret_cast<char*>(consultas), sizeof(Consulta) * totalConsultas);
        // Cerrar el archivo
        archivo.close();
    } else {
        cout << "Error al guardar el archivo de historial.\n";
    }
}

/*
 * FUNCIÓN: obtenerUltimoIdConsulta
 * PROPÓSITO: Calcula el siguiente ID disponible para una nueva consulta
 * PROCESO: Recorre todas las consultas registradas, encuentra el ID más alto
 *          y devuelve ese valor + 1
 * RETORNO: Siguiente ID disponible (int)
 */
int obtenerUltimoIdConsulta() {
    int maxId = 0;
    // Recorrer todas las consultas para encontrar el ID más alto
    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].idConsulta > maxId) {
            maxId = consultas[i].idConsulta;
        }
    }
    // Retornar el siguiente ID disponible
    return maxId + 1;
}

/*
 * FUNCIÓN: pacienteExiste
 * PROPÓSITO: Verifica si un paciente con el ID especificado existe en el sistema
 * PROCESO: Recorre el arreglo de pacientes buscando el ID
 * RETORNO: true si el paciente existe, false en caso contrario
 */
bool pacienteExiste(int id) {
    // Recorrer todos los pacientes
    for (int i = 0; i < totalPacientes; i++) {
        if (pacientes[i].idPaciente == id) {
            return true; // Paciente encontrado
        }
    }
    return false; // Paciente no encontrado
}

/*
 * FUNCIÓN: registrarConsulta
 * PROPÓSITO: Registra una nueva consulta médica en el sistema
 * PROCESO: Solicita los datos de la consulta, verifica que el paciente exista,
 *          asigna un ID automático, agrega la consulta al arreglo y guarda los cambios
 */
void registrarConsulta() {
    // Verificar si hay espacio disponible para una nueva consulta
    if (totalConsultas >= MAX_CONSULTAS) {
        cout << "Límite de consultas alcanzado. No se puede registrar más.\n";
        return;
    }

    // Crear una variable temporal para la nueva consulta
    Consulta nueva;
    // Asignar ID automático
    nueva.idConsulta = obtenerUltimoIdConsulta();

    cout << "\n--- REGISTRAR NUEVA CONSULTA ---\n";
    cout << "ID de consulta asignado: " << nueva.idConsulta << "\n";

    // Solicitar el ID del paciente
    cout << "Ingrese ID del paciente: ";
    cin >> nueva.idPaciente;
    cin.ignore(); // Limpiar el buffer

    // Verificar que el paciente exista en el sistema
    if (!pacienteExiste(nueva.idPaciente)) {
        cout << "Error: El paciente con ID " << nueva.idPaciente << " no está registrado.\n";
        return;
    }

    // Solicitar los demás datos de la consulta
    cout << "Ingrese fecha de la consulta (DD/MM/AAAA): ";
    cin.getline(nueva.fecha, 11);

    cout << "Ingrese diagnóstico: ";
    cin.getline(nueva.diagnostico, 150);

    cout << "Ingrese tratamiento indicado: ";
    cin.getline(nueva.tratamiento, 150);

    // Agregar la nueva consulta al arreglo global
    consultas[totalConsultas] = nueva;
    totalConsultas++;
    
    // Guardar los cambios en el archivo
    guardarHistorial();

    cout << "\n¡Consulta registrada correctamente con ID: " << nueva.idConsulta << "!\n";
}

/*
 * FUNCIÓN: mostrarHistorial
 * PROPÓSITO: Muestra el historial completo de consultas de un paciente
 * PROCESO: Solicita el ID del paciente, busca todas sus consultas en el arreglo
 *          y las muestra en pantalla junto con el nombre del paciente
 */
void mostrarHistorial() {
    // Verificar si hay consultas registradas
    if (totalConsultas == 0) {
        cout << "\nNo hay consultas registradas en el sistema.\n";
        return;
    }

    int idPaciente;
    cout << "\n--- CONSULTAR HISTORIAL MÉDICO ---\n";
    cout << "Ingrese ID del paciente: ";
    cin >> idPaciente;
    cin.ignore(); // Limpiar el buffer

    // Buscar el nombre del paciente
    string nombrePaciente = "Desconocido";
    for (int i = 0; i < totalPacientes; i++) {
        if (pacientes[i].idPaciente == idPaciente) {
            nombrePaciente = string(pacientes[i].nombres) + " " + pacientes[i].apellidos;
            break;
        }
    }

    bool encontrado = false;
    cout << "\n--- HISTORIAL DEL PACIENTE ---\n";
    cout << "Paciente: " << nombrePaciente << " (ID: " << idPaciente << ")\n";
    cout << "----------------------------------------\n";

    // Recorrer todas las consultas buscando las del paciente
    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].idPaciente == idPaciente) {
            cout << "Consulta #" << consultas[i].idConsulta << "\n";
            cout << "Fecha: " << consultas[i].fecha << "\n";
            cout << "Diagnóstico: " << consultas[i].diagnostico << "\n";
            cout << "Tratamiento: " << consultas[i].tratamiento << "\n";
            cout << "----------------------------------------\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron consultas para este paciente.\n";
    }
}

/*
 * FUNCIÓN: buscarConsulta
 * PROPÓSITO: Busca una consulta por ID de consulta o ID de paciente
 * PROCESO: Permite al usuario elegir el método de búsqueda, realiza la búsqueda
 *          en el arreglo y muestra los resultados encontrados
 */
void buscarConsulta() {
    int opcion;
    cout << "\n--- BUSCAR CONSULTA ---\n";
    cout << "1. Buscar por ID de consulta\n";
    cout << "2. Buscar por ID de paciente (mostrar todas sus consultas)\n";
    cout << "Opción: ";
    cin >> opcion;
    cin.ignore(); // Limpiar el buffer

    // Búsqueda por ID de consulta
    if (opcion == 1) {
        int id;
        cout << "Ingrese ID de la consulta: ";
        cin >> id;
        
        // Recorrer el arreglo buscando el ID de consulta
        for (int i = 0; i < totalConsultas; i++) {
            if (consultas[i].idConsulta == id) {
                // Mostrar los datos de la consulta encontrada
                cout << "\nConsulta encontrada:\n";
                cout << "ID Consulta: " << consultas[i].idConsulta << "\n";
                cout << "Paciente ID: " << consultas[i].idPaciente << "\n";
                cout << "Fecha: " << consultas[i].fecha << "\n";
                cout << "Diagnóstico: " << consultas[i].diagnostico << "\n";
                cout << "Tratamiento: " << consultas[i].tratamiento << "\n";
                return;
            }
        }
        cout << "Consulta no encontrada con ID: " << id << "\n";
    
    // Búsqueda por ID de paciente
    } else if (opcion == 2) {
        int idPaciente;
        cout << "Ingrese ID del paciente: ";
        cin >> idPaciente;
        
        bool encontrado = false;
        cout << "\nConsultas del paciente con ID " << idPaciente << ":\n";
        cout << "----------------------------------------\n";
        
        // Recorrer el arreglo buscando consultas del paciente
        for (int i = 0; i < totalConsultas; i++) {
            if (consultas[i].idPaciente == idPaciente) {
                cout << "ID Consulta: " << consultas[i].idConsulta << "\n";
                cout << "Fecha: " << consultas[i].fecha << "\n";
                cout << "Diagnóstico: " << consultas[i].diagnostico << "\n";
                cout << "Tratamiento: " << consultas[i].tratamiento << "\n";
                cout << "----------------------------------------\n";
                encontrado = true;
            }
        }
        
        if (!encontrado) {
            cout << "No se encontraron consultas para el paciente con ID " << idPaciente << "\n";
        }
    } else {
        cout << "Opción inválida.\n";
    }
}

/*
 * FUNCIÓN: menuHistorial
 * PROPÓSITO: Muestra y gestiona el menú principal del módulo de historial médico
 * PROCESO: Presenta las opciones disponibles y ejecuta la función correspondiente
 *          según la selección del usuario
 */
void menuHistorial() {
    int opcion;
    do {
        // Mostrar el menú de opciones
        cout << "\n--- HISTORIAL MÉDICO ---\n";
        cout << "1. Registrar consulta\n";
        cout << "2. Mostrar historial de paciente\n";
        cout << "3. Buscar consulta\n";
        cout << "4. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Ejecutar la función correspondiente a la opción seleccionada
        switch (opcion) {
            case 1: 
                registrarConsulta(); 
                break;
            case 2: 
                mostrarHistorial(); 
                break;
            case 3: 
                buscarConsulta(); 
                break;
            case 4: 
                cout << "Volviendo al menú principal...\n"; 
                break;
            default: 
                cout << "Opción inválida. Por favor, intente de nuevo.\n";
        }
    } while (opcion != 4); // Repetir hasta que el usuario elija salir
}
