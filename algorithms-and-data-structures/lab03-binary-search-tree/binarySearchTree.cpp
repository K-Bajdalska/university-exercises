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
    Node* left;
    Node* right;
    Node* parent;
    int index;
    static int current_index;

    Node() : left(nullptr), right(nullptr), parent(nullptr), index(current_index++) {}
    Node(T value, bool manage_data = false) : value(value), left(nullptr), right(nullptr), parent(nullptr), index(index) {}
    ~Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

template <typename T>
int Node<T>::current_index = 0;

// Specjalizacja klasy Node dla wskaŸników
template <typename T>
class Node<T*> {
public:
    T* value;
    Node* left;
    Node* right;
    Node* parent;
    int index;
    bool manage_memory;
    static int current_index;

    Node() : value(nullptr), left(nullptr), right(nullptr), parent(nullptr), index(current_index++), manage_memory(false) {}
    Node(T* value, bool manage_memory = false) {
        this->value = new T(*value);
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        this->index = current_index++;
        this->manage_memory = manage_memory;
    }
    ~Node() {
        if (manage_memory && value) {
            delete value;
        }
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    void set_manage_memory(bool manage_memory) {
        this->manage_memory = manage_memory;
    }
};

template <typename T>
int Node<T*>::current_index = 0;

// Pomocnicza funkcja do ustawiania zarz¹dzania pamiêci¹
template <typename T>
void set_manage_memory(Node<T>* node, bool manage_memory) {
    // Nic nie robi dla typów nie bêd¹cych wskaŸnikami
}

template <typename T>
void set_manage_memory(Node<T*>* node, bool manage_memory) {
    node->set_manage_memory(manage_memory);
}

template <typename T>
class BST_tree {
private:
    Node<T>* root;
    int size;

private:
    Node<T> * find_replacement(Node<T>* node) {
        Node<T>* current = node->right;
        Node<T>* temp = nullptr;
        while (current != nullptr) {
            temp = current;
            current = current->left;
        }
        return temp;
    }

    void preorder(Node<T>* start, Node<T>** result, int& index) {
        if (start) {
            result[index] = start; 
            index++;
            preorder(start->left, result, index);
            preorder(start->right, result, index);
        }
    }

    void inorder(Node<T>* start, Node<T>** result, int& index) {
        if (start) {
            inorder(start->left, result, index); 
            result[index++] = start;
            inorder(start->right, result, index);
        }
    }

    int height(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            int left_height = height(node->left);
            int right_height = height(node->right);
            return max(left_height, right_height) + 1;
        }
    }


public:
    BST_tree() : root(nullptr), size(0) {}
    ~BST_tree() {
        delete_tr();
        size = 0;
    }

    void add(T value, int (*data_cmp)(T, T), bool manage_data = false) {
        Node<T>* new_node = new Node<T>(value, manage_data);
        if (root == nullptr) {
            root = new_node;
        }
        else {
            int result = 0;
            Node<T>* current = root;
            Node<T>* local_parent = nullptr;
            while (current != nullptr) {
                result = data_cmp(new_node->value, current->value);
                local_parent = current;
                if (result < 0) {
                    current = local_parent->left;
                }
                else current = local_parent->right;
            }
             if (result < 0) local_parent->left = new_node;
             else local_parent->right = new_node;
             new_node->parent = local_parent;
        }
        size++;
    }

