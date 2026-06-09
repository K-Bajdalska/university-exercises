#include "pracownicy.h"

enum Menu_pracownicy1 { WYJSCIE = 0, WYSWIETLENIE = 1, STATYSTYKA = 2,
            OCENY = 3, DODAJ = 4, USUN = 5, KALKULATOR = 6};

enum Menu_pracownicy2 { WYJSCIEE = 0, INFORMATOR = 1, KALKULATORR = 2};

static int licz();
static void pobierz(struct Pracownicy* const* pracownik, const int ilosc);
static void wyswietl(struct Pracownicy * const * const pracownik, int ilosc);
static void statystyka(struct Pracownicy* const* pracownik, const int ilosc);
static void oceny(struct Pracownicy* const* pracownik, const int ilosc);
static void dodaj(struct Pracownicy*** pracownik, int *ilosc);
static void usun_jednego(struct Pracownicy*** pracownik, int *ilosc);
static void kalkulator();
static void informator();
static void usun(struct Pracownicy*** pracownik, int ilosc);

static void stworz(struct Pracownik*** pracownik, int ilosc){
    struct Pracownicy** temp = (struct Pracownicy **) malloc (sizeof(struct pracownicy*) * ilosc);
    for(int i = 0; i<ilosc;i++){
        temp[i] = (struct Pracownicy *) malloc(sizeof(struct Pracownicy));
    }
    *pracownik = temp;
}

static enum Menu_pracownicy1 wybierz(){
    //Menu dla Szefa i Managera
    int c = 10;
    char znak;
    const char menu_naglowek[] = { "|==================== PRACOWNICY ====================|\n"};
    const char ozdoba[] = { "|----------------------------------------------------|" };
    const char menu_lista[][50]= {"1. Wyswietl pracownikow", "2. Statystyka pracownikow","3. Oceny pracownikow",
                                    "4. Dodaj nowego pracownika", "5. Usun pracownika","6. Kalkulator wynagrodzen", "0. Powrot"};
    size_t elementy  = (sizeof(menu_lista)/sizeof(menu_lista[0]));
    while(c < 0 || c > 6){
        system("cls");
        printf(menu_naglowek);
        for(size_t i=1; i<= elementy; i++){
            printf("  %s \n", menu_lista[i-1]);
            printf("%s\n", ozdoba);
        }
        scanf("%d", &c);
        znak=getchar();
    }
    return c;
}

static enum Menu_pracownicy2 wybierzz(){
    //Menu dla Kucharza i Kelnera
    int c = 10;
    char znak;
    const char menu_naglowek[] = { "|==================== PRACOWNICY ====================|\n"};
    const char ozdoba[] = { "|----------------------------------------------------|" };
    const char menu_lista[][50]= {"1. Informator dla pracownikow", "2. Kalkulator wynagrodzen", "0. Powrot"};
    size_t elementy  = (sizeof(menu_lista)/sizeof(menu_lista[0]));
    while(c < 0 || c > 2){
        system("cls");
        printf(menu_naglowek);
        for(size_t i=1; i<= elementy; i++){
            printf("  %s \n", menu_lista[i-1]);
            printf("%s\n", ozdoba);
        }
        scanf("%d", &c);
        znak=getchar();
    }
    return c;
}



