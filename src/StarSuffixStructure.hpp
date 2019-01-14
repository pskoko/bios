//
// Created by pskoko on 12/15/18.
//

#ifndef LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP

#include "SuffixStructure.hpp"
#include <map>

template <typename E>
class StarSuffixStructure : public SuffixStructure<unsigned long>{
private:
    std::vector<unsigned long> text;
    SuffixStructure<E>& suffixStructure;
    std::vector<unsigned long> sortedStarSubstrings;
    bool completed = false;

public:
    StarSuffixStructure(SuffixStructure<E>& suffixStructure);
    bool compareStarSuffixes(unsigned long first, unsigned long second);
    void fillSuffixStructure();

    const unsigned long& operator[](const unsigned long index) const;
    unsigned long getSize() const;

    const std::vector<unsigned long>& getText() const;
    void induceArrays(bool induceLCp);

};

template class StarSuffixStructure<char>;
template class StarSuffixStructure<unsigned long>;
#endif //LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP
