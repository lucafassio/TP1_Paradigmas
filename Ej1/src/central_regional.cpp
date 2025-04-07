#include "central_regional.hpp"
#include "manager.hpp"
#include "empresa.hpp"

CentralRegional::CentralRegional(string nombre, set<string> paises): 
    EntidadOrganizativa(nombre), paises(paises), cantEmpleados(0)
{}

int CentralRegional::getCantEmpleados() const {
    return this->cantEmpleados;
}

set<string> CentralRegional::getEmpNames() const {
    set<string> names;
    for (auto empresa : this->empresas)
        names.insert(empresa->nombre);
    return names;
}

vector<shared_ptr<GerenteAlto>> CentralRegional::getGerentesAlto() const {
    return this->gerentesAlto;
}

vector<shared_ptr<GerenteMedio>> CentralRegional::getGerentesMedio() const {
    return this->gerentesMedio;
}

void CentralRegional::agregarGerenteAlto(shared_ptr<GerenteAlto> gerenteAlto){
    if (gerentesAlto.size() < 5) {this->gerentesAlto.push_back(gerenteAlto); this->cantEmpleados++;}
    else cout << "No se pueden agregar mas gerentes altos." << endl;
}
void CentralRegional::agregarGerenteMedio(shared_ptr<GerenteMedio> gerenteMedio){
    if (gerentesMedio.size() < 20) {this->gerentesMedio.push_back(gerenteMedio); this->cantEmpleados++;}
    else cout << "No se pueden agregar mas gerentes medios." << endl;
}