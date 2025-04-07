#ifndef EMPLEADO_HPP
#define EMPLEADO_HPP

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

class Empleado{
    private:
        int antiguedad;
        float salario;

    public:
        string nombre;
        string puesto;
        
        Empleado(int antiguedad, float salario, string nombre, string puesto);

        int getAntiguedad() const;
        bool updateSalario(float nuevoSalario);
        float getSalario() const;
};

#endif