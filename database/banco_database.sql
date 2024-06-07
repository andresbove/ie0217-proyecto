-- Creado a partir de functions.hpp

-- Creando base de datos
CREATE DATABASE IF NOT EXISTS banco_data_base;

USE banco_data_base;

-- Tabla de cliente
CREATE TABLE IF NOT EXISTS Cliente (
    cedula INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50),
    apellido1 VARCHAR(50),
    apellido2 VARCHAR(50),
    provincia VARCHAR(50),
    telefono VARCHAR(20),
    correo VARCHAR(50)
);

-- Tabla de colones
CREATE TABLE IF NOT EXISTS cuentaColones (
    cedula INT PRIMARY KEY,
    saldo FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de dolares
CREATE TABLE IF NOT EXISTS cuentaDolares (
    cedula INT PRIMARY KEY,
    saldo FLOAT,
    FOREIGN KEY (cedula) REFERENCES Cliente(cedula)
);

-- Tabla de prestamos
CREATE TABLE IF NOT EXISTS prestamo (
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

-- Insertando valores para tener un ejemplo
-- Clientes
INSERT INTO Cliente (nombre, apellido1, apellido2, provincia, telefono, correo)
VALUES ('Juan', 'Fernandez', 'Bonilla', 'San Jose', '12345678', 'juan@test.com');

-- Cuenta colones
INSERT INTO cuentaColones (cedula, saldo)
VALUES (1, 10000.50); -- Se tiene cedula 1, entonces esto seria el primer usuario (Juan)

-- Cuenta dolares
INSERT INTO cuentaDolares (cedula, saldo)
VALUES (1, 5000.75);

-- Prestamo
INSERT INTO prestamo (cedula, periodos, cuotas, moneda, saldo, intereses)
VALUES (1, 12, 100, 'CRC', 20000.00, 3.5);

-- Registro colones
INSERT INTO registroColones (cedula, cantidad, estado)
VALUES (1, 500.00, 'Completado');

-- Registro dolares
INSERT INTO registroDolares (cedula, cantidad, estado)
VALUES (1, 200.00, 'Pendiente');

-- Mostrar todas las tablas
SELECT * FROM Cliente;
SELECT * FROM cuentaColones;
SELECT * FROM cuentaDolares;
SELECT * FROM prestamo;
SELECT * FROM registroColones;
SELECT * FROM registroDolares;