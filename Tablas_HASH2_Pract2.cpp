#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace chrono;

/* =========================
   Hash con encadenamiento
   ========================= */
class HashTableChaining {
private:
    int size;
    vector<list<pair<string, string>>> table;

public:
    int collisions = 0;

    HashTableChaining(int s) : size(s), table(s) {}

    int hash_function(const string& key) {
        return std::hash<string>{}(key) % size;
    }

    void insert(const string& key, const string& value) {
        int index = hash_function(key);

        if (!table[index].empty())
            collisions++;

        table[index].push_back({key, value});
    }

    string search(const string& key) {
        int index = hash_function(key);

        for (auto& kv : table[index]) {
            if (kv.first == key)
                return kv.second;
        }
        return "";
    }

    double load_factor(int total_elements) {
        return (double)total_elements / size;
    }
};


/* =========================
   Hash con sondeo lineal
   ========================= */
class HashTableLinearProbing {
private:
    int size;
    vector<pair<string, string>> table;
    vector<bool> occupied;

public:
    int collisions = 0;

    HashTableLinearProbing(int s) : size(s) {
        table.resize(s);
        occupied.resize(s, false);
    }

    int hash_function(const string& key) {
        return std::hash<string>{}(key) % size;
    }

    void insert(const string& key, const string& value) {
        int index = hash_function(key);

        while (occupied[index]) {
            collisions++;
            index = (index + 1) % size;
        }

        table[index] = {key, value};
        occupied[index] = true;
    }

    string search(const string& key) {
        int index = hash_function(key);
        int start = index;

        while (occupied[index]) {
            if (table[index].first == key)
                return table[index].second;

            index = (index + 1) % size;
            if (index == start) break;
        }
        return "";
    }

    double load_factor(int total_elements) {
        return (double)total_elements / size;
    }
};


/* =========================
   MAIN (benchmark)
   ========================= */
int main() {

    // Simulación de datos (equivalente a keys del CSV)
    vector<string> keys;
    for (int i = 0; i < 10000; i++) {
        keys.push_back("user_" + to_string(i));
    }

    int table_size = 20011;

    /* -------- Encadenamiento -------- */
    HashTableChaining hash_chain(table_size);

    auto start = high_resolution_clock::now();
    for (auto& key : keys)
        hash_chain.insert(key, key);
    auto end = high_resolution_clock::now();

    double insert_time_chain = duration<double>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; i++)
        hash_chain.search(keys[i]);
    end = high_resolution_clock::now();

    double search_time_chain = duration<double>(end - start).count();


    /* -------- Sondeo lineal -------- */
    HashTableLinearProbing hash_linear(table_size);

    start = high_resolution_clock::now();
    for (auto& key : keys)
        hash_linear.insert(key, key);
    end = high_resolution_clock::now();

    double insert_time_linear = duration<double>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; i++)
        hash_linear.search(keys[i]);
    end = high_resolution_clock::now();

    double search_time_linear = duration<double>(end - start).count();


    /* -------- unordered_map (equivalente a dict) -------- */
    unordered_map<string, string> native_map;

    start = high_resolution_clock::now();
    for (auto& key : keys)
        native_map[key] = key;
    end = high_resolution_clock::now();

    double insert_time_map = duration<double>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; i++)
        native_map[keys[i]];
    end = high_resolution_clock::now();

    double search_time_map = duration<double>(end - start).count();


    /* -------- Resultados -------- */
    cout << "\nRESULTADOS\n";
    cout << "----------------------------------------\n";

    cout << "Encadenamiento:\n";
    cout << "Insert: " << insert_time_chain << " s\n";
    cout << "Search: " << search_time_chain << " s\n";
    cout << "Collisions: " << hash_chain.collisions << "\n\n";

    cout << "Sondeo lineal:\n";
    cout << "Insert: " << insert_time_linear << " s\n";
    cout << "Search: " << search_time_linear << " s\n";
    cout << "Collisions: " << hash_linear.collisions << "\n\n";

    cout << "unordered_map:\n";
    cout << "Insert: " << insert_time_map << " s\n";
    cout << "Search: " << search_time_map << " s\n";

    return 0;
}
