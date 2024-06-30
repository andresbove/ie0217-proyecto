/**
 * @file FuncionesPrestamos.hpp
 * Aqui es donde están definidas las funciones para el manejo de los préstamos.
*/
#include "header.hpp"

/**
 * Calcula el inter�s simple a la hora de sacar un pr�stamo.
 * @param[in] cantidadInicial
 * @param[in] years
 * @param[in] interesAnual
 * @param[out] interes
*/
float calcularInteresSimple(float cantidadInicial, int years, float interesAnual) {
    float interes = cantidadInicial * years * interesAnual;
    return interes;
}


/**
 * Encargado de calcular las cuotas a pagar por sacar un pr�stamo.
 * @param[in] cantidadInicial
 * @param[in] interesAnual
 * @param[in] periodos
 * @param[out] resultado
*/
float cuota(float cantidadInicial, float interesAnual, int periodos) {
    float interesMensual = interesAnual / 12;
    float resultado = (cantidadInicial * (interesMensual * (pow(1 + interesMensual, periodos)))) / (pow(1 + interesMensual, periodos) - 1);
    return resultado;
}


/**
 * Realiza consultas de la cuota del pr�stamo en colones.
 * @param[in] cedula
 * @param[in] tipo
 * @param[out] couta
*/
float obtenerCuotaColones(int cedula, string tipo) {
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT cuota FROM prestamo_Colones WHERE cedula=? AND tipo=?"));


    pstmt->setInt(1, cedula); // C�dula espec�fica
    pstmt->setString(2, tipo); // Tipo espec�fico

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


/**
 * Realiza consultas de la cuota del pr�stamo en d�lares.
 * @param[in] cedula
 * @param[in] tipo
 * @param[out] couta
*/
float obtenerCuotaDolares(int cedula, string tipo) {

    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT cuota FROM prestamo_Dolares WHERE cedula=? AND tipo=?"));


    pstmt->setInt(1, cedula); // C�dula espec�fica
    pstmt->setString(2, tipo); // Tipo espec�fico

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
/**
 * Permite el usuario sacar un pr�stamo, para ello se le solicita le c�dula y despu�s se hacen los c�lculos correspondientes
 * y se guarda en la base de datos.
 * @param[in] moneda
 * @param[in] tipo
*/
void sacarPrestamo(string moneda, string tipo) {

    Prestamo prestamo;
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Sacar Prestamo*************" << endl;
    cout << "*********************************" << endl;

    bool verificacion;
    //Ademas una columna con el tipo de prestamo
    //creo que lo mejor seria manejar los prestamos en dos tablas colones y dolares

    //cout << "\nEn que moneda desea solicitar el prestamo: ";
    //cin >> moneda;

    prestamo.cedula = validarCedula(); // Solicitar la cedula y verificar que el input sea adecuado

    //---------------------------------------------
    //VERIFICACION
    //---------------------------------------------

    verificacion = verificar_un_prestamo(tipo, prestamo.cedula, moneda);
    if (verificacion == false) {
        cout << "\nPor favor ingresa la cantidad de dinero del prestamo: ";
        cin >> prestamo.cantidad;
        cout << "\nPor favor ingresa los meses a los cuales sera el prestamo: ";
        cin >> prestamo.periodos;
        cout << "\nPor favor ingresa la tasa interes anual del prestamo: ";
        cin >> prestamo.interesAnual;


        prestamo.interesAnual = prestamo.interesAnual / 100; // para dejarla en terminos de 0 .. 1

        //sacaremos la cuota

        prestamo.cuota = cuota(prestamo.cantidad, prestamo.interesAnual, prestamo.periodos);//ya calculamos la cuota que tienen que pagar con interes fijo

        //insertaremos dichos datos a la base de datos


        //insertamos en tabla de prestamos de colones
        if (moneda == "CRC")
        {
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO prestamo_Colones(cedula, cantidad, periodos, cuota, saldoPendiente, cuotasRestantes, interesAnual, moneda,tipo) VALUES (?, ?, ?, ?, ?, ?, ?, ?,?)"));

            //ingresamos los datos
            pstmt->setInt(1, prestamo.cedula); // Ejemplo de c�dula
            pstmt->setDouble(2, prestamo.cantidad); // Ejemplo de cantidad
            pstmt->setInt(3, prestamo.periodos); // Ejemplo de periodos
            pstmt->setDouble(4, prestamo.cuota); // Ejemplo de cuota
            pstmt->setDouble(5, prestamo.cantidad); // Ejemplo de saldo pendiente
            pstmt->setInt(6, prestamo.periodos); // Ejemplo de cuotas restantes
            pstmt->setDouble(7, prestamo.interesAnual); // Ejemplo de inter�s anual
            pstmt->setString(8, "CRC"); // Ejemplo de moneda
            pstmt->setString(9, tipo); //tipo de prestamo
            //actualizamos la tabla
            pstmt->executeUpdate();

            //nos falta agregar esa cantidad de plata a nuestras cuentas ojo

            // Prepara una declaraci�n para actualizar el saldo
            std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo + ? WHERE cedula = ?"));

            // Establece los valores de los par�metros
            pstmt2->setDouble(1, prestamo.cantidad); // Nuevo saldo
            pstmt2->setInt(2, prestamo.cedula); // C�dula del cliente
            pstmt2->executeUpdate();

            //registramos la transaccion

            registroColones(prestamo.cedula, prestamo.cantidad, "Deposito_Prestamo");

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
            pstmt->setInt(1, prestamo.cedula); // Ejemplo de c�dula
            pstmt->setDouble(2, prestamo.cantidad); // Ejemplo de cantidad
            pstmt->setInt(3, prestamo.periodos); // Ejemplo de periodos
            pstmt->setDouble(4, prestamo.cuota); // Ejemplo de cuota
            pstmt->setDouble(5, prestamo.cantidad); // Ejemplo de saldo pendiente
            pstmt->setInt(6, prestamo.periodos); // Ejemplo de cuotas restantes
            pstmt->setDouble(7, prestamo.interesAnual); // Ejemplo de inter�s anual
            pstmt->setString(8, "USD"); // Ejemplo de moneda
            pstmt->setString(9, tipo); //tipo de prestamo
            //actualizamos la tabla
            pstmt->executeUpdate();




            // Prepara una declaraci�n para actualizar el saldo
            std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo + ? WHERE cedula = ?"));

            // Establece los valores de los par�metros
            pstmt2->setDouble(1, prestamo.cantidad); // Nuevo saldo
            pstmt2->setInt(2, prestamo.cedula); // C�dula del cliente
            pstmt2->executeUpdate();

            //registramos la transaccion

            registroDolares(prestamo.cedula, prestamo.cantidad, "Deposito_Prestamo");
            cout << endl;
            cout << endl;
            cout << "******************************" << endl;
            cout << "Prestamo Aprobado con Exito..." << endl;
            cout << "******************************" << endl;
        }
    }
    else
    {
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "El cliente  ya tiene un prestamo activoo del que esta solicitando , solo es posible 1 tipo de prestamo por cliente....." << endl << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }



    //hasta aqui ya hemos ingresado los datos de las tablas para pedir un prestamo   
}



//en las funciones de pagar prestamo , pueden ser pagarlos en efectivo o pagarlos con su propia cuenta 
//hay que tomar en cuenta esto
//Ademas manejo de excepciones por aca si el usuario no tiene mas fondos para poder pagarlos

/**
 * Permite el usuario pueda hacer un pago del pr�stamo en colones, para ello se le solicita le c�dula y despu�s se hacen los c�lculos correspondientes
 * y se guarda en la base de datos.
 * @param[in] tipo
*/
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


        pstmt->setInt(1, cedula); // C�dula espec�fica
        pstmt->setString(2, tipo); // Tipo espec�fico
        pstmt->executeUpdate();//actualizamos

        cout << "\n";
        cout << "Pago en Efectivo Realizado con exito ..." << endl;

        //Pagar en efectivo funciona de maravilla


    }
    else {
        //hay que obtener el valor de la cuota del prestamo y almacenarlo en una variable
        bool pagocolones;
        string temp;
        float cuotaRebajo = obtenerCuotaColones(cedula, tipo);

        

        cout << endl << endl;
        cout << "Quieres pagar tu prestamo de colones con colones (Y o N) : ";
        cin >> temp;
        cout << endl;
        int cantidadCuotas = validarNumero();

        if (temp == "Y" || temp == "y") {
            pagocolones = true;
        }
        else {
            pagocolones = false;
        }


        if (pagocolones) {
            //hay que buscar la cuenta de la persona en colones y quitarle la plata y hacerle este toque de arriba
            cuotaRebajo = cuotaRebajo * cantidadCuotas;// cuota de rebajao final
            //introducir funcion de Andres
            
            if (!verificarSaldoSuficiente(cedula, cuotaRebajo, "CRC")) {
                return; // Salir de la funci�n si el saldo no es suficiente
            }
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaColones SET saldo = saldo - ? WHERE cedula = ?"));


            // Establece los valores de los par�metros
            pstmt->setDouble(1, cuotaRebajo); // lo que le vamos a restar del saldo
            pstmt->setInt(2, cedula); // cedula de la persona
            pstmt->executeUpdate();





            //aqui cuando ya pago la parte del prestamo
            std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE prestamo_Colones SET saldoPendiente = saldoPendiente - ? , cuotasRestantes = cuotasRestantes - ?  WHERE cedula = ? AND tipo = ?"));

            // Configurar los valores que deseas actualizar
            //pstmt->setDouble(1, cuota); // Nuevo saldo pendiente
            //las condiciones para hacer el update
            pstmt2->setDouble(1, cuotaRebajo);
            pstmt2->setDouble(2, cantidadCuotas);
            pstmt2->setInt(3, cedula); // C�dula espec�fica
            pstmt2->setString(4, tipo); // Tipo espec�fico
            pstmt2->executeUpdate();//actualizamos
            cout << endl;
            cout << "Pago Realizado con exito ..." << endl;
            //registramos la transaccion

            registroColones(cedula, cuotaRebajo, "RETIRO");
        }
        else {
            //con esta funcion ya hacemos el rebajo de la cuenta de dolares
            convertir_crc_to_usd_pago(cuotaRebajo, cedula, cantidadCuotas);

            //aqui cuando ya pago la parte del prestamo
            std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE prestamo_Colones SET saldoPendiente = saldoPendiente - ? , cuotasRestantes = cuotasRestantes - ?  WHERE cedula = ? AND tipo = ?"));

            // Configurar los valores que deseas actualizar
            //pstmt->setDouble(1, cuota); // Nuevo saldo pendiente
            //las condiciones para hacer el update
            pstmt2->setDouble(1, cuotaRebajo*cantidadCuotas);
            pstmt2->setDouble(2, cantidadCuotas);
            pstmt2->setInt(3, cedula); // C�dula espec�fica
            pstmt2->setString(4, tipo); // Tipo espec�fico
            pstmt2->executeUpdate();//actualizamos
            cout << endl;
            cout << "Pago Realizado con exito ..." << endl;
            

        }
    }

}


