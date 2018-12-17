//
// Created by pskoko on 12/15/18.
//

#ifndef LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP

#include "SuffixStructure.hpp"

template <typename T>
class StarSuffixStructure : public SuffixStructure<unsigned long>{
private:
    std::vector<unsigned long> text;
    SuffixStructure<T>& suffixStructure;

public:
    StarSuffixStructure(SuffixStructure<T>& suffixStructure);

};


#endif //LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP
