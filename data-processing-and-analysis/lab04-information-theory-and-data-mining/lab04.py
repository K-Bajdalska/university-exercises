import numpy as np
import pandas as pd

# ZADANIE 1
def freq(x, prob=True):
    # Pusty słownik, który będzie przechowywał:
    #       Klucze -  unikalne wartości z listy x
    #       Wartości - liczby wystąpień (częstości) tych kluczy
    freq_dict = {}

    # Zliczanie wystąpień każdej wartości
    for value in x:
        if value in freq_dict:
            freq_dict[value] += 1
        else:
            freq_dict[value] = 1

    # Wyodrębnianie unikalnych wartości i ich liczności
    unique_val = sorted(freq_dict.keys())      #  sortowanie kluczy (unikalne wystąpienia)

    count_s = [freq_dict[value] for value in unique_val]          #  Dopasowywanie liczności do posortowanych wartości

    if prob:
        total = sum(count_s)                                        # Całkowita suma liczności
        probabilitie_s = [count / total for count in count_s]       # lista prawdopodobieństw - dzielenie każdej liczności przez total
        return unique_val, probabilitie_s
    else:
        return unique_val, count_s

x = [7,7,3,3,8,3,8,8,9,7,8,4,5,3,7,5,1,6,4,4,7,2,1,1,9,3,5,6,1,9,1,1,
     2,9,6,4,4,7,4,6,9,6,4,9,5,6,9,8,2,3]
unique_val, probabilitie_s = freq(x)
_, counts = freq(x, prob = False)
print("\n\n________________________________________________________________________")
print (f"ZADANIE 1:\nx: {x}\nunikalne wartosci xi: {unique_val}\nprawdopodobienstwa kazdej z tych wartosci: {probabilitie_s}")
print (f"Czestosc wystepowania tych wartosci: {counts}")
print("________________________________________________________________________")

########################################################################################################################

# ZADANIE 2

def freq2(x, y, prob=True):
    # Słownik do przechowywania wspólnych liczności
    freq_dict = {}

    # Zliczanie wystąpienia par (x, y)
    for pair in zip(x, y):          #zip(x, y) łączy w pary elementy z listy z i y: (x[0], y[0]), (x[1], y[1]), ...
        if pair in freq_dict:
            freq_dict[pair] += 1
        else:
            freq_dict[pair] = 1

    xi = []             # Wartości x z par (x, y)
    yi = []             # Wartości y z par (x, y)
    counts = []         # Liczności odpowiadające każdej parze

    for pair, count in freq_dict.items():           # Iterowanie przez każdą parę (x, y) i jej liczność
        xi.append(pair[0])                          # Dodanie wartość x z pary (x,y)
        yi.append(pair[1])                          # Dodanie wartość y z pary (x,y)
        counts.append(count)                        # Dodanie liczności pary

    if prob:
        total = sum(counts)                         # Całkowita liczba wystąpień
        probabilitie_s = [count / total for count in counts]
        return xi, yi, probabilitie_s
    else:
        return xi, yi, counts
x = [10, 20, 30, 40, 50, 10, 20, 30, 35]
y = ['a','b','b','c','d', 'a', 'b', 'e', 'e']

xi, yi, ni = freq2(x,y,False)
_,_,pi = freq2(x,y)
print(f"ZADANIE 2:\nKolumna danych x:{x}\nKolumna danych y: {y}\nxi:{xi}")
print(f"yi: {yi}\nni:{ni}\n{pi}")
print("________________________________________________________________________")
########################################################################################################################

# ZADANIE 3

def entropy(x):
    # Funkcja freq do uzyskania prawdopodobieństw
    xi, probabilities = freq(x, prob=True)

    # Obliczamy entropię - lista wartości p * np.log2(p) dla każdego p w probabilities, ale tylko wtedy, gdy p > 0
    e = -np.sum([p * np.log2(p) for p in probabilities if p > 0])

    return e

def infogain(x, y):

    # Entropie H(X) i H(Y)
    e_x = entropy(x)
    e_y = entropy(y)

    # Wspólna entropia H(X,Y) z freq2
    xi, yi, probabilities = freq2(x, y, prob=True)
    e_xy = -np.sum([p * np.log2(p) for p in probabilities if p > 0])

    # Informacja wzajemna I(X,Y)
    mutual_info = e_x + e_y - e_xy

    # Warunkowa entropia H(Y|X)
    _, px = freq(x, prob=True)          #  Lista prawdopodobieństw dla każdej unikalnej wartości w x
    e_y_given_x = 0                     #  Suma warunkowej entropii ( H(Y|X) )

    # Grupowanie prawdopodobieństw według wartości x
    x_to_joint_probs = {}           #  Klucze: wartości x       Wartości: lista wspólnych prawdopodobieństw dla danych wartości y
    for x_val, y_val, p in zip(xi, yi, probabilities):          # zip() łączy listy xi, yi i probabilities w trójki (x_val, y_val, p)
        if x_val not in x_to_joint_probs:
            x_to_joint_probs[x_val] = []
        x_to_joint_probs[x_val].append(p)           # Dodanie prawdopodobieństwa p do listy dla danego x_val.

    # Obliczanie warunkowej entropii dla każdej wartości x
    for x_val, p_xi in zip(sorted(set(x)), px):     #  zip() łączy unikalne wartości x z ich prawdopodobieństwami px
        if p_xi > 0:
            joint_probs_for_xi = x_to_joint_probs.get(x_val, [])       # pobranie listy wspólnych prawdopodobieństw dla danej wartości x
            h_y_given_xi = -np.sum([
                (p_ij / p_xi) * np.log2(p_ij / p_xi)                # sumowanie warunkowych entropii dla każdej wartości y względem x
                for p_ij in joint_probs_for_xi if p_ij > 0
            ])
            e_y_given_x += p_xi * h_y_given_xi          # Dodawanie do całkowitej warunkowej entropii, entropię warunkową ważoną przez prawdopodobieństwo p_xi

    # Przyrost informacji I(Y,X)
    info_gain = e_y - e_y_given_x

    return mutual_info, info_gain

x = [1,5,7,5,2]
x_en = entropy(x)
y = ['a', 'a', 'a', 'b', 'b']
_,y_info = infogain(x,y)
print(f"ZADANIE 3:\nentropy(x): {x_en}\ninfogain(x,y): {y_info}")
print("________________________________________________________________________")
########################################################################################################################
# ZADANIE 4
print("ZADANIE 4:")

# Wczytanie danych z pliku zoo.csv
data = pd.read_csv('zoo.csv')

# Kolumna docelowa ---> typ zwierzęcia
target = data['type']

# Lista atrybutów do oceny ---> bez 'animal' i 'type'
attributes = data.columns.drop(['animal', 'type'])   # drop usuwa wskazane kolumny

# Przyrost informacji dla każdego atrybutu względem kolumny 'type'
info_gains = {}
entropies = {}

for attribute in attributes:
    entropies[attribute] = entropy(data[attribute])
    _, info_gains[attribute] = infogain(data[attribute], target)

# Lista wyników
results = []
for attr in attributes:
    results.append({
        'Kolumna': attr,
        'Entropy': entropies[attr],
        'Info Gain': info_gains[attr]
    })

# Tworzenie DataFrame z wynikami
results_df = pd.DataFrame(results)

# Sortowanie DataFrame według przyrostu informacji
results_df = results_df.sort_values(by='Info Gain', ascending=False)

# Wyświetlanie tabeli
print(results_df)
print("________________________________________________________________________")