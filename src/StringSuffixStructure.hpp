//
// Created by pskoko on 12/15/18.
//

#ifndef LCP_INDUCING_STRINGSUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_STRINGSUFFIXSTRUCTURE_HPP

#include "SuffixStructure.hpp"
#include <string>

class StringSuffixStructure : public SuffixStructure<char> {
private:
    const std::string& text;

public:
    StringSuffixStructure(const std::string& text);
    const char& operator[](const unsigned long index) const;
    unsigned long getSize() const;
};


#endif //LCP_INDUCING_STRINGSUFFIXSTRUCTURE_HPP
