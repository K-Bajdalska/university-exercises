import string
import random

# ZADANIE 1
# Napisz funkcję, która generuje losową listę o zadanej liczbie elementów (parametr konieczny).
# Opcjonalne parametry funkcji: typ elementów (np. int, float, str, mieszany), zestaw znaków,
# z których generowane są elementy typu str i ich maksymalna długość, zakres wartości jakie przyjmują
# elementy typu: int, float.

def generuj_losowa_liste (l_elementow, typ_elementu = 'int', zestaw_znakow = string.ascii_letters,
                          max_dl_str = 50, int_range = (0, 500), float_range = (0.0, 500.00)):
    lista = list()
    for a in range (l_elementow):
        if typ_elementu == 'int':
            n = random.randint(int_range[0], int_range[-1])
            lista.append(n)
        elif typ_elementu == 'float':
            n = random.uniform(float_range[0], float_range[-1])
            lista.append(n)
        elif typ_elementu == 'str':
            x = random.randint(2, max_dl_str)
            n = ''.join(random.sample(zestaw_znakow, x))
            lista.append(n)
        elif typ_elementu == 'mieszany':
            choice = random.choice(['int', 'float', 'str'])
            if choice == 'int':
                n = random.randint(int_range[0], int_range[-1])
                lista.append(n)
            elif choice == 'float':
                n = random.uniform(float_range[0], float_range[-1])
                lista.append(n)
            elif choice == 'str':
                x = random.randint(2, max_dl_str)
                n = ''.join(random.sample(zestaw_znakow, x))
                lista.append(n)

    return lista


# ZADANIE 2 Napisz funkcję, która generuje losową krotkę o zadanej liczbie elementów (parametr konieczny).
# Opcjonalne parametry funkcji: typ elementów (np. int, float, str, mieszany), zestaw znaków,
# z których generowane są elementy typu str i ich maksymalna długość, zakres wartości jakie przyjmują
# elementy typu: int, float.

def generuj_losowa_krotke (l_elementow, typ_elementu = 'int', zestaw_znakow = string.ascii_letters,
                          max_dl_str = 50, int_range = (0, 500), float_range = (0.0, 500.00)):
    krotka = tuple(generuj_losowa_liste(l_elementow, typ_elementu, zestaw_znakow,max_dl_str, int_range,
                                        float_range))
    return krotka


# ZADANIE 3  Napisz funkcję, która generuje losowy zbiór o zadanej liczbie elementów (parametr konieczny).
# Opcjonalne parametry funkcji: typ elementów (np. int, float, str, mieszany), zestaw znaków, z których
# generowane są elementy typu str i ich maksymalna długość, zakres wartości jakie przyjmują elementy typu:
# int, float.

def generuj_losowy_zbior (l_elementow, typ_elementu = 'int', zestaw_znakow = string.ascii_letters,
                          max_dl_str = 50, int_range = (0, 500), float_range = (0.0, 500.00)):
    zbior = set(generuj_losowa_liste(l_elementow, typ_elementu, zestaw_znakow,max_dl_str, int_range,
                                        float_range))
    return zbior

# ZADANIE 4 Napisz funkcję, która generuje losowy słownik o zadanej liczbie elementów (parametr
# konieczny). Opcjonalne parametry funkcji: typ klucza, np: litery lub wartości int, typ wartości
# elementów słownika (np. int, float, str, mieszany), zestaw znaków, z których generowane
# są wartości elementów typu str i ich maksymalna długość, zakres jaki przyjmują wartości elementów
# typu: int, float.

def generuj_losowy_slownik (l_elementow, typ_klucza = 'int', typ_wartosci = 'str',
                            zestaw_znakow = string.ascii_letters, max_dl_str = 50,
                            int_range = (0, 500), float_range = (0.0, 500.00)):
    slownik = {}
    lista_klucze = generuj_losowa_liste(l_elementow, typ_klucza, zestaw_znakow, max_dl_str, int_range, float_range)
    lista_wartosci = generuj_losowa_liste(l_elementow, typ_wartosci, zestaw_znakow, max_dl_str, int_range, float_range)

    for i in range(l_elementow):
        nowy_klucz = lista_klucze[i]
        while nowy_klucz in slownik.keys():
            if typ_klucza == 'int' or typ_klucza == 'float' or typ_klucza == 'mieszany':
                nowy_klucz = str(nowy_klucz) + '1'
            else:
                nowy_klucz = str(nowy_klucz) + 'aaa'
            slownik[nowy_klucz] = lista_wartosci[i]

        slownik[lista_klucze[i]] = lista_wartosci[i]

    return slownik

# ZADANIE 5 Napisz funkcję, która generuje losowy ciąg tekstowy o zadanej liczbie znaków (parametr
# konieczny). Opcjonalne parametry funkcji: minimalna i maksymalna długość słowa, zestaw znaków,
# z których generowane są słowa, minimalna i maksymalna długość linii.

def generuj_losowy_tekst (l_znakow, min_dl_sl = 1, max_dl_sl = 25,
                            zestaw_znakow = string.ascii_letters, min_dl_linii = 5,
                            max_dl_linii = 100):
    if l_znakow <= 0:
        return ""
    wynik = ""
    aktualna_dl = 0
    aktualna_dl_linii = 0
    limit_linii = random.randint(min_dl_linii, max_dl_linii)

    while aktualna_dl < l_znakow:
        dlugosc_slowa = random.randint(min_dl_linii, max_dl_linii)
        slowo = ''.join(random.choices(zestaw_znakow, k = dlugosc_slowa))

        # Sprawdzamy czy słowo mieści się w linii
        if aktualna_dl_linii + dlugosc_slowa + 1 > limit_linii:
            wynik = wynik.rstrip() + "\n"
            aktualna_dl_linii = 0
            limit_linii = random.randint(min_dl_linii, max_dl_linii)

        wynik += slowo + " "
        aktualna_dl += dlugosc_slowa + 1
        aktualna_dl_linii += dlugosc_slowa + 1

    # Sprawdzamy czy jest za duzo znaków i usuwamy w razie potrzeby
    if aktualna_dl > l_znakow:
        wynik = wynik[0:l_znakow]

    return wynik.strip()



if __name__ == '__main__':
    print(generuj_losowa_liste(10))
    print(generuj_losowa_liste(15, typ_elementu='float'))
    print(generuj_losowa_liste(10, typ_elementu='str'))
    print(generuj_losowa_liste(10, typ_elementu='mieszany'))
    print(generuj_losowa_krotke(20, typ_elementu='str'))
    print(generuj_losowy_zbior(20, typ_elementu='int'))
    print(generuj_losowy_zbior(20, typ_elementu='mieszany'))
    print(generuj_losowy_slownik(10))
    print(generuj_losowy_tekst(500))

