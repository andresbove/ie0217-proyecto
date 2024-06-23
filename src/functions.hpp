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


void toUpperCase(string &palabra) {
    transform(palabra.begin(), palabra.end(), palabra.begin(), [](unsigned char c) {return toupper(c);});
}
void connectDB() {
    try
    {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "123.Chris001");
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


    cout << "\n Por favor ingresa el cedula: ";
    cin >> cedula;
    cout << "Por favor ingresa el nombre: ";
    cin >> nombre;
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

void depositar(string moneda) {

    int cedula;
    float deposito;
    //string moneda;
    cout << endl;
    cout << endl;

    cout << "*********************************" << endl;
    cout << "*********Depositando*************" << endl;
    cout << "*********************************" << endl;

    cout << "\n Por favor ingresa la cedula: ";
    cin >> cedula;
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
    //string moneda;
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Retirando*************" << endl;
    cout << "*********************************" << endl;

    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa la cantidad a retirar: ";
    cin >> retiro;
    //cout << "\n Por favor ingresa la moneda: ";
    //cin >> moneda;

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
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

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
    //string moneda;

    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Transfiriendo*************" << endl;
    cout << "*********************************" << endl;

    cout << "Por favor ingresa la cedula depositante: ";
    cin >> depositante;
    cout << "\n Por favor ingresa la cantidad a transferir: ";
    cin >> cantidad;
    cout << "\n Por favor ingresa la cedula del destinatario: ";
    cin >> destinatario;
    //cout << "\n Por favor ingresa la moneda: ";
    //cin >> moneda;

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

float calcularInteresSimple(float cantidadInicial,int years,float interesAnual) {
    
    float interes = cantidadInicial * years * interesAnual;
    return interes;
}

float calcularInteresCompuesto(float cantidadInicial, int years, float interesAnual, float capitalizacion=1) {
    float interes = cantidadInicial*pow(1+interesAnual/capitalizacion,years*capitalizacion);
    return interes;
}

//*******************************************
//revisar estas formulas
//*******************************************


float cuota(float cantidadInicial, float interesAnual, int periodos) {
    float interesMensual = interesAnual / 12;
    float resultado = cantidadInicial*((interesMensual * pow(1 + interesMensual, periodos)) / pow(1 + interesMensual, periodos - 1));
    return resultado;
}


float obtenerCuotaColones(int cedula,string tipo) {
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
    cout << "\nPor favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\nPor favor ingresa la cantidad de dinero del prestamo: ";
    cin >> cantidad;
    cout << "\nPor favor ingresa los meses a los cuales sera el prestamo: ";
    cin >> periodos;
    cout << "\nPor favor ingresa la tasa interes anual del prestamo: ";
    cin >> tasaInteresAnual;


    tasaInteresAnual = tasaInteresAnual / 100; // para dejarla en terminos de 0 .. 1

    //sacaremos la cuota

    Cuota = cuota(cantidad,tasaInteresAnual,periodos);//ya calculamos la cuota que tienen que pagar con interes fijo

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

    cout << "Por favor introducir su numero de cedula: ";
    cin >> cedula;

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

        
    }else {
        //hay que obtener el valor de la cuota del prestamo y almacenarlo en una variable
        
        float cuotaRebajo = obtenerCuotaColones(cedula, tipo); 

        
        
        //hay que buscar la cuenta de la persona en colones y quitarle la plata y hacerle este toque de arriba 
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));


        // Establece los valores de los parámetros
        pstmt->setDouble(1,cuotaRebajo); // lo que le vamos a restar del saldo
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
    cout << "Por favor introducir su numero de cedula: ";
    cin >> cedula;
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

    cout << "Por favor introducir su numero de cedula: ";
    cin >> cedula;

    cedulaString = to_string(cedula); // Guardar la cedula en un string para el nombre del .txt


    toUpperCase(moneda);

    // Ejecutar el query
    if (moneda == "CRC") {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM registroColones WHERE cedula = ?"));
        pstmt->setInt(1, cedula);
        res = pstmt->executeQuery();
    }
    else {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM registroDolares WHERE cedula = ?"));
        pstmt->setInt(1, cedula);
        res = pstmt->executeQuery();
    }

    // Ahora se guardan los resultado en un archivo de texto
    ofstream outFile(cedulaString + "_" + moneda + ".txt");

    if (outFile.is_open()) {
        // Columnas del archivo

        outFile << "----------------------"
            << "------------------------"
            << "-------------------------"
            << "--------------------------"
            << "-------------------------" << std::endl;

        outFile << "ID \t|\t CEDULA \t|\t  CANTIDAD \t|\t ESTADO \t|\t FECHA " << endl;

        outFile << "----------------------"
            << "------------------------"
            << "-------------------------"
            << "--------------------------"
            << "-------------------------" << std::endl;

        // Hacer escrituras
        while (res->next()) {
            outFile  << res->getInt("id") << "\t"
                << "|" << res->getInt("cedula") << "\t" << "\t"
                << "|" << res->getDouble("cantidad") << "\t" << "\t" << "\t"
                << "|" << res->getString("estado") << '\t' << "\t" 
                << "|" << res->getString("fecha")  << std::endl;

            outFile <<"----------------------"
                 << "------------------------"
                <<"-------------------------" 
                <<"--------------------------" 
                << "-------------------------" << std::endl;
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
    // REVISAR implementar error si no se encuentra una cedula ingresada
}

void generarInformePrestamo() {
    cout << "Hola" << endl;
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

    cout << "\n Por favor ingresa la cedula  para el CDP: ";
    cin >> cedula;
    cout << "\n Por favor ingresa la cantidad de meses que desea para el CDP: ";
    cin >> meses;
    cout << "\n Por favor ingresa la moneda: ";
    cin >> moneda;
    cout << "\n Por favor ingrese el monto inicial: ";
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