import numpy as np
from matplotlib import pyplot as plt
from sklearn import datasets
from sklearn.datasets import load_digits
from sklearn.decomposition import PCA

# ZADANIE 1
def wiPCA(X, n_components):
    # 1. MACIERZ ODCHYLEŃ - odejmowanie od każdego elementu danych średniej wartości dla danej cechy
    mean_vec = np.mean(X, axis = 0)         # Średni wektor wejściowy,  axis = 0 --> dla każdej kolumny
    X_center = X - mean_vec                 # Odchylenie danych od średniej

    # 2. MACIERZ KOWARIANCJI - dla zmiennych w kolumnach
    cov_matrix = np.cov(X_center, rowvar=False)    # rowvar=False --->  każda kolumna w macierzy reprezentuje zmienną,
                                                   # a każda wiersz reprezentuje obserwacje, więc nie trzeba transponować ręcznie

    # 3. WARTOŚCI I WEKTORY WŁASNE MACIERZY KOWARIANCJI
    eigenvalues, eigenvectors = np.linalg.eigh(cov_matrix)
    # eigenvalues ---> wartości własne: reprezentują wielkość wariancji danych w kierunku odpowiadającego im wektora własnego
    # eigenvectors ---> wektory własne: wskazują kierunki składowych głównych
    # np.linalg.eigh(cov_matrix) zwraca wartości własne i wektory własne macierzy hermitowskiej zespolonej (sprzężonej symetrycznej) lub macierzy rzeczywistej symetrycznej.

    # 4. SORTOWANIE MALEJĄCO
    sorted_index = np.argsort(eigenvalues)[::-1]            # np.argsort zwraca indeksy, które posortowałyby tablicę eigenvalues w rosnącej kolejności
                                                            # [::-1] odwraca kolejność wynikowych indeksów, aby były w malejącej kolejności
    eigenvalues = eigenvalues[sorted_index]                 # sortowanie według wcześniej obliczonych indeksów
    eigenvectors = eigenvectors[:, sorted_index]            # sortowanie wektorów własnych w tej samej kolejności, co wartości własne

    # 5. WYBRANIE N GŁOWNYCH SKŁADOWYCH
    selected_vectors = eigenvectors[:, :n_components]       # odpowiadają największym wartościom własnym

    # 6. MACIERZ ZREDUKOWANA
    X_reduced = np.dot(X_center, selected_vectors)          # mnożenie wycentrowanych danych X_center przez wybrane wektory własne selected_vectors
                                                            # Wynikiem jest macierz, która reprezentuje dane w nowej przestrzeni, o mniejszym wymiarze

    return X_reduced, selected_vectors, eigenvectors, mean_vec

# A) wygenerowac w sposób losowy zbiór 200 obiektów dwuwymiarowych
# np.random.seed(42)                    # Ustawienie ziarna dla powtarzalności wyników
data = np.random.randn(200, 2)          # Losowy rozkład normalny 200 punktów w 2D

# B) zwizualizowac obiekty na pomoca funkcji matplotlib, np. scatter
plt.scatter(data[:, 0], data[:, 1], alpha=0.7, color='blue')     # data[:, 0] ---> pierwszy wymiar danych oś X (wszystkie wiersze z pierwszej kolumny)
                                                                 # data[:, 1] ---> drugi wymiar danych (oś Y) (wszystkie wiersze z drugiej kolumny)
plt.title("ZADANIE 1 - dane 2D")
plt.grid(True)
plt.show()

# C) dokonac redukcji do jednego wymiaru za pomoca własnej funkcji wiPCA i zwizualizowac wektory własne oraz rzut wygenerowanych
# obiektów na pierwsza składowa
X_reduced, selected_vectors, _, mean_vector = wiPCA(data, n_components=2)

# Odchylenie danych od średniej (do rysowania rzutów) - wycentrowanie danych wokół zera (odejmowanie średnich wartości dla każdej cechy)
X_centered = data - mean_vector

# Obliczanie rzutu punktów na pierwszy wektor własny
first_vec = selected_vectors[:, 0]              # Pierwszy wektor własny ---> kierunek największej wariancji

projected = np.dot(X_centered, first_vec.reshape(-1, 1)) * first_vec.reshape(1, -1)
# np.dot(X_centered, first_vec.reshape(-1, 1)) ---> oblicza rzut danych pierwszy wektor własny, wynik to wartości wzdłuż tego kierunku
# .reshape(-1,1) ---> przekształa wektor w macierz kolumnową
# * first_vec.reshape(1, -1) ---> rozciąga rzut wzdłuż kierunku pierwszego wektora własnego

