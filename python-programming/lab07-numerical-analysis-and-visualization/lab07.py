import numpy as np
import matplotlib.pyplot as plt

# ZADANIE 1
A = np.array([[1, -2, 0, 1],
              [0, 1, 1, -1],
              [3, 0, 0, 2],
              [1, 1, 1, 1]])

B = np.array([1, 3, 11, 10])
X = np.linalg.solve(A, B)

print(f"ZADANIE 1:Rozwiązanie układu równań:\nx1 = {X[0]:.2f}\nx2 = {X[1]:.2f}"
      f"\nx3 = {X[2]:.2f}\nx4 = {X[3]:.2f}")

# ZADANIE 2
def stworz_macierz(n):
    macierz = np.ones((n,n), dtype=int)
    for i in range(n):
        macierz[i, n-i-1] = n
    for i in range(n):
        for j in range(n):
            if i > n - j - 1:
                macierz[i, j] = -1
    return macierz

n = 4
wynik = stworz_macierz(n)
print ("ZADANIE 2:")
print (wynik)

# ZADANIE 3
def macierz_naprzemiennie(n):
    macierz = np.zeros((n, n), dtype=int)
    wartosc = 1
    for i in range(n):
        if i % 2 == 0:
            for j in range(n):
                macierz[i, j] = wartosc
                wartosc += 1
        else:
            for j in range(n - 1, -1, -1):
                macierz[i, j] = wartosc
                wartosc += 1

    return macierz
n = 4
result = macierz_naprzemiennie(n)
print("ZADANIE 3")
print(result)

# ZADANIE 4
def y(x):
    return np.sqrt(np.sin(x) + 2) / (np.abs(np.sin(x) + np.cos(x)) + 1)
x = np.linspace(-5, 5, 500)
y_values = y(x)
plt.figure()
plt.plot(x, y_values, label=r'$\frac{\sqrt{\sin(x) + 2}}{|\sin(x) + \cos(x)| + 1}$')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Wykres funkcji y(x)')
plt.grid(True)
plt.show()

# ZADANIE 5
def y1(x):
    return np.sin(x) + np.cos(x)

def y2(x):
    return 0.01 * np.sin(x) * np.exp(x)

def y3(x):
    return np.cos(x) * np.log(np.abs(x) + 1)

x = np.linspace(-2 * np.pi, 2 * np.pi, 500)
y1_values = y1(x)
y2_values = y2(x)
y3_values = y3(x)
plt.figure()
plt.plot(x, y1_values, 'r-', label=r'$\sin(x) + \cos(x)$')
plt.plot(x, y2_values, 'b--', label=r'$0.01 \cdot \sin(x) \cdot \exp(x)$')
plt.plot(x, y3_values, 'g-.', label=r'$\cos(x) \cdot \ln(|x| + 1)$')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Wykresy trzech funkcji')
plt.grid(True)
plt.show()

# ZADANIE 6
def y(x, k):
    return np.exp(np.cos(k * x) + 1) / (np.abs(x) + 1)

x = np.linspace(-2 * np.pi, 2 * np.pi, 500)
plt.figure()
k_values = np.arange(1, 2.05, 0.05)
for k in k_values:
    y_values = y(x, k)
    plt.plot(x, y_values, label=f'k={k:.2f}')

plt.xlabel('x')
plt.ylabel('y')
plt.title('Rodzina funkcji y(x) dla różnych wartości k')
plt.legend(loc='upper right', fontsize='small', ncol=2)
plt.grid(True)
plt.show()

# ZADANIE 7
def z(x, y):
    return (np.sin(x * y)**2 + np.cos(x + y)**2) / (np.abs(x) + np.abs(y) + 1)
x = np.linspace(-np.pi / 2, np.pi / 2, 100)
y = np.linspace(-np.pi / 2, np.pi / 2, 100)
x, y = np.meshgrid(x, y)
z_values = z(x, y)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(x, y, z_values, cmap='viridis', edgecolor='none')
ax.set_title('Wykres funkcji $z(x, y)$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=5)
plt.show()

# ZADANIE 8
def z(x, y):
    return np.sin(x + y) + np.cos(x - y)

x = np.linspace(-2 * np.pi, 2 * np.pi, 100)
y = np.linspace(-2 * np.pi, 2 * np.pi, 100)
x, y = np.meshgrid(x, y)
z_values = z(x, y)
plt.figure()
cp = plt.contourf(x, y, z_values, cmap='viridis')
plt.colorbar(cp)
plt.title(r'Wykres poziomicowy funkcji $z(x, y) = \ sin(x + y) + \cos(x - y)$')
plt.xlabel('x')
plt.ylabel('y')
plt.show()

# ZADANIE 9
M = np.loadtxt('dane_lab_7.txt')
rows, cols = M.shape
print(f"Liczba wierszy: {rows}, Liczba kolumn: {cols}")
min_values = M.min(axis=0)
max_values = M.max(axis=0)
mean_values = M.mean(axis=0)
print(f"Najmniejsze wartości w kolumnach: {min_values}")
print(f"Największe wartości w kolumnach: {max_values}")
print(f"Średnie wartości w kolumnach: {mean_values}")
plt.figure()
plt.scatter(M[:, 1], M[:, 2], c='blue', label='Kolumna 2 vs Kolumna 3')
plt.xlabel('Kolumna 2')
plt.ylabel('Kolumna 3')
plt.title('Wykres punktowy: Kolumna 2 vs Kolumna 3')
plt.legend()
plt.grid(True)
plt.savefig('wykres_punktowy.png')
plt.show()
fig, axs = plt.subplots(cols, cols, figsize=(15, 15))
fig.suptitle('Wzajemne zależności pomiędzy kolumnami')

for i in range(cols):
    for j in range(cols):
        axs[i, j].scatter(M[:, j], M[:, i])
        if i == cols - 1:
            axs[i, j].set_xlabel(f'Kolumna {j+1}')
        if j == 0:
            axs[i, j].set_ylabel(f'Kolumna {i+1}')
        axs[i, j].grid(True)

plt.tight_layout()
plt.subplots_adjust(top=0.95)
plt.show()