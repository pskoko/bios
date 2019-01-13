//
// Created by pskoko on 12/15/18.
//

#include "StarSuffixStructure.hpp"
#include <algorithm>
#include <iterator>

template <typename T>
StarSuffixStructure<T>::StarSuffixStructure(SuffixStructure<T>& _suffixStructure) : suffixStructure(_suffixStructure) {
    suffixStructure.initSA();
    suffixStructure.generateStructures();
    for (unsigned long suffixIndex = 0; suffixIndex <= suffixStructure.getSize(); suffixIndex++){
        if (suffixStructure.isSstar(suffixIndex)) {
            suffixStructure.insertSuffix(suffixIndex);
        }
    }

    suffixStructure.induceL(false);
    suffixStructure.induceR(false);

    std::vector<unsigned long> sortedStarSubstrings;
    for(unsigned long index = 0; index <= suffixStructure.getSize(); index++){
        if(suffixStructure.isSASet(index) && suffixStructure.isSstar(suffixStructure.SA(index))){
            sortedStarSubstrings.push_back(suffixStructure.SA(index));
        }
    }

    text.push_back(0);

}
