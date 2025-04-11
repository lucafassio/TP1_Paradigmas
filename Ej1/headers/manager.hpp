#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "empleado.hpp"

enum Levels{
    LEVEL_1,
    LEVEL_2,
    LEVEL_3
};

class Manager : public Empleado{
    private:
        float bono;
        Levels level;

    public:
        Manager(string nombre, string puesto, int antiguedad, float salario, float bono, Levels level);

        bool updateBono(float nuevoBono);
        float getBono() const;
        void setLevel(Levels nuevoLevel);
};

class GerenteAlto : public Manager{
    public:
        GerenteAlto(string nombre, string puesto, int antiguedad, float salario, float bono, Levels level);
};

class GerenteMedio : public Manager{
    public:
        GerenteMedio(string nombre, string puesto, int antiguedad, float salario, float bono, Levels level);
};

class GerenteBajo : public Manager{
    public:
        GerenteBajo(string nombre, string puesto, int antiguedad, float salario, float bono, Levels level);
};

class LiderEquipo : public Manager{
    public:
        LiderEquipo(string nombre, string puesto, int antiguedad, float salario, float bono, Levels level);
};

#endif