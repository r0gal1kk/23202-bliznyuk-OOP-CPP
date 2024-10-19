#include <iostream>
#include <vector>
#include <stdexcept>

class BitArray {
private:
    std::vector<unsigned char> bits;
    unsigned long long num_bits;
    void shift_left(const int& n) {
        const int byte_shift = n / 8;
        const int bit_shift = n % 8;
        for (int i = 0; i < bits.size(); i++) {
            if (i + byte_shift < bits.size()) {
                bits[i] = bits[i + byte_shift];
            }
            else {
                bits[i] = 0;
            }
        }
        for (int i = 0; i < bits.size() - byte_shift; i++) {
            bits[i] <<= bit_shift;
            if (i + 1 < bits.size()) {
                bits[i] |= bits[i + 1] >> (8 - bit_shift);
            }
        }
    }
    void shift_right(const int& n) {
        const int byte_shift = n / 8;
        const int bit_shift = n % 8;
        for (int i = bits.size() - 1; i >= 0; i--) {
            if (i - byte_shift >= 0) {
                bits[i] = bits[i - byte_shift];
            }
            else {
                bits[i] = 0;
            }
        }
        for (int i = bits.size() - 1; i >= byte_shift; i--) {
            bits[i] >>= bit_shift;
            if (i - 1 >= 0) {
                bits[i] |= bits[i - 1] << (8 - bit_shift);
            }
        }
        bits[bits.size() - 1] &= 255 << (8 - (num_bits % 8));
    }
public:
    BitArray();

    ~BitArray();

    //Конструирует массив, хранящий заданное количество бит.
    //Первые sizeof(long) бит можно инициализровать с помощью параметра value.
    explicit BitArray(int num_bits, unsigned char value = 0) {
        if (num_bits % 8 != 0) {
            bits.resize(num_bits / 8 + 1);
            bits[0] = value;
        }
        else {
            bits.resize(num_bits / 8);
            bits[0] = value;
        }
        this->num_bits = num_bits;
    }

    BitArray(const BitArray &b) {
        bits = b.bits;
    }

    //Обменивает значения двух битовых массивов.
    void swap(BitArray &b) {
        std::swap(this->num_bits, b.num_bits);
        std::swap(bits, b.bits);
    }

    BitArray &operator=(const BitArray &b) {
        if (this != &b) {
            bits = b.bits;
            this->num_bits = b.num_bits;
        }
        return *this;
    }

    //Изменяет размер массива. В случае расширения, новые элементы
    //инициализируются значением value.
    void resize(int num_bits, unsigned char value = 0) {
        if (num_bits % 8 != 0) {
            bits.resize(num_bits / 8 + 1, value);
        }
        else {
            bits.resize(num_bits / 8, value);
        }
        if (this->num_bits > num_bits) {
            int extra_bits = this->num_bits - num_bits;
            
        }
        this->num_bits = num_bits;
    }

    //Очищает массив.
    void clear() {
        bits.clear();
        num_bits = 0;
    }

    //Добавляет новый бит в конец массива. В случае необходимости
    //происходит перераспределение памяти.
    void push_back(unsigned char bit) {
        if (num_bits % 8 == 0) {
            bits.push_back(0);
        }
        if (bit) {
            bits[(num_bits / 8)] |= 1 << (7 - (num_bits % 8));
        }
        num_bits++;
    }


    //Битовые операции над массивами.
    //Работают только на массивах одинакового размера.
    //Обоснование реакции на параметр неверного размера входит в задачу.
    BitArray &operator&=(const BitArray &b) {
        if (this->num_bits != b.num_bits) {
            throw std::invalid_argument("BitArrays must be of the same size");
        }
        for (int i = 0; i < bits.size(); i++) {
            bits[i] &= b.bits[i];
        }
        return *this;
    }

    BitArray &operator|=(const BitArray &b) {
        if (this->num_bits != b.num_bits) {
            throw std::invalid_argument("BitArrays must be of the same size");
        }
        for (int i = 0; i < bits.size(); i++) {
            bits[i] |= b.bits[i];
        }
        return *this;
    }

    BitArray &operator^=(const BitArray &b) {
        if (this->num_bits != b.num_bits) {
            throw std::invalid_argument("BitArrays must be of the same size");
        }
        for (int i = 0; i < bits.size(); i++) {
            bits[i] ^= b.bits[i];
        }
        return *this;
    }

    //Битовый сдвиг с заполнением нулями.
    BitArray &operator<<=(int n) {
        if (n < 0) {
            throw std::invalid_argument("Negative number of bits");
        }
        if (n == 0) {
            return *this;
        }
        shift_left(n);
        return *this;
    }

    BitArray &operator>>=(int n) {
        if (n < 0) {
            throw std::invalid_argument("Negative number of bits");
        }
        if (n == 0) {
            return *this;
        }
        shift_right(n);
        return *this;
    }

    BitArray operator<<(int n) const {
        BitArray result(*this);
    }

    BitArray operator>>(int n) const;


    //Устанавливает бит с индексом n в значение val.
    BitArray &set(int n, bool val = true);

    //Заполняет массив истиной.
    BitArray &set();

    //Устанавливает бит с индексом n в значение false.
    BitArray &reset(int n);

    //Заполняет массив ложью.
    BitArray &reset();

    //true, если массив содержит истинный бит.
    bool any() const;

    //true, если все биты массива ложны.
    bool none() const;

    //Битовая инверсия
    BitArray operator~() const;

    //Подсчитывает количество единичных бит.
    int count() const;


    //Возвращает значение бита по индексу i.
    bool operator[](int i) const;

    int size() const;

    bool empty() const;

    //Возвращает строковое представление массива.
    std::string to_string() const;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
