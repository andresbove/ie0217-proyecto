#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

void menuAtencionCliente();
void menuInformacionPrestamos();
void menuSacarPrestamo();
void menuPagarPrestamo();

int main() {
    int opcion;

    do {
        cout << "\n----- Menu -----" << endl;
        cout << "1- Atencion a cliente" << endl;
        cout << "2- Informacion general sobre prestamos bancarios" << endl;
        cout << "3- Salir" << endl;
        cout << "----------------" << endl;
        cout << "Ingrese su opcion (1, 2 o 3): ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar 1, 2 o 3.\n");
            }

            switch (opcion) {
            case 1:
                menuAtencionCliente();
                break;
            case 2:
                menuInformacionPrestamos();
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 3);

    return 0;
}

void menuAtencionCliente() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Atencion a cliente" << endl;
        cout << "        1. Sacar prestamo" << endl;
        cout << "        2. Pagar Prestamo" << endl;
        cout << "        3. Generar informe (.txt)" << endl;
        cout << "        4. Volver" << endl;
        cout << "--------------MENU-----------------------------" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 4.\n");
            }

            switch (opcion) {
            case 1:
                menuSacarPrestamo();
                break;
            case 2:
                menuPagarPrestamo();
                break;
            case 3:
                cout << "Ha seleccionado generar informe." << endl;
                break;
            case 4:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 4);
}

void menuSacarPrestamo() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Sacar prestamo" << endl;
        cout << "        1. Prestamo en Dolares" << endl;
        cout << "        2. Prestamo en Colones" << endl;
        cout << "        3. Volver" << endl;
        cout << "--------------MENU-----------------------------" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 3.\n");
            }

            switch (opcion) {
            case 1:
                cout << "Ha seleccionado sacar prestamo en Dolares." << endl;
                break;
            case 2:
                cout << "Ha seleccionado sacar prestamo en Colones." << endl;
                break;
            case 3:
                cout << "Volviendo al menu de Atención a Cliente..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 3);
}

void menuPagarPrestamo() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Pagar prestamo" << endl;
        cout << "        1. Prestamo en Dolares" << endl;
        cout << "        2. Prestamo en Colones" << endl;
        cout << "        3. Volver" << endl;
        cout << "--------------MENU-----------------------------"<<"\n" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 3.\n");
            }

            switch (opcion) {
            case 1:
                cout << "Ha seleccionado pagar prestamo en Dolares." << endl;
                break;
            case 2:
                cout << "Ha seleccionado pagar prestamo en Colones." << endl;
                break;
            case 3:
                cout << "Volviendo al menu de Atención a Cliente..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 3);
}

void menuInformacionPrestamos() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Informacion general sobre prestamos bancarios" << endl;
        cout << "        1. Prestamo Personal" << endl;
        cout << "        2. Prestamo Prendario" << endl;
        cout << "        3. Prestamo Hipotecario" << endl;
        cout << "        4. Volver" << endl;
        cout << "--------------MENU-----------------------------" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 4.\n");
            }

            switch (opcion) {
            case 1:
                cout << "Ha seleccionado Prestamo Personal." << endl;
                break;
            case 2:
                cout << "Ha seleccionado Prestamo Prendario." << endl;
                break;
            case 3:
                cout << "Ha seleccionado Prestamo Hipotecario." << endl;
                break;
            case 4:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 4);
}
