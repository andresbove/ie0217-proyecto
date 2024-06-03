#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

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
                cout << "Ha seleccionado atencion a cliente." << endl;
                // Ir a menu de atencion de cliente
                break;
            case 2:
                cout << "Informacion general sobre prestamos bancarios." << endl;
                // Ir a menu de atencion de cliente
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