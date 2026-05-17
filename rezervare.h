#ifndef REZERVARE_H
#define REZERVARE_H

#include <string>
#include <ostream>
#include "client.h"

template<typename T>
class Rezervare {
private:
    std::string numeClient;
    std::string numeCarte;
    std::string biblioteca;
    T codRezervare;
public:
    Rezervare( const Client& client, const std::string& carte, const std::string& biblioteca, T cod);

    T getCod() const{
        return codRezervare;
    }

    std::string getClient() const{
        return numeClient;
    }

    std::string getCarte() const{
        return numeCarte;
    }

    std::string getBiblioteca() const{
        return biblioteca;
    }

    friend std::ostream& operator<<(std::ostream& out, const Rezervare<T>& r){
        out<<r.getClient()<<" a rezervat '"<<r.getCarte()<<"' la "<<r.getBiblioteca()<<" cod:"<<r.getCod();
        return out;
    }
    bool verificaCod(T cod) const {
        return codRezervare == cod;
    }
    std::string genereazaCodClient() const{
    return biblioteca.substr(0,3) + "-" + std::to_string(codRezervare) + "-" + numeClient.substr(0,3);
    }
};

template<typename T>
Rezervare<T>::Rezervare( const Client& client, const std::string& carte, const std::string& biblioteca, T cod) :numeClient(client.getNume() +" " +client.getPrenume()),numeCarte(carte),biblioteca(biblioteca),codRezervare(cod) { }

#endif