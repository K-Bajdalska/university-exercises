#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <malloc.h>

#define INFOBUFF 300
#define BUFF1 20
#define BUFF2 40
#define koszt_uz_przychodu 250


struct Pracownicy {
    char imie[BUFF1];
    char nazwisko[BUFF1];
    int tel;
    char stanowisko [BUFF2];
    int rok_ur;
    double staz;
    double pensja;
    int pochwaly;
    int skargi;
    int spoznienia;
    double samoocena;
    double ocena_szefa;
    double ocena_wspolpracownikow;
};


