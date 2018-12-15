//
// Created by pskoko on 12/15/18.
//

#include "StringSuffixStructure.hpp"

const char& StringSuffixStructure::operator[](const unsigned long index) const {
    return text[index];
}

unsigned long StringSuffixStructure::getSize() const {
    return text.size();
}