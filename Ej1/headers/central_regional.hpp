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
        vector<GerenteAlto> gerentesAlto;
        vector<GerenteMedio> gerentesMedio;
        vector<Empresa> empresas;

    public:
        CentralRegional(string nombre);

        int getCantEmpleados() const;
        set<string> getEmpNames() const;
        vector<GerenteAlto> getGerentesAlto() const;
        vector<GerenteMedio> getGerentesMedio() const;

        //metodos agregados por mi exclusivamente para demostrar funcionalidad en el main. Se que no son parte del
        //UML original pero son necesarios para demostrar que los que si estan, funcionan.
        GerenteAlto& getGerenteAltoByName(string nombre);
        GerenteMedio& getGerenteMedioByName(string nombre);
        void agregarGerenteAlto(GerenteAlto gerenteAlto);
        void agregarGerenteMedio(GerenteMedio gerenteMedio);
        void agregarEmpresa(Empresa empresa);
        Empresa& getEmpresaByName(string nombre);
        void agregarPais(string pais);
        set<string> getPaises() const;
};

#endif