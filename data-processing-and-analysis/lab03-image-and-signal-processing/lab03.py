import numpy as np
from matplotlib import pyplot as plt
from PIL import Image
import cv2


# ------------------------------------------- DYSKRETYZACJA -------------------------------------------

########## ZADANIE 1 i 2

def generuj_sinus(f, Fs):
    dt = 1 / Fs                         # krok próbkowania - odstęp czasowy pomiędzy kolejnymi próbkami
    t = np.arange(0, 1, dt)             # tablica czasu - wartości od 0 do 1 z krokiem równym dt.
                                        #                 t reprezentuje momenty czasowe, w których zostaną pobrane próbki sygnału.
    s = np.sin(2 * np.pi * f * t)       # wartości sygnału sinusoidalnego dla każdego momentu w czasie t.

    return t, s

########## ZADANIE 3

f = 10  # Częstotliwość sygnału w Hz

Fs_list = [20, 21, 30, 45, 50, 100, 150, 200, 250, 1000]   # Lista częstotliwości próbkowania

# Wykresy
for Fs in Fs_list:
    t, s = generuj_sinus(f, Fs)
    plt.figure()
    plt.plot(t, s)
    plt.title(f'Sygnał 10 Hz próbkowany z Fs = {Fs} Hz')
    plt.xlabel('Czas [s]')
    plt.ylabel('Amplituda')
    plt.grid(True)
    plt.show()


########## ZADANIE 4 - Twierdzenie Nyquista-Shannona (twierdzenie o próbkowaniu) - aby dokładnie odtworzyć sygnał, częstotliwość
# próbkowania musi być co najmniej dwa razy większa od najwyższej częstotliwości obecnej w sygnale.

########## ZADANIE 5 - aliasing to zjawisko, w którym sygnały o wyższych częstotliwościach są błędnie interpretowane jako sygnały
# o niższych częstotliwościach podczas próbkowania

# ------------------------------------------- KWANTYZACJA -------------------------------------------

########## ZADANIE 1

img = Image.open("robal.png")

########## ZADANIE 2

print("KWANTYZACJA\nZADANIE 2:")
img_array = np.array(img)                                 # Konwersja do macierzy NumPy
print("\tLiczba wymiarów macierzy:", img_array.ndim)      # img_array.ndim zwraca liczbę wymiarów tablicy NumPy
                                                          # dla obrazów zazwyczaj 2 wymiary (czarno-białe) lub 3 wymiary (kolorowe)

########## ZADANIE 3

print("_______________________________________________________________")
print("ZADANIE 3:")
num_wartosci_pixela = img_array.shape[-1]           # shape zwraca krotkę z wymiarami tablicy, shape[-1] to ostani wymiar,
                                                    # który zazwyczaj reprezentuje liczbę wartości opisujących pojedynczy piksel
print("Liczba wartości opisujących pojedynczy piksel:", num_wartosci_pixela)

########## ZADANIE 4

print("_______________________________________________________________")

# Rozdzielenie kanałów R, G, B
R = img_array[:, :, 0].astype(float)            # wybieramy wszystkie wiersze (:), wszystkie kolumny (:) i pierwszy kanał (indeks 0) - kanał czerwony (R).
G = img_array[:, :, 1].astype(float)            # drugi kanał (indeks 1) - kanał zielony (G).
B = img_array[:, :, 2].astype(float)            # trzeci kanał (indeks 2) - kanał niebieski (B).
# wszystko konwertowane na typ float

# --- METODA 1: Jasność (brightness) = (max(R, G,B) + min(R, G,B))/2
jasnosc = ((np.maximum.reduce([R, G, B]) + np.minimum.reduce([R, G, B])) / 2).astype(np.uint8)

# np.maximum.reduce() i np.minimum.reduce()  ---> porównuje wszystkie trzy macierze (R, G, B) i zwraca najmniejszą wartość dla każdego elementu
# .astype(np.uint8) ---> konwersja na uint8 (8-bitowe liczby całkowite), bo obrazy w skali szarości są zazwyczaj reprezentowane w tym formacie

# --- METODA 2: Uśrednienie (R + G + B)/3
usrednienie = ((R + G + B) / 3).astype(np.uint8)

# --- METODA 3: Luminancja = 0.21R + 0.72G + 0.07B
luminacja = (0.21 * R + 0.72 * G + 0.07 * B).astype(np.uint8)

# --- WYNIKI

# WYZNACZENIE JASNOŚCI PIKSELA
plt.figure(figsize=(5, 5))
plt.imshow(jasnosc, cmap='gray')
plt.title('Wyznaczanie jasnosci piksela: (max(R, G,B) + min(R, G,B))/2')
plt.axis('off')
plt.tight_layout()
plt.show()

# UŚREDNIENIE WARTOŚCI PIKSELA
plt.figure(figsize=(5, 5))
plt.imshow(usrednienie, cmap='gray')
plt.title('Usrednienie wartosci piksela: (R + G + B)/3')
plt.axis('off')
plt.tight_layout()
plt.show()

# WYZNACZENIE LUMINACJI PIKSELA
plt.figure(figsize=(5, 5))
plt.imshow(luminacja, cmap='gray')
plt.title('Wyznaczenie liminacji piksela: (0.21R + 0.72G + 0.07B)')
plt.axis('off')
plt.tight_layout()
plt.show()

########## ZADANIE 5
print("_______________________________________________________________")

