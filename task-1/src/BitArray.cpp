#include "BitArray.h"

void BitArray::clear_extra_bits() {
    if (num_bits % 8 == 0) {
        return;
    }
    const int last_byte = bits.size() - 1;
    const int valid_bits = num_bits % BITS_IN_BYTE;
    const unsigned char mask = MAX_BYTE << (BITS_IN_BYTE - valid_bits);
    bits[last_byte] &= mask;
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

BitArray::BitRef BitArray::operator[](int i) {
    const int byte_index = i / BITS_IN_BYTE;
    const int bit_index = i % BITS_IN_BYTE;
    return {bits[byte_index], bit_index};
}

BitArray::BitArray() : num_bits(0) {}

BitArray::BitArray(int num_bits, long value) : num_bits(num_bits) {
    bits.resize((num_bits / BITS_IN_BYTE) + ((num_bits % BITS_IN_BYTE) != 0 ? 1 : 0));
    for (int i = 0; i < bits.size(); i++) {
        bits[i] = (value >> (i * BITS_IN_BYTE)) & MAX_BYTE;
    }
}

BitArray::BitArray(const BitArray& b) {
    bits = b.bits;
    num_bits = b.num_bits;
}

void BitArray::shift_left(const int& n) {
    const int byte_shift = n / BITS_IN_BYTE;
    const int bit_shift = n % BITS_IN_BYTE;
    for (int i = 0; i < bits.size(); i++) {
        if (i + byte_shift < bits.size()) {
            bits[i] = bits[i + byte_shift];
        } else {
            bits[i] = 0;
        }
    }
    for (int i = 0; i < bits.size() - byte_shift; i++) {
        bits[i] <<= bit_shift;
        if (i + 1 < bits.size()) {
            bits[i] |= bits[i + 1] >> (BITS_IN_BYTE - bit_shift);
        }
    }
}

void BitArray::shift_right(const int& n) {
    const int byte_shift = n / BITS_IN_BYTE;
    const int bit_shift = n % BITS_IN_BYTE;
    for (int i = bits.size() - 1; i >= 0; i--) {
        if (i - byte_shift >= 0) {
            bits[i] = bits[i - byte_shift];
        } else {
            bits[i] = 0;
        }
    }
    for (int i = bits.size() - 1; i >= byte_shift; i--) {
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
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        bits = b.bits;
        this->num_bits = b.num_bits;
    }
    return *this;
}

void BitArray::resize(const int num_bits, const unsigned char value) {
    if (value != 0 && value != 1) {
        throw std::invalid_argument("Value must be 0 or 1");
    }
    if (num_bits > this->num_bits && value) {
        bits[bits.size() - 1] |= MAX_BYTE >> (this->num_bits % BITS_IN_BYTE);
    }
    bits.resize(num_bits / BITS_IN_BYTE + (num_bits % BITS_IN_BYTE != 0 ? 1 : 0), value == 0 ? 0 : MAX_BYTE);
    bits[bits.size() - 1] &= MAX_BYTE << (num_bits % BITS_IN_BYTE);
    this->num_bits = num_bits;
}

void BitArray::clear() {
    bits.clear();
    num_bits = 0;
}

void BitArray::push_back(unsigned char bit) {
    if (num_bits % BITS_IN_BYTE == 0) {
        bits.push_back(0);
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
    for (int i = 0; i < bits.size(); i++) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (this->num_bits != b.num_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < bits.size(); i++) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (this->num_bits != b.num_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < bits.size(); i++) {
        bits[i] ^= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative number of bits");
    }
    if (n == 0) {
        return *this;
    }
    shift_left(n);
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative number of bits");
    }
    if (n == 0) {
        return *this;
    }
    shift_right(n);
    return *this;
}

BitArray BitArray::operator<<(const int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(const int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::set() {
    for (auto& byte : bits) {
        byte = MAX_BYTE;
    }
    clear_extra_bits();
    return *this;
}

BitArray& BitArray::reset() {
    for (auto& byte : bits) {
        byte = 0;
    }
    return *this;
}

bool BitArray::any() const {
    for (auto byte : bits) {
        if (byte != 0) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    for (auto byte : bits) {
        if (byte != 0) {
            return false;
        }
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray result = *this;
    for (int i = 0; i < bits.size(); i++) {
        result.bits[i] = ~(this->bits[i]);
    }
    result.clear_extra_bits();
    return result;
}

int BitArray::count() const {
    int result = 0;
    for (auto byte : bits) {
        for (int i = 0; i < BITS_IN_BYTE; i++) {
            if (byte & (1 << i)) {
                result += 1;
            }
        }
    }
    return result;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= bits.size()) {
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
    for (int i = 0; i < bits.size(); i++) {
        result += byte_to_string(bits[i]);
    }
    if (num_bits % BITS_IN_BYTE != 0) {
        result.erase(bits.size() * BITS_IN_BYTE - (BITS_IN_BYTE - (num_bits % BITS_IN_BYTE)), BITS_IN_BYTE - (num_bits % BITS_IN_BYTE));
    }
    return result;
}
