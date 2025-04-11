#ifndef DEPARTAMENTO_HPP
#define DEPARTAMENTO_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <memory>
#include <set>
using namespace std;

#include "empleado.hpp"

class Departamento{
    private:
        vector<Empleado> empleados;
        static int cantEmpleadosDepts;

    public:
        string nombre;
        string ubicacion;
    
        Departamento(string nombre, string ubicacion);

        static int contarEmpleados();
        vector<Empleado> getEmployees() const;
        bool contratarEmpleado(Empleado empleado);
        bool despedirEmpleado(Empleado empleado);

        //metodos que agrego para el main.
        Empleado& getEmployeeByName(string nombre);
};

#endif