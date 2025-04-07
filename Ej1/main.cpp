#include "headers/entidad_organizativa.hpp"
#include "headers/empresa.hpp"
#include "headers/central_regional.hpp"
#include "headers/departamento.hpp"
#include "headers/empleado.hpp"
#include "headers/manager.hpp"
using namespace std;

int main() {
    //creo 5 empleados, 2 gerentes altos y 3 medios.
    auto emp1 = make_shared<Empleado>(2, 50000, "Juan", "Analista");
    auto emp2 = make_shared<Empleado>(3, 52000, "Lucia", "Disenadora");
    auto emp3 = make_shared<Empleado>(1, 48000, "Mario", "QA");
    auto emp4 = make_shared<Empleado>(4, 60000, "Sofia", "Backend Dev");
    auto emp5 = make_shared<Empleado>(5, 62000, "Carlos", "Frontend Dev");

    auto gerenteAlto1 = make_shared<GerenteAlto>("Clara", "CTO", 10, 100000, 20000, "Alto");
    auto gerenteAlto2 = make_shared<GerenteAlto>("Eduardo", "CFO", 9, 98000, 18000, "Alto");

    auto gerenteMedio1 = make_shared<GerenteMedio>("Pedro", "Team Lead", 6, 75000, 10000, "Medio");
    auto gerenteMedio2 = make_shared<GerenteMedio>("Ana", "Tech Lead", 5, 72000, 10000, "Medio");
    auto gerenteMedio3 = make_shared<GerenteMedio>("Valeria", "QA Lead", 7, 70000, 9000, "Medio");

    //creo 3 departamentos y contrato empleados a cada uno.
    auto depto1 = make_shared<Departamento>("Desarrollo", "Oficina 1");
    auto depto2 = make_shared<Departamento>("Diseno", "Oficina 2");
    auto depto3 = make_shared<Departamento>("Calidad", "Oficina 3");

    depto1->contratarEmpleado(emp1);
    depto1->contratarEmpleado(emp4);
    depto2->contratarEmpleado(emp2);
    depto2->contratarEmpleado(emp5);
    depto3->contratarEmpleado(emp3);

    cout << "Se han creado 5 empleados, 2 gerentes altos y 3 medios." << endl;
    cout << "Se repartieron los empleados en 3 departamentos." << endl;
    cout << "Cantidad de empleados en todos los departamentos: " << Departamento::contarEmpleados() << endl;

    cout << endl << "Despido un empleado de un departamento." << endl;

    //despido un empleado
    depto2->despedirEmpleado(emp2);

    cout << "Cantidad despues de despedir: " << Departamento::contarEmpleados() << endl;

    //creo 2 empresas y agrego departamentos a cada una.
    auto empresa1 = make_shared<Empresa>("TechCorp", "Vito Dumas 284");
    auto empresa2 = make_shared<Empresa>("Designia", "Vito Dumas 285");

    empresa1->agregarDepartamento(depto1);
    empresa1->agregarDepartamento(depto3);
    empresa2->agregarDepartamento(depto2);

    //creo una central regional y agrego empresas y gerentes.
    CentralRegional central("LATAM", {"Argentina", "Uruguay"});
    central.agregarSubentidad(empresa1);
    central.agregarSubentidad(empresa2);

    central.agregarGerenteAlto(gerenteAlto1);
    central.agregarGerenteAlto(gerenteAlto2);
    central.agregarGerenteMedio(gerenteMedio1);
    central.agregarGerenteMedio(gerenteMedio2);
    central.agregarGerenteMedio(gerenteMedio3);

    cout << endl << "Departamentos en TechCorp:" << endl;
    for (auto nameDep : empresa1->getDepNames())
        cout << "- " << nameDep << endl;

    cout << endl << "Cantidad de gerentes altos: " << central.getGerentesAlto().size() << endl;
    cout << "Cantidad de gerentes medios: " << central.getGerentesMedio().size() << endl;

    //cambio el salario de un empleado y el bono de un gerente.
    cout << endl << "Salario original de Carlos: $" << emp5->getSalario() << endl;
    emp5->updateSalario(65000);
    cout << "Salario actualizado de Carlos: $" << emp5->getSalario() << endl;

    //cambio el bono de un gerente.
    cout << endl << "Bono original de Pedro (Team Lead): $" << gerenteMedio1->getBono() << endl;
    gerenteMedio1->updateBono(11000);
    cout << "Bono actualizado de Pedro: $" << gerenteMedio1->getBono() << endl;

    return 0;
}