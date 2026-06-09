#include "dostawcy.h"

enum Menu_dostawcy { WYJSCIE = 0, WYSWIETLENIE = 1, STATYSTYKA = 2,
            OCENY = 3, DODAJ = 4, USUN = 5};

static enum Menu_dostawcy wybierz(){
    //Menu dzialu dostawcy dla Szefa i Managera
    const char menu_naglowek[] = { "|==================== DOSTAWCY ====================|"};
    const char ozdoba[] = { "|--------------------------------------------------|" };
    const char menu_lista[][50]= {"1. Wyswietl dostawcow", "2. Statystyka dostawcow","3. Oceny dostawcow",
                                    "4. Dodaj nowego dostawce", "5. Usun dostawce", "0. Powrot"};
    int c = 10;
    char znak;
    size_t elementy  = (sizeof(menu_lista)/sizeof(menu_lista[0]));
    while(c < 0 || c > 5){
        system("cls");
        printf("%s\n\n", menu_naglowek);
        for(size_t i=1; i<= elementy; i++){
            printf("  %s \n", menu_lista[i-1]);
            printf("%s\n", ozdoba);
        }
        scanf("%d", &c);
        znak=getchar();
    }
    return c;
}

static int licz();
static void stworz(struct Dostawcy*** dostawca, int ilosc);
static void pobierz (struct Dostawcy* const* dostawca, const int ilosc);
static void wyswietl(struct Dostawcy * const * const dostawca, int ilosc, int upr);
static void statystyka(struct Dostawcy* const* dostawca, const int ilosc);
static void oceny(struct Dostawcy* const* dostawca, const int ilosc);
static void dodaj(struct Dostawcy*** dostawca, int *ilosc);
static void usun_jednego(struct Dostawcy*** dostawca, int *ilosc);
static void usun(struct Dostawcy*** dostawca, int ilosc);

void dostawcy(int upr){
    //Zliczanie liczby dostawcow i pobieranie ich danych z pliku
    int wybor, ilosc;
    ilosc = licz();
    struct Dostawcy** dostawca = NULL;
    stworz(&dostawca, ilosc);
    pobierz(dostawca, ilosc);
    if (upr == 1 || upr == 2) {
            do {
            //Wywolanie funkcji z menu dla Szefa i Managera, ktora zwraca wartosc przekazywana nastepnie do instrukcji switch
            wybor = wybierz();
            switch(wybor){
                case WYSWIETLENIE: wyswietl(dostawca, ilosc, 1); break;
                case STATYSTYKA: statystyka(dostawca, ilosc); break;
                case OCENY: oceny(dostawca, ilosc); break;
                case DODAJ: dodaj(&dostawca, &ilosc); dostawcy(1); break;
                case USUN: wyswietl(dostawca, ilosc, 1); usun_jednego(&dostawca, &ilosc);break;
            }
            }while (wybor != WYJSCIE);
    }
    else {
        //Wywolanie funkcji wyswietl z liczba 3(okrojona liczba informacji o dostawcach przeznaczona dla Kelnera i Kucharza)
        system("cls");
        wyswietl(dostawca, ilosc, 3);
    }
    usun(&dostawca, ilosc);
}

static int licz() {
    int c, linie = 0;
    FILE* fp;
    fp = fopen("dostawcy.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    while((c = fgetc(fp)) != EOF){
        if(c == '\n') ++linie;}
    return linie;
}

static void stworz(struct Dostawcy*** dostawca, int ilosc){
    struct Dostawcy** temp = (struct Dostawcy **) malloc (sizeof(struct Dostawcy*) * ilosc);
    for(int i = 0; i<ilosc;i++){
        temp[i] = (struct Dostawcy *) malloc(sizeof(struct Dostawcy));
    }
    *dostawca = temp;

}

