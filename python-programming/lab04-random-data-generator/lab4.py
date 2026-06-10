import lab4modul

# ZADANIE 1
print('\n')
print(lab4modul.generuj_losowa_liste(15))
print(lab4modul.generuj_losowa_liste(8, typ_elementu='float'))
print(lab4modul.generuj_losowa_liste(10, typ_elementu='str'))
print(lab4modul.generuj_losowa_liste(12, typ_elementu='mieszany'))

# ZADANIE 2
print('\n')
print(lab4modul.generuj_losowa_krotke(3))
print(lab4modul.generuj_losowa_krotke(5, typ_elementu='str'))

# ZADANIE 3
print('\n')
print(lab4modul.generuj_losowy_zbior(20, typ_elementu='int'))
print(lab4modul.generuj_losowy_zbior(20, typ_elementu='mieszany'))

# ZADANIE 4
print('\n')
print(lab4modul.generuj_losowy_slownik(10))
print(lab4modul.generuj_losowy_slownik(11, typ_klucza='str', typ_wartosci='float'))

# ZADANIE 5
print('\n')
print(lab4modul.generuj_losowy_tekst(300))
print('\n')
print(lab4modul.generuj_losowy_tekst(300, max_dl_linii=50))