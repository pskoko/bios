//
// Created by pskoko on 1/13/19.
//
#include "catch2/catch.hpp"
#include <StringSuffixStructure.hpp>
#include "StarSuffixStructure.hpp"
#include <algorithm>

TEST_CASE("Test generating string"){
    SECTION("Basic string generating 1") {
        std::string text = "aaababcbadf";
        StringSuffixStructure sa(text);
        StarSuffixStructure ssa(sa);

        const std::vector<unsigned long> &generatedText = ssa.getText();
        const std::vector<unsigned long> expectedText{0, 1, 2};
        REQUIRE(std::equal(generatedText.begin(), generatedText.end(), expectedText.begin(), expectedText.end()) ==
                true);
    }

    SECTION("Basic string generating 2") {
        std::string text = "baabaabac";
        StringSuffixStructure sa(text);
        StarSuffixStructure ssa(sa);

        const std::vector<unsigned long> &generatedText = ssa.getText();
        const std::vector<unsigned long> expectedText{0, 1, 1, 2};
        REQUIRE(std::equal(generatedText.begin(), generatedText.end(), expectedText.begin(), expectedText.end()) ==
                true);
    }
}
