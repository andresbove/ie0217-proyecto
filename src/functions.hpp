#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <iostream>
#include <format>
#include <cmath>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <regex>

//Libreria de sql
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include <cppconn/prepared_statement.h>



using namespace std;
using namespace sql;



// create a standard objects for sql tables :)
//estructura general de un cliente, para su creacion en la base de datos
//recordar que ya subido cualquier objeto de aca a la base de datos
//es posible modificar valores con las operaciones CRUD

//declaramos las variables globales
sql::mysql::MySQL_Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::ResultSet* res;



void registroColones(int cedula, float cantidad, string estado) {

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO registroColones (cedula, cantidad, estado) VALUES (?, ?, ?)"));
    // Establece los valores de los parámetros
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, cantidad); // Cantidad transferida
    pstmt->setString(3, estado); // Estado de la transferencia

    // Ejecuta la declaración
    pstmt->executeUpdate();
}

void registroDolares(int cedula, float cantidad, string estado) {

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO registroDolares (cedula, cantidad, estado) VALUES (?, ?, ?)"));
    // Establece los valores de los parámetros
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, cantidad); // Cantidad transferida
    pstmt->setString(3, estado); // Estado de la transferencia

    // Ejecuta la declaración
    pstmt->executeUpdate();
}


void toUpperCase(string& palabra) {
    transform(palabra.begin(), palabra.end(), palabra.begin(), [](unsigned char c) {return toupper(c);});
}

// Para verificar que lo ingresado son letras
bool validarLetras(const string& str) {
    return regex_match(str, regex("^[A-Za-z]+$"));
}

// Para verificar que lo ingresado son digitos
bool validarDigitos(const string& str) {
    return regex_match(str, regex("^[0-9]+$"));
}

// Validar float ingresado por el usuario
bool validarFloat(const string& str) {
    regex floatRegex(R"([0-9]*\.?[0-9]+)"); // Recuerde que por ser float siempre va a ser #.#
    return regex_match(str, floatRegex);
}

// Verificar correro
bool validarCorreo(const string& str) {
    return regex_match(str, regex(R"(^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$)"));
}

// Convertir de string a float
float stringToFloat(const string& str) {
    return stof(str);
}

// Funcion para validar cedula, que se espera que sean ints, ademas verifica que la cedula esté en la base de datos (por esto no usar en crearUsuario)
int validarCedula() {
    int cedula;
    string cedulaString;

    do {
        cout << "Por favor ingresa la cedula: ";
        cin >> cedulaString;

        // Validar si input es valido
        if (!validarDigitos(cedulaString)) {
            cout << "La cedula solo debe contener numeros.\n" << endl;
            continue;
        }

        // Convertir string a int
        cedula = stoi(cedulaString);

        try {
            // Verificar si la cédula existe en la base de datos
            unique_ptr<PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM Cliente WHERE cedula = ?"));
            pstmt->setInt(1, cedula);
            unique_ptr<ResultSet> res(pstmt->executeQuery());

            // Verificar si la cédula está en la base de datos
            if (!res->next()) {
                cout << "Error: La cedula ingresada no existe en la base de datos.\n" << endl;
                continue;
            }

            return cedula; // Se devuelve int porque así es como está el dato en la base de datos

        }
        catch (SQLException& e) {
            cerr << "Error al verificar la cedula en la base de datos: \n" << e.what() << endl;
            return -1;
        }

    } while (true); // Continúa pidiendo cedula hasta que una válida sea ingresada
}

bool verificarSaldoSuficiente(int cedula, float monto, const string& moneda) {
    std::unique_ptr<sql::PreparedStatement> pstmt;
    if (moneda == "CRC") {
        pstmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement("SELECT saldo FROM cuentaColones WHERE cedula = ?"));
    }
    else if (moneda == "USD") {
        pstmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement("SELECT saldo FROM cuentaDolares WHERE cedula = ?"));
    }
    else {
        cout << "Moneda no soportada." << endl;
        return false;
    }

    pstmt->setInt(1, cedula);
    std::unique_ptr<sql::ResultSet> result(pstmt->executeQuery());

    if (result->next()) {
        double saldo = result->getDouble("saldo");
        if (saldo >= monto) {
            return true; // El saldo es suficiente
        }
        else {
            cout << "Saldo insuficiente para realizar la operación." << endl;
            return false; // El saldo es insuficiente
        }
    }
    else {
        cout << "No se encontró la cuenta del usuario." << endl;
        return false; // No se encontró la cuenta del usuario
    }
}




