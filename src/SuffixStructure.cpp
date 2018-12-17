//
// Created by pskoko on 12/15/18.
//

#include "SuffixStructure.hpp"

template <typename T>
bool SuffixStructure<T>::isL(const unsigned long index) const {
    return !sType.at(index);
}

template <typename T>
bool SuffixStructure<T>::isS(const unsigned long index) const {
    return sType.at(index);
}

template <typename T>
bool SuffixStructure<T>::isSstar(const unsigned long index) const {
    if(index == 0) return false;
    return isS(index) && isL(index-1);
}

template <typename T>
void SuffixStructure<T>::induceL(bool induceLCP) {
    for(unsigned long index = 0; index <= getSize(); index++){
        if(!isSet(index)) continue;
        if(isL(SA(index)-1)) addToLBucket(SA(index) - 1);
    }
}

template <typename T>
void SuffixStructure<T>::induceR(bool induceLCP) {
    for(unsigned long index = getSize(); index > 0; index--){
        if(!isSet(index)) continue;
        if(isS(SA(index)-1)) addToSBucket(SA(index) - 1);
    }
}

template <typename T>
void SuffixStructure<T>::addToLBucket(unsigned long suffix) {
    T symbol = (*this)[suffix];

    SA(bucketIndices[symbol].first + bucketsOffsetL[symbol]) = suffix;
    bucketsOffsetL[symbol]++;
}

template <typename T>
void SuffixStructure<T>::addToSBucket(unsigned long suffix) {
    T symbol = (*this)[suffix];

    SA(bucketIndices[symbol].first - bucketsOffsetS[symbol]) = suffix;
    bucketsOffsetL[symbol]++;
}