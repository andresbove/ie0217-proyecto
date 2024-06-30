/**
 * @file header.hpp
 * Aqui es donde van los prototipos de las funciones.
*/
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


// Inicio de la importación de librerioas de SQL
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include <cppconn/prepared_statement.h>
// Fin de la importación de librerioas de SQL


using namespace std;
using namespace sql;


//structs


struct Cliente {
    int cedula; // Cédula debe ser única y no nula
    string nombre; // Nombre con un máximo de 50 caracteres
    string apellido1; // Primer apellido con un máximo de 50 caracteres
    string apellido2; // Segundo apellido con un máximo de 50 caracteres
    string provincia; // Provincia con un máximo de 50 caracteres
    string telefono; // Teléfono con un máximo de 20 caracteres
    string correo; // Correo con un máximo de 50 caracteres
};

struct Prestamo {
    int cedula; // Cédula del cliente
    float cantidad; // Cantidad del préstamo
    int periodos; // Número de periodos de pago
    float cuota; // Monto de la cuota de pago
    float saldoPendiente; // Saldo pendiente del préstamo
    int cuotasRestantes; // Número de cuotas restantes
    float interesAnual; // Tasa de interés anual
    string moneda; // Moneda, con un máximo de 10 caracteres
    string tipo; // Tipo de préstamo, con un máximo de 20 caracteres
};

struct CuentaCliente {
    int cedula; // Cédula del cliente, usada como clave foránea
    float saldo; // Saldo de la cuenta del cliente
};

struct Inversion {
    int cedula; // Cédula del cliente, usada como clave foránea
    double monto; // Monto de la inversión, DECIMAL(10, 2)
    string moneda; // Moneda, con un máximo de 10 caracteres
    double tasaInteres; // Tasa de interés, DECIMAL(5, 2)
    int meses; // Duración de la inversión en meses
    string fecha_inicio; // Fecha de inicio de la inversión
    string fecha_vencimiento; // Fecha de vencimiento de la inversión
};

//Inicio de Declaracion funciones
void menuPrincipal();
void menuAtencionCliente();
void menuInformacionPrestamos();
void menuSacarPrestamo();
void menuPagarPrestamo();
void menuDepositar();
void menuTransferir();
void menuRetirar();
void menuGenerarInforme();
void subMenuSacarPrestamo(const string& tipoPrestamo);
bool verificar_un_prestamo(string tipo, int cedula, string moneda);
bool verificar_un_cuenta(int cedula, string moneda);
int validarCedula();
bool validarDigitos(const std::string& str);
void registroColones(int cedula, float cantidad, string estado);
void registroDolares(int cedula, float cantidad, string estado);
bool verificarSaldoSuficiente(int cedula, float monto, const string& moneda);
bool verificarSaldotransferencia(int cedula, float monto, const string& moneda);
bool validarLetras(const string& str);
bool validarDigitos(const string& str);
bool validarFloat(const string& str);
void toUpperCase(string& palabra);
bool validarCorreo(const string& str);
float stringToFloat(const string& str);
float validarSaldo();
void connectDB();
void crear_usuario();
void crearCuentaColones();
void crearCuentaDolares();
void depositar(string moneda);
void retirar(string moneda);
void transferir(string moneda);
float calcularInteresSimple(float cantidadInicial, int years, float interesAnual);
float cuota(float cantidadInicial, float interesAnual, int periodos);
float obtenerCuotaColones(int cedula, string tipo);
float obtenerCuotaDolares(int cedula, string tipo);
void sacarPrestamo(string moneda, string tipo);
void pagarPrestamoColones(string tipo);
void pagarPrestamoDolares(string tipo);
void generarInforme(string moneda);
void generarInformePrestamo(string tipo);
tm calcularFechaActual();
tm calcularFechaFinal(tm fechaInicio, int months);
string formatearFecha(tm fecha);
void certificadoDP();
bool verificar_un_prestamo(string tipo, int cedula, string moneda);
bool verificar_un_cuenta(int cedula, string moneda);
void convertir_crc_to_usd_pago(float cuota, int cedula, int cantidad);
void convertir_usd_to_crc_pago(float cuota, int cedula, int cantidad);
int validarNumero();
int validarCedulaUsuario();
//Fin de Declaracion funciones



// create a standard objects for sql tables :)
//estructura general de un cliente, para su creacion en la base de datos
//recordar que ya subido cualquier objeto de aca a la base de datos
//es posible modificar valores con las operaciones CRUD

//declaramos las variables globales
sql::mysql::MySQL_Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::ResultSet* res;


/**
 * Calcula el interés compuesto a la hora de sacar un préstamo.
 * @param[in] cantidadInicial
 * @param[in] years
 * @param[in] interesAnual
 * @param[in] capitalizacion
 * @param[out] interes
*/
float calcularInteresCompuesto(float cantidadInicial, int years, float interesAnual, float capitalizacion = 1) {
    float interes = cantidadInicial * pow(1 + interesAnual / capitalizacion, years * capitalizacion);
    return interes;
}

#endif
