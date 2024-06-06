#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <iostream>
#include <format>
//Libreria de sql
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>



using namespace std;
using namespace sql;



// create a standard objects for sql tables :)
//estructura general de un cliente, para su creacion en la base de datos
//recordar que ya subido cualquier objeto de aca a la base de datos
//es posible modificar valores con las operaciones CRUD

//declaramos las variables globales
sql::mysql::MySQL_Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;


void connectDB(){
    try
    {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://localhost:3306","root","123.Chris001");
        // seleccionamos nuestra base de datos
        con->setSchema("<prueba>");

    if (con)
    {
        cout << "Nos hemos conectado exitosamente a la base de datos ... \n" << endl;
    }

    else
    {
        cout << "No hemos podidos conectarnos  a la base de datos :( ... \n" << endl;
    }
    }
    catch(sql::SQLException &e)
    {
        cout << "# Err: SQLexception in : " << __FILE__ << endl;
        cout << "(MySql error code :)" << e.getErrorCode() << endl;
        cout << "SQLstate :" << e.getSQLState() << endl;
    }
    
    
};

class Cliente{
    private:
        string cedula;
        string nombre;
        string apellido1;
        string apellido2;
        string provincia;
        string telefono;
        //con correo podemos usar regex para dar correos validos
        string correo;
        
    public:
        //inicializador
        Cliente (){};
        void setCedula(string cedula) { this->cedula = cedula; }
        void setNombre(string nombre) { this->nombre = nombre; }
        void setApellido1(string apellido1) { this->apellido1 = apellido1; }
        void setApellido2(string apellido2) { this->apellido2 = apellido2; }
        void setProvincia(string provincia) { this->provincia = provincia; }
        void setTelefono(string telefono) { this->telefono = telefono; }
        void setCorreo(string correo) { this->correo = correo; }

        // Getters
        string getCedula() { return cedula; }
        string getNombre() { return nombre; }
        string getApellido1() { return apellido1; }
        string getApellido2() { return apellido2; }
        string getProvincia() { return provincia; }
        string getTelefono() { return telefono; }
        string getCorreo() { return correo; }

};

//cuenta colones
class cuentaColones{
    private:
        string cedula;
        float saldo;
    public:
        // Constructor por defecto
        cuentaColones(){}

        // Setters
        void setCedula(string& nuevaCedula) {
            cedula = nuevaCedula;
        }

        void setSaldo(float nuevoSaldo) {
            saldo = nuevoSaldo;
        }

        // Getters
        string getCedula(){
            return cedula;
        }

        float getSaldo(){
            return saldo;
        }
};

//cuenta dolares
class cuentaDolares{
    private:
        string cedula;
        float saldo;
    public:
        // Constructor por defecto
        cuentaDolares() : cedula(""), saldo(0.0f) {}

        // Setters
        void setCedula(const string& nuevaCedula) {
            cedula = nuevaCedula;
        }

        void setSaldo(float nuevoSaldo) {
            saldo = nuevoSaldo;
        }

        // Getters
        string getCedula() const {
            return cedula;
        }

        float getSaldo() const {
            return saldo;
        }
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
    public:
        // Constructor por defecto
        prestamo() : cedula(""), periodos(0), cuotas(0), moneda(""), saldo(0.0f), intereses(0.0f) {}

        // Setters
        void setCedula(const string& nuevaCedula) {
            cedula = nuevaCedula;
        }

        void setPeriodos(int nuevosPeriodos) {
            periodos = nuevosPeriodos;
        }

        void setCuotas(int nuevasCuotas) {
            cuotas = nuevasCuotas;
        }

        void setMoneda(const string& nuevaMoneda) {
            moneda = nuevaMoneda;
        }

        void setSaldo(float nuevoSaldo) {
            saldo = nuevoSaldo;
        }

        void setIntereses(float nuevosIntereses) {
            intereses = nuevosIntereses;
        }

        // Getters
        string getCedula() const {
            return cedula;
        }

        int getPeriodos() const {
            return periodos;
        }

        int getCuotas() const {
            return cuotas;
        }

        string getMoneda() const {
            return moneda;
        }

        float getSaldo() const {
            return saldo;
        }

