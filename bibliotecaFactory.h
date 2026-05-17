#ifndef BIBLIOTECAFACTORY_H
#define BIBLIOTECAFACTORY_H
#include "biblioteca.h"

class BibliotecaFactory {
public:
static Biblioteca* creeazaBiblioteca( const std::string& tip, const std::string& nume, const std::string& locatie );
};
#endif