#include "bibliotecaFactory.h"
#include "bibliotecaFMI.h"
#include "bibliotecaDrept.h"
#include "bibliotecaLitere.h"
#include "bibliotecaIstorie.h"

Biblioteca* BibliotecaFactory::creeazaBiblioteca( const std::string& tip, const std::string& nume,const std::string& locatie) {
    if(tip=="FMI")
        return new BibliotecaFMI(nume,locatie);

    if(tip=="Drept")
        return new BibliotecaDrept(nume,locatie);

    if(tip=="Litere")
        return new BibliotecaLitere(nume,locatie);

    if(tip=="Istorie")
        return new BibliotecaIstorie(nume,locatie);

    return nullptr;
}
