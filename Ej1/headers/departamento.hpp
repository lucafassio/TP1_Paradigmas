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

class Empleado;

class Departamento{
    private:
        vector<shared_ptr<Empleado>> empleados;
        static int cantEmpleadosDepts;

    public:
        string nombre;
        string ubicacion;
    
        Departamento(string nombre, string ubicacion);

        static int contarEmpleados();
        vector<shared_ptr<Empleado>> getEmployees() const;
        bool contratarEmpleado(shared_ptr<Empleado> empleado);
        bool despedirEmpleado(shared_ptr<Empleado> empleado);
};

#endif