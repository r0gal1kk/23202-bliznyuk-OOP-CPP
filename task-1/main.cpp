#include <iostream>
#include "src/BitArray.h"

int main() {
    // Создание битового массива на 16 бит, инициализированного значением 5
    BitArray a(16);
    a[5] = 1;
    std::cout << a.to_string() << std::endl;
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
     a.resize(20, 1);
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
