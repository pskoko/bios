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


    SECTION("Basic inducing 6") {

        std::string text = "riKWyBiqYvhqnPaKunCyjMJbueUnXXRMjrWGNdjPwtVQOvQZXrvgMbFcPeTLDdcBAQURJvdlpRjaeIxryxWxJpVKfkTChTFnevJfKAuMCtYtWqDjfwPadeqJnjPAQZLmqZKVPfAWicTjmmUXQeHTynJYkUOdGHWRAXVUYVshmgayxixoyWsjFRdYEPXsygZOyIcySIvNaKjnMNTmOIJuPAGCxRCFYBFHRALGSgOlIemHvdiaNHDBZivAIGFHLOba";
        StringSuffixStructure sa(text);
        sa.induceArrays(true);
        REQUIRE(compareSA({256, 213, 247, 225, 64, 123, 134, 160, 101, 63, 221, 243, 5, 218, 91, 104, 215, 18, 242, 60, 110, 184, 250, 222, 180, 219, 54, 94, 214, 249, 156, 35, 227, 241, 251, 223, 146, 157, 235, 248, 209, 193, 232, 197, 77, 150, 22, 98, 119, 84, 210, 68, 100, 130, 2, 87, 201, 15, 59, 226, 252, 126, 103, 21, 204, 52, 31, 240, 205, 199, 36, 208, 253, 154, 230, 44, 191, 212, 122, 185, 13, 114, 56, 132, 39, 43, 65, 124, 46, 144, 224, 159, 217, 67, 30, 181, 73, 196, 228, 90, 93, 58, 138, 206, 147, 153, 66, 142, 163, 26, 86, 131, 42, 162, 165, 34, 158, 135, 108, 177, 82, 3, 143, 29, 161, 28, 48, 186, 220, 183, 164, 151, 106, 8, 129, 125, 190, 47, 244, 255, 200, 14, 239, 115, 75, 170, 53, 254, 23, 62, 55, 137, 194, 155, 182, 61, 116, 237, 37, 70, 145, 76, 57, 25, 233, 117, 96, 133, 99, 88, 112, 51, 229, 189, 169, 92, 167, 10, 1, 238, 136, 6, 245, 173, 179, 20, 121, 38, 74, 111, 139, 202, 32, 89, 152, 231, 71, 234, 207, 141, 168, 140, 127, 17, 149, 203, 12, 27, 95, 120, 175, 72, 85, 109, 118, 7, 128, 11, 33, 0, 49, 79, 166, 178, 187, 41, 107, 105, 102, 211, 24, 16, 246, 97, 198, 45, 236, 69, 50, 9, 113, 40, 83, 216, 81, 172, 174, 78, 4, 192, 195, 176, 188, 19, 148, 80, 171}, sa) == true);
        REQUIRE(compareLCP({-1, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 2, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 2, 1, 1, 2, 1, 1, 1, 0, 1, 1, 2, 1, 0, 2, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 2}, sa) == true);
    }


}
