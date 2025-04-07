#include "manager.hpp"

Manager::Manager(string nombre, string puesto, int antiguedad, float salario, float bono, string level):
    Empleado(antiguedad, salario, nombre, puesto), bono(bono), level(level)
{}

bool Manager::updateBono(float nuevoBono) {
    if (nuevoBono > 0) {
        this->bono = nuevoBono;
        return true;
    }
    return false;
}

float Manager::getBono() const {
    return this->bono;
}

void Manager::setLevel(string nuevoLevel) {
    this->level = nuevoLevel;
}

GerenteAlto::GerenteAlto(string nombre, string puesto, int antiguedad, float salario, float bono, string level):
    Manager(nombre, puesto, antiguedad, salario, bono, level)
{}

GerenteMedio::GerenteMedio(string nombre, string puesto, int antiguedad, float salario, float bono, string level):
    Manager(nombre, puesto, antiguedad, salario, bono, level)
{}

GerenteBajo::GerenteBajo(string nombre, string puesto, int antiguedad, float salario, float bono, string level):
    Manager(nombre, puesto, antiguedad, salario, bono, level)
{}

LiderEquipo::LiderEquipo(string nombre, string puesto, int antiguedad, float salario, float bono, string level):
    Manager(nombre, puesto, antiguedad, salario, bono, level)
{}