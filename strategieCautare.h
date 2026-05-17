#ifndef STRATEGIECAUTARE_H
#define STRATEGIECAUTARE_H

#include <string>
#include "carte.h"

class StrategieCautare {
public:
    virtual bool cauta( const Carte& c, const std::string& valoare ) = 0;

    virtual ~StrategieCautare() = default;
};
#endif