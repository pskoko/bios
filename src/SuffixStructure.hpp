//
// Created by pskoko on 12/15/18.
//

#ifndef LCP_INDUCING_SUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_SUFFIXSTRUCTURE_HPP

#include <vector>
#include <map>
#include <set>


template <typename T>
class SuffixStructure {
private:
    std::map<T, std::pair<unsigned long, unsigned long>> bucketIndices;
    std::set<T> alphabet;

    std::vector<bool> sType;
    std::vector<unsigned long> SA_data;
    std::vector<unsigned long> LCP_data;
    std::map<T, unsigned long> bucketsOffsetL;
    std::map<T, unsigned long> bucketsOffsetS;
    std::vector<bool> accessed;


public:

    void generateStructures();
    void clearAdditionalStructure();
    void cleraAll();

    bool isSet(unsigned long index) const;

    unsigned long addToLBucket(unsigned long suffix);
    unsigned long addToSBucket(unsigned long suffix);

    bool isFirstInLBucket(unsigned long index);
    bool isLastInLBucket(unsigned long index);
    bool isFirstInSBucket(unsigned long index);
    bool isLastInSBucket(unsigned long index);


    virtual unsigned long& SA(const unsigned long index);

    virtual unsigned long& LCP(const unsigned long index);

    bool isL(const unsigned long index) const;
    bool isS(const unsigned long index) const;

    bool isSstar(const unsigned long index) const;

    virtual const T& operator[](const unsigned long index) const = 0;

    virtual unsigned long getSize() const = 0;
    void induceL(bool induceLcp);
    void induceS(bool induceLcp);
    void insertSuffix(unsigned long suffix);

    virtual void induceArrays(bool induceLCp);

};


template class SuffixStructure<unsigned long>;
template class SuffixStructure<char>;

#endif //LCP_INDUCING_SUFFIXSTRUCTURE_HPP
