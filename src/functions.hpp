#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <iostream>
using namespace std;


// create a standard objects for sql tables :)
//estructura general de un cliente, para su creacion en la base de datos
//recordar que ya subido cualquier objeto de aca a la base de datos
//es posible modificar valores con las operaciones CRUD

class cliente{
    private:
        string cedula;
        string nombre;
        string apellido1;
        string apellido2;
        string provincia;
        string telefono;
        //con correo podemos usar regex para dar correos validos
        string correo;
        
};

//cuenta colones
class cuentaColones{
    private:
        string cedula;
        float saldo;
};

//cuenta dolares
class cuentaDolares{
    private:
        string cedula;
        float saldo;
};

//el atributo de moneda puede ser 
//CRC
//USD
class prestamo{
    private:
        string cedula;
        //periodos hablamos de years
        int periodos;
        //cuota por mes
        int cuotas;
        string moneda;
        float saldo;
        //hablamos de intereses , segun el tipo de prestamo
        //seran ingresados manualmente segun el tipo de interes sera calculado por una funcion
        float intereses;




};

//Agregar funciones para crear usuarios y prestamos y cuentas, para solo llamarlas en los menus


//Empezamos con las funciones de cuentas colones y dolares

void depositar(string identificacion,float cantidad){
    cout << " Depositar la cantidad de dinero" << endl;
};

void retirar(string identificaion,float cantidad){
    cout << " retirar la cantidad de dinero" << endl;
};

void transferir(string identificaion,float cantidad){
    cout << " transferir a otra cuenta  la cantidad de dinero" << endl;
};


//este registro puede ser un registro de todas las transacciones que se hayan realizado en el bancopueden haber 2 
//una tabla de registros para cuenta colones
//una tabla de registros para cuenta dolares
void registroColones(string cedula){
    cout << " Registro de todas las transacciones en colones" << endl;
}

void registroDolares(string cedula){
    cout << " Registro de todas las transacciones en Dolares" << endl;
}

//funciones para los prestamos

//crear un prestamo
void sacarPrestamo(prestamo prestamos){
    cout << "Sacar un prestamo" << endl;
}

void pagarPrestamoColones(string cedula,float cantidad){
    cout << "pagar  un prestamo en colones" << endl;
}

void pagarPrestamoDolares(string cedula,float cantidad){
    cout << "pagar  un prestamo en Dolares" << endl;
}

//genera un informe del estado del prestamo
//literal es un read en la base de datos
//solo ocupamos el nombre

void generarInforme(string identificacion, string moneda){
    cout << "generar informe  de un prestamo teniendo en cuenta identificacion y  moneda" << endl;
}

#endif