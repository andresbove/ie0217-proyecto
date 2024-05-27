# ie0217-proyecto
Repositorio para proyecto del curso IE0217 - Estructuras Abstractas de Datos y Algoritmos para Ingeniería. 

Christopher Fernandez Vivas B82951

Andres Bonilla Vega B81220

Kevin Campos Castro B91519

# Investigación
# Préstamo personal

En los préstamos personales, una entidad financiera otorga una cantidad de dinero que debe ser devuelta en un plazo específico junto con un porcentaje adicional que corresponde a los intereses generados. Este dinero puede emplearse para cubrir necesidades personales como gastos médicos, educativos, la compra de bienes, entre otros fines. [1]  

El uso que se le va a dar al capital brindado es muy importante en el momento de realizar una solicitud de préstamo. Algunos de los usos pueden ser los siguientes:

**Emergencias médicas.** Cobertura de imprevistos, como tratamientos cirugias o intervenciones de emergencia, operaciones dentales urgentes o gastos veterinarios inesperados para una mascota.

Inversiones como la adquisición de activos con el propósito de incrementar el patrimonio personal, por ejemplo, electrodomésticos para el hogar.

Prestamo de capital para satisfacer necesidades diarias, como reemplazar una computadora dañada o adquirir un celular nuevo.

# Préstamo prendario

Este es un tipo de financiamiento donde la persona proporciona un bien como garantía, o colateral, para obtener el préstamo, utilizando esta garantía como un "respaldo" para la entidad que da el préstamo. Normalmente se trata de bienes muebles como vehículos, motocicletas, entre otros. [2]

Es por esto que el bien ofrecido funciona como garantía hasta que el préstamo sea pagado. Estos préstamos se utilizan principalmente para la compra de vehículos nuevos o usados, quedando el bien adquirido como prenda a favor de la entidad financiera que otorga el financiamiento. [2]

# Préstamo Hipotecario

El préstamo hipotecario es un tipo de crédito que utiliza un inmueble como garantía. Estos préstamos se solicitan para la adquisición de terrenos, viviendas y otros tipos de propiedades. [3]

# Interes Simple

El interés simple es una forma de calcular los intereses de un préstamo que solo tiene en cuenta el capital principal. Permanece constante en el tiempo y no se añade a periodos sucesivos como en el interés compuesto. [7]

# Interes Compuesto

    El interés compuesto es una forma de calcular los intereses de una inversión, que utiliza los intereses acumulados en el pasado además del capital principal invertido. Los intereses pasados a su vez van generando nuevos intereses. Lo que provoca un efecto bola de nieve, haciendo que el capital y los nuevos intereses sean cada vez más grandes. [8]

# Interes fijo
    Este tipo de interés se mantiene constante durante toda la duración o vida del préstamo. Es independiente de la tasa de interés actual del mercado, es decir que si esta llegara a subir, no nos veríamos perjudicados, pero si bajara, tampoco nos beneficiaríamos. [6]

# Interes Variable

  Se actualiza y se revisa su cantidad en los plazos establecidos por la entidad financiera. Está sometido a los cambios en las tasas de interés. Con el interés variable nos beneficiamos de la baja en la tasa de interés, pero también nos vemos afectados si sube. Por lo general, se establece un rango dentro del cual oscila la tasa de interés. Su plazo de amortización puede ser más extenso que el de interés fijo.  [6]

# Interes Mixto

    En este tipo de interés, durante los primeros años de vida del préstamo la tasa de interés es fija y el resto de tiempo, hasta su terminación, es variable. por ejemplo los que fueron o van a comprar un carro que les dice 5 years tasa fija y el prestamo es a 8 years.[6]
# CDP

    Los certificados a corto plazo (CDP) es una herramienta de ahorros de bajo riesgo que puede generar un interés. Son remitidas por bancos e instituciones financieras. La forma en que funciona es que un inversionista deposita su dinero por un periodo determinado (puede ir desde unos cuantos meses hasta varios años), esto a cambio de una tasa fija de interés. La razón por la que son de bajo riesgo es porque la institución respalda este proceso [4]. 
