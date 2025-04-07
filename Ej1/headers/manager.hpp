#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "empleado.hpp"

class Manager : public Empleado{
    private:
        float bono;
        string level;

    public:
        Manager(string nombre, string puesto, int antiguedad, float salario, float bono, string level);

        bool updateBono(float nuevoBono);
        float getBono() const;
        void setLevel(string nuevoLevel);
};

class GerenteAlto : public Manager{
    public:
        GerenteAlto(string nombre, string puesto, int antiguedad, float salario, float bono, string level);
};

class GerenteMedio : public Manager{
    public:
        GerenteMedio(string nombre, string puesto, int antiguedad, float salario, float bono, string level);
};

class GerenteBajo : public Manager{
    public:
        GerenteBajo(string nombre, string puesto, int antiguedad, float salario, float bono, string level);
};

class LiderEquipo : public Manager{
    public:
        LiderEquipo(string nombre, string puesto, int antiguedad, float salario, float bono, string level);
};

#endif