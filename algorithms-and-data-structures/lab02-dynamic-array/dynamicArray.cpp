#include <iostream>
#include <string>
#include <time.h>

using namespace std;

const int EXPANSION_FACTOR = 2;

// PODSTAWOWA WERSJA DLA OBIEKTÓW
template <typename T>
class Dynamic_array {
private:
	T* array;
	unsigned int actual_size = 0;
	unsigned int max_size = 1;

	void resize(int new_size) {
		T* new_array = new T[new_size];
		for (unsigned int i = 0; i < actual_size; i++) {
			new_array[i] = array[i];
		}
		delete[] array;
		array = new_array;
		max_size = new_size;
	}

public:
	Dynamic_array() : actual_size(0), max_size(1) { 
		array = new T[max_size]; }
	~Dynamic_array() { clear(); }

	void add(const T& element) {
		if (actual_size == max_size) { 
			resize(max_size * EXPANSION_FACTOR); } 
		array[actual_size] = element;
		actual_size++;
	}
	void add(const T* element) {
		this->add(*element);
	}
	T get(unsigned int index) const {
		if (index >= actual_size) {
			cerr << "Index out of range" << endl;
			throw out_of_range("Index out of range");
		}
		return array[index];
	}

	void set(unsigned int index, T& element) { 
		if (index >= actual_size) { 
			throw out_of_range("Index out of range"); 
		} 
		array[index] = element; 
	}
	void set(unsigned int index, T *element) {
		this->set(index, *element);
	}
	void clear() {
		delete[] array; 
		actual_size = 0; 
		max_size = 1; 
		array = new T[max_size];
	}

	void to_string(void (*data_show)(T), unsigned int count = 10) const {
		cout << "PODSUMOWANIE TABLICY" << endl;
		cout << "Rozmiar: " << actual_size << "\t max rozmiar: "<< max_size 
			<< "\tadres w pamieci: " << this << endl;
		cout << "Adres funkcji wypisujacej dane: " << data_show << endl;
		cout << "Pierwsze " << count << " elementy/ow: " << endl;
		if (actual_size == 0) {
			cout << "Tablica pusta" << endl;
		}
		else 
		{
			for (unsigned int i = 0; i < count and i < actual_size; i++) {
				if (i <= (actual_size-1)) {
					cout << i + 1 << ". ";
					data_show(array[i]);
				}
				else break;
			}
		}
		cout << "Ostatnie " << count << " elementy/ow: " << endl;
		if (actual_size == 0) {
			cout << "Tablica pusta" << endl;
		}
		else
		{
			if (count > actual_size) {
				for (int i = actual_size - 1; i >= 0; i--) {
					cout << i + 1 << ". ";
					data_show(array[i]);
				}
			}
			else {
				for (unsigned int i = actual_size - count; i < actual_size; i++) {
					cout << i + 1 << ". ";
					data_show(array[i]);
				}
			}
			
		}
	}

	void bubble_sort(int (*comparator)(T, T, int), int search_or_no = 0) {
		for (unsigned int i = 0; i < actual_size - 1; i++){
			for (unsigned int j = 0; j < actual_size - i - 1; j++){
				if (comparator(array[j + 1], array[j], search_or_no) < 0) {
					swap(array[j], array[j + 1]);
				}
			}
		}
	}
};

// SPECJALIZACJA DLA WSKANIKÓW NA OBIEKTY
template <typename T>
class Dynamic_array<T*> {
private:
	T** array;
	unsigned int actual_size = 0;
	unsigned int max_size = 1;

	void resize(int new_size) {
		T** new_array = new T * [new_size];
		for (unsigned int i = 0; i < actual_size; i++) {
			new_array[i] = array[i];
		}
		delete[] array;
		array = new_array;
		max_size = new_size;
	}

public:
	Dynamic_array() : actual_size(0), max_size(1) {
		array = new T * [max_size];
	}
	~Dynamic_array() {
		clear();
	}

	void add(T* element) {
		if (actual_size == max_size) {
			resize(max_size * EXPANSION_FACTOR);
		}
		array[actual_size] = element;
		actual_size++;
	}

	void add(T element) {
		this->add(&element);
	}

	T* get(unsigned int index) const {
		if (index >= actual_size) {
			cerr << "Index out of range" << endl;
			throw out_of_range("Index out of range");
		}
		return array[index];
	}

	void set(unsigned int index, T* element) {
		if (index >= actual_size) {
			cerr << "Index out of range" << endl;
			throw out_of_range("Index out of range");
			}
			array[index] = element;
	}

	void set(unsigned int index, T element) {
		this->set(&element);
	}

	void clear() {
		for (unsigned int i = 0; i < actual_size; i++) {
			delete array[i];
		}
		delete[] array;
		actual_size = 0;
		max_size = 1;
		array = new T * [max_size];
	}

	void to_string(void (*data_show)(T*), unsigned int count = 10) const {
		cout << "PODSUMOWANIE TABLICY" << endl;
		cout << "Rozmiar: " << actual_size << "\t max rozmiar: " << max_size
			<< "\tadres w pamieci: " << this << endl;
		cout << "Adres funkcji wypisujacej dane: " << data_show << endl;
		cout << "Pierwsze " << count << " elementy/ow: " << endl;
		if (actual_size == 0) {
			cout << "Tablica pusta" << endl;
		}
		else
		{
			for (unsigned int i = 0; i < count and i < actual_size; i++) {
				if (i <= (actual_size - 1)) {
					cout << i + 1 << ". ";
					data_show(array[i]);
				}
				else break;
			}
		}
		cout << "Ostatnie " << count << " elementy/ow: " << endl;
		if (actual_size == 0) {
			cout << "Tablica pusta" << endl;
		}
		else
		{
			if (count > actual_size) {
				for (int i = actual_size - 1; i >= 0; i--) {
					cout << i + 1 << ". ";
					data_show(array[i]);
				}
			}
			else {
				for (unsigned int i = actual_size - count; i < actual_size; i++) {
					cout << i + 1 << ". ";
					data_show(array[i]);
				}
			}

		}
	}