## 1. Modalidad de operación: El sistema debe iniciar consultando si se va a utilizar en modalidad de atención a clientes o para obtener información general sobre préstamos bancarios. **chris**

    Este Paso es uno de los mas importante en los que va a tener el menu de nuestra aplicacion ,va a tener un menu con 2 opciones primeramente:

    --------------MENU-----------------------------

    1- Atención Clientes

    2- Información general sobre prestamos bancarios

    3- Salir

    --------------MENU----------------------------------

    La opcion 1 de atencion al cliente, la forma mas facil de localizar un cliente ademas de su nombre , es con su cedula , por ende la misma pedira ingresar la cedula del cliente que estara enlazada a las bases de datos y tendremos toda la informacion el cliente a mano.

    Por otra parte la opcion 2 sobre informacion de prestamos bancarios en un area totalmente a parte pero la misma igual pedira la cedula de identificacion del cliente, y luego se abrira un submenu el cual nos mostrara todo lo que se puede hacer referente a prestamos bancarios.

    Estas mismas se pueden tratar como funciones que al mismo tiempo dentro llaman a otras funciones que contienen todos los metodos necesarios para realizar operaciones referentes a prestamos o operaciones referentes a cuentas corrientes y en dolares.

    Todo lo anterior y los submenus se haran con switch y con bucles do while , ademas con la implementacion de excepciones.


## 2. Información general: Se deben desplegar las opciones predefinidas para préstamos personales, prendarios e hipotecarios, así como la opción de generar una tabla de pagos esperados para la opción elegida, donde el monto del préstamo es ingresado por el usuario. Además se debe dar la opción de obtener la tabla mediante valores personalizados de monto, cantidad de cuotas y la tasa de interés. **andres**

Esto se puede implementar siempre que ya se haya seleccionado la opción  2 del menú principal, que corresponde a "Información general sobre prestamos bancarios".  

Entonces, si se selecciona esta opción, se puede llevar a otro "submenu", donde hay opciones definidas en el sistema.  

```
--------------MENU-----------------------------

    1- Atención Clientes

    2- Información general sobre prestamos bancarios
        1 - Préstamo Personal 
        2- Préstamo Prendario 
        3- Préstamo Hipotecario
    3- Salir
    --------------MENU----------------------------------
```

Acá, cada una de esas opciones generará una tabla de pagos esperados para el préstamo escogido, por lo que el pago correspondiente dependerá de la opción que el usuario eligió.

Para el sistema se generará una base de datos con diferentes atributos, donde el atributo "Cédula (Key)" será la clave principal a la que las tablas restantes le harán referencia como foreign keys.  
Encabezado de la Tabla **Usuarios**:
```
| Usuarios | Cédula (Key) | Nombre | Apellidos| Provincia |Télefono | Correo |
```

Encabezado de la Tabla **Colones**:
```
| Cédula(foreign key) | Saldos |
```
Encabezado de la Tabla **Dólares**:
```
| Cédula(foreign key) | Saldos |
```

Encabezado de la Tabla **Préstamos**:
```
| Cédula(foreign key) | Periodos | Cuota | Saldo pendiente | Meses | Tasa de interés |
```


## 3. Cuentas bancarias: Un cliente puede poseer hasta dos cuentas bancarias, una en colones y otra en dólares, destinadas a gestionar sus ahorros con la entidad bancaria. Así como certificados de depósito a plazo (CDP). **kevin**

Los certificados a corto plazo (CDP) es una herramienta de ahorros de bajo riesgo que puede generar un interés. Son remitidas por bancos e instituciones financieras. La forma en que funciona es que un inversionista deposita su dinero por un periodo determinado (puede ir desde unos cuantos meses hasta varios años), esto a cambio de una tasa fija de interés. La razón por la que son de bajo riesgo es porque la institución respalda este proceso [4].

Algunas ventajas de los CDP son:
- Las tasas de interés son más altas que los intereses de las cuentas de ahorro o cuentas corriente, además se sabe de antemano y cuánto pueden generar.
- Son inversiones relativamente seguros porque son respladados por la institución encargada.

Sin embargo, es importante tener en cuenta que el interés dado por la institución no considera la inflación, puesto que la tasa de interés es fija, es posible que es posible que esta tasa no sea lo suficiente para compensar la pérdida [4].

