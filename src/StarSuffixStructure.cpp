//
// Created by pskoko on 12/15/18.
//

#include "StarSuffixStructure.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <limits>

template <typename T>
StarSuffixStructure<T>::StarSuffixStructure(SuffixStructure<T>& _suffixStructure) : suffixStructure(_suffixStructure) {
    suffixStructure.generateStructures();

    long prev = -1;
    for (unsigned long suffixIndex = 0; suffixIndex <= suffixStructure.getSize(); suffixIndex++){
        if (suffixStructure.isSstar(suffixIndex)) {
            suffixStructure.addToSBucket(suffixIndex);

            if(prev != -1){
                starSizes[prev] = suffixIndex-prev;
            }
            prev = suffixIndex;
        }
    }

    starSizes[getSize()] = 0;
    suffixStructure.clearAdditionalStructure();

    suffixStructure.induceL(false);
    suffixStructure.induceS(false);


    for(unsigned long index = 0; index <= suffixStructure.getSize(); index++){
        if(suffixStructure.isSet(index) && suffixStructure.isSstar(suffixStructure.SA(index))){
            sortedStarSubstrings.push_back(suffixStructure.SA(index));
        }
    }

    std::cerr << "sorted " << sortedStarSubstrings.size() << std::endl;
    unsigned long currentStarSuffix = sortedStarSubstrings.at(0);
    unsigned long currentSymbol = 0;

    unsigned long numSymbols = 1;
    std::map<unsigned long, unsigned long> symbolMap;
    symbolMap[currentStarSuffix] = currentSymbol;
    for(unsigned long starSuffix: sortedStarSubstrings) {
        if(currentStarSuffix == starSuffix) continue;
        if(compareStarSuffixes(currentStarSuffix, starSuffix) == false){
            currentStarSuffix = starSuffix;
            currentSymbol++;
            numSymbols++;
        }
        symbolMap[starSuffix] = currentSymbol;
    }

    sortedStarSubstrings.clear();
    for(long i = 0; i <= suffixStructure.getSize(); i++){
        if(!suffixStructure.isSstar(i)) continue;
        text.push_back(symbolMap[i]);
        sortedStarSubstrings.push_back(i);
    }
    if(numSymbols == text.size()){
        completed = true;
    }
    suffixStructure.cleraAll();
}


template<typename T>
bool StarSuffixStructure<T>::compareStarSuffixes(unsigned long first, unsigned long second) {
    if(first == suffixStructure.getSize() || second == suffixStructure.getSize()) return false;

    bool start = true;
    while(true){
        if(!start && suffixStructure.isSstar(first) && suffixStructure.isSstar(second) && suffixStructure[first] == suffixStructure[second]) return true;
        if(suffixStructure.isSstar(first) != suffixStructure.isSstar(second)) return false;
        if(suffixStructure[first] != suffixStructure[second]) return false;
        first++;
        second++;
        start = false;
    }
}

template<typename T>
void StarSuffixStructure<T>::fillSuffixStructure() {

    for(long k = 2; k <= getSize(); k++) {
        unsigned long sum = 0;

        unsigned long first = -1;
        unsigned long second = -1;
        first = sortedStarSubstrings[SA(k - 1)];
        second = sortedStarSubstrings[SA(k)];
        //for (long i = 0; i <= LCP(k); i++) {
        //    first = sortedStarSubstrings[SA(k - 1) + i];
        //    second = sortedStarSubstrings[SA(k) + i];
        //    if(i != LCP(k)) {
        //        sum += second - first;
        //    }
        //}


        for(unsigned long i = 0; i < LCP(k) ; i++){

            sum += starSizes[sortedStarSubstrings[SA(k-1)+i]];
        }

        long j = 0;
        first += sum;
        second += sum;
        while((first + j) < suffixStructure.getSize() && (second + j) < suffixStructure.getSize() && suffixStructure[first + j] == suffixStructure[second + j]) {
            j++;
            sum++;
        }
        LCP(k) = sum;
    }

    suffixStructure.generateStructures();
    for(long i = 1; i <= getSize(); i++){
        unsigned long k = suffixStructure.addToSBucketReversed(sortedStarSubstrings[SA(i)]);
        suffixStructure.LCP(k) = LCP(i);
    }

}

template<typename T>
const unsigned long& StarSuffixStructure<T>::operator[](const unsigned long index) const{
    return text.at(index);
}

template<typename E>
unsigned long StarSuffixStructure<E>::getSize() const {
    return text.size();
}

template<typename E>
const std::vector<unsigned long> &StarSuffixStructure<E>::getText() const {
    return text;
}

template<typename E>
void StarSuffixStructure<E>::induceArrays(bool induceLCp) {
    if(completed){
        generateStructures();
        for(long i = 0; i <= getSize(); i++){
            insertSuffix(i);
            //LCP(i) = std::numeric_limits<unsigned long>::max();
            LCP(i) = 0;
        }
        //SA(0) = getSize();
        //LCP(0) = std::numeric_limits<unsigned long>::max()/2;
        return;
    }
    SuffixStructure::induceArrays(induceLCp);
}

