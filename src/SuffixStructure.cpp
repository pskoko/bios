//
// Created by pskoko on 12/15/18.
//

#include "SuffixStructure.hpp"

bool SuffixStructure::isL(const unsigned long index) const {
    return !sType.at(index);
}

bool SuffixStructure::isS(const unsigned long index) const {
    return sType.at(index);
}

bool SuffixStructure::isSstar(const unsigned long index) const {
    if(index == 0) return false;
    return isS(index) && isL(index-1);
}