Para el diseño puesto que se va a tener una base de datos SQL con la información los clientes, la estructura que se tiene pensada es que cada cliente puede tener una cuenta en colones o una en dólares o ambas, pero mínimo una cuenta, esto se va a manejar mediante un booleano (el hecho de que tenga la cuenta o no), cada una de estas cuentas va a tener una tabla correspondiente dentro de la base de datos. El cliente va a poder tener un CDP en la cuenta de dólares o colones, dependiendo de las necesidades del programa esto sería por medio de una tabla separada con los datos del CDP como la tasa de interés, la duración del certificado y cuánto tiempo lleva. Se debe tener en cuenta implementar lo anterior en el menú para que el usuario pueda observar los datos cuando desee.

## 4. Operaciones disponibles: Los clientes tienen la capacidad de realizar diversas operaciones, tales como depósitos, retiros, transferencias entre cuentas dirigidas a otros clientes, abonos a préstamos tanto propios como de otras personas, etc. **chris**

Se implementará con un menú, según sea para clientes o préstamos. Las operaciones serán funciones totalmente aparte, donde las mismas harán todo tipo de operaciones "CRUD" en la base de datos. Para las operaciones que sean distintas a las del propio cliente se crearán 2 funciones aparte, donde las mismas tendrán la cuenta destino donde se harán las transferencias, tanto de préstamos como tranferencias normales, y las mismas igualmente se realizarán bajo las operaciones disponibles en la base de datos.

## 5. Registro de transacciones: El sistema debe mantener un registro detallado de todas las transacciones realizadas, garantizando un seguimiento preciso de las operaciones efectuadas. **andres**

Es como un tipo de "bitácora" de todas las operaciones que se han hecho a la cuenta, basadas en las operaciones que se describieron en el paso anterior. Esta bitácora puede ser almacenada como una tabla, guardando en una columna el tipo de operación que se realizó, en otra columna el monto con el que se hizo la operación, y en la última columna, la fecha en que se realizó dicha operación.

```
Operación   |   Monto    |    Fecha
_____________________________________________
 
Retiro      |    -3000    |    1 - 1 - 2024
Depósito    |    +1000    |    2 - 1 - 2024
Retiro      |    -5000    |    3 - 1 - 2024
Depósito    |    +9000    |    4 - 1 - 2024
Depósito    |    +1000    |    5 - 1 - 2024

```

## 6. Identicación de clientes: Cada cliente será identificado mediante un número de identi cación único, el cual estará limitado a un número decimal entre 0 y 999999999. **kevin**

Para el diseño se considera que el número de identificación no es algo que sea manejado por el usuario, sino por el mismo sistema. Puesto que el número es muy grande, es muy probable que se utilice el tipo de dato `BIGINT` en SQL, además es importante que cada número de cliente debe ser único, para esto se puede usar restricciones como `UNIQUE`. Puesto que el número de cliente va a ser manejado internamente, no hay necesidad de verificar de que el número de cliente sean solamente números y que sean del 0-9.

Otra punto importante es tener la opción de que el usuario pueda ingresar su identificación y observar todos los datos correspondientes a su cuenta. Hay que considerar de que un usuario puede llegar a simplemente querer consultar o también, un usuario llegue nada mas a crear una cuenta, por lo que se tendría un submenú para este caso en específico. 

## 7. Préstamos asociados: Los clientes pueden tener préstamos asociados, ya sea en colones o en dólares, cada uno con características específicas como la tasa de interés, el periodo en meses y la cuota mensual, las cuales estarán asociadas a valores previamente de nidos. **chris**

Definición de las características específicas de los préstamos

Tasa de interés: "La tasa de interés es un porcentaje de la operación que se realiza. Es un porcentaje que se traduce en un monto de dinero, mediante el cual se paga por el uso del dinero." Existen dos tasas de interés, el interés simple y el interés compuesto , el **interés simple** es calculado con la siguiente ecuación:

$C_{n} = C_{0} * (1+(1*t))$ 

donde:

$C_{n}$ = monto final

$C_{0}$ = monto inicial

$t$ = numero de periodos


Ecuación del **interés compuesto**:

$C_{n} = C_{0} * (1*n)^t$

donde:

$C_{n}$ = monto final

$C_{0}$ = monto inicial

$t$ = numero de periodos

$n$ = interes

Periodo de meses del préstamo: Cantidad de meses por el cual se va a estar pagando en su defecto el prestamo en su totalidad.  

