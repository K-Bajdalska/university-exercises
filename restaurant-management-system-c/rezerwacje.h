#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF4 20

struct Dane {
    char nazwisko[BUFF4];
    int nr_tel;
    int dzien;
    int miesiac;
    int rok;
    double godzina;
    int l_osob;

};

struct Stolik {
    int nr;
    char miejsce[BUFF4];


};

struct Rezerwacja {
    struct Dane dane;
    struct Stolik stolik;
};
