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

int main() {
    int opcion;

    connectDB(); // Conectar a la base de datos
    do {
        cout << "\n----- Menu -----" << endl;
        cout << "1- Crear Usuario" << endl;
        cout << "2- Atencion a cliente" << endl;
        cout << "3- Informacion general sobre prestamos bancarios" << endl;
        cout << "4- Salir" << endl;
        cout << "5- Crear cuenta en colones" << endl;
        cout << "6- Crear cuenta en dólares" << endl;
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
                cout << "Saliendo del programa..." << endl;
                break;
            case 5:
                crear_cuenta_colones();
                break;
            case 6:
                crear_cuenta_dolares();
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

    } while (opcion != 4); // Continuar hasta que se elija salir

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
                cout << "Ha seleccionado generar informe." << endl;
                // Lógica para generar informe
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
                cout << "Volviendo al menu de Sacar Prestamo..." << endl;
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
    int opcion;
    string tipo;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Pagar prestamo" << endl;
        cout << "        1. Prestamo en Dolares" << endl;
        cout << "        2. Prestamo en Colones" << endl;
        cout << "        3. Volver" << endl;
        cout << "--------------MENU-----------------------------" << "\n" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 3.\n");
            }

            switch (opcion) {
            case 1:
                cout << "Ha seleccionado pagar prestamo en Dolares." << endl;
                cout << "Que tipo de prestamo quieres pagar: ";
                cin >> tipo;

                toUpperCase(tipo);
                cout << endl;

                // Lógica para pagar préstamo en dólares
                pagarPrestamoDolares(tipo);

                break;
            case 2:
                cout << "Ha seleccionado pagar prestamo en Colones." << endl;

                cout << "Que tipo de prestamo quieres pagar: ";
                cin >> tipo;
                toUpperCase(tipo);
                // Lógica para pagar préstamo en colones
                pagarPrestamoColones(tipo);
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

void menuDepositar() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Depositar" << endl;
        cout << "        1. Depositar en Dolares" << endl;
        cout << "        2. Depositar en Colones" << endl;
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
                cout << "Ha seleccionado depositar en Dolares." << endl;
                // Lógica para depositar en dólares
                depositar("USD");
                break;
            case 2:
                cout << "Ha seleccionado depositar en Colones." << endl;
                // Lógica para depositar en colones
                depositar("CRC");
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

void menuTransferir() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Transferir" << endl;
        cout << "        1. Transferir en Dolares" << endl;
        cout << "        2. Transferir en Colones" << endl;
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
                cout << "Ha seleccionado transferir en Dolares." << endl;
                // Lógica para transferir en dólares
                transferir("USD");
                break;
            case 2:
                cout << "Ha seleccionado transferir en Colones." << endl;
                // Lógica para transferir en colones
                transferir("CRC");
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

void menuRetirar() {
    int opcion;
    do {
        cout << "\n--------------MENU-----------------------------" << endl;
        cout << "Retirar" << endl;
        cout << "        1. Retirar en Dolares" << endl;
        cout << "        2. Retirar en Colones" << endl;
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
                cout << "Ha seleccionado retirar en Dolares." << endl;
                // Lógica para retirar en dólares
                retirar("USD");
                break;
            case 2:
                cout << "Ha seleccionado retirar en Colones." << endl;
                // Lógica para retirar en colones
                retirar("CRC");
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
                // Lógica para información de préstamo personal
                break;
            case 2:
                cout << "Ha seleccionado Prestamo Prendario." << endl;
                // Lógica para información de préstamo prendario
                break;
            case 3:
                cout << "Ha seleccionado Prestamo Hipotecario." << endl;
                // Lógica para información de préstamo hipotecario
                break;
            case 4:
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

    } while (opcion != 4);
}

void crear_cuenta_colones() {
    cout << "Creando cuenta en colones..." << endl;
    // Lógica para crear cuenta en colones
    // ...
}

void crear_cuenta_dolares() {
    cout << "Creando cuenta en dólares..." << endl;
    // Lógica para crear cuenta en dólares
    // ...
}
