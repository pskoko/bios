//
// Created by pskoko on 12/15/18.
//

#include <limits>
#include <algorithm>
#include <iostream>
#include <cmath>
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
    for(int i = 0; i <= getSize(); i++) {
        LCP(i) = std::numeric_limits<unsigned long>::max();
    }

    sType = std::vector<bool>(getSize()+1, false);
    sType[getSize()] = true;
    for(int i = getSize()-2; i >= 0; i--){
        if((*this)[i] < (*this)[i+1]) sType[i] = true;
        else if(((*this)[i] == (*this)[i+1]) && sType[i+1] == true) sType[i] = true;
    }

    for(int i = 0; i < getSize(); i++){
        if(isS(i)) bucketsSizesS[(*this)[i]]++;
        else bucketsSizesL[(*this)[i]]++;
    }
}

template<typename T>
bool SuffixStructure<T>::isSet(unsigned long index) const{
    if(accessed.empty()) return false;
    return accessed[index];
}

template<typename T>
bool SuffixStructure<T>::isLastInLBucket(unsigned long index, const T &t) {
    return (bucketIndices[t].first + bucketsSizesL[t]-1) == index;
}

template<typename T>
bool SuffixStructure<T>::isFirstInSBucket(unsigned long index, const T &t) {
    return bucketIndices[t].second - bucketsSizesS[t] +1 == index;
}

template <typename T>
unsigned long& SuffixStructure<T>::SA(const unsigned long index) {
    accessed.at(index) = true;
    return SA_data[index];
}

template <typename T>
unsigned long& SuffixStructure<T>::LCP(const unsigned long index) {
    return LCP_data[index];
}

template <typename T>
void SuffixStructure<T>::cleraAll() {
    std::vector<unsigned long>().swap(SA_data);
    std::vector<unsigned long>().swap(LCP_data);
    std::vector<bool>().swap(accessed);
    bucketsSizesL.clear();
    bucketsSizesS.clear();

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

    std::map<unsigned long, unsigned long> original;
    for( long i = 0; i <= getSize(); i++) {

        bool useSlow = false;
        if(alphabet.size() > std::sqrt(getSize())) useSlow = true;

        if(!isSet(i)) continue;

        if(induceLCP) {
            if(!useSlow) {
                for (T symbol : alphabet) {
                    M[symbol] = std::min(M[symbol], LCP(i));
                }
            }
        }

        if(((long)SA(i)-1) < 0 || !isL(SA(i)-1)) {
            continue;
        }

        // position of the induced suffix in SA/LCP
        unsigned long k = addToLBucket(SA(i) - 1);
        original[k] = i;

        if(induceLCP) {


            if (isLastInLBucket(k, (*this)[SA(i) - 1]) && k < getSize() && isSet(k+1) && (*this)[SA(k)] == (*this)[SA(k+1)]) {
                unsigned long lcp = 1;
                while (((SA(k + 1) + lcp) < getSize()) && ((SA(k) + lcp) < getSize()) &&
                       (*this)[SA(k) + lcp] == (*this)[SA(k + 1) + lcp]) {
                    lcp++;
                }
                LCP(k + 1) = lcp;
            }

            if (isFirstInLBucket(k, (*this)[SA(i) - 1])) {
                LCP(k) = 0;
            } else {
                unsigned long ip = original[k - 1];

                if ((SA(i) == getSize()) || (SA(ip) == getSize()) || (*this)[SA(i)] != (*this)[SA(ip)]) {
                    LCP(k) = 1;
                } else {
//                    LCP(k) = M[(*this)[SA(i)]] + 1; // wrong
                    if(!useSlow) {
                        LCP(k) = M[(*this)[SA(i) - 1]] + 1; // right
                    } else {
                        // if in doubt, use this down
                        unsigned long min = std::numeric_limits<unsigned long>::max();
                        for (int j = ip + 1; j <= i; j++) {
                            min = std::min(min, LCP(j));
                        }
//                    if(LCP(k)-1 != min){
//                        std::cerr << "min " << min << " LCP(k)" << LCP(k)-1 <<" i" << i << " ip" << ip << std::endl;
//                        std::cerr << (*this)[SA(i) - 1] << " " << (*this)[SA(i)] << std::endl;
//                    }
                        LCP(k) = min + 1;
                    }
                }
            }

            if(SA(i) == getSize()) continue;

            //M[(*this)[SA(i)]] = LCP(i);
            if(!useSlow) {
                M[(*this)[SA(i) - 1]] = std::numeric_limits<unsigned long>::max();
            }

        }
    }
}