bool verificarSaldotransferencia(int cedula, float monto, const string& moneda) {
    std::unique_ptr<sql::PreparedStatement> pstmt;
    if (moneda == "CRC") {
        pstmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement("SELECT saldo FROM cuentaColones WHERE cedula = ?"));
    }
    else {
        pstmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement("SELECT saldo FROM cuentaDolares WHERE cedula = ?"));
    }

    pstmt->setInt(1, cedula);
    std::unique_ptr<sql::ResultSet> result(pstmt->executeQuery());

    if (result->next()) {
        double saldo = result->getDouble("saldo");
        if (saldo >= monto) {
            return true; // El saldo es suficiente
        }
        else {
            cout << "Saldo insuficiente para realizar la operación." << endl;
            return false; // El saldo es insuficiente
        }
    }
    else {
        cout << "No se encontró la cuenta del usuario." << endl;
        return false; // No se encontró la cuenta del usuario
    }
}




// Funcion que le solicita al usuario el saldo y verifica que sea el formato correcto
float validarSaldo() {
    float saldo;
    string saldoString;

    // Validar saldo
    do {
        cout << "\nPor favor ingresa el saldo inicial a depositar en colones: ";
        cin >> saldoString;

        // Validar que lo ingresado sea un float o entero
        if (!validarFloat(saldoString)) {
            cout << "El saldo solo debe contener numeros y/o 1 punto decimal.\n" << endl;
        }
    } while (!validarFloat(saldoString));

    // Convertir de string a float
    saldo = stringToFloat(saldoString);

    return saldo; // Devolver float porque asi es como lo requiere la base de datos
}

void connectDB() {
    try
    {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "Holis123#");
        // seleccionamos nuestra base de datos
        con->setSchema("banco_data_base_4");

        if (con)
        {
            cout << "*********************************************************" << endl;
            cout << "Nos Conectamos Correctamente a la base de datos papaaa.." << endl;
            cout << "*********************************************************" << endl;
        }

        else
        {
            cout << "No hemos podidos conectarnos  a la base de datos :( ... \n" << endl;
        }
    }
    catch (sql::SQLException& e)
    {
        cout << "# Err: SQLexception in : " << __FILE__ << endl;
        cout << "(MySql error code :)" << e.getErrorCode() << endl;
        cout << "SQLstate :" << e.getSQLState() << endl;
    }
};

void crear_usuario() {
    //objeto usuario de tipo cliente
    //Cliente* usuario;
    //ocupamos variables locales para luego almacenar con setter
    string nombre;
    string cedula;
    string apellido1;
    string apellido2;
    string Provincia;
    string telefono;
    string correo;
    cout << endl;
    cout << endl;

    cout << "***************************" << endl;
    cout << "*****Creando Usuario*****" << endl;
    cout << "***************************" << endl;

    // Validar cedula (solo digitos)
    do {
        cout << "\n Por favor ingresa el cedula: ";
        cin >> cedula;
        if (!validarDigitos(cedula)) {
            cout << "La cedula debe contener solo números." << endl;
        }
    } while (!validarDigitos(cedula)); // Siempre y cuando el regex devuelva False

    // Validar nombre (solo letras)
    do {
        cout << "Por favor ingresa el nombre: ";
        cin >> nombre;
        if (!validarLetras(nombre)) {
            cout << "El nombre solo debe contener letras." << endl;
        }
    } while (!validarLetras(nombre));

    // Validar apellido1 (solo letras)
    do {
        cout << "\n Por favor ingresa el primer apellido: ";
        cin >> apellido1;
        if (!validarLetras(apellido1)) {
            cout << "El primer apellido solo debe contener letras." << endl;
        }
    } while (!validarLetras(apellido1));

    // Validar apellido2 (solo letras)
    do {
        cout << "\n Por favor ingresa el segundo apellido: ";
        cin >> apellido2;
        if (!validarLetras(apellido2)) {
            cout << "El segundo apellido solo debe contener letras." << endl;
        }
    } while (!validarLetras(apellido2));

    // Validar provincia (solo letras)
    do {
        cout << "\n Por favor ingresa la provincia: ";
        cin >> Provincia;
        if (!validarLetras(Provincia)) {
            cout << "La provincia solo debe contener letras." << endl;
        }
    } while (!validarLetras(Provincia));

    // Validar telefono (solo digitos)
    do {
        cout << "\n Por favor ingresa el telefono: ";
        cin >> telefono;
        if (!validarDigitos(telefono)) {
            cout << "El telefono solo debe contener numeros." << endl;
        }
    } while (!validarDigitos(telefono));

    // Validar correo (caso especial)
    do {
        cout << "\n Por favor ingresa el correo: ";
        cin >> correo;
        if (!validarCorreo(correo)) {
            cout << "El correo solo debe seguir el patron (letras o numeros)@(letras).com." << endl;
        }
    } while (!validarCorreo(correo));

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Cliente (cedula, nombre, apellido1, apellido2, provincia, telefono, correo) VALUES (?,?, ?, ?, ?, ?, ?)"));
    // Establece los valores de los parámetros
    pstmt->setString(1, cedula);
    pstmt->setString(2, nombre);
    pstmt->setString(3, apellido1);
    pstmt->setString(4, apellido2);
    pstmt->setString(5, Provincia);
    pstmt->setString(6, telefono);
    pstmt->setString(7, correo);

    pstmt->executeUpdate();
    cout << endl;
    cout << "\n Se agrego el usuario de forma exitosa .... " << endl;
};

