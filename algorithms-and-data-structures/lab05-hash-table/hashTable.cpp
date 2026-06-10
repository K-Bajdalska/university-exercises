#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include "linked_list.h"

using namespace std;

const double MAX_FILL = 0.75;

template <typename T>
struct pair_v_k {
	string key;
	T value;

    pair_v_k(string k, T v) {
        key = k;
        value = v;
    }
};

template <typename T>
class Hash_table {
private:
	vector <Linked_list<pair_v_k<T>>*> *dynamic_array;
	unsigned int actual_size = 0;
	unsigned int max_size = 1;

    void rehash() {
        int new_size = max_size * 2;
        vector<Linked_list<pair_v_k<T>>*>* new_array = new vector<Linked_list<pair_v_k<T>>*>(new_size);
        for (unsigned int i = 0; i < new_size; i++) {
            (*new_array)[i] = new Linked_list<pair_v_k<T>>();
        }
        unsigned int prev_max = max_size;
        max_size = new_size;
        for (unsigned int i = 0; i < prev_max; i++) {
            Node<pair_v_k<T>>* current = (*dynamic_array)[i]->get_node(0);
            while (current != nullptr) {
                int new_index = hash_function(current->value.key);
                (*new_array)[new_index]->add_to_end(current->value);
                current = current->next;
            }
        }
        for (unsigned int i = 0; i < prev_max; i++) {
            delete (*dynamic_array)[i];
        }
        delete dynamic_array;
        dynamic_array = new_array;
    
    }

    long long hash_function(const string& s) const {
        const int base = 31;
        unsigned long long hash_value = 0;
        int q = (s.length()) - 1;

        for (int i = 0; i < s.length(); i++) {
            hash_value += (s[i] * pow(base, q));
            q -= 1;
        }

        return ((hash_value % max_size) + max_size) % max_size;  // gwarantowanie nieujmenego wyniku
    }
public:
	Hash_table() {
        dynamic_array = new vector<Linked_list<pair_v_k<T>>*>();  
        dynamic_array->resize(max_size);  
        for (unsigned int i = 0; i < max_size; i++) {
            (*dynamic_array)[i] = new Linked_list<pair_v_k<T>>();  
        }
	}

    void add(string key, T value) {

        if (dynamic_array == nullptr) {
            dynamic_array = new vector<Linked_list<pair_v_k<T>>*>();
            dynamic_array->resize(max_size);
            for (unsigned int i = 0; i < max_size; i++) {
                (*dynamic_array)[i] = new Linked_list<pair_v_k<T>>();
            }
        }
        if ((double)actual_size / max_size > MAX_FILL) {
            rehash();
        }
        int index = hash_function(key);  
        Node<pair_v_k<T>>* current = (*dynamic_array)[index]->get_node(0);  //pierwszy element o takim samym indeksie
        // Je¿eli klucz istnieje na liœcie:
        while (current != nullptr) {
            if (current->value.key == key) {
                current->value.value = value;  // aktualizacja wartoœci klucza
                return;
            }
            current = current->next;
        }
        // Jeœli klucz nie istnieje w liœcie
        (*dynamic_array)[index]->add_to_end(pair_v_k<T>(key, value));
        actual_size++;
    }

    pair_v_k<T>* find(const string& key) {
        int index = hash_function(key) % max_size;
        Node<pair_v_k<T>>* current = (*dynamic_array)[index]->get_node(0);

        while (current != nullptr) {
            if (current->value.key == key) {
                return &(current->value);
            }
            current = current->next;
        }

        return nullptr;
    }

    bool remove(string key) {
        int index = hash_function(key);
        Node<pair_v_k<T>>* current = (*dynamic_array)[index]->get_node(0);  // pierwszy element o takim samym indeksie
        Node<pair_v_k<T>>* previous = nullptr;

        // Szukanie klucza
        while (current != nullptr) {
            if (current->value.key == key) {
                if (previous == nullptr) {
                    // Usuwanie pierwszego elementu
                    (*dynamic_array)[index]->remove_from_start();
                }
                else {
                    // Usuwanie ze œrodka lub koñca listy
                    previous->next = current->next;
                    delete current;
                }
                actual_size--;
                return true;
            }
            previous = current;
            current = current->next;
        }

        return false;
    }

