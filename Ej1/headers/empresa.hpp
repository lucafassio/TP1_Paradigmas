#ifndef EMPRESA_HPP
#define EMPRESA_HPP

#include "entidad_organizativa.hpp"

class Departamento;

class Empresa : public EntidadOrganizativa{
    private:
        vector<shared_ptr<Departamento>> departamentos;

    public:
        string direccion;

        Empresa(string nombre, string direccion);
        
        shared_ptr<Departamento> getDepByName(string nombre) const;

        //aca en el UML dice que se debe devolver un vector a departamentos, pero como no coincide con
        //el nombre del metodo, por las dudas hice los dos casos.
        vector<shared_ptr<Departamento>> getDeps() const; //devuelve un vector de departamentos.
        vector<string> getDepNames() const; //devuelve los nombres de los departamentos.

        //como no hay un metodo para agregar departamentos, creo uno yo.
        bool agregarDepartamento(shared_ptr<Departamento> departamento);
};

#endif