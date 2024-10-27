#ifndef BITARRAY_H
#define BITARRAY_H

#include <string>
#include <stdexcept>
#include <algorithm>

class BitArray {
private:
    const unsigned char MAX_BYTE = 255;
    const int BITS_IN_BYTE = 8;
    unsigned char *bits;
    int num_bits;
    int num_bytes;

    void shift_left(const int& n);
    void shift_right(const int& n);
    std::string byte_to_string(unsigned char byte) const;
    void clear_extra_bits();
    void set(int n, bool val = true);

public:
    class BitRef {
    private:
        unsigned char& byte;
        int bit_position;

    public:
        BitRef(unsigned char& byte, int bit_position);
        BitRef& operator=(const unsigned char value);
        operator bool() const;
    };

    BitRef operator[](int i);
    BitArray();
    explicit BitArray(int num_bits, long value = 0);
    BitArray(const BitArray& b);
    ~BitArray();

    void swap(BitArray& b);
    BitArray& operator=(const BitArray& b);
    void resize(const int num_bits, const unsigned char value = 0);
    void clear();
    void push_back(unsigned char bit);

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
    bool empty() const;
    std::string to_string() const;

    friend bool operator==(const BitArray & a, const BitArray & b);
    friend bool operator!=(const BitArray & a, const BitArray & b);
    friend BitArray operator&(const BitArray& b1, const BitArray& b2);
    friend BitArray operator|(const BitArray& b1, const BitArray& b2);
    friend BitArray operator^(const BitArray& b1, const BitArray& b2);
};

#endif // BITARRAY_H