    void to_string() const {
        cout << "hash table:\n";
        cout << "Aktulany rozmiar: " << actual_size << "\n";
        cout << "Maksymalny rozmiar:: " << max_size << "\n";
        cout << "Tablica:\n{\n";

        int printed_elements = 0;
        for (unsigned int i = 0; i < max_size && printed_elements < 10; i++) {
            Node<pair_v_k<T>>* current = (*dynamic_array)[i]->get_node(0);
            if (current != nullptr) {
                cout << i << ": ";
                while (current != nullptr) {
                    cout << current->value.key << " -> " << current->value.value;
                    current = current->next;
                    if (current != nullptr) {
                        cout << ", ";
                    }
                }
                cout << ";\n";
                printed_elements++;
            }
        }

        cout << "...\n";
    }

    void print_statistics() const {
        int non_null_lists = 0;
        int min_list_size = INT_MAX;
        int max_list_size = 0;
        double total_list_size = 0;

        for (unsigned int i = 0; i < max_size; i++) {
            Node<pair_v_k<T>>* current = (*dynamic_array)[i]->get_node(0);
            if (current != nullptr) {
                non_null_lists++;
                int list_size = 0;
                while (current != nullptr) {
                    list_size++;
                    current = current->next;
                }
                min_list_size = min(min_list_size, list_size);
                max_list_size = max(max_list_size, list_size);
                total_list_size += list_size;
            }
        }

        cout << "Statystyki:\n";
        cout << "Nie puste listy: " << non_null_lists << "\n";
        cout << "Minimalny rozmiar listy: " << (non_null_lists > 0 ? min_list_size : 0) << "\n";
        cout << "Maksymalny rozmiar listy: " << max_list_size << "\n";
        cout << "Sredni rozmiar listy: " << fixed << setprecision(6)
            << (non_null_lists > 0 ? total_list_size / non_null_lists : 0) << "\n\n";
    }

    void clear() {
        for (unsigned int i = 0; i < max_size; i++) {
            delete (*dynamic_array)[i];
        }
        delete dynamic_array;
        dynamic_array = nullptr;
        actual_size = 0;
        max_size = 1;
    }

    ~Hash_table() {
        if (dynamic_array != nullptr) clear();
    }
};


string generate_random_key(int length = 6) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int max_index = sizeof(charset) - 1;
    string random_key;

    for (int i = 0; i < length; ++i) {
        random_key += charset[rand() % max_index];
    }

    return random_key;
}



int main() {

    srand(static_cast<unsigned int>(time(0)));

    const int MAX_ORDER = 7; 
    Hash_table<int>* ht = new Hash_table<int>(); 

    for (int o = 1; o <= MAX_ORDER; o++) {
        cout << " ----------- POMIAR " << o << "-----------" << endl;
        const int n = pow(10, o); 

        // Dodawanie do tablicy mieszaj¹cej
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            ht->add(generate_random_key(6), i); // Klucze losowe 6-znakowe, a jako wartoœci indeks pêtli
        }
        clock_t t2 = clock();
        double add_time = double(t2 - t1) / CLOCKS_PER_SEC;

        // Wypis na ekran aktualnej postaci tablicy mieszaj¹cej (skróconej) oraz pomiarów czasowych
        cout << "Dodawanie " << n << " elementow zajelo: " << add_time << " sekund.\n";
        ht->to_string(); // Wypis skróconej postaci tablicy mieszaj¹cej

        // Wyszukiwanie w tablicy mieszaj¹cej
        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++) {
            string random_key = generate_random_key(6);
            pair_v_k<int>* entry = ht->find(random_key); // Wyszukiwanie wg losowego klucza
            if (entry != nullptr) {
                hits++;
            }
        }
        t2 = clock();
        double search_time = double(t2 - t1) / CLOCKS_PER_SEC;

        // Wypis na ekran pomiarów czasowych i liczby trafieñ
        cout << "Wyszukiwanie " << m << " elementow zajelo: " << search_time << " sekund.\n";
        cout << "Liczba trafien: " << hits << "\n";

       
        ht->print_statistics(); 
        ht->clear(); 
    }

    delete ht;
    return 0;
}