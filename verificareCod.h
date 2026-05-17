#ifndef VERIFICARECOD_H
#define VERIFICARECOD_H

#include <vector>

template<typename T>
bool existaCod(const std::vector<T>& coduri, T cod){
    for(const auto& c : coduri){
        if(c == cod){
            return true;
        }
    }
    return false;
}

#endif