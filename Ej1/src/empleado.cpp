#include "empleado.hpp"

Empleado::Empleado(int antiguedad, float salario, string nombre, string puesto):
    antiguedad(antiguedad), salario(salario), nombre(nombre), puesto(puesto) 
{}

int Empleado::getAntiguedad() const {
    return this->antiguedad;
}

bool Empleado::updateSalario(float nuevoSalario){
    if (nuevoSalario > 0){
        this->salario = nuevoSalario;
        return true;
    }
    return false;
}

float Empleado::getSalario() const {
    return this->salario;
}

bool Empleado::operator==(const Empleado& other) const {
    if (this->nombre != other.nombre) return false;
    if (this->puesto != other.puesto) return false;
    if (this->antiguedad != other.antiguedad) return false;
    if (this->salario != other.salario) return false;
    return true;
}