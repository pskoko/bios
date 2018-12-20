//
// Created by pskoko on 12/15/18.
//

#include <limits>
#include <algorithm>
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
    for (T symbol : alphabet) {
        M[symbol] = std::numeric_limits<unsigned long>::max();
    }

    for(unsigned long i = 0; i < getSize(); i++) {

        if(!isSet(i)) continue;

        if((SA(i)-1) < 0 || !isL(SA(i)-1)) {
            continue;
        }

        // position of the induced suffix in SA/LCP
        unsigned long k = addToLBucket(SA(i) - 1);

        if(induceLCP) {

            for (T symbol : alphabet) {
                M[symbol] = std::min(M[symbol], LCP(i));
            }

            if(isFirstInLBucket(k)) {
                LCP(k) = 0;
            } else {
                LCP(k) = M[(*this)[SA(i)-1]] + 1;
            }

            M[(*this)[SA(i)-1]] = std::numeric_limits<unsigned long>::max();

            // last symbol in alphabet (lexicographic greatest symbol) has no S-type suffixes
            // so that's why we need to check if k is the last index
            if((k < (getSize()-1)) && isLastInLBucket(k)) {
                unsigned long lcp = 0;
                while((*this)[SA(k)+lcp] == (*this)[SA(k+1)+lcp]) {
                    lcp++;
                }

                LCP(k+1) = lcp;
            }

        }
    }
}

template <typename T>
void SuffixStructure<T>::induceS(bool induceLCP) {

    std::map<T, unsigned long> M;
    for (T symbol : alphabet) {
        M[symbol] = std::numeric_limits<unsigned long>::max();
    }

    for(unsigned long i = getSize()-1; i >= 0; i--) {

        if(!isSet(i)) continue;

        if((SA(i)-1) < 0 || !isS(SA(i)-1)) {
            continue;
        }

        // position of the induced suffix in SA/LCP
        unsigned long k = addToLBucket(SA(i) - 1);

        if(induceLCP) {

            for (T symbol : alphabet) {
                M[symbol] = std::min(M[symbol], LCP(i));
            }

            if(isLastInSBucket(k)) {
                // pass
            } else {
                LCP(k+1) = M[(*this)[SA(i)-1]] + 1;
            }

            M[(*this)[SA(i)-1]] = std::numeric_limits<unsigned long>::max();

            // there is no L-type suffix that starts with the smallest symbol in alphabet, e.g. '$'
            // so that's why we need to check if k > 0
            if(k > 0 && isFirstInSBucket(k)) {
                unsigned long lcp = 0;
                while((*this)[SA(k-1)+lcp] == (*this)[SA(k)+lcp]) {
                    lcp++;
                }

                LCP(k) = lcp;
            }

        }
    }
}

template <typename T>
unsigned long SuffixStructure<T>::addToLBucket(unsigned long suffix) {
    T symbol = (*this)[suffix];

    SA(bucketIndices[symbol].first + bucketsOffsetL[symbol]) = suffix;
    bucketsOffsetL[symbol]++;

    return bucketIndices[symbol].first + bucketsOffsetL[symbol] - 1;
}

template <typename T>
unsigned long SuffixStructure<T>::addToSBucket(unsigned long suffix) {
    T symbol = (*this)[suffix];

    SA(bucketIndices[symbol].first - bucketsOffsetS[symbol]) = suffix;
    bucketsOffsetL[symbol]++;

    return bucketIndices[symbol].first - bucketsOffsetS[symbol] + 1;
}