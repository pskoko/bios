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
    std::vector<bool> sStarType;
    std::vector<unsigned long> SA;
    std::vector<unsigned long> LCP;
    std::map<T, unsigned long> bucketsOffsetL;
    std::map<T, unsigned long> bucketsOffsetS;


protected:

    void generateStructures();
    void clearAdditionalStructure();
    void cleraAll();

    bool isSet(unsigned long index);

    void addToLBucket(unsigned long suffix);
    void addToSBucket(unsigned long suffix);

    bool isFirstInLBucket(unsigned long suffix);
    bool isLastInLBucket(unsigned long suffix);
    bool isFirstInSBucket(unsigned long suffix);
    bool isLastInSBucket(unsigned long suffix);


public:
    virtual const unsigned long& SA(const unsigned long index) const;
    virtual unsigned long& SA(const unsigned long index);

    virtual const unsigned long& LCP(const unsigned long index) const;
    virtual unsigned long& LCP(const unsigned long index);

    bool isL(const unsigned long index) const;
    bool isS(const unsigned long index) const;

    bool isSstar(const unsigned long index) const;

    virtual const T& operator[](const unsigned long index) const;

    virtual unsigned long getSize() const;
    void induceL(bool induceLcp);
    void induceS(bool induceLcp);

};


template class SuffixStructure<int>;
template class SuffixStructure<char>;

#endif //LCP_INDUCING_SUFFIXSTRUCTURE_HPP
