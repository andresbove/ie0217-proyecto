#include "header.hpp"

/**
 * Funcion para validar la cédula ingresada por el usuario, que se espera que sean ints, ademas verifica que la
 * cedula esté en la base de datos (por esto no usar en crearUsuario).
*/


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

int validarNumero() {
    int numero;
    string cantidadCuotasString;

    do {
        cout << "cuantas cuotas deseas pagar: ";
        cin >> cantidadCuotasString;
        cout << endl;
        // Validar si input es valido
        if (!validarDigitos(cantidadCuotasString)) {
            cout << "Solo debe de contener nuemros.\n" << endl;
            continue;
        }

        // Convertir string a int
        numero = stoi(cantidadCuotasString);
        return numero;
        



    } while (true); // Continúa pidiendo cedula hasta que una válida sea ingresada
}

/**
 * Encargado de insertar los datos relacionados a la tabla de registroColones.
 * @param[in] cedula
 * @param[in] cantidad
 * @param[in] estado
*/
void registroColones(int cedula, float cantidad, string estado) {

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO registroColones (cedula, cantidad, estado) VALUES (?, ?, ?)"));
    // Establece los valores de los parámetros
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, cantidad); // Cantidad transferida
    pstmt->setString(3, estado); // Estado de la transferencia

    // Ejecuta la declaración
    pstmt->executeUpdate();
}


/**
 * Encargado de insertar los datos relacionados a la tabla de registroDolares.
 * @param[in] cedula
 * @param[in] cantidad
 * @param[in] estado
*/
void registroDolares(int cedula, float cantidad, string estado) {

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO registroDolares (cedula, cantidad, estado) VALUES (?, ?, ?)"));
    // Establece los valores de los parámetros
    pstmt->setInt(1, cedula); // Cédula del cliente
    pstmt->setDouble(2, cantidad); // Cantidad transferida
    pstmt->setString(3, estado); // Estado de la transferencia

    // Ejecuta la declaración
    pstmt->executeUpdate();
}


/**
 * Verifica que el saldo sea suficiente en los otros procesos, por ejemplo que el usuario no pueda retirar más de lo que tiene en la cuenta.
 * @param[in] cedula
 * @param[in] monto
 * @param[in] moneda
*/
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



/**
 * Verifica que se puedan hacer transferencias de forma correcta, por ejemplo que el usuario tenga la cantidad suficientes de fondos
 * para realizar una transferencia.
 * @param[in] cedula
 * @param[in] cantidad
 * @param[in] moneda
*/
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




/**
 * Determina si el saldo ingresado por el usuario es válido, es decir, que no ingrese letras o símbolos, solo números.
*/
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



/**
 * Encargado de conectarse a la base de datos.
*/
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



/**
 * Función que crea un usuario y lo registra en la base de datos después de consultar toda la información.
*/
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



/**
 * Función que crea una cuenta en colones y lo registra en la base de datos después de consultar toda la información.
*/
void crearCuentaColones() {
    //cuentaColones cuenta;
    int cedula;
    float saldo;
    bool verificacion;
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*****Creando Cuenta Colones******" << endl;
    cout << "*********************************" << endl;

    //cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado

    //cout << "Por favor ingresa la cedula: ";
    //cin >> cedula;

    //saldo = validarSaldo(); // Solicitar el saldo y verificar que el input sea correcto
    //cout << "\n Por favor ingresa el saldo inicial a depositar en colones: ";
    //cin >> saldo;
    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    saldo = validarSaldo(); // Solicitar el saldo y verificar que el input sea correcto

    verificacion = verificar_un_cuenta(cedula, "CRC");
    cout << "la salida es: " << verificacion << endl;

    //llamada a bases de datos INSERT
    if (!verificacion) {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO cuentaColones (cedula, saldo) VALUES (?, ?)"));
        pstmt->setInt(1, cedula); // Cédula del cliente
        pstmt->setDouble(2, saldo); // Saldo inicial

        // Ejecuta la declaración
        pstmt->executeUpdate();
        //se ejecuta el query ...
        cout << "Se agrego la cuenta de colones forma exitosa .... " << endl;
        cout << "\n";
    }
    else
    {
        cout << endl << endl;
        cout << "El cliente ya tiene  una cuenta de colones activa ...." << endl << endl;
    }

};



