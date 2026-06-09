#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "zaloguj.h"
#include "informacje.h"
#include "pracownicy.h"
#include "magazyn.h"
#include "dostawcy.h"



enum Menu { WYJSCIE = 0, INFORMACJE = 1, PRACOWNICY = 2,
            MAGAZYN = 3, DOSTAWCY = 4};


static enum Menu wybierz();


int main()
{
    static int uprawnienia;
    const char ozdoba[] = {"========================================================"};
    const char przywitanie[] = {"Witaj w panelu zarzadzania restauracja ROSSO FUOCO *****"};
    //przywitanie i wywolanie funkcji zaloguj
    printf("%s\n%s\n%s\n", ozdoba, przywitanie, ozdoba);
    uprawnienia = zaloguj();
    //po poprawnym zalogowaniu wyswietlenie poziomu uprawnien i menu
    int wybor;
    do {
       wybor = wybierz(uprawnienia);
        switch(wybor) {
            case INFORMACJE: informacje(uprawnienia); break;
            case PRACOWNICY: pracownicy(uprawnienia); break;
            case MAGAZYN: magazyn(); break;
            case DOSTAWCY: dostawcy(uprawnienia); break;
        }
    }while(wybor != WYJSCIE);
    return 0;
}

static enum Menu wybierz(int uprawnienia){
    int c = 10;
    char znak;
    const char komunikat[][80] = {"Witaj w panelu zarzadzania restauracja ROSSO FUOCO *****","Posiadasz uprawnienia na poziomie: "};
    const char ozdoba[] = {"========================================================"};
    const char menu_naglowek[] = { "|======================== MENU ========================|"};
    const char ozdoba2[] = { "|------------------------------------------------------|" };
    const char menu_lista[][50]= {"1. Informacje o restauracji", "2. Pracownicy","3. Stany magazynowe",
                                    "4. Dostawcy", "0. Wyjscie"};
    size_t elementy  = (sizeof(menu_lista)/sizeof(menu_lista[0]));
    while(c < 0 || c > 4){
        system("cls");
        printf("%s\n%s\n%s: %d\n%s\n\n", ozdoba, komunikat[0], komunikat[1], uprawnienia, ozdoba);
        printf("%s\n", menu_naglowek);
        for(size_t i=1; i<= elementy; i++){
            printf("\n  %s \n", menu_lista[i-1]);
            printf("%s\n", ozdoba2);
        }
        puts("\n\nCo chcesz zrobic? ");
        scanf("%d", &c);
        znak=getchar();
    }
    return c;
}
