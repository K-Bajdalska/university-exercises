import math

# ZADANIE 3
name = input("Podaj swoje imię: ")
print("Witaj ", name)

# ZADANIE 4
wzrost_cm = int(input("Podaj swój wzrost w centymetrach: "))
waga_kg = float(input("Podaj swoją wagę w kilogramach: "))

wzrost_m = wzrost_cm / 100

waga_g = waga_kg * 1000

print(f"Twoja waga w gramach: {waga_g} g")
print(f"Twój wzrost w metrach: {wzrost_m} m")

# ZADANIE 5

x = float(input("Podaj wartość dla x: "))
y = float(input("Podaj wartość dla y: "))

bezwzgledna_x_plus_1 = abs(x + 1)
log_bezwzgledna_x_plus_1 = math.log(bezwzgledna_x_plus_1)
sin_x_plus_y = math.sin(x + y)
cos_x_minus_y = math.cos(x - y)
e_x2_y2_1 = math.exp(x**2 + y**2 + 1)
result = log_bezwzgledna_x_plus_1 * (sin_x_plus_y * cos_x_minus_y / e_x2_y2_1)

print(f"Wartość funkcji f(x, y) = {result}")

# ZADANIE 6

x = float(input("Podaj wartość dla x: "))
y = float(input("Podaj wartość dla y: "))
c = int(input("Podaj numer opcji (1: suma, 2: różnica, 3: iloczyn, 4: iloraz): "))

match c:
    case 1:
        wynik = x + y
        print(f"Suma x i y wynosi: {wynik}")
    case 2:
        wynik = x - y
        print(f"Różnica x i y wynosi: {wynik}")
    case 3:
        wynik = x * y
        print(f"Iloczyn x i y wynosi: {wynik}")
    case 4:
        if y != 0:
            wynik = x / y
            print(f"Iloraz x i y wynosi: {wynik}")
        else:
            print("Błąd: Dzielenie przez 0 jest niemożliwe!")
    case _:
        print("Błędna opcja. Wybierz 1, 2, 3 lub 4.")

# ZADANIE 7

czas_w_sekundach = int(input("Podaj czas w sekundach: "))

godziny = czas_w_sekundach // 3600
pozostale_sekundy = czas_w_sekundach % 3600
minuty = pozostale_sekundy // 60
sekundy = pozostale_sekundy % 60

print(f"{godziny} godzin, {minuty} minut, {sekundy} sekund")

# ZADANIE 8
tekst = input("Podaj tekst: ")

znak = input("Podaj znak: ")

licznik = 0

for char in tekst:
    if char == znak:
        licznik += 1

print(f"Liczba wystąpień znaku '{znak}' w tekście wynosi: {licznik}")

# ZADANIE 9
def fibonacci(n):
    if n <= 0:
        return "Liczba musi być dodatnia"
    elif n == 1 or n == 2:
        return 1
    else:
        a, b = 1, 1
        for _ in range(3, n + 1):
            a, b = b, a + b
        return b

n = int(input("Podaj liczbę elementów ciągu Fibonacciego do wyświetlenia: "))

if n <= 0:
    print("Liczba musi być dodatnia")
else:
    print("Ciąg Fibonacciego:")
    for i in range(1, n + 1):
        print(f"f({i}) = {fibonacci(i)}")

# ZADANIE 10
def czy_liczba_pierwsza(n):
    if n <= 1:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

# Przykłady użycia
print(czy_liczba_pierwsza(2))  # True
print(czy_liczba_pierwsza(4))  # False
print(czy_liczba_pierwsza(17)) # True