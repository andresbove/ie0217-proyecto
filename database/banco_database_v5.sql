-- Creando base de datos
CREATE DATABASE IF NOT EXISTS banco_data_base_4;

USE banco_data_base_4;

-- Tabla de cliente
CREATE TABLE IF NOT EXISTS Cliente (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT UNIQUE NOT NULL,
    nombre VARCHAR(50),
    apellido1 VARCHAR(50),
    apellido2 VARCHAR(50),
    provincia VARCHAR(50),
    telefono VARCHAR(20),
    correo VARCHAR(50)
);

-- Tabla de colones
CREATE TABLE IF NOT EXISTS cuentaColones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    saldo FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de dolares
CREATE TABLE IF NOT EXISTS cuentaDolares (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    saldo FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de prestamos
CREATE TABLE IF NOT EXISTS prestamo_Colones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    cantidad FLOAT,
    periodos INT,
    cuota FLOAT,
    saldoPendiente FLOAT,
    cuotasRestantes INT,
    interesAnual FLOAT,
    moneda VARCHAR(10),
    tipo VARCHAR(20),
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

CREATE TABLE IF NOT EXISTS prestamo_Dolares (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    cantidad FLOAT,
    periodos INT,
    cuota FLOAT,
    saldoPendiente FLOAT,
    cuotasRestantes INT,
    interesAnual FLOAT,
    moneda VARCHAR(10),
    tipo VARCHAR(20),
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de registro de transferencia de cuentas en colones
CREATE TABLE IF NOT EXISTS registroColones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    cantidad FLOAT,
    estado VARCHAR(50),
    fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de registro de transferencia de cuentas en dolares
CREATE TABLE IF NOT EXISTS registroDolares (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    cantidad FLOAT,
    estado VARCHAR(50),
    fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de certificados a corto plazo
CREATE TABLE IF NOT EXISTS CertificadoDeposito (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    monto DECIMAL(10, 2) NOT NULL,
    moneda VARCHAR(10),
    tasaInteres DECIMAL(5, 2) NOT NULL,
    meses INT NOT NULL,
    fecha_inicio DATE NOT NULL,
    fecha_vencimiento DATE NOT NULL,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Mostrar todas las tablas
SELECT * FROM Cliente;
SELECT * FROM cuentaColones;
SELECT * FROM cuentaDolares;
SELECT * FROM prestamo;
SELECT * FROM registroColones;
SELECT * FROM registroDolares;
SELECT * FROM CertificadoDeposito;