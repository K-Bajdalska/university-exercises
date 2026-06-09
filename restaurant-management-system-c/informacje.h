#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#define TEXTBUFF 30


struct Restauracja {
    char nazwa [TEXTBUFF];
    char adres [TEXTBUFF];
    int nr_tel;
    char email [TEXTBUFF];
    char typ_kuchni [TEXTBUFF];
    int powierzchnia;
    int l_stolikow;
    int rok_zalozenia;
    int wymagana_l_pracownikow;
    int l_pracownikow;
    int ocz_dochod_mies;
    int dochod_mies;
    int ocz_dochod_roczny;
    int dochod_roczny;

};
