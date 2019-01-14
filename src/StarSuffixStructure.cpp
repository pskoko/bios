//
// Created by pskoko on 12/15/18.
//

#include "StarSuffixStructure.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
StarSuffixStructure<T>::StarSuffixStructure(SuffixStructure<T>& _suffixStructure) : suffixStructure(_suffixStructure) {
    suffixStructure.generateStructures();
    for (unsigned long suffixIndex = 0; suffixIndex <= suffixStructure.getSize(); suffixIndex++){
        if (suffixStructure.isSstar(suffixIndex)) {
            suffixStructure.addToSBucket(suffixIndex);
        }
    }
    suffixStructure.clearAdditionalStructure();

    suffixStructure.induceL(false);
    suffixStructure.induceS(false);


    for(unsigned long index = 0; index <= suffixStructure.getSize(); index++){
        if(suffixStructure.isSet(index) && suffixStructure.isSstar(suffixStructure.SA(index))){
            sortedStarSubstrings.push_back(suffixStructure.SA(index));
        }
    }

    unsigned long currentStarSuffix = sortedStarSubstrings.at(0);
    unsigned long currentSymbol = 0;

    unsigned long numSymbols = 1;
    text.push_back(currentSymbol);
    for(unsigned long starSuffix: sortedStarSubstrings) {
        if(currentStarSuffix == starSuffix) continue;
        if(compareStarSuffixes(currentStarSuffix, starSuffix) == false){
            currentStarSuffix = starSuffix;
            currentSymbol++;
            numSymbols++;
        }
        text.push_back(currentSymbol);
    }

    if(numSymbols == text.size()){
        completed = true;
    }
    suffixStructure.cleraAll();
}


template<typename T>
bool StarSuffixStructure<T>::compareStarSuffixes(unsigned long first, unsigned long second) {
    if(first == getSize() || second == getSize()) return false;

    bool start = true;
    while(true){
        if(!start && suffixStructure.isSstar(first) && suffixStructure.isSstar(second)) return true;
        if(suffixStructure.isSstar(first) != suffixStructure.isSstar(second)) return false;
        if(suffixStructure[first] != suffixStructure[second]) return false;
        first++;
        second++;
        start = false;
    }
}

template<typename T>
void StarSuffixStructure<T>::fillSuffixStructure() {
    suffixStructure.generateStructures();
    for(long i = getSize(); i > 0; i--){
        suffixStructure.addToSBucket(sortedStarSubstrings[SA(i)]);
    }

}

template<typename T>
const unsigned long& StarSuffixStructure<T>::operator[](const unsigned long index) const{
    return text[index];
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
        for(long i = 1; i <= getSize(); i++){
            SA(i) = i-1;
            LCP(i) = 0;
        }
        SA(0) = getSize();
        return;
    }
    SuffixStructure::induceArrays(induceLCp);
}

