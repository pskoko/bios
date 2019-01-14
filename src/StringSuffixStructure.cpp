//
// Created by pskoko on 12/15/18.
//

#include "StringSuffixStructure.hpp"

StringSuffixStructure::StringSuffixStructure(const std::string &text_) : text{text_} {}
const char& StringSuffixStructure::operator[](const unsigned long index) const {
    return text.at(index);
}

unsigned long StringSuffixStructure::getSize() const {
    return text.size();
}