//
// Created by pskoko on 1/12/19.
//
#include <SuffixStructure.hpp>
#include <StringSuffixStructure.hpp>
#include "catch2/catch.hpp"

TEST_CASE("Structures managment of SuffixStructure") {
    std::string text = "This is testing string.";
    SuffixStructure suffixStructure{StringSuffixStructure(text)};


    SECTION("Set suffix array elements") {
        suffixStructure.generateStructures();

        REQUIRE(suffixStructure.isSet(5) == false);
        suffixStructure.SA(5) = 5;

        REQUIRE(suffixStructure.isSet(5) == true);
        REQUIRE(suffixStructure.SA(5) == 5);

        suffixStructure.clearAdditionalStructure();
        REQUIRE(suffixStructure.isSet(5) == true);

        suffixStructure.cleraAll();
        REQUIRE(suffixStructure.isSet(5) == true);
    }

}

