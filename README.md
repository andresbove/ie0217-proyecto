# ie0217-proyecto
Repositorio para proyecto del curso IE0217 - Estructuras Abstractas de Datos y Algoritmos para Ingeniería. 

1. Modalidad de operación: El sistema debe iniciar consultando si se va a utilizar en modalidad de atención a clientes o para obtener información general sobre préstamos bancarios. **chris**

Este Paso es uno de los mas importante en los que va a tener el menu de nuestra aplicacion ,va a tener un menu con 2 opciones primeramente:

\*--------------MENU-----------------------------
1- Atencion Clientes
2- Informacion general sobre prestamos bancarios
3- Salir
\*------------------------------------------------

La opcion 1 de atencion al cliente, la forma mas facil de localizar un cliente ademas de su nombre , es con su cedula , por ende la misma pedira ingresar la cedula del cliente que estara enlazada a las bases de datos y tendremos toda la informacion el cliente a mano.

Por otra parte la opcion 2 sobre informacion de prestamos bancarios en un area totalmente a parte pero la misma igual pedira la cedula de identificacion del cliente, y luego se abrira un submenu el cual nos mostrara todo lo que se puede hacer referente a prestamos bancarios.

Estas mismas se pueden tratar como funciones que al mismo tiempo dentro llaman a otras funciones que contienen todos los metodos necesarios para realizar operaciones referentes a prestamos o operaciones referentes a cuentas corrientes y en dolares.

Todo lo anterior y los submenus se haran con switch y con bucles do ademas con la implementacion de excepciones.


2. Información general: Se deben desplegar las opciones predefinidas para préstamos personales, prendarios e hipotecarios, así como la opción de generar una tabla de pagos esperados para la opción elegida, donde el monto del préstamo es ingresado por el usuario. Además se debe dar la opción de obtener la tabla mediante valores personalizados de monto, cantidad de cuotas y la tasa de interés. **andres**

3. Cuentas bancarias: Un cliente puede poseer hasta dos cuentas bancarias, una en colones y otra en dólares, destinadas a gestionar sus ahorros con la entidad bancaria. Así como certi cados de depósito a plazo (CDP). **kevin**

4. Operaciones disponibles: Los clientes tienen la capacidad de realizar diversas operaciones, tales como depósitos, retiros, transferencias entre cuentas dirigidas a otros clientes, abonos a préstamos tanto propios como de otras personas, etc. **chris**

Igual se implementara con un menu ,segun sea para clientes o prestamos las operaciones seran funciones totalmente aparte donde las mismas haran todo tipo de operaciones CRUD en la base de datos, para las operaciones que sean distintas a las del propio clientes se crearan 2 funciones aparte donde las mismas tendran la cuenta destino donde se haran las transferencias tanto de prestamos como tranferencias normales y las mismas igualmente se realizaran bajo las operaciones disponibles en la base de datos.

5. Registro de transacciones: El sistema debe mantener un registro detallado de todas las transacciones realizadas, garantizando un seguimiento preciso de las operaciones efectuadas. **andres**

6. Identicación de clientes: Cada cliente será identi cado mediante un número de identi cación único, el cual estará limitado a un número decimal entre 0 y 999999999. **kevin**

7. Préstamos asociados: Los clientes pueden tener préstamos asociados, ya sea en colones o en dólares, cada uno con características especícas como la tasa de interés, el periodo en meses y la cuota mensual, las cuales estarán asociadas a valores previamente de nidos. **chris**

Definicion de las caracterisiticas especificas de los prestamos

Tasa de interes:
Periodo de meses del prestamo:
cuota mensual:

 8. Reporte de préstamos: Los clientes pueden solicitar un reporte de sus préstamos. El sistema debe generar un archivo de texto que detalle las cuotas pagadas, desglosando el aporte al capital y los intereses abonados hasta el momento. Este reporte puede presentarse en forma tabular. **andres**

9. Almacenamiento de la información: Se debe hacer uso de bases de datos SQL, por lo que es recomendado primero que todo de nir el esquema a utilizar. **kevin**

