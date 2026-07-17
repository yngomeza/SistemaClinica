#include <iostream>
#include <string.h>
#include "pacientes.h"
#include "estructuras.h"
using namespace std;

const int MAX_PACIENTES = 100;
Paciente pacientes[MAX_PACIENTES];
int totalPacientes = 0;

void cargarPacientes() {
    FILE* archivo = fopen("pacientes.dat", "rb");
    if (archivo == NULL) {
        totalPacientes = 0;
        return;
    }
    
    fread(&totalPacientes, sizeof(int), 1, archivo);

    fread(pacientes, sizeof(Paciente), totalPacientes, archivo);
    
    fclose(archivo);
}

void guardarPacientes() {
    FILE* archivo = fopen("pacientes.dat", "wb");
    if (archivo == NULL) {
        cout<<"Error al guardar los pacientes."<<endl;
        return;
    }

    fwrite(&totalPacientes, sizeof(int), 1, archivo);

    fwrite(pacientes, sizeof(Paciente), totalPacientes, archivo);
    
    fclose(archivo);
}

int generarIdPaciente() {
    int maxId = 0;
    for (int i = 0; i < totalPacientes; i++) {
        if (pacientes[i].idPaciente > maxId) {
            maxId = pacientes[i].idPaciente;
        }
    }
    return maxId + 1;
}

bool dniExiste(const char* dni) {
    for (int i = 0; i < totalPacientes; i++) {
        if (strcmp(pacientes[i].dni, dni) == 0) {
            return true;
        }
    }
    return false;
}

void registrarPaciente() {
    if (totalPacientes >= MAX_PACIENTES) {
        cout<<"No se pueden registrar más pacientes. Límite alcanzado."<<endl;
        return;
    }
    
    Paciente nuevoPaciente;
    nuevoPaciente.idPaciente = generarIdPaciente();
    
    cout<<"\n=== REGISTRO DE NUEVO PACIENTE ==="<<endl;
    cout<<"ID asignado: "<<nuevoPaciente.idPaciente<<endl;
    
    cout<<"Nombres: ";
    cin.ignore();
    cin.getline(nuevoPaciente.nombres, 50);
    
    cout<<"Apellidos: ";
    cin.getline(nuevoPaciente.apellidos, 50);
    
    char dni[9];
    do {
        cout<<"DNI (8 dígitos): ";
        cin.getline(dni, 9);
        
        if (strlen(dni) != 8) {
            cout<<"Error: El DNI debe tener 8 dígitos."<<endl;
            continue;
        }
        
        if (dniExiste(dni)) {
            cout<<"Error: Ya existe un paciente con este DNI."<<endl;
            continue;
        }
        
        break;
    } while (true);
    
    strcpy(nuevoPaciente.dni, dni);
    
    cout<<"Edad: ";
    cin>>nuevoPaciente.edad;
    
    cout<<"Teléfono: ";
    cin.ignore();
    cin.getline(nuevoPaciente.telefono, 15);

    pacientes[totalPacientes] = nuevoPaciente;
    totalPacientes++;

    guardarPacientes();
    
    cout<<"\nPaciente registrado correctamente."<<endl;
    cout<<"ID del paciente: "<<nuevoPaciente.idPaciente<<endl;
}

void mostrarPacientes() {
    if (totalPacientes == 0) {
        cout<<"\nNo hay pacientes registrados."<<endl;
        return;
    }
    
    cout<<"\n=== LISTA DE PACIENTES ==="<<endl;
    cout<<"Total de pacientes: "<<totalPacientes<<endl;
    cout<<"----------------------------------------"<<endl;
    
    for (int i = 0; i < totalPacientes; i++) {
        cout<<"ID: "<<pacientes[i].idPaciente<<endl;
        cout<<"Nombre: "<<pacientes[i].nombres<<" "<<pacientes[i].apellidos<<endl;
        cout<<"DNI: "<<pacientes[i].dni<<endl;
        cout<<"Edad: "<<pacientes[i].edad<<endl;
        cout<<"Teléfono: "<<pacientes[i].telefono<<endl;
        cout<<"----------------------------------------"<<endl;
    }
}

