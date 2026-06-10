import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from scipy.stats import pearsonr, gaussian_kde

df = pd.DataFrame({"x": [1, 2, 3, 4, 5], 'y': ['a', 'b', 'a', 'b', 'b']})
print(f"WYJŚCIOWA TABELA:\n{df}")
print("-----------------------------------------------")

### ZADANIE 1: Zgrupowac tabele po zmiennej symbolicznej Y, a nastepnie wyznaczyc srednia wartosc atrybutu numerycznego X w grupach wyznaczonych przez Y.
print("ZADANIE 1")

grouped = df.groupby('y')       #  Tworzy grupę dla każdego unikalnego klucza w kolumnie 'y' (a i b). Zwraca obiekt typu DataFrameGroupBy - specjalny typ,
                                #  który pozwala na wykonywanie operacji na każdej grupie osobno. To NIE jest nowa tabela, tylko sposób na organizację danych


mean_values = grouped['x'].mean()   # grouped['x'] wyciąga kolumnę x z każdej grupy (sposrod tyc hstworzonych wyzej), zwraca obiekt typu Series,
                                    # ze wszystkimi wartościami z kolumny.   mean() oblicza średnią wartość

print(f"Srednie wartosci zgrupowanych x:\n{mean_values}")
print("-----------------------------------------------")

### ZADANIE 2: Wyznaczyc rozkład licznosci atrybutów (value counts)
print("ZADANIE 2")
#  rozkład liczności ----> liczba wystąpień każdej wartości w kolumnie

# Rozkład liczności dla kolumny 'y'
licznosc_y = df['y'].value_counts()         # df['y] wyciąga kolumnę y z df, a value_counts() przechodzi przez jej wszystkie wartości i identyfikuje
                                            # każdą unikalną wartość i zlicza jej wystąpienia

print(f"Rozkład liczności dla kolumny 'y':\n{licznosc_y}")
# licznosc_y to nowy obiekt typu Series, który przechowuje wyniki działania value_counts. Series Series to jednowymiarowa struktura danych, która przypomina list lub numpy array ,
# ale każdy element jest indeksowany

# Rozkład liczności dla kolumny 'x'
licznosc_x = df['x'].value_counts()
print(f"Rozkład liczności dla kolumny 'x':\n{licznosc_x}")
print("-----------------------------------------------")

### ZADANIE 3: Wyczytac dane autos.csv, za pomoca polecenia np.loadtxt oraz pandas.read csv. Sprawdz róznice
print("ZADANIE 3")
# Wczytanie danych za pomocą numpy.loadtxt
# np.loadtxt ładuje dane z pliku tekstowego i zwraca je jako tablicę NumPy przyjmuje:
# fname: plik, lista plików;                            #dtype: typ tablicy wynikowej
# delimiter: znak używany do rozdzielania wartości (domyślnie spacja)
# skiprows: pomija pierwsze X wierszy (domyslnie 0), ale u nas można zrobić 1 żeby pominąć nazwy nagłówków

autos_numpy = np.loadtxt('autos.csv',dtype=str, delimiter=',', skiprows=0, )
print(f"Dane wczytane za pomocą numpy.loadtxt:\n{autos_numpy}")


# Wczytanie danych za pomocą pandas.read_csv
# pd.read_csv odczytuje plik z wartościami rozdzielonymi przecinkami (csv) zwracając DataFrame
autos_pandas = pd.read_csv('autos.csv')
print(f"\nDane wczytane za pomocą pandas.read_csv:\n{autos_pandas}")


# np.loadtxt działa najlepiej z prostymi plikami, które zawierają tylko liczby, nie obsługuje automatycznego rozpoznawania typów danych i nie
# obsługuje nagłówków (trzeba je ręcznie pominąć).

# pd.read_csv jest bardziej elastyczna i zaawansowana - automatycznie rozpoznaje typy danych w kolumnach, bsługuje nagłówki,
# brakujące dane, różne formaty separatorów
print("-----------------------------------------------")

### ZADANIE 4: Zgrupowac ramke danych po zmiennej ’make’ a nastepnie wyznaczyc srednie zuzycie paliwa dla kazdego z producentów.
print("ZADANIE 4")

# Grupowanie po make
grupowanie_make = autos_pandas.groupby('make')

# Średnie zużycie dla każdego producenta
srednie_zuzycie = grupowanie_make[['city-mpg', 'highway-mpg']].mean().mean(axis=1).rename('srednie-zuzycie')
# grupowanie_make[['city-mpg', 'highway-mpg']] --->  wyciąga kolumny 'city-mpg' i 'highway-mpg' z każdej grupy utworzonej wcześniej
# .mean() ---> średnią wartość dla 'city-mpg' i 'highway-mpg' dla każdego producenta. Tworzy DataFrame (indeks to nazwa producenta,
#              a wartości to średnie zużycie paliwa w mieście i na autostradzie.
# .mean(axis=1)  ----> średnia wartość wzdłuż wierszy (czyli dla każdej grupy). To uśrednia wartości city-mpg i highway-mpg.
#                      Tworzy Series, gdzie indeks to nazwa producenta, a wartości to średnie zużycie paliwa.
# .rename('srednie-zuzycie') ----> zmienia nazwę serii, bez tego pole name Series byłoby puste

