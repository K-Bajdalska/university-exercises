import numpy as np
from numpy.lib.stride_tricks import as_strided


### ZADANIE 1: Utwórz macierz składajaca sie z pieciu kolumn i 10 wierszy losowo wybranych liczb całkowitych
# i policz sume głównej przekatnej macierzy, uzywajac funkcji ’trace’ a nastepnie wyswietl wartosci
# uzywajac funkcji ’diag’.
print("\nZADANIE 1:\n")

macierz = np.random.randint(1, 101, size=(10, 5))
print("Macierz 10x5:")
print(macierz)

suma_przekatnej = np.trace(macierz)              # np.trace() zwraca sumę elementów na przekątnej macierzy
print("\nSuma głównej przekątnej:")             # (domyslnie głównej przekątnej) ale można dodać przesunięcia
print(suma_przekatnej)

wartosci_przekatnej = np.diag(macierz)           # np.diag zwraca wartości na głównej przekątnej macierzy
print("\nWartości na głównej przekątnej:")      # jako tablicę (listę).
print(wartosci_przekatnej)

print("-----------------------------------------------")
### ZADANIE 2: Utwórz dwie tablice z losowo wybranych liczb dziesietnych z rozkładu normalnego
# i przemnóz je przez siebie.
print("\nZADANIE 2:\n")

tablica1 = np.random.randn(10)
tablica2 = np.random.randn(10)

print("Tablica 1:")
print(tablica1)

print("\nTablica 2:")
print(tablica2)

wynik = np.multiply(tablica1, tablica2)                     # mnoży elementy obu tablic element po elemencie

print("\nWynik mnożenia tablic:")
print(wynik)

print("-----------------------------------------------")
### ZADANIE 3 Utwórz dwie tablice z losowo wybranych liczb całkowitych w zakresie od 1-100.
# Stwórz z nich macierze o 5 kolumnach i dodaj je do siebie.
print("\nZADANIE 3:\n")


tablica1 = np.random.randint(1, 101, size=25)  # Tablica z 25 elementami
tablica2 = np.random.randint(1, 101, size=25)  # Tablica z 25 elementami

print("Tablica 1:")
print(tablica1)

print("\nTablica 2:")
print(tablica2)

# Przekształcenie tablic na macierze 5x5
macierz1 = tablica1.reshape(5, 5)                       #  np.reshape(tablica, (nowy_kształt)) pozwala na zmianę
macierz2 = tablica2.reshape(5, 5)                       #  kształtu (rozmiaru) tablicy bez zmiany jej danych
                                                        #  liczba el. przed i po przekształceniu musi być taka sama
print("\nMacierz 1 (5x5):")
print(macierz1)

print("\nMacierz 2 (5x5):")
print(macierz2)

wynik = np.add(macierz1, macierz2)

print("\nWynik dodawania macierzy:")
print(wynik)

print("-----------------------------------------------")
### ZADANIE 4 :Stwórz macierz o 5 kolumnach i 4 wierszach oraz 4 kolumnach i 5 wierszach i dodaj je
# do siebie uzywajac transformacji wymiarów.
print("\nZADANIE 4:\n")

# Macierz 4x5
macierz1 = np.random.randint(1, 101, size=(4, 5))

# Macierz 5x4
macierz2 = np.random.randint(1, 101, size=(5, 4))

print("Macierz 1 (4x5):")
print(macierz1)

print("\nMacierz 2 (5x4):")
print(macierz2)

# Przekształcamy macierz 2 na wymiar 4x5 za pomocą reshape
macierz2_reshape = macierz2.reshape(4, 5)

print("\nMacierz 2 po zmianie wymiarów (4x5):")
print(macierz2_reshape)

# Dodajemy macierze element po elemencie
macierz_wynik = np.add(macierz1, macierz2_reshape)

print("\nWynik dodawania macierzy:")
print(macierz_wynik)

print("-----------------------------------------------")
### ZADANIE 5: Pomnóz kolumny 3 i 4, stworzonych przez siebie macierzy.
print("\nZADANIE 5:\n")

# Tworzymy macierz 5x6 i 5x4
macierz1 = np.random.randint(1, 51, size=(5, 6))
macierz2 = np.random.randint(1, 51, size=(5, 4))

print("Macierz 1:")
print(macierz1)
print("\nMacierz 2:")
print(macierz2)


# Kolumny 3 i 4 (indeksy 2 i 3)
kolumna3 = macierz1[:, 2]                       #  wszystkie wiersze i kolumna 2
kolumna4 = macierz2[:, 3]                       #  wszystkie wiersze i kolumna 3

print("\nKolumna 3:")
print(kolumna3)

