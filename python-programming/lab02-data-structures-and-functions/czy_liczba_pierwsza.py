def czy_liczba_pierwsza(n):
    if n <= 1:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

# Przykłady użycia
# print(czy_liczba_pierwsza(2))  # True
# print(czy_liczba_pierwsza(4))  # False
# print(czy_liczba_pierwsza(17)) # True