import math

class Liczba_wymierna:

    def __init__(self, calkowita:int, licznik: int, mianownik: int):
        self.licznik = calkowita*mianownik + licznik
        self.mianownik = mianownik

        nwd = math.gcd(self.licznik, self.mianownik)

        if nwd > 1:
            self.licznik = self.licznik // nwd
            self.mianownik = self.mianownik // nwd

    def __str__(self):
        calkowita = self.licznik // self.mianownik
        licznik = self.licznik % self.mianownik
        mianownik = self.mianownik

        if licznik == 0:
            return f"{calkowita}"
        else:
            return f"{calkowita} i {licznik}/{mianownik}"

    def __repr__(self):
        calkowita = self.licznik // self.mianownik
        licznik = self.licznik % self.mianownik
        return f"{type(self).__name__} ({calkowita}, {licznik}, {self.mianownik})"

    def __eq__(self, inna ):
        if isinstance(inna, int):
            inna = Liczba_wymierna(inna, 0, 1)

        if isinstance(inna, Liczba_wymierna):
            return self.licznik * inna.mianownik == inna.licznik * self.mianownik

        return False

    def __add__(self, inna):
        if isinstance(inna, Liczba_wymierna):
            licznik = self.licznik * inna.mianownik + inna.licznik * self.mianownik
            mianownik = self.mianownik * inna.mianownik
            return Liczba_wymierna(0, licznik, mianownik)

        elif isinstance(inna, int):
            licznik = self.licznik + inna * self.mianownik
            return Liczba_wymierna(0, licznik, self.mianownik)

    def __radd__(self, inna):
        return self.__add__(inna)

    def __mul__(self, inna):
        if isinstance(inna, Liczba_wymierna):
            licznik = self.licznik * inna.licznik
            mianownik = self.mianownik * inna.mianownik
            return Liczba_wymierna(0, licznik, mianownik)

        elif isinstance(inna, int):
            licznik=self.licznik * inna
            return Liczba_wymierna(0, licznik, self.mianownik)

    def __rmul__(self, inna):
        return  self.__mul__(inna)

    def __truediv__(self, inna):
        if isinstance(inna, Liczba_wymierna):
            licznik = self.licznik * inna.mianownik
            mianownik = self.mianownik * inna.licznik
            return Liczba_wymierna(0, licznik, mianownik)

        elif isinstance(inna, int):
            if inna == 0:
                print("Nie mozna dzielic przez 0")
            else:
                licznik = self.licznik
                mianownik = self.mianownik * inna
                return Liczba_wymierna(0, licznik, mianownik)

    def __rtruediv__(self, inna):
        if isinstance(inna, int):
            licznik = inna * self.mianownik
            mianownik = self.licznik
            return Liczba_wymierna(0, licznik, mianownik)

    def __pow__(self, potega):
        licznik = self.licznik ** potega
        mianownik = self.mianownik ** potega
        return Liczba_wymierna(0, licznik, mianownik)

    def ul_niewlasciwy(self):
        return f"{self.licznik}/{self.mianownik}"

    def __bool__(self):
        return self.licznik != 0

    def __int__(self):
        return self.licznik // self.mianownik

    def __float__(self):
        return self.licznik / self.mianownik