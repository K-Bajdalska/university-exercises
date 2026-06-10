#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// ------------------- OG”LNY SZABLON KLASY NODE DLA OBIEKT”W -------------------
template <typename T>
class Node {
public:
	T value;
	int index;
	static int current_index;

	Node() : index(current_index++) {}
	Node(T value, bool manage_data = false) : value(value), index(current_index++) {}
};
template <typename T>
int Node<T>::current_index = 0;

// ------------------- SPECJALIZACJA KLASY NODE DLA WSKAèNIK”W -------------------
template <typename T>
class Node<T*> {
public:
    T* value;
    int index;
    bool manage_memory;
    static int current_index;

    Node() : value(nullptr), index(current_index++), manage_memory(false) {}
    Node(T* value, bool manage_memory = false) {
        this->value = new T(*value);
        this->index = current_index++;
        this->manage_memory = manage_memory;
    }
    ~Node() {
        if (manage_memory && value) {
            delete value;
        }
    }
    void set_manage_memory(bool manage_memory) {
        this->manage_memory = manage_memory;
    }
};

template <typename T>
int Node<T*>::current_index = 0;

// Pomocnicza funkcja do ustawiania zarzπdzania pamiÍciπ
template <typename T>
void set_manage_memory(Node<T>* node, bool manage_memory) {
    // Nic nie robi dla typÛw nie bÍdπcych wskaünikami
}

template <typename T>
void set_manage_memory(Node<T*>* node, bool manage_memory) {
    node->set_manage_memory(manage_memory);
}


// ------------------- SZABLON KOPCA DLA OBIEKT”W -------------------
template <typename T>
class Binary_heap {
private:
	vector <Node<T>*> *dynamic_array;

    void heapify_up(int index, int (*comparator)(T, T)) {
        if (index == 0) return;

        int parent_index = (index - 1) / 2;
        if (comparator((*dynamic_array)[index]->value, (*dynamic_array)[parent_index]->value) < 0) {
            swap((*dynamic_array)[index], (*dynamic_array)[parent_index]);
            heapify_up(parent_index, comparator);
        }
    }

    void heapify_down(int index, int (*comparator)(T*, T*)) {
        int left_child_index = 2 * index + 1;
        int right_child_index = 2 * index + 2;
        int largest = index;

        if (left_child_index < dynamic_array->size() &&
            comparator((*dynamic_array)[left_child_index]->value, (*dynamic_array)[largest]->value) > 0) {
            largest = left_child_index;
        }

        if (right_child_index < dynamic_array->size() &&
            comparator((*dynamic_array)[right_child_index]->value, (*dynamic_array)[largest]->value) > 0) {
            largest = right_child_index;
        }

        if (largest != index) {
            swap((*dynamic_array)[index], (*dynamic_array)[largest]);
            heapify_down(largest, comparator);
        }
    }

public:
    Binary_heap() {
        dynamic_array = new vector<Node<T>*>();
    }

    void add(T value, int (*comparator)(T, T)) {
        Node<T>* node = new Node<T>(value);
        dynamic_array->push_back(node);
        heapify_up(dynamic_array->size() - 1, comparator);
    }

    T remove_max(int (*comparator)(T, T)) {
        if (dynamic_array->empty()) {
            cerr << "Kopiec jest pusty" << endl;
        }

        Node<T>* root = (*dynamic_array)[0];
        T max_value = root->value;

        (*dynamic_array)[0] = (*dynamic_array)[dynamic_array->size() - 1];
        dynamic_array->pop_back();
        delete root;

        if (!dynamic_array->empty()) {
            heapify_down(0, comparator);
        }

        return max_value;
    }

    void clear() {
        for (Node<T>* node : *dynamic_array) {
            delete node;
        }
        dynamic_array->clear();
    }