void buscarPaciente() {
    if (totalPacientes == 0) {
        cout<<"\nNo hay pacientes registrados para buscar."<<endl;
        return;
    }
    
    int opcion;
    cout<<"\n=== BUSCAR PACIENTE ==="<<endl;
    cout<<"1. Buscar por ID"<<endl;
    cout<<"2. Buscar por DNI"<<endl;
    cout<<"Seleccione una opción: ";
    cin>>opcion;
    
    int idBuscar;
    char dniBuscar[9];
    bool encontrado = false;
    
    switch (opcion) {
        case 1:
            cout<<"Ingrese ID del paciente: ";
            cin>>idBuscar;
            
            for (int i = 0; i < totalPacientes; i++) {
                if (pacientes[i].idPaciente == idBuscar) {
                    cout<<"\n=== PACIENTE ENCONTRADO ==="<<endl;
                    cout<<"ID: "<<pacientes[i].idPaciente<<endl;
                    cout<<"Nombre: "<<pacientes[i].nombres<<" "<<pacientes[i].apellidos<<endl;
                    cout<<"DNI: "<<pacientes[i].dni<<endl;
                    cout<<"Edad: "<<pacientes[i].edad<<endl;
                    cout<<"Teléfono: "<<pacientes[i].telefono<<endl;
                    encontrado = true;
                    break;
                }
            }
            break;
            
        case 2:
            cout<<"Ingrese DNI del paciente: ";
            cin>>dniBuscar;
            
            for (int i = 0; i < totalPacientes; i++) {
                if (strcmp(pacientes[i].dni, dniBuscar) == 0) {
                    cout<<"\n=== PACIENTE ENCONTRADO ==="<<endl;
                    cout<<"ID: "<<pacientes[i].idPaciente<<endl;
                    cout<<"Nombre: "<<pacientes[i].nombres<<" "<<pacientes[i].apellidos<<endl;
                    cout<<"DNI: "<<pacientes[i].dni<<endl;
                    cout<<"Edad: "<<pacientes[i].edad<<endl;
                    cout<<"Teléfono: "<<pacientes[i].telefono<<endl;
                    encontrado = true;
                    break;
                }
            }
            break;
            
        default:
            cout<<"Opción inválida."<<endl;
            return;
    }
    
    if (!encontrado) {
        cout<<"\nPaciente no encontrado."<<endl;
    }
}

void ordenarPacientes() {
    if (totalPacientes <= 1) {
        cout<<"\nNo hay suficientes pacientes para ordenar."<<endl;
        return;
    }
    
    cout<<"\n=== ORDENANDO PACIENTES POR APELLIDO ==="<<endl;
    
    cout<<"\nAntes del ordenamiento:"<<endl;
    for (int i = 0; i < totalPacientes; i++) {
        cout<<pacientes[i].apellidos<<", "<<pacientes[i].nombres<<endl;
    }

    for (int i = 0; i < totalPacientes - 1; i++) {
        for (int j = 0; j < totalPacientes - i - 1; j++) {
            if (strcmp(pacientes[j].apellidos, pacientes[j + 1].apellidos) > 0) {
                Paciente temp = pacientes[j];
                pacientes[j] = pacientes[j + 1];
                pacientes[j + 1] = temp;
            }
        }
    }

    guardarPacientes();
    
    cout<<"\nDespués del ordenamiento:"<<endl;
    for (int i = 0; i < totalPacientes; i++) {
        cout<<pacientes[i].apellidos<<", "<<pacientes[i].nombres<<endl;
    }
    
    cout<<"\nPacientes ordenados correctamente."<<endl;
}

void menuPacientes() {
    int opcion;
    
    do {
        cout<<"\n=== GESTIÓN DE PACIENTES ==="<<endl;
        cout<<"1. Registrar paciente"<<endl;
        cout<<"2. Mostrar pacientes"<<endl;
        cout<<"3. Buscar paciente"<<endl;
        cout<<"4. Ordenar pacientes por apellido"<<endl;
        cout<<"5. Volver al menú principal"<<endl;
        cout<<"Seleccione una opción: ";
        cin>>opcion;
        
        switch (opcion) {
            case 1:
                registrarPaciente();
                break;
            case 2:
                mostrarPacientes();
                break;
            case 3:
                buscarPaciente();
                break;
            case 4:
                ordenarPacientes();
                break;
            case 5:
                cout<<"Volviendo al menú principal..."<<endl;
                break;
            default:
                cout<<"Opción inválida. Intente nuevamente."<<endl;
        }
    } while (opcion != 5);
}
