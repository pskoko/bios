//
// Created by pskoko on 12/15/18.
//

#include <limits>
#include <algorithm>
#include <iostream>
#include "SuffixStructure.hpp"
#include "StarSuffixStructure.hpp"

template <typename T>
void SuffixStructure<T>::generateStructures() {
    std::map<T, unsigned int> counts;
    for(unsigned int i = 0; i < getSize(); i++){
        T symbol = (*this)[i];
        counts[symbol]++;
        alphabet.insert(symbol);
    }

    unsigned int position = 1;
    for(T symbol: alphabet){
        bucketIndices[symbol] = std::make_pair(position, position + counts[symbol]-1);
        position += counts[symbol];
    }

    SA_data = std::vector<unsigned long>(getSize()+1);
    LCP_data = std::vector<unsigned long>(getSize()+1);
    accessed = std::vector<bool>(getSize()+1, false);

    sType = std::vector<bool>(getSize()+1, false);
    sType[getSize()] = true;
    for(int i = getSize()-2; i >= 0; i--){
        if((*this)[i] < (*this)[i+1]) sType[i] = true;
        else if((*this)[i] == (*this)[i+1] && sType[i+1]) sType[i] = true;
    }
}

template<typename T>
bool SuffixStructure<T>::isSet(unsigned long index) const{
    if(accessed.empty()) return false;
    return accessed[index];
}

template<typename T>
bool SuffixStructure<T>::isFirstInLBucket(unsigned long index) {
    return false;
}

template<typename T>
bool SuffixStructure<T>::isLastInLBucket(unsigned long index) {
    return false;
}

template<typename T>
bool SuffixStructure<T>::isFirstInSBucket(unsigned long index) {
    return false;
}

template<typename T>
bool SuffixStructure<T>::isLastInSBucket(unsigned long index) {
    return false;
}

template <typename T>
unsigned long& SuffixStructure<T>::SA(const unsigned long index) {
    accessed.at(index) = true;
    return SA_data[index];
}

template <typename T>
unsigned long& SuffixStructure<T>::LCP(const unsigned long index) {
    accessed[index] = true;
    return LCP_data[index];
}

template <typename T>
void SuffixStructure<T>::cleraAll() {
    std::vector<unsigned long>().swap(SA_data);
    std::vector<unsigned long>().swap(LCP_data);
    std::vector<bool>().swap(accessed);
    clearAdditionalStructure();
}

template <typename T>
void SuffixStructure<T>::clearAdditionalStructure() {
    bucketsOffsetL.clear();
    bucketsOffsetS.clear();
}
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

    for( long i = 0; i <= getSize(); i++) {

        if(!isSet(i)) continue;

        if(((long)SA(i)-1) < 0 || !isL(SA(i)-1)) {
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

    for(long i = getSize(); i >= 0; i--) {

        if(!isSet(i)) continue;

        if(((long)SA(i)-1) < 0 || !isS(SA(i)-1)) {
            continue;
        }

        unsigned long t = SA(i) - 1;
        // position of the induced suffix in SA/LCP
        unsigned long k = addToSBucket(SA(i) - 1);

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
    if(suffix == getSize()) {
        SA(0) = suffix;
        return 0;
    }
    T symbol = (*this)[suffix];

    SA(bucketIndices[symbol].first + bucketsOffsetL[symbol]) = suffix;
    bucketsOffsetL[symbol]++;

    return bucketIndices[symbol].first + bucketsOffsetL[symbol] - 1;
}

template <typename T>
unsigned long SuffixStructure<T>::addToSBucket(unsigned long suffix) {
    if(suffix == getSize()) {
        SA(0) = suffix;
        return 0;
    }
    T symbol = (*this)[suffix];

    SA(bucketIndices[symbol].second - bucketsOffsetS[symbol]) = suffix;
    bucketsOffsetS[symbol]++;

    return bucketIndices[symbol].second - bucketsOffsetS[symbol] + 1;
}

template<typename T>
void SuffixStructure<T>::insertSuffix(unsigned long suffix) {
    if(isS(suffix)) addToSBucket(suffix);
    else addToLBucket(suffix);
}

template<typename T>
void SuffixStructure<T>::induceArrays(bool induceLCp) {
    generateStructures();
    StarSuffixStructure starSuffixStructure(*this);
    starSuffixStructure.induceArrays(induceLCp);

    std::cerr << "in" << std::endl;
//    for(unsigned long t: starSuffixStructure.getText()){
//        std::cerr << t << " ";
//    }
//    std::cerr << std::endl;
    starSuffixStructure.fillSuffixStructure();

    clearAdditionalStructure();
    induceL(induceLCp);
    induceS(induceLCp);

}
