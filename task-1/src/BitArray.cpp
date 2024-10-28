#include "BitArray.h"
#include <cstring>

void BitArray::clearExtraBits() {
    if (numBits % bitsInByte == 0) {
        return;
    }
    const int lastByte = numBytes - 1;
    const int validBits = numBits % bitsInByte;
    const unsigned char mask = maxByte << (bitsInByte - validBits);
    bits[lastByte] &= mask;
}

void BitArray::set(int n, bool val) {
    if (n < 0 || n >= numBits) {
        throw std::out_of_range("BitArray::set");
    }
    const int byteIndex = n / bitsInByte;
    const int bitIndex = n % bitsInByte;
    if (val) {
        bits[byteIndex] |= (1 << (7 - bitIndex));
    }
    else {
        bits[byteIndex] &= ~(1 << (7 - bitIndex));
    }
}

BitArray::BitRef::BitRef(unsigned char& byte, int bitPosition) : byte(byte), bitPosition(bitPosition) {}

BitArray::BitRef& BitArray::BitRef::operator=(const unsigned char value) {
    if (value) {
        byte |= (1 << (7 - bitPosition));
    } else {
        byte &= ~(1 << (7 - bitPosition));
    }
    return *this;
}

BitArray::BitRef::operator bool() const {
    return (byte & (1 << (7 - bitPosition))) ? true : false;
}

BitArray::BitRef BitArray::operator[](int i) {
    if (i < 0 || i >= numBits) {
        throw std::out_of_range("BitArray::BitRef::operator[]");
    }
    const int byteIndex = i / bitsInByte;
    const int bitIndex = i % bitsInByte;
    return {bits[byteIndex], bitIndex};
}

BitArray::BitArray() {
    bits = nullptr;
    numBits = 0;
    numBytes = 0;
}

BitArray::~BitArray() {
    delete[] bits;
}

BitArray::BitArray(int numBits, long value) : numBits(numBits) {
    numBytes = numBits / bitsInByte + (numBits % bitsInByte == 0 ? 0 : 1);
    this->numBits = numBits;
    bits = new unsigned char[numBytes]();
    for (int i = 0; i < sizeof(long) * 8 && i < numBits; ++i) {
        set(numBits - i - 1, (value >> i) & 1);
    }
}

BitArray::BitArray(const BitArray& b) {
    this->numBits = b.numBits;
    this->numBytes = b.numBytes;
    this->bits = new unsigned char[numBytes]();
    memcpy(this->bits, b.bits, numBytes);
}

void BitArray::shiftLeft(const int& n) {
    const int byteShift = n / bitsInByte;
    const int bitShift = n % bitsInByte;
    for (int i = 0; i < numBytes; i++) {
        if (i + byteShift < numBytes) {
            bits[i] = bits[i + byteShift];
        } else {
            bits[i] = 0;
        }
    }
    for (int i = 0; i < numBytes - byteShift; i++) {
        bits[i] <<= bitShift;
        if (i + 1 < numBytes) {
            bits[i] |= bits[i + 1] >> (bitsInByte - bitShift);
        }
    }
}

void BitArray::shiftRight(const int& n) {
    const int byteShift = n / bitsInByte;
    const int bitShift = n % bitsInByte;
    for (int i = numBytes - 1; i >= 0; i--) {
        if (i - byteShift >= 0) {
            bits[i] = bits[i - byteShift];
        } else {
            bits[i] = 0;
        }
    }
    for (int i = numBytes - 1; i >= byteShift; i--) {
        bits[i] >>= bitShift;
        if (i - 1 >= 0) {
            bits[i] |= bits[i - 1] << (bitsInByte - bitShift);
        }
    }
    clearExtraBits();
}

std::string BitArray::byteToString(unsigned char byte) const {
    std::string result;
    for (int i = bitsInByte - 1; i >= 0; i--) {
        result += byte & (1 << i) ? '1' : '0';
    }
    return result;
}

void BitArray::swap(BitArray& b) {
    std::swap(this->numBits, b.numBits);
    std::swap(bits, b.bits);
    std::swap(this->numBytes, b.numBytes);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        delete[] bits;
        this->numBits = b.numBits;
        this->numBytes = b.numBytes;
        this->bits = new unsigned char[numBytes]();
        memcpy(this->bits, b.bits, numBytes);
    }
    return *this;
}

