#include "entidad_organizativa.hpp"

EntidadOrganizativa::EntidadOrganizativa(string nombre): 
    nombre(nombre)
{}

void EntidadOrganizativa::agregarSubentidad(EntidadOrganizativa entidad){
    this->subentidades.push_back(entidad);
}

int EntidadOrganizativa::contarSubentidades() const {
    return this->subentidades.size();
}