/**
 * Función que crea una cuenta en dólares y lo registra en la base de datos después de consultar toda la información.
*/
void crearCuentaDolares() {
    //cuentaDolares cuenta;
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*****Creando Cuenta Dolares******" << endl;
    cout << "*********************************" << endl;
    int cedula;
    float saldo;
    bool verificacion;
    //cout << "Por favor ingresa la cedula: ";
    //cin >> cedula;
    cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado
    saldo = validarSaldo(); // Solicitar el saldo y verificar que el input sea correcto
    //cout << "\n Por favor ingresa el saldo inicial a depositar en colones: ";
    //cin >> saldo;
    verificacion = verificar_un_cuenta(cedula, "USD");
    cout << "la salida es: " << verificacion << endl;
    //lamada a bases de datos INSERT
    if (verificacion == false) {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO cuentaDolares (cedula, saldo) VALUES (?, ?)"));
        pstmt->setInt(1, cedula); // Cédula del cliente
        pstmt->setDouble(2, saldo); // Saldo inicial

        // Ejecuta la declaración
        pstmt->executeUpdate();
        cout << "Se agrego la cuenta de dolares de  forma exitosa .... " << endl;
    }
    else
    {
        cout << endl << endl;
        cout << "El cliente ya tiene  una cuenta de dolares activa ...." << endl << endl;
    }

};



//Empezamos con las funciones de cuentas colones y dolares

/**
 * Permite que el usuario pueda realizar un depósito mediante el ingreso de la cédula y se encarga de hacer las modificaciones
 * correspondientes en la base de datos.
 * @param[in] moneda
*/
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
/**
 * Permite que el usuario pueda realizar un retiro mediante el ingreso de la cédula y se encarga de hacer las modificaciones
 * correspondientes en la base de datos.
 * @param[in] moneda
*/
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



/**
 * Permite que el usuario pueda realizar una transferencia mediante el ingreso de la cédula y se encarga de hacer las modificaciones
 * correspondientes en la base de datos.
 * @param[in] moneda
*/
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



/**
 * Calcula la fecha actual, esto para las transacciones en la base de datos
 * @param[out] now_tm
*/
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



/**
 * Calcula la fecha final, después de cierta cantidad de tiempo, esto para las fechas de finalización
 * del CDP
 * @param[out] fechaFinal
*/
tm calcularFechaFinal(tm fechaInicio, int months) {
    tm fechaFinal = fechaInicio;
    fechaFinal.tm_mon += months;
    mktime(&fechaFinal);
    return fechaFinal;
}


/**
 * Pasar la fechas de tm a string
*/
string formatearFecha(tm fecha) {
    ostringstream oss;
    oss << put_time(&fecha, "%Y-%m-%d");
    return oss.str();
}



/**
 * Hace los cálculos correspondientes para asignarle al usuario un CDP cuando lo solicita, para ello debe ingresar
 * su cédula y guarda los resultados de la transacción en la base de datos.
*/
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



