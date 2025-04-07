#ifndef CENTRALREGIONAL_HPP
#define CENTRALREGIONAL_HPP

#include "entidad_organizativa.hpp"

class GerenteAlto;
class GerenteMedio;
class Empresa;

class CentralRegional : public EntidadOrganizativa{
    private:
        set<string> paises;
        int cantEmpleados;
        vector<shared_ptr<GerenteAlto>> gerentesAlto;
        vector<shared_ptr<GerenteMedio>> gerentesMedio;
        vector<shared_ptr<Empresa>> empresas;

    public:
        CentralRegional(string nombre, set<string> paises);

        int getCantEmpleados() const;
        set<string> getEmpNames() const;
        vector<shared_ptr<GerenteAlto>> getGerentesAlto() const;
        vector<shared_ptr<GerenteMedio>> getGerentesMedio() const;

        //metodos agregados por mi para el main.
        void agregarGerenteAlto(shared_ptr<GerenteAlto> gerenteAlto);
        void agregarGerenteMedio(shared_ptr<GerenteMedio> gerenteMedio);
        void agregarEmpresa(shared_ptr<Empresa> empresa);
};

#endif