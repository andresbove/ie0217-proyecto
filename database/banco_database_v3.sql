-- Creando base de datos
CREATE DATABASE IF NOT EXISTS banco_data_base_2;

USE banco_data_base_2;

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
CREATE TABLE IF NOT EXISTS prestamo_prendario_colones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    periodos INT,
    valor_cuota INT,
    cuotas INT,
    moneda VARCHAR(10),
    saldo FLOAT,
    intereses FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

CREATE TABLE IF NOT EXISTS prestamo_personal_colones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    periodos INT,
    valor_cuota INT,
    cuotas INT,
    moneda VARCHAR(10),
    saldo FLOAT,
    intereses FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

CREATE TABLE IF NOT EXISTS prestamo_hipotecario_colones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    periodos INT,
    valor_cuota INT,
    cuotas INT,
    moneda VARCHAR(10),
    saldo FLOAT,
    intereses FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);


CREATE TABLE IF NOT EXISTS prestamo_prendario_dolares (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    periodos INT,
    valor_cuota INT,
    cuotas INT,
    moneda VARCHAR(10),
    saldo FLOAT,
    intereses FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

CREATE TABLE IF NOT EXISTS prestamo_personal_dolares (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    periodos INT,
    valor_cuota INT,
    cuotas INT,
    moneda VARCHAR(10),
    saldo FLOAT,
    intereses FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

CREATE TABLE IF NOT EXISTS prestamo_hipotecario_dolares (
    id INT AUTO_INCREMENT PRIMARY KEY,
    cedula INT,
    periodos INT,
    valor_cuota INT,
    cuotas INT,
    moneda VARCHAR(10),
    saldo FLOAT,
    intereses FLOAT,
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

-- Mostrar todas las tablas
SELECT * FROM Cliente;
SELECT * FROM cuentaColones;
SELECT * FROM cuentaDolares;
SELECT * FROM prestamo;
SELECT * FROM registroColones;
SELECT * FROM registroDolares;