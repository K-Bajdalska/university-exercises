#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>


using namespace std;

// Ogólny szablon klasy Node
template <typename T>
class Node {
public:
    T value;
    Node* prev;
    Node* next;
    Node() : prev(nullptr), next(nullptr) {}
    Node(T value, bool manage_data = false) : value(value), prev(nullptr), next(nullptr) {}
    ~Node() {
        prev = nullptr;
        next = nullptr;
    }
};

// Specjalizacja klasy Node dla wskaŸników
template <typename T>
class Node<T*> {
public:
    T* value;
    Node* prev;
    Node* next;
    bool manage_memory;
    Node() : value(nullptr), prev(nullptr), next(nullptr), manage_memory(false) {}
    Node(T* value, bool manage_memory = false) {
        this->value = new T(*value);
        *value = *value;
        prev = nullptr;
        next = nullptr;
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

// Pomocnicza funkcja do ustawiania zarz¹dzania pamiêci¹
template <typename T>
void set_manage_memory(Node<T>* node, bool manage_memory) {
    // Nic nie robi dla typów nie bêd¹cych wskaŸnikami
}

template <typename T>
void set_manage_memory(Node<T*>* node, bool manage_memory) {
    node->set_manage_memory(manage_memory);
}

// Pomocnicza funkcja do pobierania wartoœci z wêz³a
template <typename T>
T get_node_value(Node<T>* node) {
    return node->value;
}

template <typename T>
T* get_node_value(Node<T*>* node) {
    return node->value;
}



template <typename T>
class Linked_list {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Linked_list() : head(nullptr), tail(nullptr), size(0) {}
    ~Linked_list() {
        clear();
    }

    void add_to_end(T value, bool manage_data = false) {
        Node<T>* new_node = new Node<T>(value, manage_data);
        if (!head) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size++;
    }

    void add_to_begin(T value, bool manage_data = false) {
        Node<T>* new_node = new Node<T>(value, manage_data);
        if (!head) {
            head = tail = new_node;
        }
        else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        size++;
    }

    void delete_last(bool manage_data = false) {
        if (tail) {
            Node <T>* temp = tail;
            if (head == tail) {
                head = tail = nullptr;
            }
            else {
                tail = tail->prev;
                tail->next = nullptr;
            }
            set_manage_memory(temp, manage_data);
            delete temp;
            size--;
        }
        else {
            cout << "Tablica jest juz pusta" << endl;
            system("pause");
        }
    }

    void delete_first(bool manage_data = false) {
        if (head) {
            Node <T>* temp = head;
            if (head == tail) {
                head = tail = nullptr;
            }
            else {
                head = head->next;
                head->prev = nullptr;
            }
            set_manage_memory(temp, manage_data);
            delete temp;
            size--;
        }
        else {
            cout << "Tablica jest juz pusta" << endl;
            system("pause");
        }
    }

    Node<T>* get_node(int index) const {
        try {
            Node<T>* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            return current;
        }
        catch (const out_of_range& e) {
            cerr << e.what() << endl;
            return nullptr;
        }

    }


    T get_element(int index) const {
        try {
            Node<T>* element = get_node(index);
            return get_node_value(element);
        }
        catch (const out_of_range& e) {
            cerr << e.what() << endl;
        }
    }

    void set_node_value(Node<T>* node, T value, bool manage_memory = false) {
        node->value = value;
    }

    void set_node_value(Node<T*>* node, T* value, bool manage_memory = false) {
        if (manage_memory && node->value) {
            delete node->value;
        }
        node->value = value;
        node->manage_memory = manage_memory;
    }

    void set_element(int index, T value, bool manage_data = false) {
        try {
            if (index < 1 or index >= size) {
                throw out_of_range("Index out of range");
            }
            else {
                Node<T>* element = get_node(index);
                set_node_value(element, value, manage_data);
            }
        }
        catch (out_of_range& e) {
            cerr << e.what() << endl;
        }

    }

    T* search(T value, int (*data_cmp)(T*, T*, int)) {
        Node<T>* element = head;
        while (element) {
            if (data_cmp(&element->value, &value, 1) == 0) {
                return &element->value;
            }
            element = element->next;
        }
        return NULL;
    }

    bool search_and_delete(T value, int (*data_cmp)(T*, T*, int), bool manage_data = false)
    {
        Node<T>* element = head;
        while (element) {
            int result = data_cmp(&element->value, &value, 1);
            if (result == 0) {
                set_manage_memory(element, manage_data);
                if (element == head) this->delete_first();
                else if (element == tail) this->delete_last();
                else {
                    (element->prev)->next = element->next;
                    (element->next)->prev = element->prev;
                    delete element;
                    size--;
                    element = nullptr;
                }
                return true;
            }
            element = element->next;
        }
        return false;

    }

    void add_with_sort(T value, int (*data_cmp)(T*, T*, int), bool manage_data = false) {
        Node<T>* new_node = new Node<T>(value, manage_data);
        if (!head) {
            head = tail = new_node;
        }
        else {
            Node<T>* element = head;
            int result = data_cmp(&element->value, &value, 0);
            int index = 0;
            int i = 0;
            while (element) {
                int current_result = data_cmp(&element->value, &value, 0);
                if ((abs(current_result)) <= result) {
                    result = current_result;
                    index = i;
                }
                i++;
                element = element->next;
            }
            element = get_node(index);
            if (result <= 0) {
                if (index == 0) add_to_begin(value);
                else {
                    new_node->prev = element->prev;
                    new_node->next = element;
                    (element->prev)->next = new_node;
                    element->prev = new_node;
                }
            }
            else {
                if (index == size - 1) add_to_end(value);
                else {
                    new_node->prev = element;
                    new_node->next = element->next;
                    (element->next)->prev = new_node;
                    element->next = new_node;
                }
            }
        }
        size++;
    }

    void clear(bool manage_data = false) {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            set_manage_memory(current, manage_data);
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    void show_all_elements(void (*data_show)(T*)) {
        cout << "LISTA:" << endl;
        int i = 0;
        if (!head) {
            cout << "Lista pusta" << endl;
        }
        else {
            Node<T>* element = head;
            while (element) {
                cout << i + 1 << ". ";
                data_show(&(element->value));
                element = element->next;
                i++;
            }
        }
        cout << endl;
    }

    void show_all_elements_opposite(void (*data_show)(T*)) {
        cout << "LISTA:" << endl;
        int i = 0;
        if (!head) {
            cout << "Lista pusta" << endl;
        }
        else {
            Node<T>* element = tail;
            while (element) {
                cout << i + 1 << ". ";
                data_show(&(element->value));
                element = element->prev;
                i++;
            }
        }
        cout << endl;
    }

    void to_string(void (*data_show)(T*)) {
        cout << "PODSUMOWANIE LISTY" << endl;
        cout << "Rozmiar: " << size << "\tadres w pamieci: " << this << endl;
        cout << "Adres funkcji wypisujacej dane: " << data_show << endl;
        cout << "Pierwsze 3 elementy: " << endl;
        if (!head) {
            cout << "Lista pusta" << endl;
        }
        else {
            int i = 0;
            Node<T>* element = head;
            for (i = 0; i < 3; i++) {
                if (element) {
                    cout << i + 1 << ". ";
                    data_show(&(element->value));
                    element = element->next;
                }
            }
        }
        cout << "Ostatnie 3 elementy: " << endl;
        if (!head) {
            cout << "Lista pusta" << endl;
        }
        else {
            int i = 0;
            Node<T>* element = tail;
            for (i = 0; i < 3; i++) {
                if (element) {
                    cout << i + 1 << ". ";
                    data_show(&(element->value));
                    element = element->prev;
                }
            }
        }
    }

    void to_string(void (*data_show)(T*), int count) {
        cout << "PODSUMOWANIE LISTY" << endl;
        cout << "Rozmiar: " << size << "\tadres w pamieci: " << this << endl;
        cout << "Adres funkcji wypisujacej dane: " << data_show << endl;
        cout << "Pierwsze " << count << " elementy/ow: " << endl;
        if (!head) {
            cout << "Lista pusta" << endl;
        }
        else {
            int i = 0;
            Node<T>* element = head;
            for (i = 0; i < count; i++) {
                if (element) {
                    cout << i + 1 << ". ";
                    data_show(&(element->value));
                    element = element->next;
                }
            }
        }
        cout << "Ostatnie " << count << " elementy/ow: " << endl;
        if (!head) {
            cout << "Lista pusta" << endl;
        }
        else {
            int i = 0;
            Node<T>* element = tail;
            for (i = 0; i < count; i++) {
                if (element) {
                    cout << i + 1 << ". ";
                    data_show(&(element->value));
                    element = element->prev;
                }
            }
        }
    }
};

struct some_object
{
    int field1;
    char field2;

    some_object() : field1(0), field2(' ') {}
    some_object(int f1, char f2) : field1(f1), field2(f2) {}
};

static int some_objects_cmp(some_object* so1, some_object* so2, int search_or_no)
{
    int result = so1->field1 - so2->field1;
    if (search_or_no == 1) {
        if (result == 0) return result;
    }
    if (search_or_no == 0) {
        if (result != 0)
            return result;
    }
    return so1->field2 - so2->field2;
}
static int some_objects_cmp(some_object** so1, some_object** so2, int search_or_no)
{
    int result = (*so1)->field1 - (*so2)->field1;
    if (search_or_no == 1) {
        if (result == 0) return result;
    }
    if (search_or_no == 0) {
        if (result != 0)
            return result;
    }
    return (*so1)->field2 - (*so2)->field2;
}

static void show_some_object(some_object* so1) {
    if (so1) {
        string result = "Pole 1: ";
        cout << "Pole 1: " << so1->field1 << "\tPole 2: " << so1->field2 << endl;
    }
    else cout << "obiekt pusty" << endl;
}
static void show_some_object(some_object** so1) {
    if (so1) {
        string result = "Pole 1: ";
        cout << "Pole 1: " << (*so1)->field1 << "\tPole 2: " << (*so1)->field2 << endl;
    }

    else cout << "obiekt pusty" << endl;
}

// Funkcje do generowania losowych obiektów some_object
some_object generate_random_object() {
    int int_val = rand() % 10001; // Losowanie liczby ca³kowitej z zakresu 0-10000
    char char_val = 'a' + rand() % 26; // Losowanie znaku z zakresu 'a'-'z'
    return some_object(int_val, char_val);
}

static some_object* generate_ptr_random_object() {
    int int_val = rand() % 10001; // Losowanie liczby ca³kowitej z zakresu 0-10000
    char char_val = 'a' + rand() % 26; // Losowanie znaku z zakresu 'a'-'z'
    return new some_object(int_val, char_val);
}

int main() {
    srand(time(NULL)); // Inicjalizacja generatora liczb losowych
    const int MAX_ORDER = 6; // maksymalny rz¹d wielkoœci rozmiaru dodawanych danych
    Linked_list<some_object*>* ll = new Linked_list<some_object*>(); // stworzenie listy
    for (int o = 1; o <= MAX_ORDER; o++) // petla po kolejnych rzedach wielkosci
    {
        const int n = pow(10, o); // rozmiar danych
        // Dodawanie do listy
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object* so = generate_ptr_random_object(); // losowe dane
            ll->add_to_end(so, true);
        }

        clock_t t2 = clock();
        double add_time = double(t2 - t1) / CLOCKS_PER_SEC;
        double time_for_adding_element = (add_time / n) * 1000;
        cout << "POMIAR NR " << o << endl;
        cout << "Aktualna postac (skrotowa) listy: " << endl;
        ll->to_string(show_some_object);
        cout << "Czas dodawania " << n << " elementow: " << add_time << " sekund" << endl;
        cout << "Sredni czas dodawania jednego elementu: " << time_for_adding_element << " milisekund\n" << endl;

        // wyszukiwanie i usuwanie z listy
        const int m = pow(10, 4); // liczba prob wyszukania
        t1 = clock();
        for (int i = 0; i < m; i++) {
            some_object* so = generate_ptr_random_object();
            ll->search_and_delete(so, some_objects_cmp, true);
            delete so;
        }
        t2 = clock();
        double search_delete_time = double(t2 - t1) / CLOCKS_PER_SEC;
        double time_for_search_delete_element = (search_delete_time / m) * 1000;

        cout << "POMIAR NR " << o << endl;
        cout << "Aktualna postac (skrotowa) listy: " << endl;
        ll->to_string(show_some_object);
        cout << "Czas wyszukiwania i usuwania " << m << " elementow: " << search_delete_time << " sekund" << endl;
        cout << "Sredni czas dodawania jednego elementu: " << time_for_search_delete_element << " milisekund\n" << endl;
        // Czyszczenie listy
        ll->clear(true);
    }
    delete ll;
    return 0;
}