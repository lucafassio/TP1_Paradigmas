#include "departamento.hpp"
#include "empleado.hpp"

int Departamento::cantEmpleadosDepts = 0;

Departamento::Departamento(string nombre, string ubicacion):
    nombre(nombre), ubicacion(ubicacion)
{}

int Departamento::contarEmpleados(){
    return cantEmpleadosDepts;
}

vector<shared_ptr<Empleado>> Departamento::getEmployees() const {
    return this->empleados;
}

bool Departamento::contratarEmpleado(shared_ptr<Empleado> empleado) {
    this->empleados.push_back(empleado);
    this->cantEmpleadosDepts++;
    return true;
}

bool Departamento::despedirEmpleado(shared_ptr<Empleado> empleado) {
    auto it = find(this->empleados.begin(), this->empleados.end(), empleado);
    if (it != empleados.end()){
        this->empleados.erase(it);
        this->cantEmpleadosDepts--;
        return true;
    }
    return false;
}