projected += mean_vector  # przesunięcie danych z powrotem do przestrzeni oryginalnej, dodając średnią wartość dla każdego wymiaru

plt.figure(figsize=(8, 6))
plt.scatter(data[:, 0], data[:, 1], alpha=0.7, color = 'blue')              # dane oryginalne jako niebieskie punkty
plt.scatter(projected[:, 0], projected[:, 1], alpha=0.8, color='orange')    # punkty rzutowane na pierwszy wektor własny jako pomarańczowe punkty

# Rysowanie wektorów własnych od środka danych
for i in range(2):                                  # Przejście przez 2 główne składowe
    vec = selected_vectors[:, i]                    # i-ty wektor własny (wszystkie wiersze z kolumny (i), czyli współrzędne x i y wektora własnego)
    plt.arrow(mean_vector[0], mean_vector[1],       # strzałka na wykresie z punktem startowym w mean_vector[0], mean_vector[1]
              vec[0], vec[1],                       # vec[0] i vec[1] ---> współrzędne x i y wektora własnego
              color='black', width=0.01, head_width=0.1)

plt.title('ZADANIE 1 - PCA: Rzut danych na główne składowe')
plt.axis('equal')                   # ustawia proporcje osi X i Y na wykresie, żeby były takie same
plt.grid(True)
plt.show()
#_______________________________________________________________________________________________________________
# ZADANIE 2

# A) DANE IRIS
iris = datasets.load_iris()
X = iris.data    # Dane - konkretne wartości klas
y = iris.target  # Klasy - etykiety

print("Cel ćwiczenia:")
# FUNKCJA wiPCA
X_wiPCA, vectors, values, mean_vec = wiPCA(X, 2)
print("wiPCA (pierwsze 5 wierszy):\n", X_wiPCA[:5])

# sklearn PCA
pca = PCA(n_components=2)                    # tworzy obiekt PCA z sklearn z 2 składowymi głównymi
X_r_sklearn = pca.fit(X).transform(X)        # X_r_sklearn ---> dane zredukowane do przestrzeni 2D za pomocą sklearn:
                                             # fit(X): dopasowuje model PCA do danych X
                                             # transform(X): przekształca dane X do przestrzeni 2D

print("sklearn PCA (pierwsze 5 wierszy):\n", X_r_sklearn[:5])

# WYNIKI takie same ale rózniące się znakami ale to ok ponieważ: kierunek wektora własnego nie ma znaczenia — można go pomnożyć przez -1 i dalej jest poprawny.
# Wektor [1, 2] i [-1, -2] to ten sam kierunek przestrzenny, tylko przeciwny zwrot.
# Sklearn (lub wiPCA) może wybrać inny zwrot tego wektora własnego. Matematycznie to bez różnicy, wizualnie — wykres wygląda tak samo, tylko odbity względem osi

# Wizualizacja wyników PCA
colors = ['red', 'lime', 'fuchsia']

plt.figure(figsize=(8, 6))
for i, color in zip([0, 1, 2], colors):         # zip łączy klasy ([0, 1, 2]) z kolorami (colors), tworząc pary: (0, 'red'), (1, 'lime'), ...
    plt.scatter(X_wiPCA[y == i, 0],             # wybiera współrzędne x (pierwsza składowa PCA) dla punktów należących do klasy i
                X_wiPCA[y == i, 1],             # wybiera współrzędne y (druga składowa PCA) dla punktów należących do klasy i
                color=color, marker='o')

plt.grid(True)
plt.show()
#_______________________________________________________________________________________________________________
# ZADANIE 3

# A) WCZYTANIE ZBIORU DIGITS
digits = load_digits()
X = digits.data
y = digits.target

# B) REDUKCJA DO 2 GŁÓWNYCH SKŁADOWYCH
X_wiPCA, vectors, values, mean_vec = wiPCA(X, 2)

# C) KRZYWA WARIANCJI
pca = PCA()             # tworzenie obiektu PCA
pca.fit(X)              # dopasowanie modelu PCA do danych X

plt.plot(np.cumsum(pca.explained_variance_ratio_))
# np.cumsum ---> oblicza skumulowaną sumę wariancji
# pca.explained_variance_ratio_ ---> proporcje wariancji wyjaśnianej przez każdą składową główną

plt.title('ZADANIE 3 - Krzywa wariancji')
plt.grid(True)
plt.show()


