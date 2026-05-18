#include <iostream>
#include "catalog.h"
#include "bibliotecaFactory.h"
#include "client.h"
#include "exceptii.h"
#include "carte.h"
#include "cautareTitlu.h"
#include "cautareAutor.h"
#include "cautareAn.h"
#include "verificareCod.h"
#include <vector>
#include <fstream>

std::string stergere_(const std::string& text) {
    std::string rezultat = text;
    for (auto& c : rezultat) {
        if (c == '_')
            c = ' ';
    }
    return rezultat;
}

int main() {

    std::cout << "===== Sistem de gestionare a unor biblioteci =====\n";

    Catalog& catalog=Catalog::getInstance();

    Biblioteca* fmi = BibliotecaFactory::creeazaBiblioteca( "FMI", "FMI", "Bucuresti");
    Biblioteca* drept = BibliotecaFactory::creeazaBiblioteca( "Drept", "Drept", "Bucuresti");
    Biblioteca* litere = BibliotecaFactory::creeazaBiblioteca( "Litere", "Litere", "Bucuresti");
    Biblioteca* istorie = BibliotecaFactory::creeazaBiblioteca( "Istorie", "Istorie", "Bucuresti");

    catalog.adaugaBiblioteca(fmi);
    catalog.adaugaBiblioteca(drept);
    catalog.adaugaBiblioteca(litere);
    catalog.adaugaBiblioteca(istorie);

    std::string tip, nume, autor;
    int an;
    std::ifstream fin("carti.txt");

    while (fin >> tip >> nume >> autor >> an) {
        nume = stergere_(nume);
        autor = stergere_(autor);

        Biblioteca* b = catalog.getBiblioteca(tip);
        if (b)
            b->adaugaCarte(Carte(nume, autor, an));
        else
            std::cout << "Tip necunoscut\n";
    }

    std::cout << "\n--- Biblioteci ---\n";
    catalog.afiseazaBiblioteci(std::cout);

    std::string raspunsCautare;
    std::cout<<"\nDoresti sa cauti ceva? ";
    std::cin>>raspunsCautare;

    while(raspunsCautare=="Da" || raspunsCautare=="da"){
        std::string tipCautare;
        std::cout<<"\nCum vrei sa cauti?\n";
        std::cout<<"1. Dupa titlu\n2. Dupa autor\n3. Dupa an\n";
        std::cin>>tipCautare;
        std::string valoare;
        if(tipCautare=="1"){
            catalog.setStrategie(new CautareTitlu());
            std::cout<<"Introdu titlul: ";
        } else if(tipCautare=="2") {
            catalog.setStrategie(new CautareAutor());
            std::cout<<"Introdu autorul: ";
        } else{
            catalog.setStrategie(new CautareAn());
            std::cout<<"Introdu anul: ";
        }
        std::cin>>valoare;
        valoare=stergere_(valoare);
        catalog.cautaCarte(valoare,std::cout);
        std::cout<<"\nMai doresti sa cauti ceva? ";
        std::cin>>raspunsCautare;
    }

    std::string raspuns;
    std::cout << "\nVrei sa faci o rezervare? ";
    std::cin >> raspuns;

    while (raspuns == "Da" || raspuns == "da") {

        std::string numeC, prenumeC, telefon;

        std::cout << "Nume: ";
        std::cin >> numeC;

        std::cout << "Prenume: ";
        std::cin >> prenumeC;

        std::cout << "Telefon: ";
        std::cin >> telefon;

        Client client(numeC, prenumeC, telefon);

        std::string carteRez;
        std::cout << "Introdu cartea dorita: ";
        std::cin >> carteRez;
        carteRez = stergere_(carteRez);

        std::string tipBib;
        std::cout << "Biblioteca (FMI/Drept/Litere): ";
        std::cin >> tipBib;

        try {
            Biblioteca* b = catalog.getBiblioteca(tipBib);

            if (!b)
                throw BibliotecaException("Biblioteca invalida!");

            Rezervare<int> r= b->rezervaCarte(client, carteRez);

            std::cout << "Rezervare realizata cu succes!\n";
            std::cout<< "Codul rezervarii dumneavoastra este: "<<r.genereazaCodClient()<<"/n";

        } catch (const BibliotecaException& e) {
            std::cout << "Eroare: " << e.what() << "\n";
        }

        std::cout << "\nMai vrei sa faci o rezervare? ";
        std::cin >> raspuns;
    }

    std::string alegere;
    std::cout << "\nDin ce biblioteca vrei sa vezi rezervarile? (FMI/Drept/Litere): ";
    std::cin >> alegere;

    catalog.afiseazaRezervariBiblioteca(alegere, std::cout);

    std::cout << "\n--- Toate rezervarile ---\n";
    catalog.afiseazaToateRezervarile(std::cout);

    std::string raspunsVerificare;  
    std::cout<<"\nVrei sa verifici vreo rezervare? ";
    std::cin>>raspunsVerificare;
    std::vector<int> coduriInt;
    std::vector<std::string>coduriString;
    
    if(raspunsVerificare=="Da" || raspunsVerificare=="da"){
        std::vector<std::string> biblioteci= { "FMI", "Drept", "Litere", "Istorie"};

        for( const auto& numeBib:biblioteci){
            Biblioteca* b=catalog.getBiblioteca(numeBib);
            if(b){
                for(const auto& r: b->getRezervari()){
                    coduriInt.push_back(r.getCod());
                    coduriString.push_back(r.genereazaCodClient());
                }
            }
        } 
    }
    while(raspunsVerificare=="Da" || raspunsVerificare=="da"){
         std::cout<<"\nCum doresti sa cauti?\n";
         std::cout<<"1. Dupa codul unic\n";
         std::cout<<"2. Dupa codul complet\n";
         std::string alegere;
        std::cin>>alegere;
        bool gasit=false;
        if(alegere=="1") {
            int cod;
            std::cout<<"Introdu codul unic: ";
            std::cin>>cod;
            gasit=existaCod(coduriInt,cod);
        } else{
            std::string cod;
            std::cout <<"Introdu codul complet: ";
            std::cin>>cod;
            gasit=existaCod(coduriString,cod);
        }

        if(gasit){
            std::cout<<"\nRezervarea exista!\n";
        } else{
            std::cout<<"\nRezervare inexistenta!\n";
        }
        std::cout<<"\nMai vrei sa verifici o rezervare? ";
        std::cin >>raspunsVerificare;
    }

    std::cout << "\nTotal biblioteci: ";
    std::cout << Biblioteca::getTotalBiblioteci() << "\n";

    return 0;
}
