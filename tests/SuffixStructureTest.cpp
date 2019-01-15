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


    SECTION("Basic inducing 7") {

        std::string text = "riKWyBiqYvhqnPaKunCyjMJbueUnXXRMjrWGNdjPwtVQOvQZXrvgMbFcPeTLDdcBAQURJvdlpRjaeIxryxWxJpVKfkTChTFnevJfKAuMCtYtWqDjfwPadeqJnjPAQZLmqZKVPfAWicTjmmUXQeHTynJYkUOdGHWRAXVUYVshmgayxixoyWsjFRdYEPXsygZOyIcySIvNaKjnMNTmOIJuPAGCxRCFYBFHRALGSgOlIemHvdiaNHDBZivAIGFHLOba";
        StringSuffixStructure sa(text);
        sa.induceArrays(true);
        REQUIRE(compareSA({256, 213, 247, 225, 64, 123, 134, 160, 101, 63, 221, 243, 5, 218, 91, 104, 215, 18, 242, 60, 110, 184, 250, 222, 180, 219, 54, 94, 214, 249, 156, 35, 227, 241, 251, 223, 146, 157, 235, 248, 209, 193, 232, 197, 77, 150, 22, 98, 119, 84, 210, 68, 100, 130, 2, 87, 201, 15, 59, 226, 252, 126, 103, 21, 204, 52, 31, 240, 205, 199, 36, 208, 253, 154, 230, 44, 191, 212, 122, 185, 13, 114, 56, 132, 39, 43, 65, 124, 46, 144, 224, 159, 217, 67, 30, 181, 73, 196, 228, 90, 93, 58, 138, 206, 147, 153, 66, 142, 163, 26, 86, 131, 42, 162, 165, 34, 158, 135, 108, 177, 82, 3, 143, 29, 161, 28, 48, 186, 220, 183, 164, 151, 106, 8, 129, 125, 190, 47, 244, 255, 200, 14, 239, 115, 75, 170, 53, 254, 23, 62, 55, 137, 194, 155, 182, 61, 116, 237, 37, 70, 145, 76, 57, 25, 233, 117, 96, 133, 99, 88, 112, 51, 229, 189, 169, 92, 167, 10, 1, 238, 136, 6, 245, 173, 179, 20, 121, 38, 74, 111, 139, 202, 32, 89, 152, 231, 71, 234, 207, 141, 168, 140, 127, 17, 149, 203, 12, 27, 95, 120, 175, 72, 85, 109, 118, 7, 128, 11, 33, 0, 49, 79, 166, 178, 187, 41, 107, 105, 102, 211, 24, 16, 246, 97, 198, 45, 236, 69, 50, 9, 113, 40, 83, 216, 81, 172, 174, 78, 4, 192, 195, 176, 188, 19, 148, 80, 171}, sa) == true);
        REQUIRE(compareLCP({-1, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 2, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 2, 1, 1, 2, 1, 1, 1, 0, 1, 1, 2, 1, 0, 2, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 2}, sa) == true);
    }


    SECTION("Basic inducing 8") {

        std::string text = "NgXRoaPaleNgsUxraVLAQdslBZLZtRYVTqhCbNMFohFQmtCvGFQJJFbPmgbkBtCypIYTSNwlqhFMqTvlTjrxaccwLFypdheoBkRfhydUXpDmvwREXFBtBFsXodldpPkrnXFLonhmMBhttWpCbwFxMpuqrDEmFLbNutYEpyQXaGSowmGLKfpYtoAphDxphhSpRuonIFUNSBWBPxDfSeaCUSZVSFcvZMWJTXVbKSUCHABhbqsGOqctEHbdYAKGXbQb";
        StringSuffixStructure sa(text);
        sa.induceArrays(true);
        REQUIRE(compareSA({256, 233, 249, 19, 182, 116, 203, 201, 24, 234, 137, 96, 114, 60, 231, 211, 35, 143, 46, 62, 153, 206, 106, 185, 244, 111, 154, 163, 113, 156, 130, 74, 49, 42, 197, 53, 217, 39, 117, 146, 89, 48, 174, 239, 169, 251, 232, 245, 196, 65, 52, 51, 223, 250, 228, 176, 18, 88, 175, 26, 157, 131, 136, 38, 221, 148, 75, 37, 199, 0, 10, 159, 69, 240, 6, 125, 55, 204, 50, 166, 254, 20, 43, 110, 29, 98, 3, 192, 200, 216, 68, 229, 213, 208, 170, 190, 67, 224, 80, 32, 77, 230, 198, 212, 103, 13, 17, 215, 31, 226, 202, 222, 141, 112, 129, 2, 225, 167, 252, 119, 104, 248, 162, 66, 30, 179, 25, 220, 214, 27, 210, 168, 5, 16, 84, 7, 255, 227, 36, 158, 54, 253, 246, 58, 236, 144, 85, 242, 218, 86, 102, 247, 92, 121, 123, 21, 9, 209, 94, 207, 99, 177, 1, 57, 11, 34, 184, 73, 41, 189, 235, 93, 188, 134, 138, 100, 81, 59, 97, 126, 23, 79, 122, 8, 71, 155, 173, 135, 56, 44, 107, 195, 128, 133, 181, 95, 4, 120, 40, 194, 132, 171, 142, 105, 64, 124, 191, 178, 91, 183, 187, 149, 164, 76, 241, 33, 72, 151, 237, 152, 15, 127, 82, 238, 12, 118, 22, 115, 45, 61, 243, 28, 140, 161, 180, 139, 193, 150, 160, 47, 219, 78, 108, 145, 87, 109, 70, 172, 205, 147, 83, 186, 14, 165, 101, 63, 90}, sa) == true);
        REQUIRE(compareLCP({-1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1, 1, 2, 0, 1, 1, 2, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 2, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 2}, sa) == true);
    }

    SECTION("Basic inducing 9") {

        std::string text = "tNZQEtoiBcdfUxVWEyJfPhkUbgJdtnbknMsdRUZCrYYXmNqLOBedJeRnGXlEiwVRDGVHHovCvQCCYvYJBofNlrHwDHnXZGNYptCtcXKhSkttcJnurTgjqWqOtIHLuKmhHGOqjOvMmbjwDIifojujUYgkHgsDFCFRITSQuhXeYxSbOepAeIlvgoTypBspjGQalpCYirBsaFMNAueKgGclQpEfuRXFkpfplICXoEoNkRTDrGseNIqjwfPGngAlWGJy";
        StringSuffixStructure sa(text);
        sa.induceArrays(true);
        REQUIRE(compareSA({256, 175, 250, 204, 8, 49, 80, 198, 185, 74, 157, 226, 194, 75, 39, 98, 71, 155, 64, 88, 140, 235, 214, 59, 229, 4, 16, 156, 201, 158, 219, 253, 93, 129, 189, 65, 56, 209, 247, 237, 128, 67, 122, 152, 89, 68, 86, 225, 121, 160, 141, 177, 241, 79, 26, 52, 18, 109, 254, 207, 102, 125, 47, 123, 202, 135, 33, 203, 240, 94, 1, 231, 83, 45, 48, 172, 130, 119, 133, 246, 20, 73, 3, 190, 212, 163, 63, 159, 233, 36, 217, 54, 162, 170, 104, 234, 161, 113, 182, 148, 37, 23, 12, 66, 62, 14, 15, 252, 117, 218, 101, 91, 166, 57, 43, 227, 78, 42, 41, 149, 195, 95, 76, 168, 38, 92, 2, 200, 191, 171, 24, 137, 30, 108, 100, 9, 210, 51, 35, 10, 27, 176, 206, 239, 53, 167, 50, 173, 82, 245, 19, 11, 143, 222, 215, 249, 208, 25, 114, 150, 180, 153, 127, 103, 165, 21, 7, 142, 196, 60, 188, 132, 147, 115, 145, 138, 243, 151, 232, 22, 31, 220, 105, 58, 224, 211, 251, 192, 84, 178, 44, 136, 126, 55, 32, 90, 29, 248, 110, 228, 230, 181, 81, 6, 144, 69, 174, 184, 193, 213, 221, 187, 223, 96, 46, 118, 116, 131, 242, 197, 236, 85, 112, 40, 154, 199, 34, 238, 186, 97, 120, 0, 107, 99, 28, 5, 106, 124, 216, 205, 164, 146, 111, 70, 134, 72, 77, 179, 87, 139, 61, 244, 169, 13, 255, 17, 183}, sa) == true);
        REQUIRE(compareLCP({-1, 0, 1, 1, 0, 1, 1, 1, 2, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 2, 1, 1, 0, 1, 0, 1, 1}, sa) == true);
    }

    SECTION("Basic inducing 9") {

        std::string text = "tegQBngLxxtoXPnwBnLEXcpdTMRpMBklpJtXtgmCnWfSkjKfAtThaSEOnMUAGdWsXPNZuqGwnGKaijCSdIPLuDDaRxgWFAlOoOTZMpNtoMKTuSDIcoTLEJPHnimJQFnQfLURdndsIqXEZWvpLkZMBijcPHynlDwGipPafhuZTgogXJuSvtfRYpXdoOrUOPEIxobWGaxryMGpNtNBqAhdcKZeRjrZaqDjbilEtDWrvCXDTbCgLGyEXMScpJwTVvxwbcdnCaxjhcpxmeZtWxmkSLjfsntuGxmWWEbYMFIFKuHcnJCIAljhJUSbokEjlFiorvCURpGmBFBdExSbLaRxhUTGNuPssvAPlkULcSMpoOMynUCVIsDgLVnApcwSgUZifUcosiNghIWQVjhaixNFQhCatWGxbLTQAZSeEWvCvUOmeeLPDqixBSrQZGXRnvuvQscLeMxHPGmZdefbeqoXHrLtbaCoFnJmvHofYFUNWLPvjaPcGySrFYEELhReGklx";
        StringSuffixStructure sa(text);
        sa.induceArrays(true);
        REQUIRE(compareSA({512, 59, 350, 416, 209, 93, 304, 375, 48, 328, 436, 330, 148, 29, 16, 4, 207, 302, 78, 322, 366, 233, 406, 260, 238, 39, 474, 423, 85, 110, 235, 229, 86, 370, 222, 432, 157, 502, 190, 116, 503, 54, 420, 243, 19, 139, 289, 314, 227, 332, 92, 329, 293, 295, 403, 485, 500, 317, 476, 125, 73, 343, 441, 196, 60, 159, 508, 326, 457, 202, 70, 410, 284, 241, 496, 455, 298, 119, 481, 468, 153, 303, 294, 81, 393, 111, 136, 368, 191, 301, 117, 123, 308, 478, 33, 173, 249, 106, 213, 74, 46, 296, 115, 18, 240, 430, 489, 413, 129, 372, 336, 355, 451, 504, 277, 144, 470, 83, 7, 147, 28, 292, 201, 105, 25, 245, 57, 100, 358, 453, 362, 206, 402, 487, 66, 390, 204, 102, 344, 361, 188, 97, 426, 55, 95, 185, 431, 189, 456, 118, 152, 82, 65, 162, 494, 351, 13, 346, 490, 415, 3, 124, 395, 439, 127, 404, 448, 179, 131, 506, 216, 443, 324, 26, 88, 338, 109, 53, 276, 357, 334, 310, 246, 79, 418, 379, 43, 498, 437, 175, 342, 114, 24, 414, 251, 98, 236, 168, 50, 107, 58, 365, 354, 486, 187, 425, 130, 323, 309, 341, 381, 385, 367, 396, 373, 252, 288, 91, 195, 409, 488, 394, 287, 41, 230, 62, 421, 141, 272, 234, 138, 467, 172, 244, 64, 12, 442, 20, 182, 35, 501, 484, 291, 180, 440, 146, 99, 417, 167, 140, 219, 459, 214, 382, 270, 67, 473, 493, 87, 337, 52, 163, 75, 399, 220, 407, 261, 197, 237, 412, 335, 194, 290, 472, 256, 463, 224, 311, 495, 212, 450, 151, 356, 257, 299, 112, 386, 247, 21, 265, 377, 331, 80, 23, 61, 211, 460, 258, 132, 183, 134, 419, 507, 429, 452, 215, 269, 428, 461, 1, 464, 47, 128, 178, 42, 384, 483, 462, 164, 279, 239, 371, 6, 2, 380, 90, 171, 391, 37, 169, 405, 392, 307, 505, 340, 51, 398, 264, 210, 165, 389, 383, 76, 149, 225, 121, 318, 160, 434, 400, 77, 45, 492, 223, 150, 278, 306, 397, 263, 315, 217, 313, 275, 353, 145, 44, 30, 509, 156, 226, 316, 94, 305, 352, 31, 510, 327, 38, 122, 286, 458, 268, 427, 274, 479, 374, 259, 72, 300, 477, 17, 56, 126, 364, 40, 133, 5, 120, 155, 281, 444, 14, 475, 104, 360, 96, 184, 113, 466, 11, 193, 482, 170, 312, 319, 387, 325, 32, 248, 143, 27, 203, 101, 161, 181, 376, 22, 359, 266, 208, 221, 69, 137, 433, 465, 499, 469, 438, 186, 218, 320, 231, 199, 369, 135, 63, 449, 388, 280, 347, 348, 228, 205, 49, 408, 271, 34, 471, 0, 177, 36, 103, 10, 282, 84, 283, 297, 345, 108, 174, 166, 68, 446, 349, 321, 232, 422, 480, 447, 424, 491, 142, 176, 445, 253, 15, 158, 378, 250, 255, 71, 511, 435, 454, 401, 333, 411, 89, 339, 262, 285, 267, 273, 192, 198, 9, 254, 8, 242, 200, 497, 363, 154}, sa) == true);
        REQUIRE(compareLCP({-1, 0, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 2, 0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 1, 1, 1, 2, 1, 1, 1, 2, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 1, 0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0, 1, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 3, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2}, sa) == true);
    }
}