void crearCuentaColones() {
    //cuentaColones cuenta;
    int cedula;
    float saldo;
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*****Creando Cuenta Colones******" << endl;
    cout << "*********************************" << endl;

    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    saldo = validarSaldo(); // Solicitar el saldo y verificar que el input sea correcto

    //llamada a bases de datos INSERT
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO cuentaColones (cedula, saldo) VALUES (?, ?)"));
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, saldo); // Saldo inicial

    // Ejecuta la declaración
    pstmt->executeUpdate();
    //se ejecuta el query ...
    cout << "Se agrego la cuenta de colones forma exitosa .... " << endl;
    cout << "\n";
};


void crearCuentaDolares() {
    //cuentaDolares cuenta;
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*****Creando Cuenta Dolares******" << endl;
    cout << "*********************************" << endl;
    int cedula;
    float saldo;

    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    saldo = validarSaldo(); // Solicitar el saldo y verificar que el input sea correcto

    //lamada a bases de datos INSERT
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO cuentaDolares (cedula, saldo) VALUES (?, ?)"));
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, saldo); // Saldo inicial

    // Ejecuta la declaración
    pstmt->executeUpdate();
    cout << "Se agrego la cuenta de dolares de  forma exitosa .... " << endl;
};

//Empezamos con las funciones de cuentas colones y dolares

void depositar(string moneda) {

    int cedula;
    float deposito;
    //string moneda;
    cout << endl;
    cout << endl;

    cout << "*********************************" << endl;
    cout << "*********Depositando*************" << endl;
    cout << "*********************************" << endl;

    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado

    cout << "\n Por favor ingresa la cantidad a depositar: ";
    cin >> deposito;
    //cout << "\n Por favor ingresa la moneda: ";
    //cin >> moneda;


    //llamada a la base de datos
    //sera un update
    if (moneda == "CRC") {
        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, deposito); // Nuevo saldo
        pstmt->setInt(2, cedula); // Cédula del cliente
        pstmt->executeUpdate();
        cout << endl;
        cout << "Se agrego el deposito  de  forma exitosa .... " << endl;
    }
    else
    {
        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, deposito); // Nuevo saldo
        pstmt->setInt(2, cedula); // Cédula del cliente
        pstmt->executeUpdate();
        cout << endl;
        cout << "Se agrego el deposito  de  forma exitosa .... " << endl;
    }

    //registro de las transacciones

    if (moneda == "CRC")
    {
        registroColones(cedula, deposito, "DEPOSITO");
    }
    else
    {
        registroDolares(cedula, deposito, "DEPOSITO");
    }


};

//Pendiente: crear excepcion para que solo puedan ingresar monedas USD Y CRC
void retirar(string moneda) {
    int cedula;
    float retiro;

    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Retirando*************" << endl;
    cout << "*********************************" << endl;

    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado

    cout << "\n Por favor ingresa la cantidad a retirar: ";
    cin >> retiro;


    if (!verificarSaldoSuficiente(cedula, retiro, moneda)) {
        return; // Salir de la función si el saldo no es suficiente
    }

    //llamada a la base de datos
    //sera un update
    if (moneda == "CRC") {
        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, retiro); // Nuevo saldo
        pstmt->setInt(2, cedula); // Cédula del cliente
        pstmt->executeUpdate();
        cout << endl;
        cout << "Se retiro el dinero  de forma exitosa.... " << endl;

    }
    else {
        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, retiro); // Nuevo saldo
        pstmt->setInt(2, cedula); // Cédula del cliente
        pstmt->executeUpdate();
        cout << endl;
        cout << "Se retiro el dinero  de forma exitosa.... " << endl;
    }

    if (moneda == "CRC")
    {
        registroColones(cedula, retiro, "RETIRO");
    }
    else
    {
        registroDolares(cedula, retiro, "RETIRO");
    }
};

