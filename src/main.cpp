/**
 * @file main.cpp
 * En este archivo es donde se ejecuta lo necesario para que el usuario pueda realizar las operaciones de gestion de banco y que
 * pueda interactuar con el sistema.
*/

#include <iostream>
#include <stdexcept>
#include <limits>
#include "FuncionesMenu.cpp"
#include "header.hpp"
#include "FuncionesGenerales.cpp"
#include "FuncionesPrestamos.cpp"


int main() {

    connectDB();

    menuPrincipal();

    return 0;
}