/**
 * Verifica si un préstamo existe o no.
 * @param[in] tipo
 * @param[in] cedula
 * @param[in] moneda
 * @param[out] salida
*/
bool verificar_un_prestamo(string tipo, int cedula, string moneda) {
    //ejemplo
    if (moneda == "CRC" || moneda == "crc") {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT cuota FROM prestamo_Colones WHERE cedula=? AND tipo=?"));
        pstmt->setInt(1, cedula); // Cédula específica
        pstmt->setString(2, tipo); // Tipo específico

        // Ejecutar la consulta
        res = pstmt->executeQuery();
    }
    else {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT cuota FROM prestamo_Dolares WHERE cedula=? AND tipo=?"));
        pstmt->setInt(1, cedula); // Cédula específica
        pstmt->setString(2, tipo); // Tipo específico

        // Ejecutar la consulta
        res = pstmt->executeQuery();
    }


    //ahi obtenemos la respuesta

    float cuota;
    bool salida;

    // Verificar si se obtuvo un resultado
    if (res->next()) {

        salida = true;
    }
    else {
        salida = false;
    }
    //retorna 0 si es false
    //retorna 1 si es true
    return salida;
}



/**
 * Verifica si una cuenta existe o no.
 * @param[in] tipo
 * @param[in] cedula
 * @param[in] moneda
 * @param[out] salida
*/
bool verificar_un_cuenta(int cedula, string moneda) {
    //ejemplo
    if (moneda == "CRC" || moneda == "crc") {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT saldo FROM cuentaColones WHERE cedula=?"));
        pstmt->setInt(1, cedula); // Cédula específica

        // Ejecutar la consulta
        res = pstmt->executeQuery();
    }
    else {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT saldo FROM cuentaDolares WHERE cedula=?"));
        pstmt->setInt(1, cedula); // Cédula específica

        // Ejecutar la consulta
        res = pstmt->executeQuery();
    }


    //ahi obtenemos la respuesta


    bool salida;

    // Verificar si se obtuvo un resultado
    if (res->next()) {

        salida = true;// se obtuvo un resultado
    }
    else {
        salida = false;
    }
    //retorna 0 si es false
    //retorna 1 si es true
    return salida;
}

//por ejemplo pagar un prestamo en dolares con colones
void convertir_usd_to_crc_pago(float cuota, int cedula, int cantidad) {
    //tenemos que hacer primero la conversion y luego el rebajo de la cuenta en dolares
    //ademas tenemos que bajarle una cuota al del prestamo

    float conversion = cantidad * cuota * 538; //obtenemos los colones totales a pagar

    //rebajo de la cuenta de colones

    if (!verificarSaldoSuficiente(cedula, conversion, "CRC")) {
        return; // Salir de la función si el saldo no es suficiente
    }

    //llamada a la base de datos
    //sera un update
    
    // Prepara una declaración para actualizar el saldo
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));

    // Establece los valores de los parámetros
    pstmt->setDouble(1, conversion); // Nuevo saldo
    pstmt->setInt(2, cedula); // Cédula del cliente
    pstmt->executeUpdate();
    cout << endl;
    //cout << "Se retiro el dinero  de forma exitosa.... " << endl;
    registroColones(cedula, conversion, "PAGO_PRESTAMO");
}

//por ejemplo pagar un prestamo en colones con dolares
void convertir_crc_to_usd_pago(float cuota, int cedula, int cantidad) {
    //tenemos que hacer primero la conversion y luego el rebajo de la cuenta en dolares
    //ademas tenemos que bajarle una cuota al del prestamo

    float conversion = cantidad * cuota / 538; //obtenemos los dolares totales a pagar

    //rebajo de la cuenta de dolares

    if (!verificarSaldoSuficiente(cedula, conversion, "USD")) {
        return; // Salir de la función si el saldo no es suficiente
    }

    //llamada a la base de datos
    //sera un update

    // Prepara una declaración para actualizar el saldo
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo - ? WHERE cedula = ?"));

    // Establece los valores de los parámetros
    pstmt->setDouble(1, conversion); // Nuevo saldo
    pstmt->setInt(2, cedula); // Cédula del cliente
    pstmt->executeUpdate();
    cout << endl;
    //cout << "Se retiro el dinero  de forma exitosa.... " << endl;
    registroDolares(cedula, conversion, "PAGO_PRESTAMO");
}
