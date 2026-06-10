# ZADANIE 1

print("ZADANIE 1")
def display_info(obj):
    if isinstance(obj, list):
        print(f"\n\nLiczba elementów w liście: {len(obj)}")
        i = 0
        for element in obj:
            print(f"Element {i}: {element} jest typu '{type(element).__name__}'")
            i += 1
    elif isinstance(obj, tuple):
        print(f"\n\nLiczba elementów w krotce: {len(obj)}")
        i = 0
        for element in obj:
            print(f"Element {i}: {element} jest typu '{type(element).__name__}'")
            i += 1
    elif isinstance(obj, set):
        print(f"\n\nLiczba elementów w zbiorze: {len(obj)}")
        i = 0
        for element in obj:
            print(f"Element {i}: {element} jest typu '{type(element).__name__}'")
            i += 1
    elif isinstance(obj, dict):
        print(f"\n\nLiczba elementów w słowniku: {len(obj)}")
        for klucz, wartosc in obj.items():
            print(f"Element o kluczu {klucz}: {wartosc} jest typu '{type(wartosc).__name__}'")
    else:
        print('Przekazany obiekt nie jest ani listą, krotką, zbiorem ani słownikiem.')

Lista = ['abc','x',1,1.5,(1,2)]
display_info(Lista)

Krotka = ('xyz', 34, 33.33, (2,1), [5, 'a'])
display_info(Krotka)

Slownik = {'a':'abc','b':'x','c':1,'d':1.5,'e':(1,2)}
display_info(Slownik)

Zbior = {1, 67.5, 'abc'}
display_info(Zbior)

Inny = 20
display_info(Inny)
############################################################################################################
# ZADANIE 2
print("\n\nZADANIE 2")
S = {
'Szczecin':{1990:400, 2000:390, 2010:385, 2020:380},
'Poznań':{1990:550, 2000:560, 2010:565, 2020:570},
'Wrocław':{1990:700, 2000:690, 2010:705, 2020:710},
}
def pokaz_jako_tabele(slownik):
    print("Rok\t", end="")
    for klucz, wartosc in S.items():
        print(f"| {klucz}\t ", end="")
    print("\n--------------------------------------")
    lata = S['Szczecin'].keys()
    for rok in lata:
        row = f"{rok} |\t {slownik['Szczecin'][rok]}\t |\t {slownik['Poznań'][rok]}\t |\t {slownik['Wrocław'][rok]}"
        print(row)
pokaz_jako_tabele(S)

############################################################################################################
# ZADANIE 3
print("\n\nZADANIE 3")
def liczby_na_slowa(liczba):
    cyfry_slowa = {'0': 'zero', '1': 'jeden', '2': 'dwa', '3': 'trzy', '4': 'cztery', '5': 'pięć', '6': 'sześć',
                   '7': 'siedem', '8': 'osiem', '9': 'dziewięć'}
    liczba_str = str(liczba)
    reprezentacja_slowna = ' '.join(cyfry_slowa[cyfra] for cyfra in liczba_str)
    return reprezentacja_slowna
a = 56
print(a)
a = liczby_na_slowa(a)
print(a)
b = 999
print(b)
b = liczby_na_slowa(b)
print(b)

############################################################################################################
# ZADANIE 4
from collections import Counter
import string

print("\n\nZADANIE 4")
tekst = """One of the most popular programming languages used nowadays is called Python. It
has just become more potent with the addition of a few additional features in its most
recent iteration. Yet, not everyone is aware of its potency. The goal of this book is to
introduce readers to Python programming from scratch. You are welcome to learn Python
Programming like never before, whether you are a computer science undergraduate or not,
a school-going programming geek or a beginner. You’ll discover everything there is to know
about Python, including how to use it for programming, when to employ the much-touted
walrus operator and other brand-new features of version 3.11. Many solved programs that
were used as interview questions at various firms are included in the book. Understanding
the typical mistakes and how to fix them are covered in a separate chapter. The difficult
topics have been simplified and expressed in simple terms. Beginners and intermediate
readers should read the book."""

# DŁUGOŚĆ TEKSTU
print(f"Dlugość tekstu to: {len(tekst)} znaków.")

# UNIKALNE LITERY
tekst = tekst.lower()
sformatowany_tekst = ""
for litera in tekst:
    if litera not in string.punctuation and litera not in string.whitespace and litera not in string.digits:
        sformatowany_tekst += litera
unikalne_litery = Counter(sformatowany_tekst)
ilosc_unik_liter = len(unikalne_litery)

print(f"Liczba unikalnych znaków: {ilosc_unik_liter}")
print(unikalne_litery.most_common())

# WYRAZY
wyrazy = tekst.strip(string.punctuation)
wyrazy = wyrazy.split()
ilosc_wyrazow = len(wyrazy)
print(f"\nIlosc wszystkich wyrazow: {ilosc_wyrazow}")
unikalne_wyrazy = Counter(wyrazy)
ilosc_unik_wyrazow = len(unikalne_wyrazy)
print(f"Ilosc unikalnych wyrazow: {ilosc_unik_wyrazow}")
print(unikalne_wyrazy.most_common())

############################################################################################################
# ZADANIE 5
print("\n\nZADANIE 5")

def levenshtein_distance(slowo1, slowo2):
# Inicjalizacja macierzy o rozmiarze (len(s1)+1) x (len(s2)+1)
    m = len(slowo1)
    n = len(slowo2)
    macierz = [[0] * (n + 1) for _ in range(m + 1)]
# Uzupełnienie pierwszego wiersza i kolumny
    for i in range(m + 1):
        macierz[i][0] = i
    for j in range(n + 1):
        macierz[0][j] = j
# Wypełnienie macierzy
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if slowo1[i - 1] == slowo2[j - 1]:
                macierz[i][j] = macierz[i - 1][j - 1]
            else: macierz[i][j] = 1 + min(macierz[i - 1][j], macierz[i][j - 1], macierz[i - 1][j - 1])
    return macierz[m][n]

# Przykładowe użycie funkcji
slowo1 = "kot"
slowo2 = "kocioł"
distance = levenshtein_distance(slowo1, slowo2)
print(f"Odległość Levenshteina między '{slowo1}' a '{slowo2}' wynosi: {distance}")
