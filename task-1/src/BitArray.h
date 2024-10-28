#ifndef BITARRAY_H
#define BITARRAY_H

#include <string>
#include <stdexcept>
#include <algorithm>

class BitArray {
private:
    const unsigned char maxByte = 255;
    const int bitsInByte = 8;
    unsigned char* bits;
    int numBits;
    int numBytes;

    void shiftLeft(const int& n);
    void shiftRight(const int& n);
    std::string byteToString(unsigned char byte) const;
    void clearExtraBits();
    void set(int n, bool val = true);

public:
    class BitRef {
    private:
        unsigned char& byte;
        int bitPosition;

    public:
        BitRef(unsigned char& byte, int bitPosition);
        BitRef& operator=(const unsigned char value);
        operator bool() const;
    };

    BitArray();
    explicit BitArray(int numBits, long value = 0);
    BitArray(const BitArray& b);
    ~BitArray();

    BitRef operator[](int i);
    BitArray& operator=(const BitArray& b);
    void swap(BitArray& b);
    void resize(const int numBits, const unsigned char value = 0);
    void clear();
    void pushBack(unsigned char bit);
    void shrink();

    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(const int n) const;
    BitArray operator>>(const int n) const;

    BitArray& set();
    BitArray& reset();
    bool any() const;
    bool none() const;
    BitArray operator~() const;
    int count() const;
    bool operator[](int i) const;
    int size() const;
    int getBytesCount() const;
    bool empty() const;
    std::string toString() const;

    friend bool operator==(const BitArray& a, const BitArray& b);
    friend bool operator!=(const BitArray& a, const BitArray& b);
    friend BitArray operator&(const BitArray& b1, const BitArray& b2);
    friend BitArray operator|(const BitArray& b1, const BitArray& b2);
    friend BitArray operator^(const BitArray& b1, const BitArray& b2);
};

#endif // BITARRAY_H
