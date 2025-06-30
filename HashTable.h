#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <optional>

class HashTable {
public:
    explicit HashTable(size_t size);
    bool insert(const std::string& login, const std::string& password);
    std::optional<std::string> getPassword(const std::string& login) const;
    void remove(const std::string& login);
    void display() const; // для отладки

private:
    struct Entry {
        std::string login;
        std::string passwordHash;
        bool isDeleted;

        Entry() : login(""), passwordHash(""), isDeleted(false) {}
        Entry(const std::string& l, const std::string& p) : login(l), passwordHash(p), isDeleted(false) {}
    };

    std::vector<Entry> table;
    size_t size;
    size_t count;

    size_t hashFunction(const std::string& key) const;
    size_t probe(const std::string& key, size_t attempt) const;
    unsigned int stringHash(const std::string& str) const;
};

#endif // HASHTABLE_H