template <typename T>
void SuffixStructure<T>::induceS(bool induceLCP) {

    bool useSlow = false;
    if(alphabet.size() > std::sqrt(getSize())) useSlow = true;
    std::map<T, unsigned long> M;

    if(!useSlow) {
        for (T symbol : alphabet) {
            M[symbol] = std::numeric_limits<unsigned long>::max();
        }
    }

    std::map<unsigned long, unsigned long> original;
    for(long i = getSize(); i >= 0; i--) {

        if (!isSet(i)) {
            continue;
        }

        if(((long)SA(i)-1) < 0 || !isS(SA(i)-1)) {

            if((long)SA(i) - 1 >= 0 && induceLCP && !useSlow) {
                M[(*this)[SA(i) - 1]] = LCP(i);
                for (T symbol : alphabet) {
                    M[symbol] = std::min(M[symbol], LCP(i));
                }
            }

            continue;
        }

        unsigned long t = SA(i) - 1;
        // position of the induced suffix in SA/LCP
        unsigned long k = addToSBucket(SA(i) - 1);        

        original[k] = i;
        if(induceLCP) {


            if (isFirstInSBucket(k, (*this)[SA(i) - 1])) {
                unsigned long lcp = 0;
                while (((SA(k - 1) + lcp) != getSize()) && ((SA(k) + lcp) != getSize()) &&
                       (*this)[SA(k - 1) + lcp] == (*this)[SA(k) + lcp]) {
                    lcp++;
                }

                LCP(k) = lcp;
            }

            if(isLastInSBucket(k, (*this)[SA(i) - 1])) {
                // don't do anything
            } else {
                unsigned long ip = original[k + 1];
                if ((SA(i) == getSize()) || (SA(ip) == getSize()) || (*this)[SA(i)] != (*this)[SA(ip)]) {
                    LCP(k + 1) = 1;
                } else {
                    //LCP(k + 1) = M[(*this)[SA(i)]] + 1;
                    if(!useSlow) {
                        LCP(k + 1) = M[(*this)[SA(i) - 1]] + 1;
                    } else {
                        unsigned long min = std::numeric_limits<unsigned long>::max();
                        for (int j = i + 1; j <= ip; j++) {
                            min = std::min(min, LCP(j));
                        }
//                    if(LCP(k+1)-1 != min){
//                        std::cerr << "min " << min << " LCP(k+1)" << LCP(k+1)-1 <<" i" << i << " ip" << ip << std::endl;
//                        std::cerr << (*this)[SA(i) - 1] << " " << (*this)[SA(i)] << std::endl;
//                    }
                        LCP(k + 1) = min + 1;
                    }
                }
            }

            if(SA(i) == getSize())  continue;
//
            if(!useSlow) {
                M[(*this)[SA(i) - 1]] = LCP(i);
                for (T symbol : alphabet) {
                    M[symbol] = std::min(M[symbol], LCP(i));
                }
            }
//            M[(*this)[SA(i)-1]] = std::numeric_limits<unsigned long>::max();

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
//    for(unsigned long t: starSuffixStructure.getText()){
//        std::cerr << t << " ";
//    }
//    std::cerr << std::endl;
    starSuffixStructure.induceArrays(induceLCp);


//
//    for(int i = 0; i <= starSuffixStructure.getSize(); i++){
//        std::cerr << starSuffixStructure.SA(i) << " ";
//    }
//    std::cerr << std::endl;
    std::cerr << "in fill" << std::endl;
    starSuffixStructure.fillSuffixStructure();
    std::cerr << "out fill" << std::endl;

   clearAdditionalStructure();
    induceL(induceLCp);
    induceS(induceLCp);

}

template<typename T>
bool SuffixStructure<T>::isFirstInLBucket(unsigned long index, const T &t) {
    return index == bucketIndices[t].first;
}

template<typename T>
bool SuffixStructure<T>::isLastInSBucket(unsigned long index, const T &t) {
    return index == bucketIndices[t].second;
}

template<typename T>
unsigned long SuffixStructure<T>::addToSBucketReversed(unsigned long suffix) {
    if(suffix == getSize()) {
        SA(0) = suffix;
        return 0;
    }
    T symbol = (*this)[suffix];
    long where = bucketIndices[symbol].second - bucketsSizesS[symbol] +1 + bucketsOffsetS[symbol];
    SA(where) = suffix;
    bucketsOffsetS[symbol]++;
    return where;
}
