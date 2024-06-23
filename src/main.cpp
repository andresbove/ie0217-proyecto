#include <iostream>
#include <stdexcept>
#include <limits>
#include "functions.hpp"

using namespace std;

void menuAtencionCliente();
void menuInformacionPrestamos();
void menuSacarPrestamo();
void menuPagarPrestamo();
void menuDepositar();
void menuTransferir();
void menuRetirar();
void subMenuSacarPrestamo(const string& tipoPrestamo);
void crear_cuenta_colones();
void crear_cuenta_dolares();
void generarInforme();
void generarInformeDolares();
void generarInformeColones();

int main() {
    int opcion;

    connectDB(); // Conectar a la base de datos
    do {
        cout << "\n----- Menu -----" << endl;
        cout << "1- Crear Usuario" << endl;
        cout << "2- Atencion a cliente" << endl;
        cout << "3- Informacion general sobre prestamos bancarios" << endl;
        cout << "4- Crear cuenta en dolares" << endl;
        cout << "5- Crear cuenta en colones" << endl;
        cout << "6- Salir" << endl;
        cout << "----------------" << endl;
        cout << "Ingrese su opcion (1, 2, 3, 4, 5 o 6): ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un número del 1 al 6.\n");
            }

            switch (opcion) {
            case 1:
                crear_usuario(); // Crear usuario y volver al menú principal
                break;
            case 2:
                menuAtencionCliente();
                break;
            case 3:
                menuInformacionPrestamos();
                break;
            case 4:
                crear_cuenta_dolares();
                break;
            case 5:
                crear_cuenta_colones();
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 6); // Continuar hasta que se elija salir

    return 0;
}

void menuAtencionCliente() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Atencion a cliente" << endl;
        cout << "        1. Sacar prestamo" << endl;
        cout << "        2. Pagar Prestamo" << endl;
        cout << "        3. Generar informe" << endl;
        cout << "        4. Depositar" << endl;
        cout << "        5. Transferir" << endl;
        cout << "        6. Retirar" << endl;
        cout << "        7. CDP" << endl;
        cout << "        8. Volver" << endl;
        cout << "--------------MENU-----------------------------" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 8.\n");
            }

            switch (opcion) {
            case 1:
                menuSacarPrestamo();
                break;
            case 2:
                menuPagarPrestamo();
                break;
            case 3:
                generarInforme(); // Llamar a la función para generar el informe
                break;
            case 4:
                menuDepositar();
                break;
            case 5:
                menuTransferir();
                break;
            case 6:
                menuRetirar();
                break;
            case 7:
                certificadoDP();
                break;
            case 8:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 8);
}

void generarInforme() {
    int opcion;
    do {
        cout << "\n--------------SUBMENU---------------------------" << endl;
        cout << "Generar informe" << endl;
        cout << "        1. Generar informe en Dolares" << endl;
        cout << "        2. Generar informe en Colones" << endl;
        cout << "        3. Volver" << endl;
        cout << "--------------SUBMENU---------------------------" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 3.\n");
            }

            switch (opcion) {
            case 1:
                cout << "Generando informe en Dolares..." << endl;
                // Lógica para generar informe en dólares
                generarInformeDolares();
                break;
            case 2:
                cout << "Generando informe en Colones..." << endl;
                // Lógica para generar informe en colones
                generarInformeColones();
                break;
            case 3:
                cout << "Volviendo al menu de Atencion a Cliente..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 3);
}

void generarInformeDolares() {
    // Aquí implementar la lógica para generar el informe en dólares
    cout << "Informe en Dolares generado correctamente." << endl;
}

void generarInformeColones() {
    // Aquí implementar la lógica para generar el informe en colones
    cout << "Informe en Colones generado correctamente." << endl;
}

void menuSacarPrestamo() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Sacar prestamo" << endl;
        cout << "        1. Prestamo Prendario" << endl;
        cout << "        2. Prestamo Hipotecario" << endl;
        cout << "        3. Prestamo Personal" << endl;
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
                subMenuSacarPrestamo("PRENDARIO");
                break;
            case 2:
                subMenuSacarPrestamo("HIPOTECARIO");
                break;
            case 3:
                subMenuSacarPrestamo("PERSONAL");
                break;
            case 4:
                cout << "Volviendo al menu de Atencion a Cliente..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 4);
}

void subMenuSacarPrestamo(const string& tipoPrestamo) {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Sacar prestamo " << tipoPrestamo << endl;
        cout << "        1. En Dolares" << endl;
        cout << "        2. En Colones" << endl;
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
                cout << "Ha seleccionado sacar prestamo " << tipoPrestamo << " en Dolares." << endl;
                // Lógica para sacar préstamo específico en dólares
                sacarPrestamo("USD", tipoPrestamo);
                break;
            case 2:
                cout << "Ha seleccionado sacar prestamo " << tipoPrestamo << " en Colones." << endl;
                // Lógica para sacar préstamo específico en colones
                sacarPrestamo("CRC", tipoPrestamo);
                break;
            case 3:
                cout << "Volviendo al menu de Sacar prestamo..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar opcion ingresada
        }

    } while (opcion != 3);
}

void menuPagarPrestamo() {
    // Implementación de la función para pagar préstamo
    cout << "Funcion no implementada aún." << endl;
}

void menuDepositar() {
    // Implementación de la función para depositar
    cout << "Funcion no implementada aún." << endl;
}

void menuTransferir() {
    // Implementación de la función para transferir
    cout << "Funcion no implementada aún." << endl;
}

void menuRetirar() {
    // Implementación de la función para retirar
    cout << "Funcion no implementada aún." << endl;
}



void menuInformacionPrestamos() {
    // Implementación de la función para mostrar información general sobre préstamos
    cout << "Funcion no implementada aún." << endl;
}

void crear_cuenta_colones() {
    // Implementación de la función para crear cuenta en colones
    cout << "Funcion no implementada aún." << endl;
}

void crear_cuenta_dolares() {
    // Implementación de la función para crear cuenta en dólares
    cout << "Funcion no implementada aún." << endl;
}