print("\nKolumna 4:")
print(kolumna4)

# Mnożenie kolumn
wynik = np.multiply(kolumna3, kolumna4)

print("\nWynik mnożenia kolumn 3 i 4:")
print(wynik)

print("-----------------------------------------------")
### ZADANIE 6: Wygeneruj dwie macierze o rozkładzie normalnym (np.random.normal) i jednostajnym
# (np.random.uniform). Policz wartosc srednia, odchylenie standardowa, wariancje itp.
# Porównaj wyniki z obu zbiorów danych.
# Wygenerowanie macierzy o rozkładzie normalnym (np.random.normal)
print("\nZADANIE 6:\n")

macierz_normalna = np.random.normal(size=(5, 5))        # Średnia=0, Odchylenie=1   ---> domyślne
macierz_normalna = np.round(macierz_normalna, 6)    # Zaokrąglanie do 6 miejsc po przecinku
print("Macierz z rozkładu normalnego (zaokrąglona do 6 miejsc po przecinku):")
print(macierz_normalna)


macierz_jednostajna = np.random.uniform(size=(5, 5))  # Zakres [0, 1]   ---> domyślny
macierz_jednostajna = np.round(macierz_jednostajna, 6) # Zaokrąglanie do 6 miejsc po przecinku
print("\nMacierz o rozkładzie jednostajnym (zaokrąglona do 6 miejsc po przecinku):")
print(macierz_jednostajna)

#  STATYSTYKI - macierz normalna
srednia_normalna = np.mean(macierz_normalna)
odchylenie_normalne = np.std(macierz_normalna)
wariancja_normalna = np.var(macierz_normalna)
minimum_normalne = np.min(macierz_normalna)
maksimum_normalne = np.max(macierz_normalna)

# STATYSTYKI - macierz jednostajna
srednia_jednostajna = np.mean(macierz_jednostajna)
odchylenie_jednostajne = np.std(macierz_jednostajna)
wariancja_jednostajna = np.var(macierz_jednostajna)
minimum_jednostajne = np.min(macierz_jednostajna)
maksimum_jednostajne = np.max(macierz_jednostajna)

# Wyświetlenie wyników
print("\nStatystyki dla macierzy normalnej:")
print(f"Średnia: {srednia_normalna}")
print(f"Odchylenie standardowe: {odchylenie_normalne}")
print(f"Wariancja: {wariancja_normalna}")
print(f"Minimum: {minimum_normalne}")
print(f"Maksimum: {maksimum_normalne}")

print("\nStatystyki dla macierzy jednostajnej:")
print(f"Średnia: {srednia_jednostajna}")
print(f"Odchylenie standardowe: {odchylenie_jednostajne}")
print(f"Wariancja: {wariancja_jednostajna}")
print(f"Minimum: {minimum_jednostajne}")
print(f"Maksimum: {maksimum_jednostajne}")

###
# ŚREDNIA: w r. normalnym oscyluje wokół 0, a w r. jednostajnym wokół 0.5 (bo wartości są równomiernie rozłożone)
# ODCHYLENIE STANDARDOWE: znacznie mniejsze w r. jednostajnym
# WARIANCJA: znacznie mniejsza w r. jednostajnym
# WNIOSKI: r. normalny jest bardziej rozproszony, a jednostajny "uporządkowany"


print("-----------------------------------------------")
### ZADANIE 7: Wygeneruj dwie macierze kwadratowe a i b, pomnóz je przez siebie uzywajac (a*b)
# oraz funkcji dot. Jaka jest róznica? Napisz kiedy warto wykorzystac funkcje dot?
print("\nZADANIE 7:\n")

macierzA = np.random.randint(1, 20, size=(4, 4))
macierzB = np.random.randint(1, 20, size=(4, 4))

print("Macierz A:")
print(macierzA)

print("\nMacierz B:")
print(macierzB)

# Mnożenie element po elemencie
wynik_elementowy = macierzA * macierzB
print("\nWynik mnożenia element po elemencie (A * B):")
print(wynik_elementowy)

# Mnożenie macierzowe - suma iloczynów elementów wierszy z macierzA i kolumn z macierzB
wynik_macierzowy = np.dot(macierzA, macierzB)
print("\nWynik mnożenia macierzowego (np.dot(A, B)):")
print(wynik_macierzowy)

# * (element po elemencie):
# Mnoży odpowiadające sobie elementy z obu macierzy.
# Wynikowa macierz ma taki sam wymiar jak macierze wejściowe.
# Przydatne w operacjach, gdzie chcemy pracować na pojedynczych wartościach (np. skalowanie, maskowanie).