# Wyświetlenie wyników
print(srednie_zuzycie)
print("-----------------------------------------------")

### ZADANIE 5 : Zgrupowac ramke danych po zmiennej ’make’ licznosci dla atrybutu ’fuel-type’.
print("ZADANIE 5:")

# Grupowanie po 'make' i liczenie liczności dla 'fuel-type'
licznik_typow_paliwa = autos_pandas.groupby('make')['fuel-type'].value_counts()
# grupuje dane według producenta, wyciąga tylko kolumnę z typami paliwa a potem zlicza ile razy każdy rodzaj paliwa występuje u producentów
# licznik_typow_paliwa przechowuje obiekt typu Series, indeks jest złożony: 1 poziom to producent (make), 2 poziom to rodzaj paliwa (fuel-type).
# Wartości to liczność rodzajów dla każdego producenta.

# Sumowanie liczności dla każdego rodzaju paliwa
ogolna_licznosc_paliwa = licznik_typow_paliwa.groupby(level=1).sum()
#  grupuje dane w według 2 poziomu indeksu (level=1) - fuel-type. Grupy są tworzone na podstawie rodzaju paliwa, a producent jest ignorowany

ogolna_licznosc_paliwa = ogolna_licznosc_paliwa.sort_values(ascending=False)
# Sortowanie w porządku malejącym

# Wyświetlenie wyników
print(ogolna_licznosc_paliwa)
print("-----------------------------------------------")

### ZADANIE 6 : Dopasowac wielomian 1 i 2 stopnia prognozujacy wartosc zmiennej ’city-mpg’, wzgledem ’length’ (np.polyfit , np.polyval).
print("ZADANIE 6:")

# Dopasowanie wielomianów do danych, aby stworzyć model matematyczny, który przewiduje wartość 'city-mpg' na podstawie 'length'.
# Wielomian 1. stopnia to funkcja liniowa (ax + b), a wielomian 2. stopnia to funkcja kwadratowa (ax^2 + bx + c)

x = autos_pandas['length'].values           # zmienna niezależna (długość samochodu)
y = autos_pandas['city-mpg'].values         # zmienna zależna (zużycie paliwa w mieście).

# np.polyfit (x,y, deg:stopien wielomianu) - Dopasowanie wielomianu metodą najmniejszych kwadratów
# Wielomian 1. stopnia (liniowy)
p1 = np.polyfit(x, y, 1)

# Wielomian 2. stopnia (kwadratowy)
p2 = np.polyfit(x, y, 2)

# Wyświetlenie współczynników
print(p1)
print(p2)


print("-----------------------------------------------")

### ZADANIE 7 : Wyznaczyc współczynnik korelacji liniowej pomiedzy tymi zmiennymi (scipy.stats).
print("ZADANIE 7:")

# Obliczenie współczynnika korelacji liniowej
statistic, p_value = pearsonr(x, y)
# pearsonr mierzy liniową zależność między x a y. Waha się między -1 i +1 (0 oznacza brak korelacji).
# Dodatnie korelacje oznaczają, że wraz ze wzrostem x, y również wzrasta. Ujemne korelacje oznaczają, że wraz ze wzrostem x, y maleje.
# p_value to liczba, która wskazuje, czy zaobserwowana korelacja (wartość statistic) jest statystycznie istotna. Mówi, czy korelacja,
# którą widzimy, mogła powstać przypadkowo.

print(f"Współczynnik korelacji Pearsona: {statistic}")
print(f"p-value: {p_value}")

# WYNIKI:
# Współczynnik korelacji Pearsona: -0.6709086615585711 --->  silna ujemną korelację pomiędzy zmiennymi length a city-mpg zużycie paliwa w mieście
# p-value: 3.595528842225762e-28 ---> bardzo mała wartość, co oznacza, że istnieje bardzo małe prawdopodobieństwo, że zaobserwowana korelacja
# jest przypadkowa. Korelacja jest statystycznie istotna.
print("-----------------------------------------------")

### ZADANIE 8 : Zwizualizowac wyniki dopasowania, zaznaczajac próbki oraz dopasowane krzywe na tle próbek dla zmiennych ’city-mpg’, ’length’.
print("ZADANIE 8")