void transferir(string moneda) {
    //esta es una mezcla de las funciones retirar y depositar
    int depositante;
    float cantidad;
    int destinatario;

    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Transfiriendo*************" << endl;
    cout << "*********************************" << endl;

    //cout << "Por favor ingresa la cedula depositante: ";
    //cin >> depositante;
    cout << "\n(Datos de depositante) ";
    depositante = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado

    cout << "\nPor favor ingresa la cantidad a transferir: ";
    cin >> cantidad;

    //cout << "\n Por favor ingresa la cedula del destinatario: ";
    //cin >> destinatario;
    cout << "\n(Datos del destinatario) ";
    destinatario = validarCedula();


    if (!verificarSaldoSuficiente(depositante, cantidad, moneda)) {
        return; // Salir de la función si el saldo no es suficiente
    }

    if (moneda == "CRC") {

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, cantidad); // Nuevo saldo
        pstmt->setInt(2, depositante); // Cédula del cliente
        pstmt->executeUpdate();

        std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt2->setDouble(1, cantidad); // Nuevo saldo
        pstmt2->setInt(2, destinatario); // Cédula del cliente
        pstmt2->executeUpdate();
        cout << endl;
        cout << "Se Realizo la transferencia de forma exitosa.... " << endl;
        cout << endl;
        cout << endl;
    }
    else
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, cantidad); // Nuevo saldo
        pstmt->setInt(2, depositante); // Cédula del cliente
        pstmt->executeUpdate();

        std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt2->setDouble(1, cantidad); // Nuevo saldo
        pstmt2->setInt(2, destinatario); // Cédula del cliente
        pstmt2->executeUpdate();
        cout << endl;
        cout << "Se Realizo la transferencia de forma exitosa.... " << endl;
        cout << endl;
        cout << endl;
    }

    //registro de transacciones
    if (moneda == "CRC")
    {
        registroColones(depositante, cantidad, "RETIRO");
        registroColones(destinatario, cantidad, "DEPOSITO");
    }
    else
    {
        registroDolares(depositante, cantidad, "RETIRO");
        registroColones(destinatario, cantidad, "DEPOSITO");
    }
};

//las funciones de aqui hacia arriba todas funcionan correctamente :)

//funciones para los prestamos
//funciones para los prestamos

float calcularInteresSimple(float cantidadInicial, int years, float interesAnual) {

    float interes = cantidadInicial * years * interesAnual;
    return interes;
}

float calcularInteresCompuesto(float cantidadInicial, int years, float interesAnual, float capitalizacion = 1) {
    float interes = cantidadInicial * pow(1 + interesAnual / capitalizacion, years * capitalizacion);
    return interes;
}

//*******************************************
//revisar estas formulas
//*******************************************


float cuota(float cantidadInicial, float interesAnual, int periodos) {
    float interesMensual = interesAnual / 12;
    float resultado = cantidadInicial * ((interesMensual * pow(1 + interesMensual, periodos)) / pow(1 + interesMensual, periodos - 1));
    return resultado;
}


float obtenerCuotaColones(int cedula, string tipo) {
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT cuota FROM prestamo_Colones WHERE cedula=? AND tipo=?"));


    pstmt->setInt(1, cedula); // Cédula específica
    pstmt->setString(2, tipo); // Tipo específico

    // Ejecutar la consulta
    res = pstmt->executeQuery();
    //ahi obtenemos la respuesta

    float cuota;

    // Verificar si se obtuvo un resultado
    if (res->next()) {
        cuota = res->getDouble("cuota");
        //std::cout << "El valor de la cuota es: " << cuota << std::endl;
    }
    else {
        std::cout << "No se encontraron registros que coincidan con los criterios especificados." << std::endl;
    }
    return cuota;

    //ahi obtuvimos la cuota en colones




}

float obtenerCuotaDolares(int cedula, string tipo) {

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT cuota FROM prestamo_Dolares WHERE cedula=? AND tipo=?"));


    pstmt->setInt(1, cedula); // Cédula específica
    pstmt->setString(2, tipo); // Tipo específico

    // Ejecutar la consulta
    res = pstmt->executeQuery();
    //ahi obtenemos la respuesta

    float cuota;

    // Verificar si se obtuvo un resultado
    if (res->next()) {
        cuota = res->getDouble("cuota");
        //std::cout << "El valor de la cuota es: " << cuota << std::endl;
    }
    else {
        std::cout << "No se encontraron registros que coincidan con los criterios especificados." << std::endl;
    }
    return cuota;

}




