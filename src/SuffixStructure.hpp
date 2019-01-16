/**
* @file SuffixStructure.h
* @brief this header file contains all required
* declarations for the base SuffixStructure class responsible for
* storing the algorithm state and performing all state operations including
* the induction algorithm itself for a given text
*
* @author pskoko
*
* @date 12/15/2018
*/

#ifndef LCP_INDUCING_SUFFIXSTRUCTURE_HPP
#define LCP_INDUCING_SUFFIXSTRUCTURE_HPP

#include <vector>
#include <map>
#include <set>


/**
 * Abstract class which represents suffix structure over some text.
 * It encapsulates LCP i SA arrays, and other data structures and operations
 * neccesary for implementing the modifyed SA-IS algorithm like bucket indices
 * @tparam T type of characters in text
 */
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
    std::map<T, unsigned long> bucketsSizesL;
    std::map<T, unsigned long> bucketsSizesS;


public:

    /**
    * Initializes the alphabet, sType and bucketIndices structures along with
    * all intermediate structures.
    */
    void generateStructures();
    
    /**
    * Empties the bucket offset structures of this SuffixStructure.
    */
    void clearAdditionalStructure();

    /**
    * Empties all intermediate structures of this SuffixStructure.
    * Doesn't clear the alphabet nor the bucketIndices structures.
    */
    void cleraAll();

    /**
     * Returns true if the suffix array was set for the provided index, 
     * otherwise false.
     * @param index The index of the suffix array to be checked 
     */
    bool isSet(unsigned long index) const;

    /**
     * Adds the provided suffix to it's appropriate L bucket and adjusts
     * bucket offsets accordingly. Returns the index into the suffix array
     * where the suffix was added.
     * @param suffix The suffix to add to it's L bucket 
     */
    unsigned long addToLBucket(unsigned long suffix);
    
    /**
     * Adds the provided suffix to it's appropriate S bucket and adjusts
     * bucket offsets accordingly. Returns the index into the suffix array
     * where the suffix was added.
     * @param suffix The suffix to add to it's S bucket 
     */
    unsigned long addToSBucket(unsigned long suffix);

    /**
     * Adds the provided suffix to the end of it's appropriate S bucket and adjusts
     * bucket offsets accordingly. Returns the index into the suffix array
     * where the suffix was added.
     * @param suffix The suffix to add to the end of it's S bucket 
     */
    unsigned long addToSBucketReversed(unsigned long suffix);

    /**
     * Returns true if the provided index into the suffix array is the first index
     * of the L bucket for the provided character. Otherwise false.
     * @param index The index into the SA for which to check if first
     * @param &t A reference to the character defining the L bucket to check
     */
    bool isFirstInLBucket(unsigned long index, const T &t);

    /**
     * Returns true if the provided index into the suffix array is the last index
     * of the S bucket for the provided character. Otherwise false.
     * @param index The index into the SA for which to check if first
     * @param &t A reference to the character defining the S bucket to check
     */
    bool isLastInSBucket(unsigned long index, const T &t);

    /**
     * Returns true if the provided index into the suffix array is the last index
     * of the L bucket for the provided character. Otherwise false.
     * @param index The index into the SA for which to check if first
     * @param &t A reference to the character defining the L bucket to check
     */
    bool isLastInLBucket(unsigned long index, const T &t);

    /**
     * Returns true if the provided index into the suffix array is the first index
     * of the S bucket for the provided character. Otherwise false.
     * @param index The index into the SA for which to check if first
     * @param &t A reference to the character defining the S bucket to check
     */
    bool isFirstInSBucket(unsigned long index, const T &t);

    /**
     * Returns a reference to the suffix array element at the provided index.
     * @param index The index into the suffix array
     */
    virtual unsigned long& SA(const unsigned long index);

    /**
     * Returns a reference to the LCP array element at the provided index.
     * @param index The index into the LCP array
     */
    virtual unsigned long& LCP(const unsigned long index);

    /**
     * Returns true if the character in the text at the provided index is L-type.
     * Otherwise returns false.
     * @param index The index into the text
     */
    bool isL(const unsigned long index) const;
    
    /**
     * Returns true if the character in the text at the provided index is S-type.
     * Otherwise returns false.
     * @param index The index into the text
     */
    bool isS(const unsigned long index) const;

    /**
     * Returns true if the character in the text at the provided index is S*-type.
     * Otherwise returns false.
     * @param index The index into the text
     */
    bool isSstar(const unsigned long index) const;

    /**
    * Returns the character at the provided index in the text.
    * @param index The index into the text
    */
    virtual const T& operator[](const unsigned long index) const = 0;

    /**
    * Returns the length of the text represented by this SuffixStructure
    */
    virtual unsigned long getSize() const = 0;

    /**
    * Induces the L suffixes of the suffix array by scanning the array from
    * left to right. If the induceLcp parameter is set to true, will also
    * induce the LCP values for the L suffixes induced.
    * Requires the sorted S* suffixes to be inserted previously.
    * @param induceLcp if true, the induce step will also induce the LCP values
    */
    void induceL(bool induceLcp);
    
    /**
    * Induces the S suffixes of the suffix array by scanning the array from
    * right to left. If the induceLcp parameter is set to true, will also
    * induce the LCP values for the S suffixes induced.
    * Requires that induceL be performed previously.
    * @param induceLcp if true, the induce step will also induce the LCP values
    */
    void induceS(bool induceLcp);

    /**
    * Inserts the given suffix into it's appropriate bucket in the suffix array.
    * Calls addToSBucket or addToLBucket depending on the provided suffix type.
    * @param suffix The suffix which to insert into the SA
    */
    void insertSuffix(unsigned long suffix);

    /**
    * Initializes all intermediate structures required and performs the SA-IS 
    * recursive induction algorithm.
    * @param induceLcp if true, will also induce the LCP values for the text
    */
    virtual void induceArrays(bool induceLCp);

};


template class SuffixStructure<unsigned long>;
template class SuffixStructure<char>;

#endif //LCP_INDUCING_SUFFIXSTRUCTURE_HPP
