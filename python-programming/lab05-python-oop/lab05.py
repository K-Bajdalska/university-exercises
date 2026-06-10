import lab05modul

# WYŚWIETLANIE LICZBY, FORMA REPREZENTACYJNA I UŁAMEK NIEWŁAŚCIWY
l1 = lab05modul.Liczba_wymierna(1, 4, 1)
l2 = lab05modul.Liczba_wymierna(3, 2, 4)

print("\nWyswietlanie liczby, jej reprezentacji i postaci ulamka niewlasciwego: ")
print(f"DANE WEJSCIOWE: 1, 4, 1:\t{l1}\t\t\t{repr(l1)}\t\t{l1.ul_niewlasciwy()}")
print(f"DANE WEJSCIOWE: 3, 2, 4:\t{l2}\t\t{repr(l2)}\t\t{l2.ul_niewlasciwy()}")

# PORÓWNYWANIE LICZB
l1 = lab05modul.Liczba_wymierna(4, 5, 7)        # 4 i 5/7
l2 = lab05modul.Liczba_wymierna(4, 15, 21)      # 4 i 5/7
l3 = lab05modul.Liczba_wymierna(0, 33, 7)       # 4 i 5/7
l4 = lab05modul.Liczba_wymierna(0, 66, 14)      # 4 i 5/7
l5 = lab05modul.Liczba_wymierna(4,8,9)          # 2 i 8/9

print ("\nPorownywanie liczb wymiernych z liczbami wymiernymi:")
print(f"DANE 1: 4,5,7\t\tDANE 2: 4,15,21 : \t\t{l1==l2}")
print(f"DANE 1: 4,5,7\t\tDANE 2: 0,33,7  : \t\t{l1==l3}")
print(f"DANE 1: 4,15,21\t\tDANE 2: 0,66,14 : \t\t{l2==l4}")
print(f"DANE 1: 4,8,9\t\tDANE 2: 4,5,7   : \t\t{l5==l1}")

l6 = lab05modul.Liczba_wymierna(6,0,1)      # 6
l7 = lab05modul.Liczba_wymierna(0, 90, 10)  # 9
print ("\nPorownywanie liczb wymiernych z calkowitymi:")
print(f"DANE 1: 6,0,1\t\tDANE 2: 6 : \t{l6==6}")
print(f"DANE 1: 6,0,1\t\tDANE 2: 66 : \t{l6==66}")
print(f"DANE 1: 0,90,10\t\tDANE 2: 9 : \t{l7==9}")
print(f"DANE 1: 0,90,10\t\tDANE 2: 90 : \t{l7==90}")

# DODAWANIE
l1 = lab05modul.Liczba_wymierna(6,7,9)
l2 = lab05modul.Liczba_wymierna(1,5,10)
l3 = lab05modul.Liczba_wymierna(0, 66, 11)
print ("\nDodwanie:")
wynik = l1 + l2
print(f"{l1} + {l2} = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l2 + l3
print(f"{l2} + {l3} = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l1 + 10
print(f"{l1} + 10 = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = 10 + l1
print(f"10 + {l1} = {wynik}  ({wynik.ul_niewlasciwy()})")

# MNOŻENIE
l1 = lab05modul.Liczba_wymierna(13,13,42)
l2 = lab05modul.Liczba_wymierna(2,5,10)
l3 = lab05modul.Liczba_wymierna(0, 71, 12)
print ("\nMnozenie:")
wynik = l1 * l2
print(f"{l1} * {l2} = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l2 * l3
print(f"{l2} * {l3} = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l1 * 11
print(f"{l1} * 11 = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = 11 * l1
print(f"11 * {l1} = {wynik}  ({wynik.ul_niewlasciwy()})")

# DZIELENIE
l1 = lab05modul.Liczba_wymierna(15,12,10)
l2 = lab05modul.Liczba_wymierna(4,3,6)
l3 = lab05modul.Liczba_wymierna(0, 32, 11)
print ("\nDzielenie:")
wynik = l1 / l2
print(f"{l1} / {l2} = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l2 / l3
print(f"{l2} / {l3} = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l1 / 4
print(f"{l1} / 4 = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = 4 / l1
print(f"4 / {l1} = {wynik}  ({wynik.ul_niewlasciwy()})")

# POTĘGOWANIE
print ("\nPotegowanie:")
wynik = l2 ** 2
print(f"{l2} do potegi 2 = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l2 ** 5
print(f"{l2} do potegi 5 = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l3 ** 3
print(f"{l3} do potegi 3 = {wynik}  ({wynik.ul_niewlasciwy()})")
wynik = l3 ** 7
print(f"{l3} do potegi 7 = {wynik}  ({wynik.ul_niewlasciwy()})")

# KONWERSJI DO INT, FLOAT I BOOL
l1 = lab05modul.Liczba_wymierna(2, 3, 7)  # 2 i 3/7
l2 = lab05modul.Liczba_wymierna(1, 1, 2)  # 1 i 1/2
l3 = lab05modul.Liczba_wymierna(0, 0, 1)  # 0
l4 = lab05modul.Liczba_wymierna(0, 7, 7)  # 1

print ("\nKonwersja do int:")
print (f"{l1}:\t{int(l1)}")
print (f"{l2}:\t{int(l2)}")
print (f"{l3}:\t\t\t{int(l3)}")
print (f"{l4}:\t\t\t{int(l4)}")
print (f"{l5}:\t{int(l5)}")

print ("\nKonwersja do float:")
print (f"{l1}:\t{float(l1)}")
print (f"{l2}:\t{float(l2)}")
print (f"{l3}:\t\t\t{float(l3)}")
print (f"{l4}:\t\t\t{float(l4)}")
print (f"{l5}:\t{float(l5)}")

print ("\nKonwersja do bool:")
print (f"{l1}:\t{bool(l1)}")
print (f"{l2}:\t{bool(l2)}")
print (f"{l3}:\t\t\t{bool(l3)}")
print (f"{l4}:\t\t\t{bool(l4)}")
print (f"{l5}:\t{bool(l5)}")