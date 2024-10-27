#include "BitArray.h"
#include <cstring>

void BitArray::clear_extra_bits() {
    if (num_bits % 8 == 0) {
        return;
    }
    const int last_byte = num_bytes - 1;
    const int valid_bits = num_bits % BITS_IN_BYTE;
    const unsigned char mask = MAX_BYTE << (BITS_IN_BYTE - valid_bits);
    bits[last_byte] &= mask;
}

void BitArray::set(int n, bool val) {
    if (n < 0 || n >= num_bits) {
        throw std::out_of_range("BitArray::set");
    }
    const int byte_index = n / BITS_IN_BYTE;
    const int bit_index = n % BITS_IN_BYTE;
    if (val) {
        bits[byte_index] |= (1 << (7 - bit_index));
    }
    else {
        bits[byte_index] &= ~(1 << (7 - bit_index));
    }
}

BitArray::BitRef::BitRef(unsigned char& byte, int bit_position) : byte(byte), bit_position(bit_position) {}

BitArray::BitRef& BitArray::BitRef::operator=(const unsigned char value) {
    if (value) {
        byte |= (1 << (7 - bit_position));
    } else {
        byte &= ~(1 << (7 - bit_position));
    }
    return *this;
}

BitArray::BitRef::operator bool() const {
    return (byte & (1 << (7 - bit_position))) ? true : false;
}

BitArray::BitRef BitArray::operator[](int i) {
    if (i < 0 || i >= num_bits) {
        throw std::out_of_range("BitArray::BitRef::operator[]");
    }
    const int byte_index = i / BITS_IN_BYTE;
    const int bit_index = i % BITS_IN_BYTE;
    return {bits[byte_index], bit_index};
}

BitArray::BitArray() {
    bits = nullptr;
    num_bits = 0;
    num_bytes = 0;
}

BitArray::~BitArray() {
    delete[] bits;
}

BitArray::BitArray(int num_bits, long value) : num_bits(num_bits) {
    num_bytes = num_bits / BITS_IN_BYTE + (num_bits % BITS_IN_BYTE == 0 ? 0 : 1);
    this->num_bits = num_bits;
    bits = new unsigned char[num_bytes]();
    for (int i = 0; i < sizeof(long) * 8 && i < num_bits; ++i) {
        set(num_bits - i - 1, (value >> i) & 1);
    }
}

BitArray::BitArray(const BitArray& b) {
    this->num_bits = b.num_bits;
    this->num_bytes = b.num_bytes;
    this->bits = new unsigned char[num_bytes]();
    memcpy(this->bits, b.bits, num_bytes);
}

void BitArray::shift_left(const int& n) {
    const int byte_shift = n / BITS_IN_BYTE;
    const int bit_shift = n % BITS_IN_BYTE;
    for (int i = 0; i < num_bytes; i++) {
        if (i + byte_shift < num_bytes) {
            bits[i] = bits[i + byte_shift];
        } else {
            bits[i] = 0;
        }
    }
    for (int i = 0; i < num_bytes - byte_shift; i++) {
        bits[i] <<= bit_shift;
        if (i + 1 < num_bytes) {
            bits[i] |= bits[i + 1] >> (BITS_IN_BYTE - bit_shift);
        }
    }
}

void BitArray::shift_right(const int& n) {
    const int byte_shift = n / BITS_IN_BYTE;
    const int bit_shift = n % BITS_IN_BYTE;
    for (int i = num_bytes - 1; i >= 0; i--) {
        if (i - byte_shift >= 0) {
            bits[i] = bits[i - byte_shift];
        } else {
            bits[i] = 0;
        }
    }
    for (int i = num_bytes - 1; i >= byte_shift; i--) {
        bits[i] >>= bit_shift;
        if (i - 1 >= 0) {
            bits[i] |= bits[i - 1] << (BITS_IN_BYTE - bit_shift);
        }
    }
    clear_extra_bits();
}

std::string BitArray::byte_to_string(unsigned char byte) const {
    std::string result;
    for (int i = BITS_IN_BYTE - 1; i >= 0; i--) {
        result += byte & (1 << i) ? '1' : '0';
    }
    return result;
}

