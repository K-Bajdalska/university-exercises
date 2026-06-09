#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <malloc.h>
#define BUFF3 30

struct Dostawcy {
    char nazwa [BUFF3];
    int telefon;
    char typ_produktu [BUFF3];
    char dzien_dostawy [BUFF3];
    int termin_platnosci;
    int znizka;
    int lata_wsp;
    int ogolna_l_dostaw;
    int l_reklamacji;
};