void pracownicy(int upr) {
//Zliczanie pracownikow, pobieranie ich danych z zewnetrznego pliku
    int ilosc = licz();
    struct Pracownicy** pracownik = NULL;
    stworz(&pracownik, ilosc);
    pobierz(pracownik, ilosc);
    if (upr == 1 || upr == 2) {
            int wybor;
            do {
                //Funkcja z menu dla Szefa i Managera (zwracajaca wybor uzytkownika i przekazujaca go do instrukcji switch)
                wybor = wybierz();
                switch(wybor){
                    //Wywolanie odpowiednich dla wyboru funkcji
                    case WYSWIETLENIE: wyswietl(pracownik, ilosc); break;
                    case STATYSTYKA: statystyka(pracownik, ilosc); break;
                    case OCENY: oceny(pracownik, ilosc); break;
                    case DODAJ: dodaj(&pracownik, &ilosc); break;
                    case USUN: wyswietl(pracownik, ilosc), usun_jednego(&pracownik, &ilosc);break;
                    case KALKULATOR: kalkulator(); break;
            }
            }while (wybor != WYJSCIE);
}
else {
    int wybor;
        do {
                //Funkcja z menu dla Kucharza i Kelnera (zwracajaca wybor uzytkownika i przekazujaca go do instrukcji switch)
                wybor = wybierzz();
                switch (wybor) {
                    //Wywolanie odpowiednich dla wyboru funkcji
                    case INFORMATOR: informator(); break;
                    case KALKULATORR: kalkulator(); break;
                }
            } while(wybor != WYJSCIEE);
            }
    usun (&pracownik, ilosc);
}

static int licz() {
    int c, linie = 0;
    FILE* fp;
    fp = fopen("pracownicy.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    while((c = fgetc(fp)) != EOF){
        if(c == '\n') ++linie;}

    return linie;
}

static void pobierz (struct Pracownicy* const* pracownik, const int ilosc) {
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
    //pobranie danych z pliku
    FILE *fp;
    fp = fopen("pracownicy.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    for(int i=0; i<ilosc; i++){
    fscanf(fp,"%s %s %d %s %d %lf %lf %d %d %d %lf %lf %lf", imie, nazwisko, &tel, stanowisko, &rok_ur, &staz, &pensja,
            &pochwaly, &skargi, &spoznienia, &samoocena, &ocena_szefa, &ocena_wspolpracownikow);
    strcpy(pracownik[i]->imie, imie);
    strcpy(pracownik[i]->nazwisko, nazwisko);
    pracownik[i]->tel = tel;
    strcpy(pracownik[i]->stanowisko, stanowisko);
    pracownik[i]->rok_ur = rok_ur;
    pracownik[i]->staz = staz;
    pracownik[i]->pensja = pensja;
    pracownik[i]->pochwaly = pochwaly;
    pracownik[i]->skargi = skargi;
    pracownik[i]->spoznienia = spoznienia;
    pracownik[i]->samoocena = samoocena;
    pracownik[i]->ocena_szefa = ocena_szefa;
    pracownik[i]->ocena_wspolpracownikow = ocena_wspolpracownikow;
    }
    fclose(fp);
}

static void wyswietl(struct Pracownicy * const * const pracownik, int ilosc) {
    const char naglowek[] = { "====================== WYSWIETL PRACOWNIKOW ======================"};
    const char ozdoba[] = { "--------------------------------------------------------------------" };
    system("cls");
    printf("%s\n\n", naglowek);
    for(int i=0; i< ilosc;i++) {
    printf("%d. %s %s:   Telefon:%d   Stanowisko: %s\nRok urodzenia: %d   Staz pracy:%.2lf   Pesja: %.2lf zl\n\n%s\n\n",
           i+1,pracownik[i]->imie, pracownik[i]->nazwisko, pracownik[i]->tel, pracownik[i]->stanowisko,
           pracownik[i]->rok_ur, pracownik[i]->staz, pracownik[i]->pensja, ozdoba);
    }
    getchar();
}