    void to_string(void(*data_show)(T), unsigned int count = 10) {
        cout << "Kopiec Binarny\n\tLiczba elementow: " << dynamic_array->size() << "\tadres w pamieci: "
            << this << "\tadres funckji wypisujacej dane: " << data_show << endl;
        cout << "Pierwsze " << count << "elemty / elementow:";
        for (size_t i = 0; i < count; ++i) {
            if (dynamic_array->size() == 0) {
                cout << "Kopiec pusty" << endl;
                break;
            }
            cout << i + 1 << ". " << data_show((*dynamic_array)[i]->value);
        }
        cout << "Ostatnie " << count << " elementy/ow: " << endl;
        if (dynamic_array->size() == 0) {
            cout << "Kopiec pusty" << endl;
        }
        else {
            if (count > dynamic_array->size()) {
                for (int i = dynamic_array->size() - 1; i >= 0; i--) {
                    cout << i + 1 << ". ";
                    data_show((*dynamic_array)[i]->value);
                }
            }
            else {
                for (int i = dynamic_array->size() - count; i < dynamic_array->size(); i++) {
                    cout << i + 1 << ". ";
                    data_show((*dynamic_array)[i]->value);
                }

            }
        }
    }

    ~Binary_heap() {
        clear();
        delete dynamic_array;
    }
};

// ------------------- SZABLON KOPCA DLA WSKAèNIK”W NA OBIEKTY -------------------
template <typename T>
class Binary_heap <T*> {
private:
	vector <Node<T*>*>* dynamic_array;

    void heapify_up(int index, int (*comparator)(T*, T*)) {
        if (index == 0) return;

        int parent_index = (index - 1) / 2;
        if (comparator((*dynamic_array)[index]->value, (*dynamic_array)[parent_index]->value) > 0) {
            swap((*dynamic_array)[index], (*dynamic_array)[parent_index]);
            heapify_up(parent_index, comparator);
        }
    }

    void heapify_down(int index, int (*comparator)(T*, T*)) {
        int left_child_index = 2 * index + 1;
        int right_child_index = 2 * index + 2;
        int largest = index;

        if (left_child_index < dynamic_array->size() &&
            comparator((*dynamic_array)[left_child_index]->value, (*dynamic_array)[largest]->value) > 0) {
            largest = left_child_index;
        }

        if (right_child_index < dynamic_array->size() &&
            comparator((*dynamic_array)[right_child_index]->value, (*dynamic_array)[largest]->value) > 0) {
            largest = right_child_index;
        }

        if (largest != index) {
            swap((*dynamic_array)[index], (*dynamic_array)[largest]);
            heapify_down(largest, comparator);
        }
    }
public:
    Binary_heap() {
        dynamic_array = new vector<Node<T*>*>();
    }


    void add(T* value, int (*comparator)(T*, T*), bool manage_memory = false) {
        Node<T*>* node = new Node<T*>(value, manage_memory);
        dynamic_array->push_back(node);
        heapify_up(dynamic_array->size() - 1, comparator);
    }

    T* remove_max(int (*comparator)(T*, T*)) {
        if (dynamic_array->empty()) {
            cerr << "Kopiec jest pusty" << endl;
            return nullptr;
        }

        Node<T*>* root = (*dynamic_array)[0];
        T* max_value = root->value;

        (*dynamic_array)[0] = (*dynamic_array)[dynamic_array->size() - 1];
        dynamic_array->pop_back();
        //delete root;

        if (!dynamic_array->empty()) {
            heapify_down(0, comparator);
        }

        return max_value;
    }


    void clear() {
        for (Node<T*>* node : *dynamic_array) {
            delete node;
        }
        dynamic_array->clear();
    }