# Wizualizacja dopasowania wielomianów
plt.figure(figsize=(8, 6))      # nowy wykres o wymiarach 8x6 cali
plt.scatter(x, y, label="Dane (próbki)", color='blue', alpha=0.6)
# plt.scatter(x, y) ---> rysuje punkty danych x (długość pojazdu) i y (zużycie paliwa w mieście).
# label="Dane (próbki)": etykieta do legendy
# color='blue': kolor punktów
# alpha=0.6: przeźroczystość punktów

# Generowanie wartości dla linii trendu
x_fit = np.linspace(min(x), max(x), 100)            # 100 równomiernie rozmieszczonych punktów na osi x (długość pojazdu)
                                                         # od najmniejszej do największej wartości w danych.
y_fit_1 = np.polyval(p1, x_fit)             # wartości y dla wielomianu 1. stopnia (p1) w punktach x_fit. Funkcja np.polyval bierze
                                            # współczynniki wielomianu (z p1) i oblicza wartość funkcji dla każdego punktu w x_fit.
y_fit_2 = np.polyval(p2, x_fit)             # t o samo dla wielomianu 2 stopnia

# Rysowanie dopasowanych krzywych
plt.plot(x_fit, y_fit_1, label="Wielomian 1. stopnia", color='green')                      # dla wielomianu 1 stopnia
plt.plot(x_fit, y_fit_2, label="Wielomian 2. stopnia", color='red', linestyle='dashed')    # dla wielomianu 2 stopnia

# Opisy wykresu
plt.xlabel("Długość pojazdu (length)")
plt.ylabel("Zużycie paliwa w mieście (city-mpg)")
plt.title("Dopasowanie wielomianowe: City-mpg vs Length")
plt.legend()
plt.show()

print("-----------------------------------------------")

### ZADANIE 9: Dla zmiennej ’length’ utworzyc jednowymiarowy estymator funkcji gestosci, w tym celu uzyc scipy.stats.gaussian kde. Zwizualizowac
# wynik przedstawiajac jednoczesnie próbki i funkcje gestosci. Do wykresu dodac legende. W tym celu uzyc (plot(...,label=’...’), legend)
print("ZADANIE 9")

x_length = autos_pandas['length'].values    # pobiera wartości długości pojazdów i konwertuje dane do formatu tablicy NumPy

kde = gaussian_kde(x_length)                # estymator funkcji gęstości za pomocą jądra Gaussa, KDE to metoda, która wygładza dane
                                            # i estymację rozkładu prawdopodobieństwa


# Wartości do wykresu
x_wartosci = np.linspace(min(x_length), max(x_length), 1000)  # 1000 równomiernie rozmieszczonych punktów pomiędzy najmniejszą a największą wartością
                                                                   # długości pojazdów - 1000 punktów zapewnia gładką krzywą na wykresie

y_wartosci = kde(x_wartosci)  #  wartości funkcji gęstości dla wygenerowanych punktów x_wartosci

y_samples = kde(x_length)  # wartości funkcji gęstości dla rzeczywistych danych długości pojazdów


plt.figure(figsize=(8, 6))
# Rysowanie estymowanej funkcji gęstości
plt.plot(x_wartosci, y_wartosci, color='red', label="Funkcja KDE", linewidth=2)

# Rysowanie punktów danych (próbki) jako linia na krzywej
plt.plot(x_length, kde(x_length), 'o', color='fuchsia', label="Próbki")

# Opisy wykresu
plt.xlabel("Długość pojazdu (length)")
plt.ylabel("Gęstość")
plt.title("Estymacja funkcji gęstości dla 'length'")
plt.legend()
plt.grid()

plt.show()

print("-----------------------------------------------")

### ZADANIE 10: Utworzyc w jednym oknie graficznym dwa wykresy ax=subplot(...), ax.plot(...) Na drugim wykresie przedstawic analogicznie
# rozkład dla zmiennej ’width’.

x_length = autos_pandas['length'].values        # wartości długości pojazdów jako tablica NumPy
x_width = autos_pandas['width'].values          # wartości szerokości pojazdów jako tablica NumPy

kde_length = gaussian_kde(x_length)             # estymator funkcji gęstości dla zmiennej length
kde_width = gaussian_kde(x_width)               # estymator funkcji gęstości dla zmiennej width

x_wartosci_length = np.linspace(min(x_length), max(x_length), 1000)
# 1000 równomiernie rozmieszczonych punktów na osi długości pojazdów (length)

x_wartosci_width = np.linspace(min(x_width), max(x_width), 1000)
# 1000 równomiernie rozmieszczonych punktów na osi szerokości pojazdów (width)

y_wartosci_length = kde_length(x_wartosci_length)
# wartości estymowanej funkcji gęstości dla długości pojazdów w punktach x_wartosci_length
y_wartosci_width = kde_width(x_wartosci_width)
# wartości estymowanej funkcji gęstości dla szerokości pojazdów w punktach x_wartosci_width.

