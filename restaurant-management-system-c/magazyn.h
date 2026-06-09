#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <malloc.h>
#include <time.h>
#include <locale.h>

#define BUFF 20
#define LICZBAPOLEK 10
#define LICZBAREGALOW 5


struct Produkty {
    char nazwa [BUFF];
    float ilosc;
    char jednostka [BUFF];
    char dostawca [BUFF];
    float wym_ilosc;
};

struct Polka{
    int stan;
    int l_przechowywanych_art;


};

struct Informacje{
    int powierzchnia;
    int temperatura;

};

struct Regal {
    int nr_regalu;
    struct Polka polka[LICZBAPOLEK];
};

struct Magazyn {
    struct Informacje informacje;
    struct Regal regal[LICZBAREGALOW];

};
