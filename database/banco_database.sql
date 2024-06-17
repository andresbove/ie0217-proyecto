-- Creado a partir de functions.hpp

-- Creando base de datos
CREATE DATABASE IF NOT EXISTS banco_data_base;

USE banco_data_base;

-- Tabla de cliente
CREATE TABLE IF NOT EXISTS Cliente (
    id INT AUTO_INCREMENT primary key,
    cedula varchar(50),
    nombre VARCHAR(50),
    apellido1 VARCHAR(50),
    apellido2 VARCHAR(50),
    provincia VARCHAR(50),
    telefono VARCHAR(20),
    correo VARCHAR(50)
);

-- Tabla de colones
CREATE TABLE IF NOT EXISTS cuentaColones (
    id INT AUTO_INCREMENT,
    cedula INT PRIMARY KEY,
    saldo FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de dolares
CREATE TABLE IF NOT EXISTS cuentaDolares (
    id INT AUTO_INCREMENT,
    cedula INT PRIMARY KEY,
    saldo FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de prestamos
CREATE TABLE IF NOT EXISTS prestamo (
    id INT AUTO_INCREMENT,
    cedula INT,
    periodos INT,
    cuotas INT,
    moneda VARCHAR(10),
    saldo FLOAT,
    intereses FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de registro de transferencia de cuentas
CREATE TABLE IF NOT EXISTS registroColones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    cantidad FLOAT,
    estado VARCHAR(50),
    fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de registro de transferencia de dolares
CREATE TABLE IF NOT EXISTS registroDolares (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    cantidad FLOAT,
    estado VARCHAR(50),
    fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);


-- Mostrar todas las tablas
SELECT * FROM Cliente;
SELECT * FROM cuentaColones;
SELECT * FROM cuentaDolares;
SELECT * FROM prestamo;
SELECT * FROM registroColones;
SELECT * FROM registroDolares;