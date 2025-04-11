#include "headers/entidad_organizativa.hpp"
#include "headers/empresa.hpp"
#include "headers/central_regional.hpp"
#include "headers/departamento.hpp"
#include "headers/empleado.hpp"
#include "headers/manager.hpp"
using namespace std;

int main(){
    CentralRegional central("LATAM");

    central.agregarPais("Uruguay");
    central.agregarPais("Argentina");
    central.agregarPais("Argentina");

    cout << endl << "Paises que abarca la central regional:" << endl;
    for (auto pais : central.getPaises())
        cout << "- " << pais << endl;

    //creo dos empresas para mostrar que cumplen con la condicion de unique y ordered.
    //luego, voy a operar en una sola empresa ya que sino pierde el sentido el contador estatico de
    //Departamentos. Estaria contando los empleados de todas las empresas.

    central.agregarEmpresa(Empresa("TechCorp", "Vito Dumas 284"));
    central.agregarEmpresa(Empresa("Designia", "Vito Dumas 285"));
    central.agregarEmpresa(Empresa("TechCorp", "Vito Dumas 284"));

    cout << endl << "Empresas en la central regional:" << endl;
    for (auto empresa : central.getEmpNames())
        cout << "- " << empresa << endl;
    
    //creo departamentos y contrato empleados.
    central.getEmpresaByName("TechCorp").agregarDepartamento(Departamento("Desarrollo", "Oficina 1"));
    central.getEmpresaByName("TechCorp").agregarDepartamento(Departamento("Diseño", "Oficina 2"));
    central.getEmpresaByName("TechCorp").agregarDepartamento(Departamento("Calidad", "Oficina 3"));

    cout << endl << "Departamentos en TechCorp:" << endl;
    for (auto nameDep : central.getEmpresaByName("TechCorp").getDepNames())
        cout << "- " << nameDep << endl;

    central.getEmpresaByName("TechCorp").getDepByName("Desarrollo").contratarEmpleado(Empleado(2, 50000, "Juan", "Analista"));
    central.getEmpresaByName("TechCorp").getDepByName("Desarrollo").contratarEmpleado(Empleado(3, 52000, "Lucia", "Disenadora"));
    central.getEmpresaByName("TechCorp").getDepByName("Diseño").contratarEmpleado(Empleado(1, 48000, "Mario", "QA"));
    central.getEmpresaByName("TechCorp").getDepByName("Calidad").contratarEmpleado(Empleado(4, 60000, "Sofia", "Backend Dev"));
    central.getEmpresaByName("TechCorp").getDepByName("Calidad").contratarEmpleado(Empleado(5, 62000, "Carlos", "Frontend Dev"));

    cout << "Se repartieron los empleados en 3 departamentos." << endl;
    cout << "Cantidad de empleados en todos los departamentos: " << Departamento::contarEmpleados() << endl;

    cout << endl << "Despido un empleado de un departamento." << endl;

    central.getEmpresaByName("TechCorp").getDepByName("Desarrollo").despedirEmpleado(Empleado(2, 50000, "Juan", "Analista"));

    cout << "Cantidad despues de despedir: " << Departamento::contarEmpleados() << endl;

    cout << endl << "Lista de empleados en el departamento de Desarrollo:" << endl;
    for (auto empleado : central.getEmpresaByName("TechCorp").getDepByName("Desarrollo").getEmployees()){
        cout << "- " << empleado.nombre << " (" << empleado.puesto << ")" << endl;
    }

    cout << endl << "Agrego gerentes a la central." << endl;

    central.agregarGerenteAlto(GerenteAlto("Clara", "CTO", 10, 100000, 20000, LEVEL_1));
    central.agregarGerenteAlto(GerenteAlto("Eduardo", "CFO", 9, 98000, 18000, LEVEL_1));
    central.agregarGerenteAlto(GerenteAlto("Mariana", "COO", 8, 95000, 15000, LEVEL_1));
    central.agregarGerenteAlto(GerenteAlto("Javier", "CEO", 12, 120000, 25000, LEVEL_1));

    //estos no entran.
    central.agregarGerenteAlto(GerenteAlto("Luciana", "CIO", 11, 110000, 22000, LEVEL_1));
    central.agregarGerenteAlto(GerenteAlto("Fernando", "CMO", 13, 115000, 23000, LEVEL_1));

    //estos tambien estan limitados a 20 pero no los agregue todos.
    central.agregarGerenteMedio(GerenteMedio("Pedro", "Team Lead", 6, 75000, 10000, LEVEL_2));
    central.agregarGerenteMedio(GerenteMedio("Ana", "Tech Lead", 5, 72000, 10000, LEVEL_2));
    central.agregarGerenteMedio(GerenteMedio("Valeria", "QA Lead", 7, 70000, 9000, LEVEL_2));
    cout << endl << "Se crean empresas y una central regional." << endl;

    cout << endl << "Gerentes altos en la central regional:" << endl;
    for (auto gerente : central.getGerentesAlto())
        cout << "- " << gerente.nombre << " (" << gerente.puesto << ")" << endl;

    cout << endl << "Gerentes medios en la central regional:" << endl;
    for (auto gerente : central.getGerentesMedio())
        cout << "- " << gerente.nombre << " (" << gerente.puesto << ")" << endl;

    cout << endl << "Pruebas de salario y bono:" << endl;
    //cambio el salario de un empleado y el bono de un gerente.
    cout << "Salario original de Carlos: $" << central.getEmpresaByName("TechCorp").getDepByName("Calidad").getEmployeeByName("Carlos").getSalario() << endl;
    central.getEmpresaByName("TechCorp").getDepByName("Calidad").getEmployeeByName("Carlos").updateSalario(65000);
    cout << "Cambio el salario de Carlos a $65000." << endl;
    cout << "Salario actualizado de Carlos: $" << central.getEmpresaByName("TechCorp").getDepByName("Calidad").getEmployeeByName("Carlos").getSalario() << endl;

    //cambio el bono de un gerente.
    cout << endl << "Bono original de Pedro (Team Lead): $" << central.getGerenteMedioByName("Pedro").getBono() << endl;
    central.getGerenteMedioByName("Pedro").updateBono(11000);
    cout << "Cambio el bono de Pedro a $11000." << endl;
    cout << "Bono actualizado de Pedro: $" << central.getGerenteMedioByName("Pedro").getBono() << endl;

    return 0;
}