static void pobierz (struct Dostawcy* const* dostawca, const int ilosc) {
    char nazwa [BUFF3];
    int telefon;
    char typ_produktu [BUFF3];
    char dzien_dostawy[BUFF3];
    int termin_platnosci;
    int znizka;
    int lata_wsp;
    int ogolna_l_dostaw;
    int l_reklamacji;
    //pobranie danych z pliku
    FILE *fp;
    fp = fopen("dostawcy.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    for(int i=0; i<ilosc; i++){
    fscanf(fp,"%s %d %s %s %d %d %d %d %d", nazwa, &telefon, typ_produktu, dzien_dostawy, &termin_platnosci, &znizka,
           &lata_wsp, &ogolna_l_dostaw, &l_reklamacji );
    strcpy(dostawca[i]->nazwa, nazwa);
    dostawca[i]->telefon = telefon;
    strcpy(dostawca[i]->typ_produktu, typ_produktu);
    strcpy(dostawca[i]->dzien_dostawy, dzien_dostawy);
    dostawca[i]->termin_platnosci = termin_platnosci;
    dostawca[i]->znizka = znizka;
    dostawca[i]->lata_wsp = lata_wsp;
    dostawca[i]->ogolna_l_dostaw = ogolna_l_dostaw;
    dostawca[i]->l_reklamacji = l_reklamacji;
    }
    fclose(fp);
}

static void wyswietl(struct Dostawcy * const * const dostawca, int ilosc, int upr) {
    //Wyswietlanie odpowiedniej liczby informacji - zaleznej od poziomu posiadanych uprawnien
    const char naglowek[] = { "==================== INFORMACJE O DOSTAWCACH ====================\n\n"};
    const char elementy[][50]= {"Numer do centrali", "Typ produktow","Termin platnosci faktury",
                                    "Dzien dostawy", "Znizka lojalnosciowa", "Lata wspolpracy"};
    system("cls");
    printf("%s", naglowek);
    if (upr == 1 || upr == 2) {
        //Wszystkie informacje dla Szefa i Managera
        char p = 37;
        for(int i=0; i< ilosc;i++) {
        printf("%d  ~~~~~~~~ %s ~~~~~~~~\n%s: %d  %s:%s \n%s: %d dni  ", i+1,
               dostawca[i]->nazwa, elementy[0], dostawca[i]->telefon, elementy[1],
                dostawca[i]->typ_produktu, elementy[2], dostawca[i]->termin_platnosci);
        printf("%s: %s  \n%s: %d%c  %s: %d\n\n", elementy[3],
               dostawca[i]->dzien_dostawy, elementy[4], dostawca[i]->znizka, p, elementy[5],
                dostawca[i]->lata_wsp);
    }
    }
    else {
            //Okrojone informacje dla Kelnera i Kucharza
            for(int i=0; i< ilosc;i++) {
                printf("~~~~~~~~ %s ~~~~~~ ~~\n%s: %d  %s:%s  %s: %s\n\n",
               dostawca[i]->nazwa,elementy[0], dostawca[i]->telefon, elementy[1], dostawca[i]->typ_produktu,
               elementy[3],dostawca[i]->dzien_dostawy);
    }
    }
    getchar();
}

