#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>

class BitArray {
private:
    const unsigned char MAX_BYTE = 255;
    const int BITS_IN_BYTE = 8;
    std::vector<unsigned char> bits;
    int num_bits;
    std::string to_binary(int number) {
        if (number == 0) return "0";

        std::string result;
        while (number) {
            result += (number % 2) + '0';
            number >>= 1;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    void shift_left(const int& n) {
        const int byte_shift = n / BITS_IN_BYTE;
        const int bit_shift = n % BITS_IN_BYTE;
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
                bits[i] |= bits[i + 1] >> (BITS_IN_BYTE - bit_shift);
            }
        }
    }

    void shift_right(const int& n) {
        const int byte_shift = n / BITS_IN_BYTE;
        const int bit_shift = n % BITS_IN_BYTE;
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
                bits[i] |= bits[i - 1] << (BITS_IN_BYTE - bit_shift);
            }
        }
        bits[bits.size() - 1] &= MAX_BYTE << (BITS_IN_BYTE - (num_bits % BITS_IN_BYTE));
    }

    std::string byte_to_string(unsigned char byte) const {
        std::string result;
        for (int i = BITS_IN_BYTE - 1; i >=0; i--) {
            result += byte & (1 << i) ? '1' : '0';
        }
        return result;
    }
public:
    class BitRef {
        private:
        unsigned char& byte;
        int bit_position;
        public:
        BitRef(unsigned char& byte, int bit_position) : byte(byte), bit_position(bit_position) {}

        BitRef &operator=(const unsigned char value) {
            if (value) {
                byte |= (1 << (7 - bit_position));
            }
            else {
                byte &= ~(1 << (7 - bit_position));
            }
            return *this;
        }
    };

    BitRef operator[](int i) {
        const int byte_index = i / BITS_IN_BYTE;
        const int bit_index = i % BITS_IN_BYTE;
        return {bits[byte_index], bit_index};
    }

    BitArray() = default;

    ~BitArray() = default;

    //Конструирует массив, хранящий заданное количество бит.
    //Первые sizeof(long) бит можно инициализровать с помощью параметра value.
    explicit BitArray(int num_bits, long value = 0) {
        bits.resize((num_bits / BITS_IN_BYTE) + ((num_bits % BITS_IN_BYTE) != 0 ? 1 : 0));
        //std::string binary = to_binary(value);
        //for (int i = num_bits - 1, j = binary.size() - 1; i >= num_bits - binary.size(); i--) {
        //
        //}
        this->num_bits = num_bits;
    }

    BitArray(const BitArray &b) {
        bits = b.bits;
        num_bits = b.num_bits;
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
    void resize(const int num_bits, const unsigned char value = 0) {
        if (value != 0 && value != 1) {
            throw std::invalid_argument("Value must be 0 or 1");
        }
        if (num_bits > this->num_bits && value) {
            bits[bits.size() - 1] |= MAX_BYTE >> (this->num_bits % BITS_IN_BYTE);
        }
        bits.resize(num_bits / BITS_IN_BYTE + (num_bits % BITS_IN_BYTE == 0 ? 0 : 1), value == 0 ? 0 : MAX_BYTE);
        bits[bits.size() - 1] &= MAX_BYTE << (num_bits % BITS_IN_BYTE);
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
        if (num_bits % BITS_IN_BYTE == 0) {
            bits.push_back(0);
        }
        if (bit) {
            bits[(num_bits / BITS_IN_BYTE)] |= 1 << (7 - (num_bits % BITS_IN_BYTE));
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

    BitArray operator<<(const int n) const {
        BitArray result(*this);
        result <<= n;
        return result;
    }

    BitArray operator>>(const int n) const {
        BitArray result(*this);
        result >>= n;
        return result;
    }

    //Заполняет массив истиной.
    BitArray &set() {
        for (auto &byte : bits) {
            byte = MAX_BYTE;
        }
        bits[bits.size() - 1] &= MAX_BYTE << (num_bits % BITS_IN_BYTE);
        return *this;
    }

    //Заполняет массив ложью.
    BitArray &reset() {
        for (auto &byte : bits) {
            byte = 0;
        }
        return *this;
    }

    //true, если массив содержит истинный бит.
    bool any() const {
        for (auto byte : bits) {
            if (byte != 0) {
                return true;
            }
        }
        return false;
    }

    //true, если все биты массива ложны.
    bool none() const {
        for (auto byte : bits) {
            if (byte != 0) {
                return false;
            }
        }
        return true;
    }

    //Битовая инверсия
    BitArray operator~() const {
        BitArray result = *this;
        for (int i = 0; i < bits.size(); i++) {
            result.bits[i] = ~(this->bits[i]);
        }
        return result;
    }

    //Подсчитывает количество единичных бит.
    int count() const {
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

    //Возвращает значение бита по индексу i.
    bool operator[](int i) const {
        if (i < 0 || i >= bits.size()) {
            throw std::out_of_range("Index out of range");
        }
        return bits[i / BITS_IN_BYTE] & (1 << (7 - (i % BITS_IN_BYTE)));
    }

    int size() const {
        return num_bits;
    }

    bool empty() const {
        return num_bits == 0;
    }

    //Возвращает строковое представление массива.
    std::string to_string() const {
        std::string result;
        for (int i = 0; i < bits.size(); i++) {
            result += byte_to_string(bits[i]);
        }
        if (num_bits % BITS_IN_BYTE != 0) {
            result.erase(bits.size() * BITS_IN_BYTE - (BITS_IN_BYTE - (num_bits % BITS_IN_BYTE)), BITS_IN_BYTE - (num_bits % BITS_IN_BYTE));
        }
        return result;
    }
};

int main() {
    // Создание битового массива на 16 бит, инициализированного значением 5
    BitArray a(16);

    // Выводим строковое представление
    std::cout << "Initial BitArray: " << a.to_string() << std::endl;

    // Устанавливаем все биты в 1
    a.set();
    std::cout << "After set: " << a.to_string() << std::endl;

    // Сбрасываем все биты в 0
    a.reset();
    std::cout << "After reset: " << a.to_string() << std::endl;

    // Добавляем бит в конец
    a.push_back(1);
    std::cout << "After push_back(1): " << a.to_string() << std::endl;

    // Изменяем размер массива
    a.resize(20);
    std::cout << "After resize to 20 (with value 1): " << a.to_string() << std::endl;

    // Создаем еще один битовый массив
    BitArray b(20); // 00000011
    std::cout << "Second BitArray (b): " << b.to_string() << std::endl;

    // Выполняем побитовую операцию И
    a &= b;
    std::cout << "After a &= b: " << a.to_string() << std::endl;

    // Проверяем наличие истинных битов
    std::cout << "Any bit is true in a: " << (a.any() ? "true" : "false") << std::endl;

    // Проверяем, все ли биты ложны
    std::cout << "All bits are false in a: " << (a.none() ? "true" : "false") << std::endl;

    // Инвертируем биты
    BitArray c = ~a;
    std::cout << "After inversion of a: " << c.to_string() << std::endl;

    // Подсчитываем количество единичных бит
    std::cout << "Count of 1s in c: " << c.count() << std::endl;

    return 0;
}