void BitArray::resize(const int numBits, const unsigned char value) {
    if (value != 0 && value != 1) {
        throw std::invalid_argument("Value must be 0 or 1");
    }
    if (numBits < 0) {
        throw std::invalid_argument("BitArray::resize");
    }

    if (numBits > this->numBits && value) {
        bits[numBytes - 1] |= maxByte >> (this->numBits % bitsInByte);
    }

    const int newNumBytes = numBits / bitsInByte + (numBits % bitsInByte == 0 ? 0 : 1);
    unsigned char* newBits = new unsigned char[newNumBytes]();
    if (bits) {
        std::memcpy(newBits, bits, std::min(numBytes, newNumBytes));
        delete[] bits;
    }

    bits = newBits;

    if (newNumBytes > this->numBytes && value) {
        for (int i = this->numBytes; i < newNumBytes; i++) {
            bits[i] = maxByte;
        }
    }
    this->numBits = numBits;
    this->numBytes = newNumBytes;
    clearExtraBits();
}

void BitArray::clear() {
    if (bits == nullptr) {
        return;
    }
    delete[] bits;
    bits = nullptr;
    numBytes = 0;
    numBits = 0;
}

void BitArray::pushBack(unsigned char bit) {
    if (numBits % bitsInByte == 0) {
        resize(numBits + 1);
        numBits--;
    }
    if (bit) {
        bits[(numBits / bitsInByte)] |= 1 << (7 - (numBits % bitsInByte));
    }
    numBits++;
}

void BitArray::shrink() {
    int last_one_pos = 0;
    for (int i = numBytes - 1; i >= 0; i--) {
        for (int j = 0; j < bitsInByte; j++) {
            if (bits[i] & (1 << j)) {
                last_one_pos = (i * bitsInByte) + (7 - j);
                break;
            }
        }
        if (last_one_pos) {
            break;
        }
    }
    resize(last_one_pos + 1);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (this->numBits != b.numBits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < numBytes; i++) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (this->numBits != b.numBits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < numBytes; i++) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (this->numBits != b.numBits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < numBytes; i++) {
        bits[i] ^= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative shift. Use operator>>= instead.");
    }
    if (n == 0) {
        return *this;
    }
    shiftLeft(n);
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative shift. Use operator<<= instead.");
    }
    if (n == 0) {
        return *this;
    }
    shiftRight(n);
    return *this;
}

BitArray BitArray::operator<<(const int n) const {
    if (n < 0) {
        throw std::invalid_argument("Negative shift. Use operator>> instead.");
    }
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(const int n) const {
    if (n < 0) {
        throw std::invalid_argument("Negative shift. Use operator<< instead.");
    }
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::set() {
    for (int i = 0; i < numBytes; i++) {
        bits[i] = maxByte;
    }
    clearExtraBits();
    return *this;
}

BitArray& BitArray::reset() {
    for (int i = 0; i < numBytes; i++) {
        bits[i] = 0;
    }
    return *this;
}

bool BitArray::any() const {
    if (bits == nullptr) {
        return false;
    }
    for (int i = 0; i < numBytes; i++) {
        if (bits[i] != 0) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    if (bits == nullptr) {
        return true;
    }
    for (int i = 0; i < numBytes; i++) {
        if (bits[i] != 0) {
            return false;
        }
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray result = *this;
    for (int i = 0; i < numBytes; i++) {
        result.bits[i] = ~(this->bits[i]);
    }
    result.clearExtraBits();
    return result;
}

int BitArray::count() const {
    int result = 0;
    for (int i = 0 ; i < numBytes; i++) {
        for (int j = 0; j < bitsInByte; j++) {
            if (bits[i] & (1 << j)) {
                result += 1;
            }
        }
    }
    return result;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= numBits) {
        throw std::out_of_range("Index out of range");
    }
    return bits[i / bitsInByte] & (1 << (7 - (i % bitsInByte)));
}

int BitArray::size() const {
    return numBits;
}

int BitArray::getBytesCount() const {
    return numBytes;
}

bool BitArray::empty() const {
    return numBits == 0;
}

std::string BitArray::toString() const {
    std::string result;
    for (int i = 0; i < numBytes; i++) {
        result += byteToString(bits[i]);
    }
    if (numBits % bitsInByte != 0) {
        result.erase(numBytes * bitsInByte - (bitsInByte - (numBits % bitsInByte)), bitsInByte - (numBits % bitsInByte));
    }
    return result;
}

bool operator==(const BitArray & a, const BitArray & b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray & a, const BitArray & b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result[i] = b1[i] & b2[i];
    }
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result[i] = b1[i] | b2[i];
    }
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result[i] = b1[i] ^ b2[i];
    }
    return result;
}
