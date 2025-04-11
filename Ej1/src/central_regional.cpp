#include "central_regional.hpp"
#include "manager.hpp"
#include "empresa.hpp"
#include "departamento.hpp"

CentralRegional::CentralRegional(string nombre): 
    EntidadOrganizativa(nombre), cantEmpleados(0)
{}

int CentralRegional::getCantEmpleados() const {
    return this->cantEmpleados;
}

set<string> CentralRegional::getEmpNames() const {
    set<string> names;
    for (auto empresa : this->empresas)
        names.insert(empresa.nombre);
    return names;
}

vector<GerenteAlto> CentralRegional::getGerentesAlto() const {
    return this->gerentesAlto;
}

vector<GerenteMedio> CentralRegional::getGerentesMedio() const {
    return this->gerentesMedio;
}

GerenteAlto& CentralRegional::getGerenteAltoByName(string nombre){
    for (auto& gerente : this->gerentesAlto)
        if (gerente.nombre == nombre) return gerente;
    throw invalid_argument("El Gerente Alto no existe.");
}

GerenteMedio& CentralRegional::getGerenteMedioByName(string nombre){
    for (auto& gerente : this->gerentesMedio)
        if (gerente.nombre == nombre) return gerente;
    throw invalid_argument("El Gerente Medio no existe.");
}

void CentralRegional::agregarGerenteAlto(GerenteAlto gerenteAlto){
    if (gerentesAlto.size() < 5) {this->gerentesAlto.push_back(gerenteAlto); this->cantEmpleados++;}
    else cout << "No se pueden agregar mas gerentes altos." << endl;
}

void CentralRegional::agregarGerenteMedio(GerenteMedio gerenteMedio){
    if (gerentesMedio.size() < 20) {this->gerentesMedio.push_back(gerenteMedio); this->cantEmpleados++;}
    else cout << "No se pueden agregar mas gerentes medios." << endl;
}

void CentralRegional::agregarEmpresa(Empresa empresa){
    this->empresas.push_back(empresa);
    this->cantEmpleados += Departamento::contarEmpleados();
}

Empresa& CentralRegional::getEmpresaByName(string nombre){
    for (auto& empresa : this->empresas)
        if (empresa.nombre == nombre) return empresa;
    throw invalid_argument("La Empresa no existe.");
}

void CentralRegional::agregarPais(string pais){
    this->paises.insert(pais);
}

set<string> CentralRegional::getPaises() const {
    return this->paises;
}