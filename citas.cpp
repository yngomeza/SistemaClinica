#include <iostream>
#include <fstream>
#include <cstring>
#include "citas.h"

using namespace std;

const int MAX_CITAS = 100;
Cita listaCitas[MAX_CITAS];
int contadorCitas = 0;

void programarCitas() {
    if (contadorCitas >= MAX_CITAS) {
        cout << "Límite de citas alcanzado." << endl;
        return;
    }
    
    cout << "--- Programar Cita ---" << endl;
    cout << "ID de cita: ";
    cin >> listaCitas[contadorCitas].idCita;
    
    cout << "ID del paciente: "; 
    cin >> listaCitas[contadorCitas].idPaciente;
    cin.ignore();
    
    cout << "Fecha (DD/MM/AAAA): ";
    cin.getline(listaCitas[contadorCitas].fecha, 11);
    
    cout << "Hora (HH:MM): ";
    cin.getline(listaCitas[contadorCitas].hora, 6);
    
    cout << "Motivo: ";
    cin.getline(listaCitas[contadorCitas].motivo, 100);
    
    contadorCitas++;
    cout << "Cita programada con éxito.\n";
}

void mostrarCitas() {
    cout << "--- Todas las Citas Registradas ---" << endl;
    for (int i = 0; i < contadorCitas; i++) {
        cout << "ID Cita: " << listaCitas[i].idCita 
             << " | ID Paciente: " << listaCitas[i].idPaciente 
             << " | Fecha: " << listaCitas[i].fecha 
             << " | Hora: " << listaCitas[i].hora 
             << " | Motivo: " << listaCitas[i].motivo << endl;
    }
}

void buscarCitas() {
    int opcion, id;
    cout << "--- Buscar Citas ---" << endl;
    cout << "1. Buscar por ID de cita\n2. Buscar por ID de paciente\nOpción: ";
    cin >> opcion;
    cout << "Ingrese el ID: ";
    cin >> id;
    
    bool encontrado = false;
    for (int i = 0; i < contadorCitas; i++) {
        if ((opcion == 1 && listaCitas[i].idCita == id) || 
            (opcion == 2 && listaCitas[i].idPaciente == id)) {
            cout << "- Cita Encontrada - Fecha: " << listaCitas[i].fecha 
                 << ", Hora: " << listaCitas[i].hora 
                 << ", Motivo: " << listaCitas[i].motivo << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron citas asociadas." << endl;
}

void ordenarCitas() {
  
    for (int i = 0; i < contadorCitas - 1; i++) {
        for (int j = 0; j < contadorCitas - i - 1; j++) {
            int cmpFecha = strcmp(listaCitas[j].fecha, listaCitas[j + 1].fecha);
            if (cmpFecha > 0 || (cmpFecha == 0 && strcmp(listaCitas[j].hora, listaCitas[j + 1].hora) > 0)) {
                Cita temp = listaCitas[j];
                listaCitas[j] = listaCitas[j + 1];
                listaCitas[j + 1] = temp;
            }
        }
    }
    cout << "Citas ordenadas cronológicamente.\n";
}

void guardarCitas() {
    ofstream archivo("citas.dat", ios::binary);
    if (archivo.is_open()) {
        archivo.write((char*)&contadorCitas, sizeof(int));
        archivo.write((char*)listaCitas, contadorCitas * sizeof(Cita));
        archivo.close();
        cout << "Datos guardados en citas.dat correctamente.\n";
    } else {
        cout << "Error al abrir el archivo para guardar.\n";
    }
}

void cargarCitas() {
    ifstream archivo("citas.dat", ios::binary);
    if (archivo.is_open()) {
        archivo.read((char*)&contadorCitas, sizeof(int));
        archivo.read((char*)listaCitas, contadorCitas * sizeof(Cita));
        archivo.close();
        cout << "Citas cargadas correctamente desde el sistema.\n";
    } else {
        cout << "Archivo citas.dat no encontrado. Iniciando con 0 citas registradas.\n";
    }
}