    void to_string(void(*data_show)(T*), unsigned int count = 10) {
        cout << "Kopiec Binarny\n\tLiczba elementow: " << dynamic_array->size() << "\tadres w pamieci: "
            << this << "\n\tadres funkcji wypisujacej dane: " << (void*)data_show << endl;
        if (dynamic_array->size() == 0) {
            cout << "Kopiec pusty" << endl;
            return;
        }
        cout << "Pierwsze " << count << " elementy / elementow:" << endl;
        for (size_t i = 0; i < count; ++i) {
            cout << i + 1 << ". ";
            data_show((*dynamic_array)[i]->value);
        }
        cout << "Ostatnie " << count << " elementy / elementow:" << endl;
        if (count > dynamic_array->size()) {
            for (int i = dynamic_array->size() - 1; i >= 0; --i) {
                cout << i + 1 << ". ";
                data_show((*dynamic_array)[i]->value);
            }
        }
        else {
            for (int i = dynamic_array->size() - count; i < dynamic_array->size(); ++i) {
                cout << i + 1 << ". ";
                data_show((*dynamic_array)[i]->value);
                }
        }
        
    }

    ~Binary_heap() {
        clear();
        delete dynamic_array;
    }
};

struct some_object
{
    int field1;
    char field2;

    some_object() : field1(0), field2(' ') {}
    some_object(int f1, char f2) : field1(f1), field2(f2) {}
};

static int some_objects_cmp(some_object so1, some_object so2)
{
    int result = so1.field1 - so2.field1;
    if (result != 0) return result;
    return so1.field2 - so2.field2;
}
static int some_objects_cmp(some_object* so1, some_object* so2)
{
    int result = (so1)->field1 - (so2)->field1;
    if (result != 0) return result;
    return (so1)->field2 - (so2)->field2;
}


static void show_some_object(some_object so1) {
    if (&so1) {
        string result = "Pole 1: ";
        cout << "Pole 1: " << so1.field1 << "\tPole 2: " << so1.field2 << endl;
    }
    else cout << "obiekt pusty" << endl;
}

static void show_some_object(some_object* so1) {
    if (so1) {
        string result = "Pole 1: ";
        cout << "Pole 1: " << so1->field1 << "\tPole 2: " << so1->field2 << endl;
    }
    else cout << "obiekt pusty" << endl;
}


some_object generate_random_object() {
    int int_val = rand() % 10001; // Losowanie liczby ca≥kowitej z zakresu 0-10000
    char char_val = 'a' + rand() % 26; // Losowanie znaku z zakresu 'a'-'z'
    return some_object(int_val, char_val);
}

static some_object* generate_ptr_random_object() {
    int int_val = rand() % 10001; // Losowanie liczby ca≥kowitej z zakresu 0-10000
    char char_val = 'a' + rand() % 26; // Losowanie znaku z zakresu 'a'-'z'
    return new some_object(int_val, char_val);
}

int main() {

    srand(static_cast<unsigned int>(time(0)));
    const int MAX_ORDER = 7; // maksymalny rzπd wielkoúci dodawanych danych
    Binary_heap<some_object*>* bh = new Binary_heap<some_object*>();

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o); // rozmiar danych
        cout << "\n\n------------------ POMIAR NR " << o << " ------------------" << endl;
        // dodawanie do kopca
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object* so = generate_ptr_random_object(); // losowe dane
            bh->add(so, some_objects_cmp, true);
        }
        clock_t t2 = clock();
        bh->to_string(show_some_object);
        double add_time = double(t2 - t1) / CLOCKS_PER_SEC;
        cout << "\nDodawanie " << n << " elementow zajelo: " << add_time << " sekund" << endl;

        // pobieranie (i usuwanie) elementu maksymalnego z kopca
        t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object* polled = bh->remove_max(some_objects_cmp); 
            // if (n < 100) show_some_object(polled);
            delete polled;
        }
        t2 = clock();
        bh->to_string(show_some_object);
        double remove_time = double(t2 - t1) / CLOCKS_PER_SEC;
        cout << "\nUsuwanie " << n << " elementow zajelo: " << remove_time << " sekund" << endl;

        bh->clear(); // czyszczenie kopca (tak naprawdÍ "zresetowanie" tablicy dynamicznej opakowanej przez kopiec)
    }

    delete bh;
    return 0;

}