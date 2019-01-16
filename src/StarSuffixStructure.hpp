/**
* @file StarSuffixStructure.h
* @brief this header file contains all required
* declarations for the StarSuffixStructure class implementing
* SuffixStructure for unsigned long type.
* This implementation specializes in storing S* suffixes for sorting and 
* recursive inductions used in the LCP induction algorithm.
*
* This implementation is required by and used in the base SuffixStructure class
*
* @author pskoko
*
* @date 12/15/2018
*/

#ifndef LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP

#include "SuffixStructure.hpp"
#include <map>

/**
 * SuffixStructure class which creates text of S\* substrings of some
 * other abstract structure. It supports creating such text and putting its SA values
 * and scaled LCP values into original SuffixStructure
 * @tparam E
 */
template <typename E>
class StarSuffixStructure : public SuffixStructure<unsigned long>{
private:
    std::vector<unsigned long> text;
    SuffixStructure<E>& suffixStructure;
    std::vector<unsigned long> sortedStarSubstrings;
    bool completed = false;
    std::map<unsigned long, unsigned long> starSizes;

public:
    /**
     * Constructor which creates text of S\* substrings of text of received
     * Suffix Structure
     * @param suffixStructure
     */
    StarSuffixStructure(SuffixStructure<E>& suffixStructure);

    /**
     * Naively compares two star suffixes of original suffixStructure
     * @param first
     * @param second
     * @return
     */
    bool compareStarSuffixes(unsigned long first, unsigned long second);

    /**
     * Puts SA values and scaled LCP values into original SuffixStructure
     */
    void fillSuffixStructure();

    const unsigned long& operator[](const unsigned long index) const;
    unsigned long getSize() const;

    const std::vector<unsigned long>& getText() const;
    void induceArrays(bool induceLCp);

};

template class StarSuffixStructure<char>;
template class StarSuffixStructure<unsigned long>;
#endif //LCP_INDUCING_STARSUFFIXSTRUCTURE_HPP
