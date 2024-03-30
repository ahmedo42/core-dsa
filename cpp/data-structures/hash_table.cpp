#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

template <typename T, typename V>

class HashTable
{
private:
    const int initial_size = 1543; // credits: https://planetmath.org/goodhashtableprimes
    std::vector<std::pair<T, V>> table;
    int free_slots = initial_size;
    std::hash<T> hashing;

    std::pair<int, std::pair<T, V>> search(T key)
    {
        int index = hashing(key) % (table.size());
        int search_idx = index;
        while (table[search_idx] != std::pair<T, V>())
        {

            if (table[search_idx].first == key)
            {
                return std::make_pair(search_idx, table[search_idx]);
            }

            search_idx += 1;
            search_idx %= table.size();

            if (search_idx == index)
            {
                break;
            }
        }
        return std::make_pair(search_idx, std::pair<T, V>());
    }

    void resize()
    {
        std::vector<std::pair<T, V>> new_table(table.size() * 2);
        for (auto e : table)
        {
            if (e != std::pair<T, V>())
            {
                int new_idx = hashing(e.first) % new_table.size();
                new_table[new_idx] = e;
            }
        }
        this->table = new_table;
        this->free_slots = this->table.size();
    }

public:
    HashTable()
    {
        table.resize(initial_size);
    }
    void add(T key, V value)
    {

        auto result = search(key);
        this->table[result.first] = std::make_pair(key, value);
        if (result.second == std::pair<T, V>())
        {
            this->free_slots -= 1;
        }

        if (this->free_slots < 0.3 * this->table.size())
        {
            resize();
        }
        print();
    }
    void remove(T key)
    {
        auto result = search(key);
        if (result.second != std::pair<T, V>())
        {
            table[result.first] = std::pair<T, V>();
            this->free_slots += 1;
            print();
            return;
        }
        throw std::invalid_argument("key doesn't exist");
    }
    V get(T key)
    {
        auto result = search(key);
        if (result.second != std::pair<T, V>())
        {
            return result.second.second;
        }
        throw std::invalid_argument("key doesn't exist");
    }
    void print()
    {
        for (auto e : table)
        {
            if (e != std::pair<T, V>())
            {
                std::cout << e.first << ": " << e.second << '\n';
            }
        }
        std::cout << std::endl;
    }
};