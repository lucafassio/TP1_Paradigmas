#ifndef ENTIDADORGANIZATIVA_HPP
#define ENTIDADORGANIZATIVA_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <memory>
#include <set>
using namespace std;

class EntidadOrganizativa {
    protected:
        vector<shared_ptr<EntidadOrganizativa>> subentidades;

    public:
        string nombre;
        
        EntidadOrganizativa(string nombre);

        void agregarSubentidad(shared_ptr<EntidadOrganizativa> entidad);
        int contarSubentidades() const;
};

#endif