Ejemplo:  
Periodo de 24 meses, se tienen 24 meses para concluir con el pago del prestamo con todo e interés.  

Cuota mensual: Cuota que deberá pagar el cliente mes a mes para poder concluir la paga total del préstamo. Este mismo se extrae de la división del precio total del préstamo con interés, dividido con la cantidad de meses del periodo.


## 8. Reporte de préstamos: Los clientes pueden solicitar un reporte de sus préstamos. El sistema debe generar un archivo de texto que detalle las cuotas pagadas, desglosando el aporte al capital y los intereses abonados hasta el momento. Este reporte puede presentarse en forma tabular. **andres**
Se puede trabajar creando una opción desde el menú principal, después de escoger la opción 1.

```
--------------MENU-----------------------------

1- Atención Clientes
        I. Sacar prestamo
            - Prestamo en Dólares
            - Prestamo en Colones
        II. Pagar Prestamo
            - Pagar prestamo en Dólares
            - Pagar prestamo en Colones
        III. Generar informe (.txt)

2- Información general sobre prestamos bancarios
        1 - Préstamo Personal 
        2- Préstamo Prendario 
        3- Préstamo Hipotecario

3- Volver
    --------------MENU----------------------------------
```

Con este menú, al seleccionar "Pagar prestamo", ya sea en dolares o en colones, se le pida al usuario que ingrese el dinero con el que va a pagar. Una vez escogido el monto, se le restará este a la cuenta principal para hacer el pago del préstamo. Luego, al seleccionar generar informe, se crea un ".txt" donde van a estar las cuotas pagadas, desglosando el aporte al capital y los intereses abonados hasta el momento.

## 9. Almacenamiento de la información: Se debe hacer uso de bases de datos SQL, por lo que es recomendado primero que todo de unir el esquema a utilizar. **kevin**

- ¿Qué es una base de datos?

    Una base de datos es un sistema organizado de almacenamiento de datos que permite almacenar y recuperar información de manera eficiente. Es como un archivo digital enorme donde se guardan datos de manera estructurada. Se puede comparar una base de datos con un armario de archivadores donde cada cajón representa una tabla diferente de datos relacionados. Son usados para manejar y almacenar una gran cantidad de datos de manera eficiente. [5]

- ¿Qué es SQL?

    SQL o Structured Query Language es un lenguaje de programación especificamente diseñado para interactuar y manejar con bases de datos relacionales (las bases de datos relacionales utilizan tablas para organizar los datos. Cada tabla tiene filas (registros) y columnas (atributos)). Permite hacer varias tareas como [5]:
    - CRUD (crear, leer, actualizar y eliminar).
    - Extraer datos específicos de la base de datos basado en ciertos criterios.

Se tiene el siguiente esquema de alto nivel que podría llegar a cambiar en base a las necesidades durante el desarrollo del proyecto:

![Diagrama de la estructura del software del banco generalizada](https://github.com/andresbove/ie0217-proyecto/blob/main/diagrama_2.png)

### Cronograma a seguir (puede variar)
![cronograma](https://github.com/andresbove/ie0217-proyecto/assets/116931494/b0c5f92c-984a-49f9-bb94-986d512836a9)

# Referencias
[1] : https://www.bncr.fi.cr/3-detalles-que-no-pod%C3%A9s-pasar-por-alto-antes-de-pedir-un-pr%C3%A9stamo-personal#:~:text=Un%20pr%C3%A9stamo%20personal%20es%20una,porcentaje%20adicional%20correspondiente%20a%20intereses.

[2] : https://www.supervielle.com.ar/blog/educacion-financiera/que-es-un-prestamo-prendario

[3] : https://www.inavirtual.ed.cr/pluginfile.php/1932699/mod_resource/content/2/SERVER%20GUIA%20MEIC%20BLOQUE4%20ACT%20/s3.html


[4] : https://bettermoneyhabits.bankofamerica.com/es/personal-banking/what-is-a-cd-investment

[5] : https://www.springboard.com/blog/data-analytics/what-is-sql/

[6] : https://edu.gcfglobal.org/es/credito/cuales-son-los-tipos-de-interes/1/

[7] : https://economipedia.com/definiciones/interes-simple.html

[8] : https://economipedia.com/definiciones/interes-compuesto.html