        float getIntereses() const {
            return intereses;
        }
};

//Agregar funciones para crear usuarios y prestamos y cuentas, para solo llamarlas en los menus

void crear_usuario(Cliente& usuario){
    //objeto usuario de tipo cliente
    Cliente* usuario;
    //ocupamos variables locales para luego almacenar con setter
    string nombre;
    string cedula;
    string apellido1;
    string apellido2;
    string Provincia;
    string telefono;
    string correo;

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

    //teniendo esto asignamos con los setterns

    usuario.setApellido1(apellido1);
    usuario.setApellido2(apellido2);
    usuario.setCedula(cedula);
    usuario.setCorreo(correo);
    usuario.setNombre(nombre);
    usuario.setProvincia(Provincia);
    usuario.setTelefono(telefono);

    //ahora tenemos que subir dichos valores a la base de datos con los getters

    //unique_ptr<sql::PreparedStatement> psmt(con->prepareStatement("INSERT INTO <prueba> (cedula,nombre,apellido1,apellido2,provincia,telefono,correo) VALUES (?,?,?,?,?,?,?)"));
    string query = std::format("INSERT INTO <prueba> (cedula,nombre,apellido1,apellido2,provincia,telefono,correo) VALUES ({},{},{},{},{},{},{})",usuario.getCedula(),usuario.getNombre(),usuario.getApellido1(),usuario.getApellido2(),usuario.getProvincia(),usuario.getTelefono(),usuario.getCorreo());
    stmt = con->createStatement();
    stmt ->execute(query);
    //se ejecuta el query ...
    cout << "Se agrego el usuario de forma exitosa .... " << endl;  
};

void crearCuentaColones(cuentaColones* cuenta){
    cuentaColones cuenta;
    string cedula;
    float saldo;

    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa el saldo inicial a depositar en colones: ";
    cin >> saldo;

    cuenta->setCedula(cedula);
    cuenta->setSaldo(saldo);
    //lamada a bases de datos INSERT
    
    string query = std::format("INSERT INTO <prueba> (cedula,saldo) VALUES ({},{})", cuenta->getCedula(),cuenta->getSaldo());
    stmt = con->createStatement();
    stmt ->execute(query);
    //se ejecuta el query ...
    cout << "Se agrego la cuenta de colones forma exitosa .... " << endl;
};


void crearCuentaDolares(cuentaDolares* cuenta){
    cuentaDolares cuenta;
    
    string cedula;
    float saldo;

    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa el saldo inicial a depositar en dolares: ";
    cin >> saldo;

    //lamada a bases de datos INSERT
    cuenta->setCedula(cedula);
    cuenta->setSaldo(saldo);
    //lamada a bases de datos INSERT
    
    string query = std::format("INSERT INTO <nombre_tabla> (cedula,saldo) VALUES ({},{})", cuenta->getCedula(),cuenta->getSaldo());
    stmt = con->createStatement();
    stmt ->execute(query);
    //se ejecuta el query ...
    cout << "Se agrego la cuenta de dolares de  forma exitosa .... " << endl;
};

//Empezamos con las funciones de cuentas colones y dolares

void depositar(){
    
    string cedula;
    float deposito;
    string moneda;

    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa la cantidad a depositar: ";
    cin >> deposito;
    cout << "\n Por favor ingresa la moneda: ";
    cin >> moneda;
    

    //llamada a la base de datos
    //sera un update
    if (moneda == "CRC"){
    string query = std::format("UPDATE <cuentas_colones> SET saldo = saldo + {} WHERE cedula = {}", deposito,cedula);
    stmt = con->createStatement();
    stmt ->execute(query);
    //se ejecuta el query ...
    cout << "Se agrego el dep[osito  de  forma exitosa .... " << endl;
    }else
    {
    string query = std::format("UPDATE <cuentas_dolares> SET saldo = saldo + {} WHERE cedula = {}", deposito,cedula);
    stmt = con->createStatement();
    stmt ->execute(query);
    //se ejecuta el query ...
    cout << "Se agrego el dep[osito  de  forma exitosa .... " << endl;
    }
    
    //registro de las transacciones

    if (moneda == "CRC")
    {
        registroColones( cedula, deposito, "DEPOSITO");
    }
    else
    {
        registroDolares(cedula, deposito, "DEPOSITO");
    }
    
    
};

