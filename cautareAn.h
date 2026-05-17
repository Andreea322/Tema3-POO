#ifndef CAUTAREAN_H
#define CAUTAREAN_H

#include "strategieCautare.h"

class CautareAn : public StrategieCautare {
public:
    bool cauta( const Carte& c, const std::string& valoare) override{
        return std::to_string(c.getAn()) == valoare;
    }
};

#endif