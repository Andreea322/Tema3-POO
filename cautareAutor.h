#ifndef CAUTAREAUTOR_H
#define CAUTAREAUTOR_H

#include "strategieCautare.h"

class CautareAutor : public StrategieCautare {
public:
    bool cauta( const Carte& c, const std::string& valoare) override{
        return c.getAutor()==valoare;
    }
};

#endif