#ifndef CAUTARETITLU_H
#define CAUTARETITLU_H

#include "strategieCautare.h"

class CautareTitlu : public StrategieCautare {
public:
    bool cauta( const Carte& c, const std::string& valoare) override{
        return c.getNume() == valoare;
    }
};
#endif