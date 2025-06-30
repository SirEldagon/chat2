#include <iostream>
#include "HashTable.h"

int main() {
    HashTable chatTable(10); // размер таблицы

    // Регистрация пользователей
    chatTable.insert("user1", "pass1");
    chatTable.insert("user2", "pass2");
    chatTable.insert("admin", "adminpass");

    // Вход
    std::string login, password;
    std::cout << "Введите логин: ";
    std::cin >> login;
    std::cout << "Введите пароль: ";
    std::cin >> password;

    auto storedHashOpt = chatTable.getPassword(login);
    if (storedHashOpt.has_value()) {
        if (storedHashOpt.value() == std::to_string(HashTable::stringHash(password))) {
            std::cout << "Успешный вход!\n";
        } else {
            std::cout << "Неверный пароль.\n";
        }
    } else {
        std::cout << "Пользователь не найден.\n";
    }

    // Для демонстрации
    std::cout << "\nТекущие пользователи:\n";
    chatTable.display();

    return 0;
}