static void statystyka(struct Dostawcy* const* dostawca, const int ilosc){
    //Funkcja zliczajaca srednie dane w poszczegolnych kategoriach i wyswietla czy sa one zgodne z ustalonymi normami
    const char naglowek[] = { "==================== STATYSTYKA DOSTAWCOW ====================\n\n"};
    system("cls");
    printf("%s", naglowek);
    const char elementy[][50]= {"Termin platnosci Faktur VAT", "Znizka lojalnosciowa","Lata wspolpracy",
                                    "Ogolna liczba dostaw", "Liczba reklamacji"};
    double srednia = 0;
    int najmniejsza = 100;
    char *nazwa1 [BUFF3];
    int najwieksza = 0;
    char *nazwa2 [BUFF3];
    //Termin platnosci Faktur Vat
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
    printf("1. %s:", elementy[0]);
    printf("\nSredni:%.2lf      Najdluzszy:%d (%s)      Najkrotszy:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(najmniejsza < 4) {
        printf("\n----> Bardzo krotki czas na oplacenie faktury z firmy %s! Sprobuj renegocjowac warunki! <----", *nazwa1);
    }
    if(srednia < 7){
        printf("\n----> Niski sredni termin platnosci faktur VAT! Sprobuj renegocjowac warunki! <----");
    }
    else{
        printf("\n----> Prawidlowy sredni termin platnosci faktur VAT. Tak trzymac! <----");
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
    printf("\n\n2. %s: ", elementy[1]);
    printf("\nSrednia:%.2lf%c      Najwieksza:%d%c (%s)      Najmniejsza:%d%c (%s)", srednia,p, najwieksza,p, *nazwa2, najmniejsza,p, *nazwa1);
    if(srednia < 6) {
        printf("\n----> Bardzo niska srednia znizka lojalnosciowa! Sprobuj renegocjowac warunki! <----");
    }
    else {
        printf("\n----> Prawidlowa srednia znizka lojalnosciowa. Tak trzymac! <----");
    }
    if(najmniejsza < 2) {
        printf("\n----> Bardzo niska znizka w firmie %s! Sprobuj renegocjowac warunki! <----", *nazwa1);
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
    printf("\n\n3. %s: ", elementy[2]);
    printf("\nSrednio:%.2lf      Najdluzej:%d (%s)      Najkrocej:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia < 5) {
        printf("\n----> Niska srednia liczba lat wspolpracy! Postaraj sie nawiazywac dlugotrwale realcje z dostawcami!----");
    }
    else {
        printf("\n----> Prawidlowa srednia liczba lat wspolpracy! Tak trzymac! <----");
    }
    printf("\n----> Zwroc uwage na wspolprace z firma %s! To dostawca z ktorym wspolpracujemy najdluzej.", *nazwa2);
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
    printf("\n\n4. %s:", elementy[3]);
    printf("\nSrednio:%.0lf      Najwiecej:%d (%s)      Najmniej:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    printf("\n----> Zwroc uwage na wspolprace z firma %s! To dostawca ktory zrealizowal najwiecej zlecen.", *nazwa2);
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
    printf("\n\n5. %s:", elementy[4]);
    printf("\nSrednio:%.2lf      Najwiecej:%d (%s)      Najmniej:%d (%s)", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    getchar();
}

static void oceny(struct Dostawcy* const* dostawca, const int ilosc){
    //Funkcja dokonujaca indywidualnej oceny i porownania wszystkich dostawcow
    const char naglowek[] = { "==================== OCENA DOSTAWCOW ====================\n"};
    const char elementy[][50] = {"przyznane punkty", "Termin platnosci faktury (WAGA1)", "Znizka lojalnosciowa na lata wspolpracy (WAGA 2)",
                                "Lata wspolpracy (WAGA 2)","Liczba dostaw na lata wspolpracy (WAGA 3)","Wskaznik reklamacji (WAGA 3)",
                                "OCENA OGOLNA" };
    system("cls");
    printf("%s", naglowek);
    int punkty, suma_punktow_waga, waga, suma_waga;
    char p = 37;
    char *najlepszy[BUFF3];
    char *najgorszy [BUFF3];
    double wynik_najlepszy, wynik_najgorszy;
    wynik_najlepszy = 0;
    wynik_najgorszy = 100;
    for(int i=0; i<ilosc; i++){
            printf("\n\n~~~~~~~~ %s ~~~~~~~~", dostawca[i]->nazwa);
            punkty = 0;
            waga = 0;
            suma_punktow_waga = 0;
            suma_waga = 0;
            //punkty za termin platnosci faktury VAT
            if (dostawca[i]->termin_platnosci <= 5) {punkty = 1;}
            else if(dostawca[i]->termin_platnosci > 5 && dostawca[i]->termin_platnosci <= 10) {punkty = 2;}
            else if(dostawca[i]->termin_platnosci > 10) {punkty = 3;}
            waga = 1;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %d,  %s: %d", elementy[1], dostawca[i]->termin_platnosci, elementy[0], (punkty * waga));
            //punkty za wskaznik znizki lojalnosciowej (znizka/lata wspolpracy)
            if ((dostawca[i]->znizka)/(dostawca[i]->lata_wsp) <= 0.6) {punkty = 1;}
            else if((((float)dostawca[i]->znizka)/(float)(dostawca[i]->lata_wsp)) > 0.6 && (((float)(dostawca[i]->znizka)/(float)(dostawca[i]->lata_wsp))) <= 1.2) {punkty = 2;}
            else if((((float)dostawca[i]->znizka)/(float)(dostawca[i]->lata_wsp)) > 1.2) {punkty = 3;}
            waga = 2;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %d,  %s: %d",elementy[2], dostawca[i]->znizka, elementy[0], (punkty * waga));
            //punkty za lata wspolpracy
            if (dostawca[i]->lata_wsp <= 4) {punkty = 1;}
            else if(dostawca[i]->lata_wsp > 4 && dostawca[i]->lata_wsp <= 10) {punkty = 2;}
            else if(dostawca[i]->lata_wsp > 10) {punkty = 3;}
            waga = 2;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %d,  %s: %d", elementy[3], dostawca[i]->lata_wsp, elementy[0], (punkty * waga));
            //punkty za wskaznik liczby dostaw (liczba dostaw / lata wspolpracy
            if ((dostawca[i]->ogolna_l_dostaw/dostawca[i]->lata_wsp) <= 50) {punkty = 1;}
            else if((dostawca[i]->ogolna_l_dostaw/dostawca[i]->lata_wsp) > 50 && (dostawca[i]->ogolna_l_dostaw/dostawca[i]->lata_wsp) <= 52) {punkty = 2;}
            else if(dostawca[i]->ogolna_l_dostaw/dostawca[i]->lata_wsp > 52) {punkty = 3;}
            waga = 3;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %d,  %s: %d", elementy[4], dostawca[i]->ogolna_l_dostaw/dostawca[i]->lata_wsp, elementy[0], (punkty * waga));
            //punkty za wskaznik reklamacji (liczba reklamacji / liczba dostaw)
            if (((dostawca[i]->l_reklamacji)*100/dostawca[i]->ogolna_l_dostaw) >= 5 ) {punkty = 1;}
            else if (((dostawca[i]->l_reklamacji)*100/dostawca[i]->ogolna_l_dostaw) < 5
                     && ((dostawca[i]->l_reklamacji)*100/dostawca[i]->ogolna_l_dostaw) >= 3 ) {punkty = 2;}
            else if(((dostawca[i]->l_reklamacji)*100/dostawca[i]->ogolna_l_dostaw) < 3 ) {punkty = 3;}
            waga = 3;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %d%c,  %s: %d", elementy[5], dostawca[i]->l_reklamacji*100/dostawca[i]->ogolna_l_dostaw,
                    p, elementy[0], (punkty * waga));
            //Ocena ogolna
            double ogolna;
            ogolna = 0;
            ogolna = ((double)(suma_punktow_waga))/((double)(suma_waga));
            printf("\n%s:  %.2lf", elementy[6], ogolna);
            if (ogolna > wynik_najlepszy) {
                    wynik_najlepszy = ogolna;
                    *najlepszy = dostawca[i]->nazwa;}
            if (ogolna < wynik_najgorszy) {
                wynik_najgorszy = ogolna;
                *najgorszy = dostawca[i]->nazwa;}

    }
    printf("\n\n =========== Z ocen wynika, ze: ");
    printf("\n\n ----------> Najlepiej oceniony dostawca to: %s", *najlepszy);
    printf("\n\n ----------> Najgorzej oceniony dostawca to: %s", *najgorszy);
    getchar();
}

static void dodaj(struct Dostawcy*** dostawca, int *ilosc){
    //Dodanie nowego dostawcy i wpisanie jego danych do pliku
    int new_size = *ilosc + 1;
    struct Dostawcy** temp =(struct Dostawcy **)malloc(sizeof(struct Dostawcy*)*(new_size));
    for(int i=0; i<*ilosc;++i){
        temp[i] = (*dostawca)[i];
    }
    temp[*ilosc] = (struct Dostawcy *) malloc(sizeof(struct Dostawcy));
    const char naglowek[] = { "|==================== DODAWANIE NOWEGO DOSTAWCY ====================|\n\n"};
    const char komunikat[] = {"Prosze wpisywac wszystkie dane bez spacji (w razie potrzeby zamiast niej uzyc '-')"};
    const char elementy [][50] = {"Nazwa dostawcy", "Telefon do centrali", "Typ produktu", "Dzien dostawy", "Termin platnosci faktury Vat:",
                                    "Znizka lojalnosciowa", "Lata wspolpracy", "Liczba zrealizowanych dostaw", "Liczba reklamacji"};
    char nazwa [BUFF3];
    int telefon;
    char typ_produktu [BUFF3];
    char dzien_dostawy [BUFF3];
    int termin_platnosci;
    int znizka;
    int lata_wsp;
    int ogolna_l_dostaw;
    int l_reklamacji;
    system("cls");
    printf("%s", naglowek);
    printf("------> %s\n", komunikat);
    printf("\n~~ %s: ", elementy[0]);
    scanf("%s", nazwa);
    printf("\n\n~~ %s: ", elementy[1]);
    scanf("%d", &telefon);
    printf("\n\n~~ %s: ", elementy[2]);
    scanf("%s", typ_produktu);
    printf("\n\n~~ %s: ", elementy[3]);
    scanf("%s", dzien_dostawy);
    printf("\n\n~~ %s: ", elementy[4]);
    scanf("%d", &termin_platnosci);
    printf("\n\n~~ %s: ", elementy[5]);
    scanf("%d", &znizka);
    printf("\n\n~~ %s: ", elementy[6]);
    scanf("%d", &lata_wsp);
    printf("\n\n~~ %s: ", elementy[7]);
    scanf("%d", &ogolna_l_dostaw);
    printf("\n\n~~ %s: ", elementy[8]);
    scanf("%d", &l_reklamacji);
    strcpy(temp[*ilosc]->nazwa, nazwa);
    temp[*ilosc]->telefon = telefon;
    strcpy(temp[*ilosc]->typ_produktu, typ_produktu);
    strcpy(temp[*ilosc]->dzien_dostawy, dzien_dostawy);
    temp[*ilosc]->termin_platnosci = termin_platnosci;
    temp[*ilosc]->znizka = znizka;
    temp[*ilosc]->lata_wsp = lata_wsp;
    temp[*ilosc]->ogolna_l_dostaw = ogolna_l_dostaw;
    temp[*ilosc]->l_reklamacji = l_reklamacji;
    FILE *fp;
    fp = fopen("dostawcy.txt","a");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
        fprintf(fp, "\n%s %d %s %s %d %d %d %d %d", temp[*ilosc]->nazwa, temp[*ilosc]->telefon, temp[*ilosc]->typ_produktu,
                temp[*ilosc]->dzien_dostawy, temp[*ilosc]->termin_platnosci, temp[*ilosc]->znizka, temp[*ilosc]->lata_wsp,
                temp[*ilosc]->ogolna_l_dostaw, temp[*ilosc]->l_reklamacji);
    fclose(fp);
    free(*dostawca);
    *dostawca = temp;
    ++(*ilosc);
}

static void usun_jednego(struct Dostawcy*** dostawca, int *ilosc){
    const char naglowek[] = { "====================== USUN DOSTAWCE ======================"};
    int j = 0, wybor;
    char znak;
    printf("\n\n%s\n\n", naglowek);
    printf("Wybierz numer dostawcy, ktorego chcesz usunac z bazy: ");
    scanf("%d", &wybor);
    znak=getchar();
    int new_size = *ilosc - 1;
    struct Dostawcy** temp =(struct Dostawcy **)malloc(sizeof(struct Dostawcy*)*(new_size));
    for(int i=0; i < *ilosc; ++i){
            if (i != wybor - 1){
            temp[j] = (*dostawca)[i];
            j++;}
    }
    FILE *fp;
    fp = fopen("dostawcy.txt","w");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    for(int i=0; i<new_size; i++){
    fprintf (fp, "%s %d %s %s %d %d %d %d %d\n", temp[i]->nazwa, temp[i]->telefon, temp[i]->typ_produktu,
                temp[i]->dzien_dostawy, temp[i]->termin_platnosci, temp[i]->znizka, temp[i]->lata_wsp,
                temp[i]->ogolna_l_dostaw, temp[i]->l_reklamacji);
    }
    fclose(fp);
    free(*dostawca);
    *dostawca = temp;
    --(*ilosc);
}

static void usun(struct Dostawcy*** dostawca, int ilosc){
    for(int i=0; i<ilosc; i++){
        free((*dostawca)[i]);
        (*dostawca)[i] = NULL;
    }
    free (*dostawca);
    *dostawca = NULL;
}