y_samples_length = kde_length(x_length)
# wartości funkcji gęstości dla rzeczywistych próbek długości pojazdów (length).
y_samples_width = kde_width(x_width)
# wartości funkcji gęstości dla rzeczywistych próbek szerokości pojazdów (width)

# Tworzenie figury z dwoma wykresami
fig, ax = plt.subplots(2, 1, figsize=(8, 5))  # Dwa wykresy obok siebie

# Pierwszy wykres: length
ax[0].plot(x_wartosci_length, y_wartosci_length, color='red', label="funkcja", linewidth=2) # estymowana funkcja gęstości dla length
ax[0].scatter(x_length, y_samples_length, color='fuchsia', label="próbki", marker='o') # rzeczywiste próbki
ax[0].set_xlabel("Długość pojazdu (length)")    # Opis osi x
ax[0].set_ylabel("Gęstość")                     # Opis osi y
ax[0].set_title("Estymacja funkcji gęstości dla 'length'")  # tytuł
ax[0].legend()
ax[0].grid()

# Drugi wykres: width
ax[1].plot(x_wartosci_width, y_wartosci_width, color='yellow', label="funkcja", linewidth=2)
ax[1].scatter(x_width, y_samples_width, color='indigo', label="próbki", marker='o')
ax[1].set_xlabel("Szerokość pojazdu (width)")
ax[1].set_ylabel("Gęstość")
ax[1].set_title("Estymacja funkcji gęstości dla 'width'")
ax[1].legend()
ax[1].grid()

# Pokaż wykresy
plt.tight_layout()  #  automatycznie dostosowuje rozmieszczenie wykresów, aby nie nachodziły na siebie.
plt.show()
print("-----------------------------------------------")

### ZADANIE 11: Utworzyc dwuwymiarowy estymator funkcji gestosci dla zmiennych ’width’ i ’length’, wynik przedstawic graficznie w nowym
# oknie rysujac próbki poleceniem plot oraz funkcje gestosci uzywajac polecenia meshgrid i contour. Wynik zapisac do plików w formacie
# *.png i *.pdf (savefig).

# Pobranie danych i usunięcie braków
x_length = autos_pandas['length'].values  # OX: długość pojazdu
y_width = autos_pandas['width'].values    # OY: szerokość pojazdu

# Łączenie zmiennych w jedną macierz dla KDE
data = np.vstack([x_length, y_width])
# Łączymy dane x_length (długość) i y_width (szerokość) w jedną macierz NumPy, gdzie:
# pierwszy wiersz reprezentuje długość pojazdu, drugi wiersz reprezentuje szerokość pojazdu

kde = gaussian_kde(data)    # estymator funkcji gęstości dla danych 2D (długość i szerokość pojazdów)

# Tworzenie siatki do rysowania funkcji gęstości
x_min, x_max = x_length.min(), x_length.max()   #  minimalna i maksymalna wartość dla długości pojazdów - zekres osi X
y_min, y_max = y_width.min(), y_width.max()     # minimalna i maksymalna wartość dla szerokości pojazdów - zakres osi Y

# Tworzymy siatkę punktów w przestrzeni 2D (100x100), która obejmuje zakresy długości i szerokości pojazdów
x_grid, y_grid = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100))

# Transformacja siatki do formatu 2xN
grid_coords = np.vstack([x_grid.ravel(), y_grid.ravel()])
# x_grid.ravel() i y_grid.ravel() - spłaszcza macierze siatki do jednowymiarowych tablic
# np.vstack - łączenie spłaszczonych tablic w macierz 2xN, gdzie każdy punkt siatki jest reprezentowany jako para współrzędnych (X, Y)

# Obliczanie wartości KDE na siatce
z_vals = kde(grid_coords).reshape(x_grid.shape)
#kde(grid_coords) - oliczanie wartości funkcji gęstości dla każdego punktu siatki
# .reshape(x_grid.shape)- przekształcenie wyników do kształtu siatki (100x100)

plt.figure(figsize=(8, 6))
plt.scatter(x_length, y_width, color='black', label="Próbki", marker='o', s=5)  # rzeczywiste próbki

# Rysowanie konturów gęstości (różne kolory, brak wypełnienia)
contour = plt.contour(x_grid, y_grid, z_vals, levels=6, cmap="rainbow")

# Opisy wykresu
plt.xlabel("Długość pojazdu (length)")  # OX: długość
plt.ylabel("Szerokość pojazdu (width)")  # OY: szerokość
plt.title("Dwuwymiarowa estymacja funkcji gęstości (KDE)")
plt.grid()



# Zapisanie wykresu do plików
plt.savefig("dwuwymiarowa_kde.png", dpi=300, facecolor='white')
plt.savefig("dwuwymiarowa_kde.pdf", facecolor='white')

# Wyświetlenie wykresu
plt.show()

print("-----------------------------------------------")