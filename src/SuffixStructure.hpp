//
// Created by pskoko on 12/15/18.
//

#ifndef LCP_INDUCING_SUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_SUFFIXSTRUCTURE_HPP

#include <vector>
#include <cstdef>
#include <map>
#include <set>

template <typename T>
class SuffixStructure {
private:
    std::map<T, pair<unsigned long, unsigned long>> bucketIndices;
    std::set<T> alphabet;

    std::vector<bool> sType;
    std::vector<bool> sStarType;

protected:

    void generateStructures();


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

};


template class SuffixStructure<int>;
template class SuffixStructure<char>;

#endif //LCP_INDUCING_SUFFIXSTRUCTURE_HPP
