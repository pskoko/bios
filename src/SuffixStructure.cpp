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
    std::map<T, unsigned long> M;
    unsigned long j;
    unsigned long lcp;
    T curr; // bucket symbol of the current index
    T prev; // bucket symbol of the previous index
    bool flag = false; // entering first bucket

    for(unsigned long i = 0; i <= getSize(); i++) {
        if(!isSet(i)) continue;
        // TODO: check if SA(index)-1 < 0
        if(isL(SA(i)-1)) addToLBucket(SA(i) - 1);

        if(induceLCP) {

            lcp = LCP(i);
            if(i > 0 && isFirstInSBucket(SA(i))) {
                lcp = 0;
                while((*this)[SA(i)+lcp] == (*this)[SA(i-1)+lcp]) {
                    lcp++;
                }
            }

            j = SA(i)-1;

            if(isFirstInLBucket(j)) {
                LCP(j) = 0;
                continue;
            }

            curr = (*this)[i];
            if(flag && curr != prev) {
                LCP(j) = 1;
                continue;
            }

            LCP = M[(*this)[j]] + 1;

            prev = curr;
            flag = true;
        }
    }
}

template <typename T>
void SuffixStructure<T>::induceS(bool induceLCP) {
    std::map<T, unsigned long> M;
    unsigned long j;
    unsigned long lcp;
    T curr; // bucket symbol of the current index
    T prev; // bucket symbol of the previous index
    bool flag = false; // entering first bucket

    for(unsigned long index = getSize(); index > 0; index--){
        if(!isSet(index)) continue;
        // TODO: check if SA(index)-1 < 0
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