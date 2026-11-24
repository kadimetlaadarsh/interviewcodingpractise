#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template <typename K, typename V>
class MyHashMap {
private:
    static const int INITIAL_CAPACITY = 16;
    static const int MAXIMUM_CAPACITY = 1 << 30;

    struct Entry {
        K key;
        V value;
        Entry* next;

        Entry(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    vector<Entry*> hashTable;

    int tableSizeFor(int cap) {
        if (cap <= 1) return 1;
        if (cap >= MAXIMUM_CAPACITY) return MAXIMUM_CAPACITY;

        unsigned int n = static_cast<unsigned int>(cap - 1);
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;

        return static_cast<int>(n + 1);
    }

    size_t getIndex(const K& key) const {
        size_t hashCode = hash<K>{}(key);
        return hashCode & (hashTable.size() - 1);
    }

public:
    MyHashMap() : hashTable(INITIAL_CAPACITY, nullptr) {}

    explicit MyHashMap(int capacity)
        : hashTable(tableSizeFor(capacity), nullptr) {}

    void put(const K& key, const V& value) {
        size_t index = getIndex(key);
        Entry* node = hashTable[index];

        while (node != nullptr) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }

        Entry* newNode = new Entry(key, value);
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }

    bool get(const K& key, V& result) const {
        size_t index = getIndex(key);
        Entry* node = hashTable[index];

        while (node != nullptr) {
            if (node->key == key) {
                result = node->value;
                return true;
            }
            node = node->next;
        }

        return false;
    }

    ~MyHashMap() {
        for (Entry* node : hashTable) {
            while (node != nullptr) {
                Entry* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }
};

int main() {
    MyHashMap<int, string> map(7);

    map.put(1, "hi");
    map.put(2, "my");
    map.put(3, "name");
    map.put(4, "is");
    map.put(5, "Shrayansh");
    map.put(6, "how");
    map.put(7, "are");
    map.put(8, "you");
    map.put(9, "friends");
    map.put(10, "?");

    string value;

    if (map.get(8, value)) {
        cout << value << endl;
    }

    return 0;
}