//crear un prestamo
//segun lo de arriba creemos que ya es suficiente para saber que prestamos iremos a sacar
void sacarPrestamo(string moneda, string tipo) {
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Sacar Prestamo*************" << endl;
    cout << "*********************************" << endl;

    //string moneda;
    int cedula;//cedula de identidad
    float cantidad;
    int periodos;// meses a los que saco el presto
    float Cuota;//cuota a pagar mensual
    float saldoPendiente;// saldo que sigue debiendo la persona
    int cuotasRestantes;//cuota que debe aun por pagar
    float tasaInteresAnual; //tasa de interes por sacar el prestamo
    //Ademas una columna con el tipo de prestamo
    //creo que lo mejor seria manejar los prestamos en dos tablas colones y dolares

    //cout << "\nEn que moneda desea solicitar el prestamo: ";
    //cin >> moneda;
    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    cout << "\nPor favor ingresa la cantidad de dinero del prestamo: ";
    cin >> cantidad;
    cout << "\nPor favor ingresa los meses a los cuales sera el prestamo: ";
    cin >> periodos;
    cout << "\nPor favor ingresa la tasa interes anual del prestamo: ";
    cin >> tasaInteresAnual;


    tasaInteresAnual = tasaInteresAnual / 100; // para dejarla en terminos de 0 .. 1

    //sacaremos la cuota

    Cuota = cuota(cantidad, tasaInteresAnual, periodos);//ya calculamos la cuota que tienen que pagar con interes fijo

    //insertaremos dichos datos a la base de datos


    //insertamos en tabla de prestamos de colones
    if (moneda == "CRC")
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO prestamo_Colones(cedula, cantidad, periodos, cuota, saldoPendiente, cuotasRestantes, interesAnual, moneda,tipo) VALUES (?, ?, ?, ?, ?, ?, ?, ?,?)"));

        //ingresamos los datos
        pstmt->setInt(1, cedula); // Ejemplo de cédula
        pstmt->setDouble(2, cantidad); // Ejemplo de cantidad
        pstmt->setInt(3, periodos); // Ejemplo de periodos
        pstmt->setDouble(4, Cuota); // Ejemplo de cuota
        pstmt->setDouble(5, cantidad); // Ejemplo de saldo pendiente
        pstmt->setInt(6, periodos); // Ejemplo de cuotas restantes
        pstmt->setDouble(7, tasaInteresAnual); // Ejemplo de interés anual
        pstmt->setString(8, "CRC"); // Ejemplo de moneda
        pstmt->setString(9, tipo); //tipo de prestamo
        //actualizamos la tabla
        pstmt->executeUpdate();

        //nos falta agregar esa cantidad de plata a nuestras cuentas ojo

        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt2->setDouble(1, cantidad); // Nuevo saldo
        pstmt2->setInt(2, cedula); // Cédula del cliente
        pstmt2->executeUpdate();

        //registramos la transaccion

        registroColones(cedula, cantidad, "Deposito_Prestamo");

        cout << "\n" << endl;
        cout << endl;
        cout << endl;
        cout << "******************************" << endl;
        cout << "Prestamo Aprobado con Exito..." << endl;
        cout << "******************************" << endl;


    }
    //insertamos en tabla de prestamos de dolares
    else
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO prestamo_Dolares(cedula, cantidad, periodos, cuota, saldoPendiente, cuotasRestantes, interesAnual, moneda,tipo) VALUES (?, ?, ?, ?, ?, ?, ?, ?,?)"));

        //ingresamos los datos
        pstmt->setInt(1, cedula); // Ejemplo de cédula
        pstmt->setDouble(2, cantidad); // Ejemplo de cantidad
        pstmt->setInt(3, periodos); // Ejemplo de periodos
        pstmt->setDouble(4, Cuota); // Ejemplo de cuota
        pstmt->setDouble(5, cantidad); // Ejemplo de saldo pendiente
        pstmt->setInt(6, periodos); // Ejemplo de cuotas restantes
        pstmt->setDouble(7, tasaInteresAnual); // Ejemplo de interés anual
        pstmt->setString(8, "USD"); // Ejemplo de moneda
        pstmt->setString(9, tipo); //tipo de prestamo
        //actualizamos la tabla
        pstmt->executeUpdate();




        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt2->setDouble(1, cantidad); // Nuevo saldo
        pstmt2->setInt(2, cedula); // Cédula del cliente
        pstmt2->executeUpdate();

        //registramos la transaccion

        registroDolares(cedula, cantidad, "Deposito_Prestamo");
        cout << endl;
        cout << endl;
        cout << "******************************" << endl;
        cout << "Prestamo Aprobado con Exito..." << endl;
        cout << "******************************" << endl;
    }


    //hasta aqui ya hemos ingresado los datos de las tablas para pedir un prestamo   
}

