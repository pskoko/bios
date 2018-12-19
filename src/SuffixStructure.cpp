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

    // std::map<T, unsigned long> M;

    // from current bucket to i' iteration in paper
    std::map<T,unsigned long> bucketToIPrime;

    T symbol, currBucket;
    unsigned long k; // position of the induced suffix in SA/LCP
    unsigned long i_; // i' in paper
    unsigned long min;
    unsigned long lcp;

    for(unsigned long i = 0; i <= getSize(); i++) {

        if(!isSet(i)) continue;

        if((SA(i)-1) < 0 || !isL(SA(i)-1)) {
            continue;
        }

        k = addToLBucket(SA(i) - 1);

        if(induceLCP) {

            currBucket = (*this)[SA(i)];

            if(isFirstInLBucket(k)) {
                bucketToIPrime[currBucket] = i;
                lcp = 0;
            } else {
                i_ = bucketToIPrime[currBucket];
                if(currBucket != (*this)[SA(i_)]) {
                    bucketToIPrime[currBucket] = i;
                    lcp = 1;
                } else {
                    min = LCP(i_+1);
                    for(unsigned long j = i_+2; j <= i; j++) {
                        if(LCP(j) < min) {
                            min = LCP(j);
                        }
                    }
                    lcp = min + 1;
                }
            }

            LCP(k) = lcp;

            if((k < getSize()) && isLastInLBucket(k)) {
                lcp = 0;
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