#include <iostream>

#include "pacientes.h"
#include "citas.h"
#include "historial.h"
#include "reportes.h"


using namespace std;


int main(){
    int opcion;

    do{
        cout << "\n===================================";
        cout << "\n SISTEMA DE GESTION CLINICA MEDICA";
        cout << "\n===================================";

        cout << "\n1. Gestion de pacientes";
        cout << "\n2. Programacion de citas";
        cout << "\n3. Historial medico";
        cout << "\n4. Reportes diarios";
        cout << "\n5. Salir";

        cout << "\n\nSeleccione una opcion: ";
        cin >> opcion;


        switch(opcion){
            case 1:
                menuPacientes();
                break;
            case 2:
                menuCitas();
                break;
            case 3:
                menuHistorial();
                break;
            case 4:
                menuReportes();
                break;
            case 5:
                cout << "\nSaliendo del sistema...";
                break;

            default:
                cout << "\nOpcion no valida.";
        }
    }while(opcion != 5);

    return 0;
}