//en las funciones de pagar prestamo , pueden ser pagarlos en efectivo o pagarlos con su propia cuenta 
//hay que tomar en cuenta esto
//Ademas manejo de excepciones por aca si el usuario no tiene mas fondos para poder pagarlos
void pagarPrestamoColones(string tipo) {
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Pagar Prestamo*************" << endl;
    cout << "************Colones**************" << endl;

    //solo nos fijaremos en la tabla de prestamos colones
    int cedula;
    bool efectivo;
    string eleccion;
    //si es falso se pagara con la cuenta que tenga asociada al banco 

    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado

    //implementar excepciones aqui
    cout << " \n Pagara con Efectivo (Y o N): ";
    cin >> eleccion;

    if (eleccion == "Y" || eleccion == "y") {
        efectivo = true;
    }
    else {
        efectivo = false;
    }

    //ya sabiendo que pagara con efectivo aplicaremos otro condicional

    if (efectivo == true) {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE prestamo_Colones SET saldoPendiente = saldoPendiente - cuota , cuotasRestantes = cuotasRestantes -1  WHERE cedula = ? AND tipo = ?"));


        pstmt->setInt(1, cedula); // Cédula específica
        pstmt->setString(2, tipo); // Tipo específico
        pstmt->executeUpdate();//actualizamos

        cout << "\n";
        cout << "Pago en Efectivo Realizado con exito ..." << endl;

        //Pagar en efectivo funciona de maravilla


    }
    else {
        //hay que obtener el valor de la cuota del prestamo y almacenarlo en una variable

        float cuotaRebajo = obtenerCuotaColones(cedula, tipo);



        //hay que buscar la cuenta de la persona en colones y quitarle la plata y hacerle este toque de arriba 
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));


        // Establece los valores de los parámetros
        pstmt->setDouble(1, cuotaRebajo); // lo que le vamos a restar del saldo
        pstmt->setInt(2, cedula); // cedula de la persona
        pstmt->executeUpdate();

        //aqui cuando ya pago
        std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE prestamo_Colones SET saldoPendiente = saldoPendiente - cuota , cuotasRestantes = cuotasRestantes -1  WHERE cedula = ? AND tipo = ?"));

        // Configurar los valores que deseas actualizar
        //pstmt->setDouble(1, cuota); // Nuevo saldo pendiente
        //las condiciones para hacer el update
        pstmt2->setInt(1, cedula); // Cédula específica
        pstmt2->setString(2, tipo); // Tipo específico
        pstmt2->executeUpdate();//actualizamos
        cout << endl;
        cout << "Pago Realizado con exito ..." << endl;
        //registramos la transaccion

        registroColones(cedula, cuotaRebajo, "RETIRO");
    }

}

void pagarPrestamoDolares(string tipo) {
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Pagar Prestamo*************" << endl;
    cout << "************Dolares**************" << endl;

    //solo nos fijaremos en la tabla de prestamos dolares
    int cedula;
    bool efectivo;
    string eleccion;
    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    //si es falso se pagara con la cuenta que tenga asociada al banco 

    //implementar excepciones aqui
    cout << " \n Pagara con Efectivo (Y o N): ";
    cin >> eleccion;

    if (eleccion == "Y" || eleccion == "y") {
        efectivo = true;
    }
    else {
        efectivo = false;
    }

    //ya sabiendo que pagara con efectivo aplicaremos otro condicional

    if (efectivo == true) {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE prestamo_Dolares SET saldoPendiente = saldoPendiente - cuota , cuotasRestantes = cuotasRestantes - 1  WHERE cedula = ? AND tipo = ?"));

        // Configurar los valores que deseas actualizar
        //pstmt->setDouble(1, cuota); // Nuevo saldo pendiente
        //las condiciones para hacer el update
        pstmt->setInt(1, cedula); // Cédula específica
        pstmt->setString(2, tipo); // Tipo específico
        pstmt->executeUpdate();//actualizamos

        cout << "\n";
        cout << "Pago en Efectivo Realizado con exito ..." << endl;
    }
    else {

        //hay que obtener el valor de la cuota del prestamo y almacenarlo en una variable

        float cuotaRebajo = obtenerCuotaDolares(cedula, tipo);



        //hay que buscar la cuenta de la persona en colones y quitarle la plata y hacerle este toque de arriba 
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo - ? WHERE cedula = ?"));


        // Establece los valores de los parámetros
        pstmt->setDouble(1, cuotaRebajo); // lo que le vamos a restar del saldo
        pstmt->setInt(2, cedula); // cedula de la persona
        pstmt->executeUpdate();

        //aqui cuando ya pago
        std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE prestamo_Dolares SET saldoPendiente = saldoPendiente - cuota , cuotasRestantes = cuotasRestantes -1  WHERE cedula = ? AND tipo = ?"));

        // Configurar los valores que deseas actualizar
        //pstmt->setDouble(1, cuota); // Nuevo saldo pendiente
        //las condiciones para hacer el update
        pstmt2->setInt(1, cedula); // Cédula específica
        pstmt2->setString(2, tipo); // Tipo específico
        pstmt2->executeUpdate();//actualizamos

        cout << endl;
        cout << "Pago Realizado con exito ..." << endl;
        //registro de la transaccion

        registroDolares(cedula, cuotaRebajo, "RETIRO");
    }


}