# np.dot (iloczyn macierzowy):
#
# Wykonuje pełny iloczyn macierzowy zgodny z zasadami algebry liniowej.
# Wynikowa macierz ma wymiary zgodne z zasadami mnożenia macierzy:
# Jeśli macierzA ma wymiary m x n i macierzB ma wymiary n x p, wynikowa macierz ma wymiary m x p.
# Przydatne w operacjach związanych z algebrą liniową, np. obliczeniach naukowych, grafice komputerowej,
# uczeniu maszynowym.

print("-----------------------------------------------")
### ZADANIE 8: Sprawdz funkcje strides oraz as strided. Zastosuj je do wyboru danych z macierzy
# np. 5 kolumn z trzech pierwszych wierszy.
print("\nZADANIE 8:\n")

# Każda tablica w NumPy ma atrybut strides, który mówi, ile bajtów należy przesunąć w pamięci,
# aby przejść do kolejnego elementu.
# as_strided pozwala na tworzenie nowych "widoków" na dane w tablicy, zmieniając sposób ich odczytu.

macierz = np.random.randint(1, 101, size=(7, 7))
print("Macierz:")
print(macierz)

# Wyświetlenie atrybutu strides dla macierzy
print("\nStrides macierzy:")                    # (28,4) oznacza że do następnego wiersza jest 28 bajtów pamięci
print(macierz.strides)                          #        a do następnej kolumny 4 bajty

# Zastosowanie as_strided do wyboru 5 kolumn z trzech pierwszych wierszy
wiersze = 3  # Liczba wierszy do wyboru
kolumny = 5  # Liczba kolumn do wyboru
widok = as_strided(macierz, shape=(wiersze, kolumny), strides=macierz.strides)

print("\nWidok (5 kolumn z trzech pierwszych wierszy):")
print(widok)

print("-----------------------------------------------")
# ZADANIE 9 : Wygeneruj dwie tablice a i b. Połacz je z uzyciem funkcji vstack i
# hstack. Czym one sie róznia? Zastanów sie i napisz, w jakich przypadkach
# warto je zastosowac?
print("\nZADANIE 9:\n")

tablicaA = np.random.randint(1, 10, size=(2,3))
tablicaB = np.random.randint(1, 10, size=(2,3))

print("Tablica A:")
print(tablicaA)

print("\nTablica B:")
print(tablicaB)

# Łączenie tablic vstack (pionowo) - dodaje nowe wiersze
vstack_result = np.vstack((tablicaA, tablicaB))
print("\nWynik vstack (pionowe połączenie):")
print(vstack_result)

# Łączenie tablic hstack (poziomo) - dodaje nowe kolumny
hstack_result = np.hstack((tablicaA, tablicaB))
print("\nWynik hstack (poziome połączenie):")
print(hstack_result)

# vstack jest przydatne, gdy chcemy organizować dane w wierszach np. dodawanie nowych zestawów danych do macierzy

# hstack jest przydatne, gdy chcemy organizować dane w kolumnach np. w analizie danych, gdy dodajemy
# nowe cechy (np. wyniki eksperymentów).

print("-----------------------------------------------")
# ZADANIE 10 Uzyj funkcji strides i as strided do obliczenia wartosci maksymalnej
# bloków danych z macierzy (rysunek)
print("\nZADANIE 10:\n")

macierz = np.array([[0, 1, 2, 3, 4, 5],
                    [6, 7, 8, 9, 10, 11],
                    [12, 13, 14, 15, 16, 17],
                    [18, 19, 20, 21, 22, 23]
                    ])
print("Macierz:")
print(macierz)

kroki_wiersze, kroki_kolumny = macierz.strides  # kroki dla wierszy i kolumn

bloki = as_strided(macierz,
                   shape=(2, 2, 2, 3),  # Tworzymy siatkę bloków 2x2, każdy blok ma 2 wiersze i 3 kolumny
                   strides=(kroki_wiersze * 2, kroki_kolumny * 3, kroki_wiersze, kroki_kolumny))    #

# kroki_wiersze * 2 → Żeby przejść do nowego rzędu bloków (skok o 2 wiersze)                  kroki_wiersze → Skok w obrębie bloku na nowy wiersz
# kroki_kolumny * 3 → Żeby przejść do nowej kolumny bloków (skok o 3 kolumny)                 kroki_kolumny → Skok w obrębie bloku na nową kolumnę.
# bloki to widok na naszą macierz, ale podzielony na 4 bloki 2x3.

maksymalne_wartosci = np.max(bloki, axis=(2, 3))        # axis=(2, 3) → maksimum wewnątrz każdego bloku (wymiar 2x3)
print("\nMaksymalne wartości bloków:\n", maksymalne_wartosci)