# D) WIZUALIZACJA ELEMENTÓW ZBIORU Z PIONOWĄ LEGENDĄ
colors = ['palevioletred', 'pink', 'lightsalmon', 'peachpuff', 'lemonchiffon', 'darkkhaki', 'palegreen', 'aquamarine',
          'lightseagreen', 'mediumslateblue']

plt.figure(figsize=(8, 6))
for i in range(10):         # iterowanie przez cyfry od 1 do 9
    plt.scatter(X_wiPCA[y == i, 0],         # wybiera współrzędne x (pierwsza składowa PCA) dla punktów należących do klasy i
                X_wiPCA[y == i, 1],         # wybiera współrzędne y (druga składowa PCA) dla punktów należących do klasy i
                color=colors[i], marker='o', label=f'Cyfra {i}')


plt.title("ZADANIE 3 - PCA na zbiorze Digits")
plt.xlabel("składowa 1")
plt.ylabel("składowa 2")

# LEGEND — jako pionowy słupek z boku
plt.legend(title="Cyfry", loc='center left', bbox_to_anchor=(1, 0.5), ncol=1)
# loc='center left' ---> ustawia legendę po lewej stronie
# bbox_to_anchor=(1, 0.5) --->  przesuwa legendę poza obszar wykresu (na prawo)
# ncol=1 ---> ustawia legendę jako jedną kolumnę (każda cyfra w osobnym wierszu)
plt.grid(True)
plt.tight_layout()
plt.show()

# E)

# Funkcja odwrotna do PCA - rekonstruuje dane z przestrzeni głównych składowych do oryginalnej przestrzeni
def inverse_wiPCA(X_reduced, eigenvectors, mean):
    return np.dot(X_reduced, eigenvectors.T) + mean
    # Mnożenie zredukowanych danych przez transponowaną macierz wektorów własnych, aby odtworzyć oryginalną przestrzeń
    # i dodaje średnią, aby przywrócić dane do oryginalnej skali

# Funkcja obliczająca średni błąd rekonstrukcji (średnią odległość euklidesową między danymi oryginalnymi a zrekonstruowanymi)
def reconstruction_error(X_original, X_reconstructed):
    return np.mean(np.linalg.norm(X_original - X_reconstructed, axis=1))
    # X_original - X_reconstructed –--> różnica między oryginałem a rekonstrukcją
    # np.linalg.norm(..., axis=1) --–> norma (odległość euklidesową) dla każdego wiersza (punktu danych)
    # np.mean(...) –--> średnią z tych odległości

errors = []                         # błędy rekonstrukcji dla różnych liczby głównych składowych
components_range = range(1, 65)     # zakres liczby głównych składowych, od 1 do 64 bo digits.data ma 64 cechy

X = digits.data                     # zbiór danych digits
X_mean = np.mean(X, axis=0)         # średnia dla każdej kolumny (cechy) w danych
X_centered = X - X_mean             # centrowanie danych - odejmowanie średniej, aby dane miały środek w zerze

cov = np.cov(X_centered.T)                                   # macierz kowariancji dla transponowanych danych (kolumny jako zmienne)
eigenvalues, eigenvectors = np.linalg.eigh(cov)              # wartości własne (eigenvalues) i wektory własne (eigenvectors) macierzy kowariancji
sorted_index = np.argsort(eigenvalues)[::-1]                 # sortowanie indeksów wartości własnych w malejącej kolejności
eigenvectors = eigenvectors[:, sorted_index]                 # przestawienie kolumn macierzy wektorów własnych zgodnie z posortowanymi wartościami własnymi

# Liczenie błędów rekonstrukcji
for n in components_range:
    vectors = eigenvectors[:, :n]                                   # pierwsze n wektorów własnych (główne składowe)
    X_reduced = np.dot(X_centered, vectors)                         # projekcja danych na wybrane główne składowe
    X_reconstructed = inverse_wiPCA(X_reduced, vectors, X_mean)     # rekonstrukcja danych z przestrzeni zredukowanej
    error = reconstruction_error(X, X_reconstructed)                # obliczanie błędu rekonstrukcji
    errors.append(error)                                            # dodanie błędu do listy

plt.figure(figsize=(6, 4))
plt.plot(components_range, errors)
plt.xlabel("liczba składowych")
plt.ylabel("odległość")
plt.title("Wizualizacja błędu rekonstrukcji")
plt.grid(True)
plt.tight_layout()
plt.show()