//genera un informe del estado del prestamo
//literal es un read en la base de datos
//solo ocupamos el nombre
void generarInforme(string moneda) {
    cout << endl;
    cout << endl;
    cout << "*************************************" << endl;
    cout << "*********Generar Informe*************" << endl;
    cout << "*************************************" << endl;
    cout << endl;
    cout << endl;

    int cedula;
    string cedulaString;

    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado

    cedulaString = to_string(cedula); // Guardar la cedula en un string para el nombre del .txt


    toUpperCase(moneda);

    try {
        // Ejecutar el query
        if (moneda == "CRC") {
            unique_ptr<PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM registroColones WHERE cedula = ?"));
            pstmt->setInt(1, cedula);
            res = pstmt->executeQuery();
        }
        else {
            unique_ptr<PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM registroDolares WHERE cedula = ?"));
            pstmt->setInt(1, cedula);
            res = pstmt->executeQuery();
        }

        // Verificar si la cédula existe en la base de datos
        if (!res->next()) {
            cerr << "Error: La cedula ingresada no existe en la base de datos." << endl;
            return;
        }

        // Ahora se guardan los resultado en un archivo de texto
        ofstream outFile(cedulaString + "_" + moneda + ".txt");

        if (outFile.is_open()) {
            // Columnas del archivo

            outFile << "----------------------"
                << "------------------------"
                << "-------------------------"
                << "--------------------------"
                << "-------------------------" << endl;

            outFile << "ID \t|\t CEDULA \t|\t  CANTIDAD \t|\t ESTADO \t|\t FECHA " << endl;

            outFile << "----------------------"
                << "------------------------"
                << "-------------------------"
                << "--------------------------"
                << "-------------------------" << endl;

            // Hacer escrituras
            while (res->next()) {
                outFile << res->getInt("id") << "\t"
                    << "|" << res->getInt("cedula") << "\t" << "\t"
                    << "|" << res->getDouble("cantidad") << "\t" << "\t" << "\t"
                    << "|" << res->getString("estado") << '\t' << "\t"
                    << "|" << res->getString("fecha") << endl;

                outFile << "----------------------"
                    << "------------------------"
                    << "-------------------------"
                    << "--------------------------"
                    << "-------------------------" << endl;
            }

            outFile.close();
            cout << endl;
            cout << "--------------------------------------------------------------------------------------------" << endl;
            cout << "Las transacciones se han escrito al archivo " << cedulaString + "_" + moneda << ".txt" << endl;
            cout << "--------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }
        else {
            cerr << "No se pudo abrir el archivo " << cedulaString + moneda << " para hacer escrituras." << endl;
        }
    }
    catch (SQLException& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void generarInformePrestamo(string tipo) {
    cout << endl;
    cout << endl;
    cout << "*************************************" << endl;
    cout << "*********Generar Informe Prestamo*************" << endl;
    cout << "*************************************" << endl;
    cout << endl;
    cout << endl;

    int cedula;
    string cedulaString, moneda;
    int periodosA;
    int cuotasRest{};
    float cuotav{};
    float cantidadRe;

    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    cout << endl;
    cout << "Por favor introducir la moneda (CRC o USD): ";
    cin >> moneda;

    cedulaString = to_string(cedula); // Guardar la cedula en un string para el nombre del .txt


    toUpperCase(moneda);

    // Ejecutar el query
    if (moneda == "CRC" || moneda == "crc") {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM prestamo_Colones WHERE cedula = ? and tipo = ?"));
        pstmt->setInt(1, cedula);
        pstmt->setString(2, tipo);
        res = pstmt->executeQuery();
    }
    else {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM prestamo_Dolares WHERE cedula = ? and tipo = ?"));
        pstmt->setInt(1, cedula);
        pstmt->setString(2, tipo);
        res = pstmt->executeQuery();
    }

    // Ahora se guardan los resultado en un archivo de texto
    ofstream outFile(cedulaString + "_" + tipo + ".txt");

    if (outFile.is_open()) {
        // Columnas del archivo

        outFile << "----------------------"
            << "------------------------"
            << "-------------------------"
            << "--------------------------"
            << "--------------------------" << std::endl;

        outFile << "CEDULA \t   | CANTIDAD \t |  PERIODOS \t |  CUOTA \t |  SALDO_PENDIENTE \t |  Cuotas_Restantes \t |  Interes_anual | Tipo" << endl;

        outFile << "----------------------"
            << "------------------------"
            << "-------------------------"
            << "--------------------------"
            << "--------------------------" << std::endl;

        // Hacer escrituras
        while (res->next()) {
            outFile
                << "|" << res->getInt("cedula") << "   "
                << "|" << res->getDouble("cantidad") << "\t  "
                << "|" << res->getInt("periodos") << '\t' << "\t "
                << "|" << res->getDouble("cuota") << "\t "
                << "|" << res->getDouble("saldoPendiente") << "\t" << "\t "
                << "|" << res->getInt("cuotasRestantes") << "\t" << "\t" << "\t "
                << "|" << res->getDouble("interesAnual") << "\t  "
                << "|" << res->getString("tipo") << endl;

            outFile << "----------------------"
                << "------------------------"
                << "-------------------------"
                << "--------------------------"
                << "--------------------------" << endl;

            periodosA = res->getInt("periodos");
            cuotasRest = res->getInt("cuotasRestantes");
            cuotav = res->getInt("cuota");
            cantidadRe = res->getDouble("saldoPendiente");

        }
        int cuotasMomento = periodosA - cuotasRest;
        float valorPagado = cuotasMomento * cuotav;

        //aqui agregamos algo de informacion general
        outFile << endl << endl;
        outFile << "-----------------------------------" << endl;
        outFile << "Cuotas Pagadas hasta el momento: " << cuotasMomento << endl;
        outFile << "-----------------------------------" << endl;
        outFile << "Dinero abonado hasta el momento: " << valorPagado << endl;
        outFile << "-----------------------------------" << endl;
        outFile << "Cantidad de dinero pendiente a pagar: " << cantidadRe << endl;
        outFile << "-----------------------------------" << endl;

        outFile.close();
        cout << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
        cout << "Las transacciones se han escrito al archivo " << cedulaString + "_" + tipo
            << ".txt" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
        cout << endl;
    }
    else {
        cerr << "No se pudo abrir el archivo " << cedulaString + moneda << " para hacer escrituras." << endl;
    }
}

tm calcularFechaActual() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm now_tm;
    localtime_s(&now_tm, &now_time);
    now_tm.tm_hour = 0;
    now_tm.tm_min = 0;
    now_tm.tm_sec = 0;
    return now_tm;
}

tm calcularFechaFinal(tm fechaInicio, int months) {
    tm fechaFinal = fechaInicio;
    fechaFinal.tm_mon += months;
    mktime(&fechaFinal);
    return fechaFinal;
}

string formatearFecha(tm fecha) {
    ostringstream oss;
    oss << put_time(&fecha, "%Y-%m-%d");
    return oss.str();
}

// Funcion para manejar el CDP
void certificadoDP() {
    int cedula;
    int meses;
    double monto, tasaInteres;
    string moneda, opcion, fechaInicioStr, fechaVencimientoStr;

    cout << endl;
    cout << endl;
    cout << "********************************" << endl;
    cout << "************ CDP ***************" << endl;
    cout << "********************************" << endl;

    cout << "\n(Certificado de deposito a plazo): ";
    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    cout << "\nPor favor ingresa la cantidad de meses que desea para el CDP: ";
    cin >> meses;
    cout << "\nPor favor ingresa la moneda: ";
    cin >> moneda;
    cout << "\nPor favor ingrese el monto inicial: ";
    cin >> monto;

    if (0 < meses && meses <= 2) {
        tasaInteres = 1.05;
    }
    else if (3 <= meses && meses < 6) {
        tasaInteres = 1.25;
    }
    else if (6 <= meses) {
        tasaInteres = 1.50;
    }
    else {
        cout << "Meses ingresado no valido." << endl; // Manejar este error
    }

    // Calculos de ganancia
    double tasaMensual = tasaInteres / 12;
    double gananciaInteres = monto * tasaMensual * meses;
    double ganancia = gananciaInteres + monto;

    cout << endl;
    cout << endl;
    cout << "Para " << meses << ", con un monto de " << monto << ", a una tasa de " << tasaInteres << ", va a tener una ganancia de " << ganancia << "." << endl;

    // Implementar esto por si el usuario quiere cancelar
    // cout << "\n Desea continuar (y/n)? (Este proceso es irreversible)" << endl;
    // cin >> opcion;

    std::tm fecha_inicio = calcularFechaActual();
    std::tm fecha_vencimiento = calcularFechaFinal(fecha_inicio, meses);

    // Pasar fechas de formato date a string
    fechaInicioStr = formatearFecha(fecha_inicio);
    fechaVencimientoStr = formatearFecha(fecha_vencimiento);

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO CertificadoDeposito(cedula, monto, moneda, tasaInteres, meses, fecha_inicio, fecha_vencimiento) VALUES (?, ?, ?, ?, ?, ?, ?)"));

    pstmt->setInt(1, cedula);
    pstmt->setDouble(2, monto);
    pstmt->setString(3, moneda);
    pstmt->setDouble(4, tasaInteres);
    pstmt->setInt(5, meses);
    pstmt->setString(6, fechaInicioStr);
    pstmt->setString(7, fechaVencimientoStr);

    // Actualizar valores de la cuenta del cliente
    if (moneda == "CRC" || moneda == "crc") {

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los par�metros
        pstmt->setDouble(1, monto); // Restar cantidad del CDP (colones)
        pstmt->setInt(2, cedula); // C�dula del cliente
        pstmt->executeUpdate();

        cout << "Su proceso de CDP (en colones) se ha realizado de forma correcta." << endl;


        //agregar el registro en colones

        registroColones(cedula, monto, "CDP");
    }
    else
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los par�metros
        pstmt->setDouble(1, monto); // Restar cantidad del CDP (dolares)
        pstmt->setInt(2, cedula); // C�dula del cliente
        pstmt->executeUpdate();

        cout << "Su proceso de CDP (en dolares) se ha realizado de forma correcta." << endl;

        //agregar el registro en Dolares
        registroDolares(cedula, monto, "CDP");
    }

    pstmt->executeUpdate();
}




#endif
