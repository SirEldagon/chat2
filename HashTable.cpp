#include "HashTable.h"
#include <iostream>
#include <cmath>

HashTable::HashTable(size_t size) : size(size), count(0) {
    table.resize(size);
}

// Хеш-функция методом умножения
size_t HashTable::hashFunction(const std::string& key) const {
    const double A = 0.6180339887; // (sqrt(5)-1)/2, золотое сечение
    unsigned int hashValue = stringHash(key);
    double frac = fmod(hashValue * A, 1.0);
    return static_cast<size_t>(floor(size * frac));
}

// Простая хеш-функция для строки (сумма символов)
unsigned int HashTable::stringHash(const std::string& str) const {
    unsigned int sum = 0;
    for (char ch : str) {
        sum += static_cast<unsigned char>(ch);
    }
    return sum;
}

// Пробирование квадратичное
size_t HashTable::probe(const std::string& key, size_t attempt) const {
    size_t hash = hashFunction(key);
    return (hash + attempt * attempt) % size;
}

// Вставка
bool HashTable::insert(const std::string& login, const std::string& password) {
    if (count >= size) {
        std::cerr << "Хеш-таблица заполнена!\n";
        return false;
    }

    size_t attempt = 0;
    size_t index;
    while (attempt < size) {
        index = probe(login, attempt);
        if (table[index].login.empty() || table[index].isDeleted) {
            table[index] = Entry(login, std::to_string(stringHash(password)));
            ++count;
            return true;
        } else if (table[index].login == login) {
            // Обновление пароля
            table[index].passwordHash = std::to_string(stringHash(password));
            return true;
        }
        ++attempt;
    }
    return false;
}

// Получение пароля по логину
std::optional<std::string> HashTable::getPassword(const std::string& login) const {
    size_t attempt = 0;
    size_t index;
    while (attempt < size) {
        index = probe(login, attempt);
        if (table[index].login.empty() && !table[index].isDeleted) {
            return std::nullopt; // не найден
        }
        if (!table[index].isDeleted && table[index].login == login) {
            return table[index].passwordHash;
        }
        ++attempt;
    }
    return std::nullopt;
}

// Удаление
void HashTable::remove(const std::string& login) {
    size_t attempt = 0;
    size_t index;
    while (attempt < size) {
        index = probe(login, attempt);
        if (table[index].login.empty() && !table[index].isDeleted) {
            return; // не найден
        }
        if (!table[index].isDeleted && table[index].login == login) {
            table[index].isDeleted = true;
            --count;
            return;
        }
        ++attempt;
    }
}

// Для отладки
void HashTable::display() const {
    for (size_t i = 0; i < size; ++i) {
        if (!table[i].login.empty() && !table[i].isDeleted) {
            std::cout << i << ": " << table[i].login << " -> " << table[i].passwordHash << "\n";
        } else {
            std::cout << i << ": [empty]\n";
        }
    }
}