void BitArray::swap(BitArray& b) {
    std::swap(this->num_bits, b.num_bits);
    std::swap(bits, b.bits);
    std::swap(this->num_bytes, b.num_bytes);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        delete[] bits;
        this->num_bits = b.num_bits;
        this->num_bytes = b.num_bytes;
        this->bits = new unsigned char[num_bytes]();
        memcpy(this->bits, b.bits, num_bytes);
    }
    return *this;
}

void BitArray::resize(const int num_bits, const unsigned char value) {
    if (value != 0 && value != 1) {
        throw std::invalid_argument("Value must be 0 or 1");
    }
    if (num_bits < 0) {
        throw std::invalid_argument("BitArray::resize");
    }

    if (num_bits > this->num_bits && value) {
        bits[num_bytes - 1] |= MAX_BYTE >> (this->num_bits % BITS_IN_BYTE);
    }

    const int new_num_bytes = num_bits / BITS_IN_BYTE + (num_bits % BITS_IN_BYTE == 0 ? 0 : 1);
    unsigned char* new_bits = new unsigned char[new_num_bytes]();
    if (bits) {
        std::memcpy(new_bits, bits, std::min(num_bytes, new_num_bytes));
        delete[] bits;
    }

    bits = new_bits;

    if (new_num_bytes > this->num_bytes && value) {
        for (int i = this->num_bytes; i < new_num_bytes; i++) {
            bits[i] = MAX_BYTE;
        }
    }
    this->num_bits = num_bits;
    this->num_bytes = new_num_bytes;
    clear_extra_bits();
}

void BitArray::clear() {
    if (bits == nullptr) {
        return;
    }
    delete[] bits;
    bits = nullptr;
    num_bytes = 0;
    num_bits = 0;
}

void BitArray::push_back(unsigned char bit) {
    if (num_bits % BITS_IN_BYTE == 0) {
        resize(num_bits + 1);
        num_bits--;
    }
    if (bit) {
        bits[(num_bits / BITS_IN_BYTE)] |= 1 << (7 - (num_bits % BITS_IN_BYTE));
    }
    num_bits++;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (this->num_bits != b.num_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < num_bytes; i++) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (this->num_bits != b.num_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < num_bytes; i++) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (this->num_bits != b.num_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < num_bytes; i++) {
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
    shift_left(n);
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative shift. Use operator<<= instead.");
    }
    if (n == 0) {
        return *this;
    }
    shift_right(n);
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
    for (int i = 0; i < num_bytes; i++) {
        bits[i] = MAX_BYTE;
    }
    clear_extra_bits();
    return *this;
}

BitArray& BitArray::reset() {
    for (int i = 0; i < num_bytes; i++) {
        bits[i] = 0;
    }
    return *this;
}

bool BitArray::any() const {
    if (bits == nullptr) {
        return false;
    }
    for (int i = 0; i < num_bytes; i++) {
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
    for (int i = 0; i < num_bytes; i++) {
        if (bits[i] != 0) {
            return false;
        }
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray result = *this;
    for (int i = 0; i < num_bytes; i++) {
        result.bits[i] = ~(this->bits[i]);
    }
    result.clear_extra_bits();
    return result;
}

int BitArray::count() const {
    int result = 0;
    for (int i = 0 ; i < num_bytes; i++) {
        for (int j = 0; j < BITS_IN_BYTE; j++) {
            if (bits[i] & (1 << j)) {
                result += 1;
            }
        }
    }
    return result;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= num_bits) {
        throw std::out_of_range("Index out of range");
    }
    return bits[i / BITS_IN_BYTE] & (1 << (7 - (i % BITS_IN_BYTE)));
}

int BitArray::size() const {
    return num_bits;
}

bool BitArray::empty() const {
    return num_bits == 0;
}

std::string BitArray::to_string() const {
    std::string result;
    for (int i = 0; i < num_bytes; i++) {
        result += byte_to_string(bits[i]);
    }
    if (num_bits % BITS_IN_BYTE != 0) {
        result.erase(num_bytes * BITS_IN_BYTE - (BITS_IN_BYTE - (num_bits % BITS_IN_BYTE)), BITS_IN_BYTE - (num_bits % BITS_IN_BYTE));
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