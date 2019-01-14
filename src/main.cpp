//
// Created by pskoko on 1/12/19.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "StringSuffixStructure.hpp"

int main(int argc, const char* argv[]){
    std::ifstream fin(argv[1]);
    std::stringstream buffer;

    buffer << fin.rdbuf();
    std::string text{buffer.str()};

    StringSuffixStructure suffixStructure(text);
    suffixStructure.induceArrays(true);
    std::cout << -1 << " ";
    for(int i = 1; i <= suffixStructure.getSize(); i++){
        std::cout << suffixStructure.LCP(i) << " ";
//        if(i != suffixStructure.getSize()) std::cout << " ";

    }

    return 0;
}