/**
 * Permite el usuario pueda hacer un pago del pr�stamo en dolares, para ello se le solicita le c�dula y despu�s se hacen los c�lculos correspondientes
 * y se guarda en la base de datos.
 * @param[in] tipo
*/
void pagarPrestamoDolares(string tipo) {
    cout << endl;
    cout << endl;
    cout << "*********************************" << endl;
    cout << "*********Pagar Prestamo*************" << endl;
    cout << "************Dolares**************" << endl;

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
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE prestamo_Dolares SET saldoPendiente = saldoPendiente - cuota , cuotasRestantes = cuotasRestantes -1  WHERE cedula = ? AND tipo = ?"));


        pstmt->setInt(1, cedula); // C�dula espec�fica
        pstmt->setString(2, tipo); // Tipo espec�fico
        pstmt->executeUpdate();//actualizamos

        cout << "\n";
        cout << "Pago en Efectivo Realizado con exito ..." << endl;

        //Pagar en efectivo funciona de maravilla


    }
    else {
        //hay que obtener el valor de la cuota del prestamo y almacenarlo en una variable
        bool pagoDolares;
        string temp;

        float cuotaRebajo = obtenerCuotaDolares(cedula, tipo);

        cout << endl << endl;
        cout << "Quieres pagar tu prestamo de Dolares con Dolares (Y o N) : ";
        cin >> temp;
        cout << endl;

        int cantidadCuotas = validarNumero();


        if (temp == "Y" || temp == "y") {
            pagoDolares = true;
        }
        else {
            pagoDolares = false;
        }


        if (pagoDolares) {
            //hay que buscar la cuenta de la persona en colones y quitarle la plata y hacerle este toque de arriba
            cuotaRebajo = cuotaRebajo * cantidadCuotas;// cuota de rebajao final
            //introducir funcion de Andres

            if (!verificarSaldoSuficiente(cedula, cuotaRebajo, "USD")) {
                return; // Salir de la funci�n si el saldo no es suficiente
            }
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE cuentaDolares SET saldo = saldo - ? WHERE cedula = ?"));


            // Establece los valores de los par�metros
            pstmt->setDouble(1, cuotaRebajo); // lo que le vamos a restar del saldo
            pstmt->setInt(2, cedula); // cedula de la persona
            pstmt->executeUpdate();





            //aqui cuando ya pago la parte del prestamo
            std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE prestamo_Dolares SET saldoPendiente = saldoPendiente - ? , cuotasRestantes = cuotasRestantes - ?  WHERE cedula = ? AND tipo = ?"));

            // Configurar los valores que deseas actualizar
            //pstmt->setDouble(1, cuota); // Nuevo saldo pendiente
            //las condiciones para hacer el update
            pstmt2->setDouble(1, cuotaRebajo);
            pstmt2->setDouble(2, cantidadCuotas);
            pstmt2->setInt(3, cedula); // C�dula espec�fica
            pstmt2->setString(4, tipo); // Tipo espec�fico
            pstmt2->executeUpdate();//actualizamos
            cout << endl;
            cout << "Pago Realizado con exito ..." << endl;
            //registramos la transaccion

            registroColones(cedula, cuotaRebajo, "RETIRO");
        }
        else {
            //con esta funcion ya hacemos el rebajo de la cuenta de colones
            convertir_usd_to_crc_pago(cuotaRebajo, cedula, cantidadCuotas);

            //aqui cuando ya pago la parte del prestamo
            std::unique_ptr<sql::PreparedStatement> pstmt2(con->prepareStatement("UPDATE prestamo_Dolares SET saldoPendiente = saldoPendiente - ? , cuotasRestantes = cuotasRestantes - ?  WHERE cedula = ? AND tipo = ?"));

            // Configurar los valores que deseas actualizar
            //pstmt->setDouble(1, cuota); // Nuevo saldo pendiente
            //las condiciones para hacer el update
            pstmt2->setDouble(1, cuotaRebajo * cantidadCuotas);
            pstmt2->setDouble(2, cantidadCuotas);
            pstmt2->setInt(3, cedula); // C�dula espec�fica
            pstmt2->setString(4, tipo); // Tipo espec�fico
            pstmt2->executeUpdate();//actualizamos
            cout << endl;
            cout << "Pago Realizado con exito ..." << endl;


        }
    }

}


/**
 * Genera un informe de las transacciones que ha tenido el usuario basado en la c�dula ingresada
 * y tambi�n la moneda (ya que puede tener cuenta en colones o d�lares)
 * @param[in] moneda
*/
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

        // Verificar si la c�dula existe en la base de datos
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


/**
 * Genera un informe de los pr�stamos del cliente (puede ser PRENDARIO, HIPOTECARIO o PERSONAL) basado en la c�dula ingresada y tambi�n
 * la moneda (ya que puede tener cuenta en colones o d�lares)
 * @param[in] tipo
*/
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