	void bubble_sort(int (*comparator)(T*, T*, int), int search_or_no = 0) {
		for (unsigned int i = 0; i < actual_size - 1; i++) {
			for (unsigned int j = 0; j < actual_size - i - 1; j++) {
				if (comparator(array[j + 1], array[j], search_or_no) < 0) {
					swap(array[j],
						array[j + 1]);
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

static int some_objects_cmp(some_object so1, some_object so2, int search_or_no = 0)
{
	int result = so1.field1 - so2.field1;
	if (search_or_no == 1) {
		if (result == 0) return result;
	}
	if (search_or_no == 0) {
		if (result != 0)
			return result;
	}
	return so1.field2 - so2.field2;
}
static int some_objects_cmp(some_object* so1, some_object* so2, int search_or_no)
{
	int result = (so1)->field1 - (so2)->field1;
	if (search_or_no == 1) {
		if (result == 0) return result;
	}
	if (search_or_no == 0) {
		if (result != 0)
			return result;
	}
	return (so1)->field2 - (so2)->field2;
}
static some_object generate_random_object() {
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
	Dynamic_array < some_object*>* array = new Dynamic_array < some_object* >(); // stworzenie tablicy
	const int order = 7; // rzad wielkosci rozmiaru dodawanych danych
	const int n = pow(10, order); // rozmiar danych

	// Pomiar dla add
	cout << "--------DODAWANIE DO TABLICY---------" << endl;
	clock_t t1 = clock();
	double max_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji dodawania
	for (int i = 0; i < n; i++) {
		some_object* so = generate_ptr_random_object(); // losowe dane 
		clock_t t1_element = clock();
		array->add(so);
		clock_t t2_element = clock();
		double add_time = double(t2_element - t1_element) / CLOCKS_PER_SEC;
		double time_per_element = add_time * 1000; // obliczenie czasu pojedynczej operacji dodawania w milisekundach 
		if (time_per_element > max_time_per_element) {
			max_time_per_element = time_per_element;
			cout << "Nowy najgorszy czas: " << time_per_element << " ms przy indeksie " << i << endl;
		}
	}
	clock_t t2 = clock();
	double total_time = double(t2 - t1) / CLOCKS_PER_SEC;
	double amortized_time_per_element = (total_time / n) * 1000; // czas zamortyzowany 
	cout << "Calkowity czas add: " << total_time << " s" << endl;
	cout << "Czas zamortyzowany na element: " << amortized_time_per_element << " ms" << endl;

	// Pomiar dla get
	cout << "--------POBIERANIE Z TABLICY---------" << endl;
	clock_t t3 = clock();
	double max_get_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji get 
	for (int i = 0; i < n; i++) {
		clock_t t1_element = clock();
		some_object* so = array->get(i);
		clock_t t2_element = clock();
		double get_time = double(t2_element - t1_element) / CLOCKS_PER_SEC;
		double time_per_element = get_time * 1000; // obliczenie czasu pojedynczej operacji get w milisekundach 
		if (time_per_element > max_get_time_per_element) {
			max_get_time_per_element = time_per_element;
			cout << "Nowy najgorszy czas get: " << time_per_element << " ms przy indeksie " << i << endl;
		}
	}
	clock_t t4 = clock();
	double total_get_time = double(t4 - t3) / CLOCKS_PER_SEC;
	double amortized_get_time_per_element = (total_get_time / n) * 1000; // czas zamortyzowany 
	cout << "Calkowity czas get: " << total_get_time << " s" << endl;
	cout << "Czas zamortyzowany na element (get): " << amortized_get_time_per_element << endl;

	// Pomiar dla set
	cout << "--------USTAWIANIE ELEMENTÓW---------" << endl;
	clock_t t5 = clock();
	double max_set_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji set 
	for (int i = 0; i < n; i++) {
		some_object* so = generate_ptr_random_object(); // losowe dane 
		clock_t t1_element = clock();
		array->set(i, so);
		clock_t t2_element = clock();
		double set_time = double(t2_element - t1_element) / CLOCKS_PER_SEC;
		double time_per_element = set_time * 1000; // obliczenie czasu pojedynczej operacji set w milisekundach 
		if (time_per_element > max_set_time_per_element) {
			max_set_time_per_element = time_per_element;
			cout << "Nowy najgorszy czas set: " << time_per_element << " ms przy indeksie " << i << endl;
		}
	}
	clock_t t6 = clock();
	double total_set_time = double(t6 - t5) / CLOCKS_PER_SEC;
	double amortized_set_time_per_element = (total_set_time / n) * 1000; // czas zamortyzowany 
	cout << "Calkowity czas set: " << total_set_time << " s" << endl;
	cout << "Czas zamortyzowany na element (set): " << amortized_set_time_per_element << " ms\n" << endl;
	

	array->to_string(show_some_object, 10); // Wypisanie aktualnej postaci tablicy (skrócona wersja) 
	array->clear(); // czyszczenie tablicy wraz z uwalnianiem pamiêci danych delete array; return 0
	return 0;
}