static void statystyka(struct Pracownicy* const* pracownik, const int ilosc){
    //Funkcja zliczajaca srednie dane w poszczegolnych kategoriach i wyswietla czy sa one zgodne z ustalonymi normami
    const char naglowek[] = { "============================ STATYSTYKA PRACOWNIKOW ============================"};
    const char elementy[][50]= {"ROK URODZENIA", "STAZ","PESJA","POCHWALY","SKARGI", "SPOZNIENIA","SAMOOCENA",
                                    "OCENA SZEFA", "OCENA WSPOLPRACOWNIKOW"};
    const char ozdoba[] = {"---------------------------------"};
    system("cls");
    printf("%s\n\n", naglowek);
    double srednia = 0.0;
    double najmniejsza = 10000.0;
    char *nazwa1 [BUFF1];
    double najwieksza = 0.0;
    char *nazwa2 [BUFF1];
    //Sredni wiek pracownikow
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> rok_ur;
        if(pracownik[i]-> rok_ur < najmniejsza) {
                najmniejsza = pracownik[i]-> rok_ur;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> rok_ur > najwieksza) {
                najwieksza = pracownik[i]-> rok_ur;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("%s %s %s", ozdoba, elementy[0], ozdoba);
    printf("\nSredni:%.0lf      Najwiekszy:%.0lf (%s)      Najmniejszy:%.0lf (%s)\n", srednia, najmniejsza, *nazwa1, najwieksza, *nazwa2);
    if(srednia < 1990) {printf("\n----> Wysoki sredni wiek pracownikow. Rozwaz odmlodzenie zalogi <----\n\n");}
    else {printf("\n----> Prawidlowy sredni wiek pracownikow. Tak trzymac! <----\n\n");}
    //Sredni staz pracownikow
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 100;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> staz;
        if(pracownik[i]-> staz < najmniejsza) {
                najmniejsza = pracownik[i]-> staz;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> staz > najwieksza) {
                najwieksza = pracownik[i]-> staz;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[1], ozdoba);
    printf("\nSredni:%.1lf      Najwiekszy:%.1lf (%s)      Najmniejszy:%.1lf (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia < 6.0) {printf("\n----> Niski sredni staz pracy. Pomysl jak zatrzymac u siebie pracownikow na dluzej! <----\n\n");}
    else {printf("\n----> Prawidlowy sredni staz pracy. Tak trzymac! <----\n\n");}
    //Srednia pesja
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 10000;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> pensja;
        if(pracownik[i]-> pensja < najmniejsza) {
                najmniejsza = pracownik[i]-> pensja;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> pensja > najwieksza) {
                najwieksza = pracownik[i]-> pensja;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[2], ozdoba);
    printf("\nSrednia:%.2lf zl      Najwieksza:%.2lf zl (%s)      Najmniejsza:%.2lf zl (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia < 5000.00) {printf("\n----> Niska srednia placa BRUTTO. Bedzie problem z pracownikami! <----\n\n");}
    else {printf("\n----> Odpowiednia srednia placa BRUTTO. Tak trzymac! <----\n\n");}
    //Srednia ilosc pochwal
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 10000;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> pochwaly;
        if(pracownik[i]-> pochwaly < najmniejsza) {
                najmniejsza = pracownik[i]-> pochwaly;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> pochwaly > najwieksza) {
                najwieksza = pracownik[i]-> pochwaly;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[3], ozdoba);
    printf("\nSrednia:%.2lf       Najwieksza:%.0lf (%s)      Najmniejsza:%.0lf (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia < 10) {printf("\n----> Niska srednia ilosc pochwal pracownikow. Pomysl jak zmotywowac pracownikow! <----\n\n");}
    else {printf("\n----> Odpowiednia srednia ilosc pochwal pracownikow. Tak trzymac! <----\n\n");}
    //Srednia ilosc skarg
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 10000;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> skargi;
        if(pracownik[i]-> skargi < najmniejsza) {
                najmniejsza = pracownik[i]-> skargi;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> skargi > najwieksza) {
                najwieksza = pracownik[i]-> skargi;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[4], ozdoba);
    printf("\nSrednia:%.2lf       Najwieksza:%.0lf (%s)      Najmniejsza:%.0lf (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia > 4) {printf("\n----> Wysoka srednia liczba skarg na pracownikow. Zbadaj przyczyne! <----\n\n");}
    else {printf("\n----> Odpowiednia srednia ilosc skarg na pracownikow. Tak trzymac! <----\n\n");}
    //Srednia ilosc spoznien
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 10000;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> spoznienia;
        if(pracownik[i]-> spoznienia < najmniejsza) {
                najmniejsza = pracownik[i]-> spoznienia;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> spoznienia > najwieksza) {
                najwieksza = pracownik[i]-> spoznienia;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[5], ozdoba);
    printf("\nSrednia:%.2lf       Najwieksza:%.0lf (%s)      Najmniejsza:%.0lf (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia > 5) {printf("\n----> Wysoka srednia liczba spoznien pracownikow. Zbadaj przyczyne! <----\n\n");}
    else {printf("\n----> Odpowiednia srednia ilosc spoznien pracownikow. Tak trzymac! <----\n\n");}
    //Srednia samoocena pracownikow
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 10000;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> samoocena;
        if(pracownik[i]-> samoocena < najmniejsza) {
                najmniejsza = pracownik[i]-> samoocena;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> samoocena > najwieksza) {
                najwieksza = pracownik[i]-> samoocena;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[6], ozdoba);
    printf("\nSrednia:%.2lf       Najwieksza:%.2lf (%s)      Najmniejsza:%.2lf (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia > 8) {printf("\n----> Wysoka srednia samoocena pracownikow. Sprawdz czy slusznie! <----\n\n");}
    else {printf("\n----> Dosc niska srednia samoocena pracownikow. Sprawdz dlaczego! <----\n\n");}
    //Srednia ocena szefa
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 10000;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> ocena_szefa;
        if(pracownik[i]-> ocena_szefa < najmniejsza) {
                najmniejsza = pracownik[i]-> ocena_szefa;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> ocena_szefa > najwieksza) {
                najwieksza = pracownik[i]-> ocena_szefa;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[7], ozdoba);
    printf("\nSrednia:%.2lf       Najwieksza:%.2lf (%s)      Najmniejsza:%.2lf (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia < 8) {printf("\n----> Niska srednia ocena szefa. Zbadaj przyczyne! <----\n\n");}
    else {printf("\n---->  Odpowiednia srednia ocena szefas. Tak trzymac! <----\n\n");}
    //Srednia ocena wspolpracownikow
    srednia = 0.0;
    najwieksza = 0;
    najmniejsza = 10000;
    for(int i=0; i<ilosc; i++){
        srednia += pracownik[i]-> ocena_wspolpracownikow;
        if(pracownik[i]-> ocena_wspolpracownikow < najmniejsza) {
                najmniejsza = pracownik[i]-> ocena_wspolpracownikow;
                *nazwa1 = pracownik[i]->nazwisko;}
        if(pracownik[i]-> ocena_wspolpracownikow > najwieksza) {
                najwieksza = pracownik[i]-> ocena_wspolpracownikow;
                *nazwa2 = pracownik[i]-> nazwisko;}
    }
    srednia = srednia/ilosc;
    printf("\n%s %s %s", ozdoba, elementy[8], ozdoba);
    printf("\nSrednia:%.2lf       Najwieksza:%.2lf (%s)      Najmniejsza:%.2lf (%s)\n", srednia, najwieksza, *nazwa2, najmniejsza, *nazwa1);
    if(srednia < 8) {printf("\n----> Niska srednia ocena wspolpracownikow. Zbadaj przyczyne! <----\n\n");}
    else {printf("\n----> Odpowiednia srednia ocena wspolpracownikow. Tak trzymac! <----\n\n");}
    getchar();

}

static void oceny(struct Pracownicy* const* pracownik, const int ilosc){
    //Funkcja dokonujaca indywidualnej oceny i porownania wszystkich pracownikow
    const char naglowek[] = { "==================== OCENA PRACOWNIKOW ====================\n"};
    const char elementy[][50] = {"przyznane punkty", "Liczba pochwal na rok pracy (WAGA 2)", "Liczba skarg na rok pracy (WAGA 2)",
                                "Liczba spoznien na rok (WAGA 1))","Samoocena pracownika (WAGA 1)","Ocena szefa (WAGA 3)",
                                "Ocena wspolpracownikow (WAGA 2)","OCENA OGOLNA" };
    system("cls");
    printf("%s", naglowek);
    int punkty, suma_punktow_waga, waga, suma_waga;
    char *najlepszy[BUFF1];
    char *najgorszy [BUFF1];
    double wynik_najlepszy, wynik_najgorszy;
    wynik_najlepszy = 0;
    wynik_najgorszy = 100;
    for(int i=0; i<ilosc; i++){
            printf("\n\n~~~~~~~~ %s %s ~~~~~~~~", pracownik[i]->imie, pracownik[i]->nazwisko);
            punkty = 0;
            waga = 0;
            suma_punktow_waga = 0;
            suma_waga = 0;
            //punkty za pochwaly / staz pracy
            if (pracownik[i]->pochwaly/pracownik[i]->staz <= 1) {punkty = 1;}
            else if(pracownik[i]->pochwaly/pracownik[i]->staz > 1 && pracownik[i]->pochwaly/pracownik[i]->staz <= 2) {punkty = 2;}
            else if(pracownik[i]->pochwaly/pracownik[i]->staz > 2) {punkty = 3;}
            waga = 2;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %.2lf,  %s: %d",elementy[1], (double)(pracownik[i]->pochwaly)/(double)(pracownik[i]->staz), elementy[0],
                   (punkty * waga));
            //punkty za skargi / staz pracy
            if (pracownik[i]->skargi/pracownik[i]->staz > 2) {punkty = 1;}
            else if(pracownik[i]->skargi/pracownik[i]->staz > 1 && pracownik[i]->skargi/pracownik[i]->staz <= 2) {punkty = 2;}
            else if(pracownik[i]->skargi/pracownik[i]->staz <= 1) {punkty = 3;}
            waga = 2;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %.2lf,  %s: %d", elementy[2], (double)(pracownik[i]->skargi)/(double)(pracownik[i]->staz),
                   elementy[0],(punkty * waga));
             //punkty za spoznienia / lata pracy
            if (pracownik[i]->spoznienia/pracownik[i]->staz > 2) {punkty = 1;}
            else if(pracownik[i]->spoznienia/pracownik[i]->staz > 1 && pracownik[i]->spoznienia/pracownik[i]->staz <= 2) {punkty = 2;}
            else if(pracownik[i]->spoznienia/pracownik[i]->staz <= 1) {punkty = 3;}
            waga = 1;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %.2lf,  %s: %d",elementy[3], (double)(pracownik[i]->spoznienia)/(double)(pracownik[i]->staz),
                   elementy[0], (punkty * waga));
            //punkty za samoocene
            if (pracownik[i]->samoocena < 6) {punkty = 1;}
            else if(pracownik[i]->samoocena >= 6 && pracownik[i]->samoocena < 8.5) {punkty = 2;}
            else if(pracownik[i]->samoocena >= 8.5) {punkty = 3;}
            waga = 1;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %.2lf,  %s: %d", elementy[4], pracownik[i]->samoocena, elementy[0], (punkty * waga));
            //punkty za ocene szefa
            if (pracownik[i]->ocena_szefa < 5) {punkty = 1;}
            else if(pracownik[i]->ocena_szefa >= 5 && pracownik[i]->samoocena < 8) {punkty = 2;}
            else if(pracownik[i]->ocena_szefa >= 8) {punkty = 3;}
            waga = 3;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s): %.2lf,  %s: %d", elementy[5], pracownik[i]->ocena_szefa, elementy[0], (punkty * waga));
            //punkty za ocene wspolpracownikow
            if (pracownik[i]->ocena_wspolpracownikow < 6) {punkty = 1;}
            else if(pracownik[i]->ocena_wspolpracownikow >= 6 && pracownik[i]->ocena_wspolpracownikow < 8.5) {punkty = 2;}
            else if(pracownik[i]->ocena_wspolpracownikow >= 8.5) {punkty = 3;}
            waga = 1;
            suma_waga = suma_waga + waga;
            suma_punktow_waga = suma_punktow_waga + (punkty * waga);
            printf("\n::::::%s: %.2lf,  %s: %d", elementy[6], pracownik[i]->ocena_wspolpracownikow, elementy[0], (punkty * waga));
            //Ocena ogolna
            double ogolna;
            ogolna = 0;
            ogolna = ((double)(suma_punktow_waga))/((double)(suma_waga));
            printf("\n%s:  %.2lf", elementy[7], ogolna);
            if (ogolna > wynik_najlepszy) {
                    wynik_najlepszy = ogolna;
                    *najlepszy = pracownik[i]->nazwisko;}
            if (ogolna < wynik_najgorszy) {
                wynik_najgorszy = ogolna;
                *najgorszy = pracownik[i]->nazwisko;}
    }
    printf("\n\n =========== Z ocen wynika, ze: ");
    printf("\n\n ----------> Najlepiej oceniony pracownik to: %s", *najlepszy);
    printf("\n\n ----------> Najgorzej oceniony pracownik to: %s", *najgorszy);
    getchar();
}

static void dodaj(struct Pracownicy*** pracownik, int *ilosc){
    //Dodanie nowego pracownika i wpisanie jego danych do pliku
    int new_size = *ilosc + 1;
    struct Pracownicy** temp =(struct Pracownicy **)malloc(sizeof(struct Pracownicy*)*(new_size));
    for(int i=0; i<*ilosc;++i){
        temp[i] = (*pracownik)[i];
    }
    temp[*ilosc] = (struct Pracownicy *) malloc(sizeof(struct Pracownicy));
    const char naglowek[] = { "|==================== DODAWANIE NOWEGO PRACOWNIKA ====================|\n\n"};
    const char komunikat[] = {"Prosze wpisywac wszystkie dane bez spacji (w razie potrzeby zamiast niej uzyc '-')"};
    const char elementy [][50] = {"Imie", "Nazwisko", "Telefon", "Stanowisko", "Rok urodzenia", "Staz pracy", "Pesja",
                                    "Pochwaly", "Skargi", "Spoznienia", "Samoocena", "Ocena szefa", "Ocena wspolpracownikow"};
    char imie[BUFF1];
    char nazwisko[BUFF1];
    int tel;
    char stanowisko [BUFF1];
    int rok_ur;
    double staz;
    double pensja;
    int pochwaly;
    int skargi;
    int spoznienia;
    double samoocena;
    double ocena_szefa;
    double ocena_wspolpracownikow;
    system("cls");
    printf("%s", naglowek);
    printf("------> %s\n", komunikat);
    printf("\n%s: ", elementy[0]);
    scanf("%s", imie);
    printf("\n%s: ", elementy[1]);
    scanf("%s", nazwisko);
    printf("\n%s: ", elementy[2]);
    scanf("%d", &tel);
    printf("\n%s: ", elementy[3]);
    scanf("%s", stanowisko);
    printf("\n%s: ", elementy[4]);
    scanf("%d", &rok_ur);
    printf("\n%s: ", elementy[5]);
    scanf("%lf", &staz);
    printf("\n%s: ", elementy[6]);
    scanf("%lf", &pensja);
    printf("\n%s: ", elementy[7]);
    scanf("%d", &pochwaly);
    printf("\n%s: ", elementy[8]);
    scanf("%d", &skargi);
    printf("\n%s: ", elementy[9]);
    scanf("%d", &spoznienia);
    printf("\n%s: ", elementy[10]);
    scanf("%lf", &samoocena);
    printf("\n%s: ", elementy[11]);
    scanf("%lf", &ocena_szefa);
    printf("\n%s: ", elementy[12]);
    scanf("%lf", &ocena_wspolpracownikow);
    strcpy(temp[*ilosc]->imie, imie);
    strcpy(temp[*ilosc]->nazwisko, nazwisko);
    temp[*ilosc]->tel = tel;
    strcpy(temp[*ilosc]->stanowisko, stanowisko);
    temp[*ilosc]->rok_ur = rok_ur;
    temp[*ilosc]->staz = staz;
    temp[*ilosc]->pensja = pensja;
    temp[*ilosc]->pochwaly = pochwaly;
    temp[*ilosc]->skargi = skargi;
    temp[*ilosc]->spoznienia = spoznienia;
    temp[*ilosc]->samoocena = samoocena;
    temp[*ilosc]->ocena_szefa = ocena_szefa;
    temp[*ilosc]->ocena_wspolpracownikow = ocena_wspolpracownikow;
    FILE *fp;
    fp = fopen("pracownicy.txt","a");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
        fprintf(fp, "\n%s %s %d %s %d %.2lf %.2lf %d %d %d %.2lf %.2lf %.2lf", temp[*ilosc]->imie, temp[*ilosc]->nazwisko, temp[*ilosc]->tel,
                temp[*ilosc]->stanowisko, temp[*ilosc]->rok_ur, temp[*ilosc]->staz, temp[*ilosc]->pensja,
                temp[*ilosc]->pochwaly, temp[*ilosc]->skargi, temp[*ilosc]->spoznienia, temp[*ilosc]->samoocena, temp[*ilosc]->ocena_szefa,
                temp[*ilosc]->ocena_wspolpracownikow);
    fclose(fp);
    free(*pracownik);
    *pracownik = temp;
    ++(*ilosc);
}

static void usun_jednego(struct Pracownicy*** pracownik, int *ilosc){
    const char naglowek[] = { "====================== USUN PRACOWNIKA ======================"};
    int j = 0, wybor;
    char znak;
    printf("\n\n%s\n\n", naglowek);
    printf("Wybierz numer pracownika, ktorego chcesz usunac z bazy: ");
    scanf("%d", &wybor);
    znak=getchar();
    int new_size = *ilosc - 1;
    struct Pracownicy** temp =(struct Pracownicy **)malloc(sizeof(struct Pracownicy*)*(new_size));
    for(int i=0; i < *ilosc; ++i){
            if (i != wybor - 1){
            temp[j] = (*pracownik)[i];
            j++;}
    }
    FILE *fp;
    fp = fopen("pracownicy.txt","w");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    for(int i=0; i<new_size; i++){
    fprintf(fp, "%s %s %d %s %d %.2lf %.2lf %d %d %d %.2lf %.2lf %.2lf\n", temp[i]->imie, temp[i]->nazwisko, temp[i]->tel,
                temp[i]->stanowisko, temp[i]->rok_ur, temp[i]->staz, temp[i]->pensja,
                temp[i]->pochwaly, temp[i]->skargi, temp[i]->spoznienia, temp[i]->samoocena, temp[i]->ocena_szefa,
                temp[i]->ocena_wspolpracownikow);
    }
    fclose(fp);
    free(*pracownik);
    *pracownik = temp;
    --(*ilosc);
}

static void kalkulator() {
    //Kalkulator wynagrodzen dla I i II progu podatkowego (III liczony niepoprawnie!)
    const char naglowek[] = { "==================== KALKULATOR WYNAGRODZEN ===================="};
    const char komunikat [] = {"WYNAGRODZENIE BRUTTO (minimum 3600 zl)"};
    const char elementy [][50] = {"Skladka emerytalna", "Skladka rentowa", "Skladka chorobowa", "Skladka zdrowotna", "Zaliczka na PIT",
                                    "WYNAGRODZENIE NETTO"};
    double wynagrodzenie;
    char ch;
    system("cls");
    printf("%s\n", naglowek);
    printf("%s: ", komunikat);
    scanf("%lf", &wynagrodzenie);
    ch = getchar();
    double pomocnicza, pomocnicza2, netto, procenty;
    char p = 37;
    pomocnicza = wynagrodzenie * 0.0976;
    pomocnicza2 = wynagrodzenie - pomocnicza;
    netto = wynagrodzenie - pomocnicza;
    procenty = (pomocnicza * 100)/ wynagrodzenie;
    printf("\n  - %s ---> %.2lf zl czyli %.2lf %c placy brutto",elementy[0], pomocnicza, procenty, p);
    pomocnicza = wynagrodzenie * 0.015;
    pomocnicza2 = pomocnicza2 - pomocnicza;
    netto = netto - pomocnicza;
    procenty = (pomocnicza * 100)/ wynagrodzenie;
    printf("\n\n  - %s ---> %.2lf zl czyli %.2lf %c placy brutto", elementy[1], pomocnicza, procenty, p);
    pomocnicza = wynagrodzenie * 0.0245;
    pomocnicza2 = pomocnicza2 - pomocnicza;
    netto = netto - pomocnicza;
    procenty = (pomocnicza * 100)/ wynagrodzenie;
    printf("\n\n  - %s --->: %.2lf zl czyli %.2lf %c placy brutto", elementy[2], pomocnicza, procenty, p);
    pomocnicza = wynagrodzenie * 0.0777;
    netto = netto - pomocnicza;
    procenty = (pomocnicza * 100)/ wynagrodzenie;
    printf("\n\n  - %s --->: %.2lf zl czyli %.2lf %c placy brutto", elementy[3], pomocnicza, procenty, p);
    pomocnicza2 = pomocnicza2 - 250;
    //obliczanie stawki skladki na PIT
    if (pomocnicza2 < 10000) {
        pomocnicza2 = pomocnicza2 * 0.12;
        pomocnicza2 = pomocnicza2 - 300;}
    else if (pomocnicza2 > 10000) {
        pomocnicza = (pomocnicza2 - 10000) * 0.32;
        pomocnicza2 = 10800/12;
        pomocnicza2 = pomocnicza2 + pomocnicza;
    }
    procenty = (pomocnicza2 * 100)/ wynagrodzenie;
    printf("\n\n  - %s ---> %.0lf zl czyli %.2lf %c placy brutto", elementy[4], pomocnicza2, procenty, p);
    netto = netto - pomocnicza2;
    procenty = (netto * 100)/ wynagrodzenie;
    printf("\n\n%s: %.2lf zl czyli %.2lf %c placy brutto", elementy[5], netto, procenty, p);
    getchar();
}

static void informator() {
    //Wyswietlanie informacji o charakterystyce umowy o prace i umowy zlecenie
    const char naglowek[]= { "============ INFORMATOR DLA PRACOWNIKOW ============"};
    const char naglowek2[] = {"============== INFORMATOR UMOWA O PRACE =============="};
    const char naglowek3[] = {"============== INFORMATOR UMOWA ZLECENIE =============="};
    const char ozdoba[] = { "|--------------------------------------------------|" };
    const char menu_lista[][50]= {"1. Umowa o prace", "2. Umowa zlecenie", "0. Powrot"};
    int c = 10;
    char znak;
    size_t elementy  = (sizeof(menu_lista)/sizeof(menu_lista[0]));
    while(c < 0 || c > 4){
        system("cls");
        printf("%s\n", naglowek);
        for(size_t i=1; i<= elementy; i++){
            printf("  %s \n", menu_lista[i-1]);
            printf("%s\n", ozdoba);
        }
        scanf("%d", &c);
        znak=getchar();
    }
    char buffor[INFOBUFF];
   switch (c) {
            case 1:
                system("cls");
                FILE *fp;
                fp=fopen("info_UOP.txt","r");
                if(fp==NULL) {
                printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
                printf("%s\n\n", naglowek2);
                while(fgets(buffor,300,fp)) {
                    printf("%s", buffor);
                }
                getchar();
                fclose(fp);
                informator();
                break;
            case 2:
                system("cls");
                FILE *plik;
                plik=fopen("info_UZ.txt","r");
                if(plik==NULL) {
                printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
                printf("%s\n\n", naglowek3);
                while(fgets(buffor,300,plik)) {
                    printf("%s", buffor);
                }
                getchar();
                fclose(plik);
                informator();
            case 0: break;
        }

    }

static void usun(struct Pracownicy*** pracownik, int ilosc){
    for(int i=0; i<ilosc; i++){
        free((*pracownik)[i]);
        (*pracownik)[i] = NULL;
    }
    free (*pracownik);
    *pracownik = NULL;
}