# Funkcja do generowania histogramu
def rysuj_histogram(image, title):
    histogram, bin_edges = np.histogram(image, bins=256, range=(0, 255))
    # np.histogram(image, bins=256, range=(0, 255)) ---> Oblicza histogram dla wartości pikseli w obrazie
    # bins=256: Dzielimy zakres wartości pikseli (od 0 do 255) na 256 przedziałów (tzw. binów), gdzie każdy bin odpowiada jednej wartości pikseli
    # range=(0, 255): Określamy zakres wartości pikseli, który nas interesuje (od 0 do 255, ponieważ obrazy w skali szarości mają takie wartości)
    #
    # histogram: Tablica, w której każdy element zawiera liczbę pikseli w danym przedziale (binie).
    # bin_edges: Tablica zawierająca granice przedziałów (binów). Ma długość o 1 większą niż histogram, ponieważ opisuje również prawą granicę ostatniego przedziału.


    plt.figure()
    plt.title(title)
    plt.xlabel("Wartość pikseli")
    plt.ylabel("Częstotliwość")
    plt.plot(bin_edges[0:-1], histogram)  # używamy wszystkich elementów bin_edges z wyjątkiem ostatniego, ponieważ
                                                # liczba krawędzi binów jest o 1 większa niż liczba binów

    plt.xlim([0, 255])                          # zakres osi X od 0 do 255, bo to zakres wartości pikseli w obrazie w skali szarości
    plt.show()

# Generowanie histogramów dla każdego obrazu
rysuj_histogram(jasnosc, "Histogram Jasność (max+min)/2")
rysuj_histogram(usrednienie, "Histogram Uśrednienie (R+G+B)/3")
rysuj_histogram(luminacja, "Histogram Luminancja (0.21R+0.72G+0.07B)")

########## ZADANIE 6
print("_______________________________________________________________")
print("ZADANIE 6:")

# Histogram z 16 przedziałami (redukcja do 16 poziomów jasności)
hist_16, bin_edges = np.histogram(luminacja.flatten(), bins=16, range=(0, 256))

# luminacja.flatten() ---> spłaszcza macierz obrazu w skali szarości (np. luminancji) do jednowymiarowego wektora, ponieważ np.histogram
#                          oczekuje danych w formie listy lub wektora
# bins=16 --->   dzielenie zakresu wartości pikseli (0–255) na 16 przedziałów
# range=(0, 256) ---> zakres wartości pikseli, 256 to górna granica

# Wyświetlenie wyników
print("Zakresy nowych 16 kolorów (jasności):")
for i in range(len(hist_16)):
    print(f"{i+1}. Przedział {int(bin_edges[i])} - {int(bin_edges[i+1]) - 1} : {hist_16[i]} pikseli")

########## ZADANIE 7
print("_______________________________________________________________")

# Funkcja do przypisania nowej wartości piksela na podstawie środka przedziału
def redukcja_kolorow(image, bin_edges, bin_centers):
    # Stwórz nową macierz o tych samych wymiarach co oryginalny obraz
    new_image = np.zeros_like(image)

    # Iteruj przez każdy piksel obrazu
    for x in range(image.shape[0]):  # Iteracja po wierszach
        for y in range(image.shape[1]):  # Iteracja po kolumnach
            # Pobierz wartość piksela
            pixel_value = image[x, y]

            # Znajdź odpowiedni przedział dla tego piksela
            for i in range(len(bin_edges) - 1):
                if bin_edges[i] <= pixel_value < bin_edges[i + 1]:      #  do którego przedziału należy wartość piksela
                    # Przypisz wartość środka przedziału
                    new_image[x, y] = bin_centers[i]
                    break  # Wyjdź z pętli, gdy znajdziesz odpowiedni przedział

    return new_image

# Histogram z 16 przedziałami (redukcja do 16 poziomów jasności)
hist_16, bin_edges = np.histogram(luminacja.flatten(), bins=16, range=(0, 256))

bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2

# Stwórz nowy obraz z zredukowaną liczbą kolorów
reduced_image = redukcja_kolorow(luminacja, bin_edges, bin_centers)

# Wyświetl nowy obraz
plt.figure(figsize=(6, 6))
plt.imshow(reduced_image, cmap='gray')
plt.title("Obraz z zredukowaną liczbą kolorów")
plt.axis('off')
plt.show()


# ------------------------------------------- BINARYZACJA -------------------------------------------

histogram, bin_edges = np.histogram(luminacja, bins=256, range=(0, 255))

########## ZADANIE 3
otsu_threshold, _ = cv2.threshold(luminacja, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
# cv2.threshold ---> funkcja z biblioteki OpenCV do binaryzacji obrazu

# thresh: 0 --> początkowy próg - ignorowany w metodzie Otsu, ponieważ Otsu samodzielnie wyznacza optymalny próg
# maxval: 255 --> max wartość, którą otrzymuje piksel po binaryzacji
# cv2.THRESH_BINARY + cv2.THRESH_OTSU --> Flagi określające typ binaryzacji.
#       cv2.THRESH_BINARY oznacza binaryzację, gdzie piksele poniżej progu są ustawiane na 0 (czarny), a powyżej na 255 (biały)
#       cv2.THRESH_OTSU uruchamia metodę Otsu, która automatycznie wyznacza optymalny próg

# otsu_threshold --->  zmienna z wartością progu wyznaczoną przez metodę Otsu
# _ --> zbinaryzowany obraz (w tym przypadku ignorowany))

print("Punkt progowania (Otsu):", otsu_threshold)

########## ZADANIE 4

binary_image = (luminacja >= otsu_threshold).astype(np.uint8)
# Jeśli wartość piksela jest większa lub równa progowi (otsu_threshold), wynik to True.
# Jeśli wartość piksela jest mniejsza od progu, wynik to False.
# astype(np.uint8) konwertuje macierz z wartościami logicznymi (True/False) na macierz z wartościami liczbowymi (0/1)

########## ZADANIE 5

plt.figure(figsize=(6, 6))
plt.imshow(binary_image, cmap='gray')
plt.title("Obraz z wysegmentowanym obiektem")
plt.axis('off')
plt.show()
