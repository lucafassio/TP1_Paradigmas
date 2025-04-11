#include "departamento.hpp"

int Departamento::cantEmpleadosDepts = 0;

Departamento::Departamento(string nombre, string ubicacion):
    nombre(nombre), ubicacion(ubicacion)
{}

int Departamento::contarEmpleados(){
    return cantEmpleadosDepts;
}

vector<Empleado> Departamento::getEmployees() const {
    return this->empleados;
}

bool Departamento::contratarEmpleado(Empleado empleado){
    this->empleados.push_back(empleado);
    this->cantEmpleadosDepts++;
    return true;
}

bool Departamento::despedirEmpleado(Empleado empleado){
    for (int i=0; i<(int)empleados.size(); i++){
        if (empleados[i] == empleado){
            empleados.erase(empleados.begin() + i);
            this->cantEmpleadosDepts--;
            return true;
        }
    }
    return false;
}

Empleado& Departamento::getEmployeeByName(string nombre){
    for (auto& empleado : this->empleados)
        if (empleado.nombre == nombre) return empleado;
    throw invalid_argument("El Empleado no existe.");
}