//Pendiente: crear excepcion para que solo puedan ingresar monedas USD Y CRC
void retirar(){
    
    string cedula;
    float retiro;
    string moneda;

    cout << "Por favor ingresa la cedula: ";
    cin >> cedula;
    cout << "\n Por favor ingresa la cantidad a retirar: ";
    cin >> retiro;
    cout << "\n Por favor ingresa la moneda: ";
    cin >> moneda;

    //llamada a la base de datos
    //sera un update
    if (moneda == "CRC"){
    string query = std::format("UPDATE <cuentas_colones> SET saldo = saldo - {} WHERE cedula = {}", retiro,cedula);
    stmt = con->createStatement();
    stmt ->execute(query);
    //se ejecuta el query ...
    cout << "Se retiro el dinero  de forma exitosa.... " << endl;
    }else{
    string query = std::format("UPDATE <cuentas_dolares> SET saldo = saldo - {} WHERE cedula = {}", retiro,cedula);
    stmt = con->createStatement();
    stmt ->execute(query);
    //se ejecuta el query ...
    cout << "Se retiro el dinero  de forma exitosa.... " << endl;
    }

    if (moneda == "CRC")
    {
        registroColones( cedula, retiro, "RETIRO");
    }
    else
    {
        registroDolares(cedula, retiro, "RETIRO");
    }
};

void transferir(){
    //esta es una mezcla de las funciones retirar y depositar

    string depositante;
    float cantidad;
    string destinatario;
    string moneda;

    cout << "Por favor ingresa la cedula depositante: ";
    cin >> depositante;
    cout << "\n Por favor ingresa la cantidad a transferir: ";
    cin >> cantidad;
    cout << "\n Por favor ingresa la cedula del destinatario: ";
    cin >> destinatario;
    cout << "\n Por favor ingresa la moneda: ";
    cin >> moneda;

    if (moneda == "CRC"){
    string query = std::format("UPDATE <cuentas_colones> SET saldo = saldo - {} WHERE cedula = {}", cantidad,depositante);
    stmt = con->createStatement();
    stmt ->execute(query);


    string query2 = std::format("UPDATE <cuentas_colones> SET saldo = saldo + {} WHERE cedula = {}", cantidad,destinatario);
    stmt = con->createStatement();
    stmt ->execute(query2);
    cout << "Se Realizo la transferencia de forma exitosa.... " << endl;
    }else
    {
     string query = std::format("UPDATE <cuentas_dolares> SET saldo = saldo - {} WHERE cedula = {}", cantidad,depositante);
    stmt = con->createStatement();
    stmt ->execute(query);


    string query2 = std::format("UPDATE <cuentas_dolares> SET saldo = saldo + {} WHERE cedula = {}", cantidad,destinatario);
    stmt = con->createStatement();
    stmt ->execute(query2);
    cout << "Se Realizo la transferencia de forma exitosa.... " << endl;
    }
    
    //registro de transacciones
    if (moneda == "CRC")
    {
        registroColones( depositante, cantidad, "RETIRO");
        registroColones( destinatario, cantidad, "DEPOSITO");
    }
    else
    {
        registroDolares( depositante, cantidad, "RETIRO");
        registroColones( destinatario, cantidad, "DEPOSITO");
    }
};


//este registro puede ser un registro de todas las transacciones que se hayan realizado en el bancopueden haber 2 
//una tabla de registros para cuenta colones
//una tabla de registros para cuenta dolares
void registroColones(string cedula, float cantidad, string estado){
    
    string query = std::format("INSERT INTO <tabla_registro_colones> (cedula,cantidad,estado) VALUES ({},{},{})",cedula,cantidad,estado );
    stmt = con->createStatement();
    stmt ->execute(query);
}

void registroDolares(string cedula, float cantidad, string estado){
    
    string query = std::format("INSERT INTO <tabla_registro_dolares> (cedula,cantidad,estado) VALUES ({},{},{})",cedula,cantidad,estado );
    stmt = con->createStatement();
    stmt ->execute(query);
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