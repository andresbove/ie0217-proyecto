#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <iostream>
#include <format>

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
void connectDB() {
    try
    {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "123.Chris001");
        // seleccionamos nuestra base de datos
        con->setSchema("banco_data_base_2");

        if (con)
        {
            cout << "Nos hemos conectado exitosamente a la base de datos ... \n" << endl;
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
    

    cout << "***************************" << endl;
    cout << "*****Creando Usuario*****" << endl;
    cout << "***************************" << endl;



    cout << "Por favor ingresa el nombre: ";
    cin >> nombre;
    cout << "\n Por favor ingresa el cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa el primer apellido: ";
    cin >> apellido1;
    cout << "\n Por favor ingresa el segundo apellido: ";
    cin >> apellido2;
    cout << "\n Por favor ingresa la provincia: ";
    cin >> Provincia;
    cout << "\n Por favor ingresa el telefono: ";
    cin >> telefono;
    cout << "\n Por favor ingresa el correo: ";
    cin >> correo;

    


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
    cout << "Se agrego el usuario de forma exitosa .... " << endl;
};


void crearCuentaColones() {
    //cuentaColones cuenta;
    int cedula;
    float saldo;
    cout << "*********************************" << endl;
    cout << "*****Creando Cuenta Colones******" << endl;
    cout << "*********************************" << endl;

    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa el saldo inicial a depositar en colones: ";
    cin >> saldo;

  
    //lamada a bases de datos INSERT
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO cuentaColones (cedula, saldo) VALUES (?, ?)"));
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, saldo); // Saldo inicial

    // Ejecuta la declaración
    pstmt->executeUpdate();
    //se ejecuta el query ...
    cout << "Se agrego la cuenta de colones forma exitosa .... " << endl;
};


void crearCuentaDolares() {
    //cuentaDolares cuenta;
    cout << "*********************************" << endl;
    cout << "*****Creando Cuenta Dolares******" << endl;
    cout << "*********************************" << endl;
    int cedula;
    float saldo;
    cout << "Creando nueva cuenta en dolares" << endl;
    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa el saldo inicial a depositar en dolares: ";
    cin >> saldo;


    //lamada a bases de datos INSERT
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO cuentaDolares (cedula, saldo) VALUES (?, ?)"));
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, saldo); // Saldo inicial

    // Ejecuta la declaración
    pstmt->executeUpdate();
    cout << "Se agrego la cuenta de dolares de  forma exitosa .... " << endl;
};

//Empezamos con las funciones de cuentas colones y dolares

void depositar() {

    int cedula;
    float deposito;
    string moneda;

    cout << "*********************************" << endl;
    cout << "*********Depositando*************" << endl;
    cout << "*********************************" << endl;

    cout << "\n Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa la cantidad a depositar: ";
    cin >> deposito;
    cout << "\n Por favor ingresa la moneda: ";
    cin >> moneda;


    //llamada a la base de datos
    //sera un update
    if (moneda == "CRC") {
        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, deposito); // Nuevo saldo
        pstmt->setInt(2, cedula); // Cédula del cliente
        pstmt->executeUpdate();
        
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
void retirar() {

    int cedula;
    float retiro;
    string moneda;
    cout << "*********************************" << endl;
    cout << "*********Retirando*************" << endl;
    cout << "*********************************" << endl;

    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa la cantidad a retirar: ";
    cin >> retiro;
    cout << "\n Por favor ingresa la moneda: ";
    cin >> moneda;

    //llamada a la base de datos
    //sera un update
    if (moneda == "CRC") {
        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, retiro); // Nuevo saldo
        pstmt->setInt(2, cedula); // Cédula del cliente
        pstmt->executeUpdate();
        cout << "Se retiro el dinero  de forma exitosa.... " << endl;

    }
    else {
        // Prepara una declaración para actualizar el saldo
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, retiro); // Nuevo saldo
        pstmt->setInt(2, cedula); // Cédula del cliente
        pstmt->executeUpdate();
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

void transferir() {
    //esta es una mezcla de las funciones retirar y depositar

    int depositante;
    float cantidad;
    int destinatario;
    string moneda;

    cout << "*********************************" << endl;
    cout << "*********Transfiriendo*************" << endl;
    cout << "*********************************" << endl;

    cout << "Por favor ingresa la cedula depositante: ";
    cin >> depositante;
    cout << "\n Por favor ingresa la cantidad a transferir: ";
    cin >> cantidad;
    cout << "\n Por favor ingresa la cedula del destinatario: ";
    cin >> destinatario;
    cout << "\n Por favor ingresa la moneda: ";
    cin >> moneda;

    if (moneda == "CRC") {
    
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt->setDouble(1, cantidad); // Nuevo saldo
        pstmt->setInt(2, depositante); // Cédula del cliente
        pstmt->executeUpdate();

        std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo + ? WHERE cedula = ?"));

        // Establece los valores de los parámetros
        pstmt2->setDouble(1, cantidad); // Nuevo saldo
        pstmt2->setInt(2, destinatario); // Cédula del cliente
        pstmt2->executeUpdate();
        cout << "Se Realizo la transferencia de forma exitosa.... " << endl;
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
        cout << "Se Realizo la transferencia de forma exitosa.... " << endl;
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



//funciones para los prestamos
//funciones para los prestamos



//crear un prestamo
void sacarPrestamo() {
    cout << "Sacar un prestamo" << endl;
}

void pagarPrestamoColones(string cedula, float cantidad) {
    cout << "pagar  un prestamo en colones" << endl;
}

void pagarPrestamoDolares(string cedula, float cantidad) {
    cout << "pagar  un prestamo en Dolares" << endl;
}

//genera un informe del estado del prestamo
//literal es un read en la base de datos
//solo ocupamos el nombre

void generarInforme(string identificacion, string moneda) {
    cout << "generar informe  de un prestamo teniendo en cuenta identificacion y  moneda" << endl;
}

#endif