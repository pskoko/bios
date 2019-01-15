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

TEST_CASE("Structures managment of SuffixStructure") {


    SECTION("Set suffix array elements") {
        std::string text = "This is testing string.";
        StringSuffixStructure suffixStructure(text);

        suffixStructure.generateStructures();

        REQUIRE(suffixStructure.isSet(5) == false);
        suffixStructure.SA(5) = 5;

        REQUIRE(suffixStructure.isSet(5) == true);
        REQUIRE(suffixStructure.SA(5) == 5);

        suffixStructure.clearAdditionalStructure();
        REQUIRE(suffixStructure.isSet(5) == true);

        suffixStructure.cleraAll();
        REQUIRE(suffixStructure.isSet(5) == false);
    }

    SECTION("Type induction"){
        std::string text = "aaabacadf";
        StringSuffixStructure sa(text);

        sa.generateStructures();

        REQUIRE(sa.isL(3) == true);
        REQUIRE(sa.isS(3) == false);
        REQUIRE(sa.isSstar(4) == true);
        REQUIRE(sa.isS(4) == true);

        REQUIRE(sa.isSstar(1) == false);
        REQUIRE(sa.isS(1) == true);

    }

    SECTION("Bucket management") {
        std::string text = "aaababcbadf";
        StringSuffixStructure sa(text);

        sa.generateStructures();

        REQUIRE(sa.addToLBucket(3) == 6);
        REQUIRE(sa.addToSBucket(5) == 8);
        REQUIRE(sa.addToLBucket(7) == 7);

        REQUIRE(sa.SA(6) == 3);
        REQUIRE(sa.SA(7) == 7);
        REQUIRE(sa.SA(8) == 5);


    }

}

TEST_CASE("Inducing test"){
    SECTION("Basic inducing 1"){
        std::string text = "cabbage";
        StringSuffixStructure sa(text);
        sa.generateStructures();
        sa.insertSuffix(1);
        sa.insertSuffix(4);
        sa.insertSuffix(7);

        sa.clearAdditionalStructure();

        sa.induceL(false);
        REQUIRE(compareSA({7, 4,1, 3, 2, 0, 6, 5}, sa) == true);
        sa.induceS(false);
        REQUIRE(compareSA({7, 1,4, 3, 2, 0, 6, 5}, sa) == true);

    }

    SECTION("Basic inducing 2"){
        std::string text = "baabaabac";
        StringSuffixStructure sa(text);
        sa.generateStructures();
        sa.insertSuffix(1);
        sa.insertSuffix(4);
        sa.insertSuffix(7);
        sa.insertSuffix(9);

        sa.clearAdditionalStructure();

        sa.induceL(false);
        REQUIRE(compareSA({9, -1, -1, 7, 4, 1, 6, 3, 0, 8}, sa) == true);
        sa.induceS(false);
        REQUIRE(compareSA({9, 4, 1, 5, 2, 7, 6, 3, 0, 8}, sa) == true);

    }
}


TEST_CASE("Inducing the suffix array"){
    SECTION("Basic inducing 1"){
        StringSuffixStructure sa("cba");
        sa.induceArrays(true);
        REQUIRE(compareSA({3,2,1,0}, sa) == true);
        REQUIRE(compareLCP({0, 0, 0, 0}, sa) == true);

    }

    SECTION("Basic inducing 2"){
        StringSuffixStructure sa("abc");
        sa.induceArrays(false);
        REQUIRE(compareSA({3, 0, 1, 2}, sa) == true);
    }

    SECTION("Basic inducing 3"){
        StringSuffixStructure sa("aac");
        sa.induceArrays(true);
        REQUIRE(compareSA({3,0,1,2}, sa) == true);
        REQUIRE(compareLCP({0,0,1,0}, sa) == true);
    }

    SECTION("Basic inducing 3"){
        StringSuffixStructure sa("baac");
        sa.induceArrays(true);
        REQUIRE(compareSA({4,1,2,0,3}, sa) == true);
        REQUIRE(compareLCP({0,0,1,0,0}, sa) == true);
    }

    SECTION("Basic inducing 4"){
        StringSuffixStructure sa("abaac");
        sa.induceArrays(true);
        REQUIRE(compareSA({5, 2, 0, 3, 1, 4}, sa) == true);
        REQUIRE(compareLCP({0, 0, 1, 1, 0, 0}, sa) == true);
    }

    SECTION("Basic inducing 5"){
        StringSuffixStructure sa("mississippi");
        sa.induceArrays(true);
        REQUIRE(compareSA({11, 10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2}, sa) == true);
        REQUIRE(compareLCP({0, 0, 1, 1, 4, 0, 0, 1, 0, 2, 1, 3}, sa) == true);
    }

    SECTION("Basic inducing 6"){
        StringSuffixStructure sa("wolloomooloo");
        sa.induceArrays(false);
        REQUIRE(compareSA({12, 2, 9, 3, 6, 11, 1, 8, 5, 10, 7, 4, 0}, sa) == true);
    }

    SECTION("Basic inducing 6") {
        StringSuffixStructure sa("aaaaa");
        sa.induceArrays(false);
        REQUIRE(compareSA({5, 4, 3, 2, 1, 0}, sa) == true);
    }

}
