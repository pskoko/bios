//
// Created by pskoko on 1/12/19.
//
#include "catch2/catch.hpp"
#include <StringSuffixStructure.hpp>
#include <iostream>
#include "StarSuffixStructure.hpp"

template <typename T>
bool compareSA(const std::vector<long>& first, SuffixStructure<T>& sa){
    if(first.size() != sa.getSize()+1) return false;
    for(int i = 0; i < first.size(); i++)
        if(!sa.isSet(i) && first[i] != -1) return false;
        else if(sa.isSet(i) && first[i] != sa.SA(i)) return false;
    return true;
}

template <typename T>
bool compareLCP(const std::vector<long>& first, SuffixStructure<T>& sa){
    if(first.size() != sa.getSize()+1) return false;
    for(int i = 1; i < first.size(); i++)
        if(!sa.isSet(i) && first[i] != -1) return false;
        else if(sa.isSet(i) && first[i] != sa.LCP(i)) return false;
    return true;
}

TEST_CASE("Inducing the suffix array") {

    SECTION("Basic inducing 5"){
        StringSuffixStructure sa("mississippi");
        sa.induceArrays(true);
        std::cout << -1 << " ";
        for(int i = 1; i <= sa.getSize(); i++){
            std::cout << sa.LCP(i) << " ";
//        if(i != suffixStructure.getSize()) std::cout << " ";

        }
        std::cout << "\n";
        REQUIRE(compareSA({11, 10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2}, sa) == true);
        REQUIRE(compareLCP({0, 0, 1, 1, 4, 0, 0, 1, 0, 2, 1, 3}, sa) == true);
    }

}