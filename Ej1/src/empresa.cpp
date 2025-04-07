#include "empresa.hpp"
#include "departamento.hpp"

Empresa::Empresa(string nombre, string direccion): 
    EntidadOrganizativa(nombre), direccion(direccion) 
{}

shared_ptr<Departamento> Empresa::getDepByName(string nombre) const {
    for (auto departamento : this->departamentos)
        if (departamento->nombre == nombre) return departamento;
    return nullptr;
}

vector<shared_ptr<Departamento>> Empresa::getDeps() const {
    return this->departamentos;
}

vector<string> Empresa::getDepNames() const {
    vector<string> names;
    for (auto departamento : this->departamentos)
        names.push_back(departamento->nombre);
    return names;
}

bool Empresa::agregarDepartamento(shared_ptr<Departamento> departamento) {
    this->departamentos.push_back(departamento);
    return true;
}