#include "empresa.hpp"
#include "departamento.hpp"

Empresa::Empresa(string nombre, string direccion): 
    EntidadOrganizativa(nombre), direccion(direccion) 
{}

Departamento& Empresa::getDepByName(string nombre){
    for (auto& departamento : this->departamentos)
        if (departamento.nombre == nombre) return departamento;
    throw invalid_argument("El Departamento no existe.");
}

vector<Departamento> Empresa::getDeps() const {
    return this->departamentos;
}

vector<string> Empresa::getDepNames() const {
    vector<string> names;
    for (auto departamento : this->departamentos)
        names.push_back(departamento.nombre);
    return names;
}

bool Empresa::agregarDepartamento(Departamento departamento){
    this->departamentos.push_back(departamento);
    return true;
}