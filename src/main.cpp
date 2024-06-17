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

int main() {
    int opcion;

    connectDB();
    //Cliente usuario;
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
        }
        catch (const exception& e) {
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
        cout << "        4. Depositar" << endl;
        cout << "        5. Transferir" << endl;
        cout << "        6. Retirar" << endl;
        cout << "        7. Volver" << endl;
        cout << "--------------MENU-----------------------------" << endl;
        cout << "Ingrese su opcion: ";

        try {
            cin >> opcion;

            if (cin.fail()) {
                throw runtime_error("Opcion no valida, debe ingresar un numero del 1 al 7.\n");
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

    } while (opcion != 7);
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
                subMenuSacarPrestamo("Prendario");
                break;
            case 2:
                subMenuSacarPrestamo("Hipotecario");
                break;
            case 3:
                subMenuSacarPrestamo("Personal");
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
                sacarPrestamo("Dolares", tipoPrestamo);
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
                // Lógica para pagar préstamo en dólares
                pagarPrestamoDolares("Dolares");
                break;
            case 2:
                cout << "Ha seleccionado pagar prestamo en Colones." << endl;
                // Lógica para pagar préstamo en colones
                pagarPrestamoColones("CRC");
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
                depositar("Dolares");
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
                transferir("Dolares");
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
                retirar("Dolares");
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