    Node<T>* search(T value, int (*data_search)(T, T)) {
        Node<T>* current = root;
        int result = 0;
        while (current != nullptr) {
            result = data_search(value, current->value);
            if (result == 0) return current;
            if (result < 0) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

    void delete_node(Node<T>* node) {
        if (node == nullptr) return;

        if (node->left == nullptr && node->right == nullptr) {
            if (node == root) {
                root = nullptr;
            }
            else if (node == (node->parent)->left) {
                (node->parent)->left = nullptr;
            }
            else if (node == (node->parent)->right) {
                (node->parent)->right = nullptr;
            }
            delete node;
        }
        else if ((node->left == nullptr) || (node->right == nullptr)) {
            Node<T>* child = (node->left != nullptr) ? node->left : node->right;
            if (node == root) {
                root = child;
            }
            else {
                if (node == node->parent->left) {
                    node->parent->left = child;
                }
                else {
                    node->parent->right = child;
                }
            }
            child->parent = node->parent;
            delete node;
        }

        else {
            Node<T>* replacement = find_replacement(node);
            if (replacement->parent != node) {
                if (replacement == replacement->parent->left) {
                    replacement->parent->left = replacement->right;
                }
                else {
                    replacement->parent->right = replacement->right;
                }
                if (replacement->right != nullptr) {
                    replacement->right->parent = replacement->parent;
                }
                replacement->right = node->right;
                node->right->parent = replacement;
            }



            replacement->left = node->left;
            node->left->parent = replacement;

            if (node == root) {
                root = replacement;
            }
            else {
                if (node == node->parent->left) {
                    node->parent->left = replacement;
                }
                else {
                    node->parent->right = replacement;
                }
            }
            replacement->parent = node->parent;
            delete node;
        }
        size--;
    }

    Node<T>** get_preorder() {
        Node<T>** result = new Node<T>*[size];
        int index = 0;
        preorder(root, result, index);
        return result;
    }

    Node<T>** get_inorder() {
        Node<T>** result = new Node<T>*[size];
        int index = 0;
        inorder(root, result, index);
        return result;
    }

    int get_height() {
        return height(root);
    }

    void to_string(string (*data_show)(T), int count = 15) {
        cout << "PODSUMOWANIE DRZEWA BTS" << endl;
        cout << "\trozmiar: " << size << "\twysokosc: " << get_height() << endl;
        cout << "{" << endl;
        Node<T>** preorder = get_preorder();

        for (int i = 0; i < count && i < size; i++) {
            if (preorder[i] != nullptr) {
      
                cout << "(" << preorder[i]->index << ": [p: ";
                if (preorder[i]->parent == nullptr) cout << "NULL";
                else cout << preorder[i]->parent->index;
                cout << ",   l: ";
                if (preorder[i]->left == nullptr) cout << "NULL";
                else cout << preorder[i]->left->index;
                if (preorder[i]->parent != nullptr && preorder[i]->left != nullptr) cout << ",      r: ";
                else cout << ",   r: ";
                if (preorder[i]->right == nullptr) cout << "NULL";
                else cout << preorder[i]->right->index;
                cout << "],   data: " << data_show(preorder[i]->value) << ")," << endl;
            }
            else {
                break;
            }
        }

        cout << "}" << endl;
        delete[] preorder;
    }

    void delete_tr(bool manage_data = false) {
        delete_tree(root, manage_data);
    }

    void delete_tree(Node<T>* node, bool manage_data = false)
    {
        if (node != nullptr) {
            delete_tree(node->left);
            delete_tree(node->right);
            set_manage_memory(node, manage_data);
            delete node;
        }
        size = 0;
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

static string show_some_object(some_object* so1) {
    if (so1) {
        return "( " + to_string(so1->field1) + ", " + so1->field2 + " )";
    }
    else {
        return("Obiekt pusty");
    }
}
static string show_some_object(some_object so1) {
    return (show_some_object(&so1));
}

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

   
    const int MAX_ORDER = 6; 

        for (int o = 1; o <= MAX_ORDER; o++)
        {
            BST_tree < some_object*>* bst = new BST_tree < some_object* >();
            const int n = pow(10, o); // rozmiar danych
            // Pomiar dla add
            cout << "--------DODAWANIE DO DRZEWA BST---------" << endl;
            clock_t t1 = clock();
            double max_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji dodawania
            for (int i = 0; i < n; i++)
            {
                some_object* so = generate_ptr_random_object(); // losowe dane 
                bst->add(so, some_objects_cmp); // dodanie ( drugi argument to wskaznik na komparator )
            }
            clock_t t2 = clock();
            double add_time = double(t2 - t1) / CLOCKS_PER_SEC;
            double time_for_adding_element = (add_time / n) * 1000; // czas zamortyzowany 
            cout << "POMIAR NR " << o << endl;
            cout << "Aktualna postac (skrotowa) drzewa: " << endl;
            bst->to_string(show_some_object);
            cout << "Czas dodawania " << n << " elementow: " << add_time << " sekund" << endl;
            cout << "Sredni czas dodawania jednego elementu: " << time_for_adding_element << " milisekund\n" << endl;
                
            // Pomiar dla wyszukiwania
            cout << "--------WYSZUKIWANIE W DRZEWIE BST---------" << endl;
            const int m = pow(10, 4); // liczba prob wyszukiwania
            int hits = 0; // liczba trafien
            t1 = clock();
            for (int i = 0; i < m; i++)
            {
                some_object* so = generate_ptr_random_object(); // losowe dane  
                Node<some_object*>* result = bst->search(so, some_objects_cmp);
                if (result != nullptr)
                    hits++;
                delete so;
            }
            t2 = clock();
            double search_time = double(t2 - t1) / CLOCKS_PER_SEC;
            double time_for_search_element = (search_time / m) * 1000;
            cout << "POMIAR NR " << o << endl;
            cout << "Aktualna postac (skrotowa) listy: " << endl;
            bst->to_string(show_some_object);
            cout << "Czas wyszukiwania " << m << " elementow: " << search_time << " sekund" << endl;
            cout << "Sredni czas wyszukiwania jednego elementu: " << time_for_search_element << " milisekund\n" << endl;
            // Czyszczenie listy
            bst->delete_tr(true);
        }
       // delete bst;
        return 0;
}