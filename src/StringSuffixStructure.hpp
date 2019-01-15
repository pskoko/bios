/**
* @file StringSuffixStructure.h
* @brief this header file contains all required
* declarations for the StringSuffixStructure class implementing
* SuffixStructure for char type.
*
* @author pskoko
*
* @date 12/15/2018
*/

#ifndef LCP_INDUCING_STRINGSUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_STRINGSUFFIXSTRUCTURE_HPP

#include "SuffixStructure.hpp"
#include <string>

class StringSuffixStructure : public SuffixStructure<char> {
private:
    const std::string& text;

public:
    /**
    * Constructs a new StringSuffixStructure based on the provided string text reference.
    */
    StringSuffixStructure(const std::string& text);

    /**
    * Returns the character literal reference at the text provided index 
    */
    const char& operator[](const unsigned long index) const;

    /**
    * Returns the length of the text this suffix structure describes
    */
    unsigned long getSize() const;
};


#endif //LCP_INDUCING_STRINGSUFFIXSTRUCTURE_HPP
