static void statystyka(struct Dostawcy* const* dostawca, const int ilosc){
    double srednia = 0;
    int najmniejsza = 100;
    char *nazwa1 [BUFF3];
    int najwieksza = 0;
    char *nazwa2 [BUFF3];
    //Termin platnosci
    for(int i=0; i<ilosc; i++){
        srednia += dostawca[i]-> termin_platnosci;
        if(dostawca[i]-> termin_platnosci < najmniejsza) {
                najmniejsza = dostawca[i]-> termin_platnosci;
                *nazwa1 = dostawca[i]->nazwa;}
        if(dostawca[i]-> termin_platnosci > najwieksza) {
                najwieksza = dostawca[i]-> termin_platnosci;
                *nazwa2 = dostawca[i]-> nazwa;}
    }
    srednia = srednia/ilosc;
    system("cls");
    printf("1. Termin platnosci Faktur VAT:");
    printf("\nSredni:%.2lf      Najdluzszy:%d (%s)      Najkrotszy:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(najmniejsza < 4) {
        printf("\n----Bardzo krotki czas na oplacenie faktury z firmy %s! Sprobuj renegocjowac warunki!----", *nazwa1);
    }
    srednia = 0.00;
    najwieksza = 0;
    najmniejsza = 1000;
    //Znizki
    char p = 37;
    for(int i=0; i<ilosc; i++){
        srednia += dostawca[i]-> znizka;
        if(dostawca[i]-> znizka < najmniejsza) {
                najmniejsza = dostawca[i]-> znizka;
                *nazwa1 = dostawca[i]->nazwa;}
        if(dostawca[i]-> znizka > najwieksza) {
                najwieksza = dostawca[i]-> znizka;
                *nazwa2 = dostawca[i]-> nazwa;}
    }
    srednia = srednia/ilosc;
    printf("\n\n2. Znizka lojalnosciowa: ");
    printf("\nSrednia:%.2lf%c      Najwieksza:%d%c (%s)      Najmniejsza:%d%c (%s)", srednia,p, najwieksza,p, *nazwa2, najmniejsza,p, *nazwa1);
    if(srednia < 6) {
        printf("\n----Bardzo niska srednia znizka lojalnosciowa! Sprobuj renegocjowac warunki!----");
    }
    if(najmniejsza < 2) {
        printf("\n----Bardzo niska znizka w firmie %s! Sprobuj renegocjowac warunki!----", *nazwa1);
    }
    srednia = 0.00;
    najwieksza = 0;
    najmniejsza = 1000;
    //Lata wspolpracy
    for(int i=0; i<ilosc; i++){
        srednia += dostawca[i]-> lata_wsp;
        if(dostawca[i]-> lata_wsp < najmniejsza) {
                najmniejsza = dostawca[i]-> lata_wsp;
                *nazwa1 = dostawca[i]->nazwa;}
        if(dostawca[i]-> lata_wsp > najwieksza) {
                najwieksza = dostawca[i]-> lata_wsp;
                *nazwa2 = dostawca[i]-> nazwa;}
    }
    srednia = srednia/ilosc;
    printf("\n\n3. Lata wspolpracy: ");
    printf("\nSrednio:%.2lf      Najdluzej:%d (%s)      Najkrocej:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia < 5) {
        printf("\n----Niska srednia liczba lat wspolpracy! Postaraj sie nawiazywac dlugotrwale realcje z dostawcami!----");
    }
    srednia = 0.00;
    najwieksza = 0;
    najmniejsza = 1000;
    //Ogolna liczba dostaw
    for(int i=0; i<ilosc; i++){
        srednia += dostawca[i]-> ogolna_l_dostaw;
        if(dostawca[i]-> ogolna_l_dostaw < najmniejsza) {
                najmniejsza = dostawca[i]-> ogolna_l_dostaw;
                *nazwa1 = dostawca[i]->nazwa;}
        if(dostawca[i]-> ogolna_l_dostaw > najwieksza) {
                najwieksza = dostawca[i]-> ogolna_l_dostaw;
                *nazwa2 = dostawca[i]-> nazwa;}
    }
    srednia = srednia/ilosc;
    printf("\n\n4. Ogolna liczba dostaw: ");
    printf("\nSrednio:%.0lf      Najwiecej:%d (%s)      Najmniej:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    srednia = 0.00;
    najwieksza = 0;
    najmniejsza = 1000;
    //Liczba reklamacji
    for(int i=0; i<ilosc; i++){
        srednia += dostawca[i]-> l_reklamacji;
        if(dostawca[i]-> l_reklamacji < najmniejsza) {
                najmniejsza = dostawca[i]-> l_reklamacji;
                *nazwa1 = dostawca[i]->nazwa;}
        if(dostawca[i]-> l_reklamacji > najwieksza) {
                najwieksza = dostawca[i]-> l_reklamacji;
                *nazwa2 = dostawca[i]-> nazwa;}
    }
    srednia = srednia/ilosc;
    printf("\n\n5. Liczba reklamacji: ");
    printf("\nSrednio:%.2lf      Najwiecej:%d (%s)      Najmniej:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    getchar();
}









/*static enum Menu_dostawcy wybierz(){
    const char menu_naglowek[] = { "==================== DOSTAWCY ====================\n\n"};
    const char menu_lista[][50]= {"1. Wyswietl dostawcow", "2. Statystyka dostawcow","3. Oceny dostwcow",
                                    "4. Dodaj nowego dostawce", "0. Powrot"};
    int c = 10;
    char *znak = (char*) malloc (sizeof(char));
    size_t elementy  = (sizeof(menu_lista)/sizeof(menu_lista[0]));
    while(c < 0 || c > 4){
        system("cls");
        printf(menu_naglowek);
        for(size_t i=1; i<= elementy; i++){
            printf("%s \n", menu_lista[i-1]);
        }
        scanf("%d", &c);
        *znak=getchar();
    }
    free(znak);
    return c;
}

static void wyswietl(struct Dostawcy * const * const dostawca, int ilosc, int upr) {
    const char wyswietlanie[][50]= {"Numer do centrali:", "Typ produktow: ","Termin platnosci faktury:",
                                    "Dzien dostawy", "Znizka lojalnosciowa", "Lata wspolpracy:"};
    if (upr == 1 || upr == 2) {
        char p = 37;
        for(int i=0; i< ilosc;i++) {
        printf("%s:\n%s: %d  %s:%s \n%s: %d dni  ",
               dostawca[i]->nazwa, wyswietlanie[0], dostawca[i]->telefon, wyswietlanie[1],
                dostawca[i]->typ_produktu, wyswietlanie[2], dostawca[i]->termin_platnosci);
        printf("%s: %s  \n%s: %d%c  %s: %d\n\n", wyswietlanie[3],
               dostawca[i]->dzien_dostawy, wyswietlanie[4], dostawca[i]->znizka, p, wyswietlanie[5],
                dostawca[i]->lata_wsp);
    }
    }
    else {
            for(int i=0; i< ilosc;i++) {
                printf("%s:\n%s: %d  %s:%s  %s: %s\n\n",
               dostawca[i]->nazwa,wyswietlanie[0], dostawca[i]->telefon, wyswietlanie[1], dostawca[i]->typ_produktu,
               wyswietlanie[3],dostawca[i]->dzien_dostawy);
    }
    }
    getchar();
}
*/
