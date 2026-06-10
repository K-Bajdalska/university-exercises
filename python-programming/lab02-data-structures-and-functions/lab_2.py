import math

from czy_liczba_pierwsza import czy_liczba_pierwsza

# ZADANIE 1
print("ZADANIE 1")
def tribonacci(n):
    if n==0 or n == 1:
        return 0
    if n == 2:
        return 1
    else:
        return (tribonacci(n - 1) +
                tribonacci(n - 2) +
                tribonacci(n - 3))

# Pobieranie liczby elementów od użytkownika
n = int(input("Podaj liczbę elementów ciągu Tribonacciego do wyświetlenia: "))

if n<0:
    print("Liczba musi być dodatnia")
else:
    print("Ciąg Tribonacciego")
    for i in range(0, n+1):
        print(f"f({i}) = {tribonacci(i)}")

# ZADANIE 2
print("ZADANIE 2")
# Tworzenie krotki
krotka = tuple(range(1, 31))
print("Krotka:", krotka)

# Odwrocona krotka
odwrocona_krotka = krotka[::-1]
print("Odwrocona krotka:", odwrocona_krotka)

# Parzyste wartosci
krotka_parzysta = krotka[1::2]
print("Parzyste wartości:", krotka_parzysta)

# Wartosci z liczbami pierwszymi
print("Liczby pierwsze:", end =" ")
for i in range(0, len(krotka)):
    if czy_liczba_pierwsza(krotka[i]):
        print(krotka[i], end =" ")

# ZADANIE 3
print("\nZADANIE 3")
macierz = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16]
]

glowna = [macierz[i][i] for i in range(4)]
poboczna = [macierz[i][3-i] for i in range(4)]

print("\nGłówna przekątna:", glowna)
print("Poboczna przekątna:", poboczna)

# ZADANIE 4
print("ZADANIE 4")

def f(x, n=10, k=2):
    return math.log(x + 5, n) * (x ** k)

wyniki = []

x_wartosci = [i * 0.1 for i in range(-20, 21)]

for x in x_wartosci:
    wyniki.append(f(x))

print(wyniki)

# ZADANIE 5
print("ZADANIE 5")

lista = list(range(1, 100, 2))
print ("Oryginalna lista: ", lista)

kopia_listy = lista.copy()
print ("Kopia listy: ", kopia_listy)

lista[0] = 999
print ("Oryginalna lista: ", lista)
print ("Kopia listy: ", kopia_listy)

# ZADANIE 6
print("ZADANIE 6")

def analizujProstokat (lewy_gorny, prawy_dolny):
    x1= abs(lewy_gorny[0])
    y1 = abs(lewy_gorny[1])
    x2 = abs(prawy_dolny[0])
    y2 = abs(prawy_dolny[1])

    wysokosc = abs(x2 - x1)
    szerokosc = abs(y2 - y1)

    obwod = 2 * (wysokosc + szerokosc)
    pole = wysokosc * szerokosc

    info_prostokat = (obwod, pole)
    return info_prostokat

x_lewy = float(input("Podaj x dla lewego gornego naroznika: "))
y_lewy = float(input("Podaj y dla lewego gornego naroznika: "))
x_prawy = float(input("Podaj x dla prawego dolnego naroznika: "))
y_prawy = float(input("Podaj y dla prawego dolnego naroznika: "))

lewyGorny = (x_lewy, y_lewy)
prawyDolny = (x_prawy, y_prawy)

informacje = analizujProstokat(lewyGorny, prawyDolny)
print(f"Obwód: {informacje[0]}, Pole: {informacje[1]}")

# ZADANIE 7
print("ZADANIE 7")


def usun_spacje(tekst):
    # Usuń białe znaki na początku i końcu tekstu
    tekst = tekst.strip()

    # Zamień wszystkie podwójne spacje na pojedyncze
    while '  ' in tekst:
        tekst = tekst.replace('  ', ' ')

    return tekst

tekst = "       Na poczatku sa spacje     i       tu     tez      a           tu    jeszcze   wiecej.  "
poprawiony_tekst = usun_spacje(tekst)
print(poprawiony_tekst)

# ZADANIE 8
print("ZADANIE 8")

A = {1, 2, 3, 4, 5}
B = {2, 4, 5}
C = {3, 4, 5, 6, 7, 8}

# Część wspólna A i C
czesc_wspolna = A.intersection(C)
print("Część wspólna zbiorów A i C: ", czesc_wspolna)

# Suma A i C
suma = A.union(C)
print("Suma zbiorow A i C: ", suma)

# Roznica A i B
roznica = A.difference(B)
print("Roznica zbiorow A i B: ", roznica)

# Roznica symetryczna A i C
roznica_symetryczna = A.symmetric_difference(C)
print("Roznica symetryczna zbiorow A i C: ", roznica_symetryczna)

# Czy B jest podzbiorem A
if B.issubset(A):
    print("B jest podzbiorem A")
else:
    print ("B nie jest podzbiorem A")

if B.issubset(C):
    print("B jest podzbiorem C")
else:
    print("B nie jest podzbiorem C")
