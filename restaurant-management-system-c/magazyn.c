#include "magazyn.h"

enum Menu_magazyn { WYJSCIE = 0, WYSWIETLENIE = 1, INWENTARYZACJA = 2, MAGAZYN = 3};

static enum Menu_magazyn wybierz(){
    const char menu_naglowek[] = { "|==================== STANY MAGAZYNOWE ====================|\n"};
    const char ozdoba[] = { "|----------------------------------------------------------|" };
    const char menu_lista[][50]= {"1. Wyswietl stany magazynowe", "2. Inwentaryzacja - stworz nowy dokument","3. Magazyn",
                                    "0. Powrot"};
    int c = 10;
    char znak;
    size_t elementy  = (sizeof(menu_lista)/sizeof(menu_lista[0]));
    while(c < 0 || c > 3){
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

static void stworz(struct Produkty*** lista_produktow, int ilosc_prod);
static void wczytaj_i_wykaz_braki(struct Produkty* const* lista_produktow, const int ilosc_prod);
static void wyswietl(struct Produkty * const * const lista_produktow, int ilosc_prod);
static void inwentaryzacja();
static void stan_magazyn();
static void usun (struct Produkty*** lista_produktow, int ilosc);

void magazyn() {
    int wybor;
    int ilosc_prod = 50;
    struct Produkty** lista_produktow = NULL;
    stworz(&lista_produktow, ilosc_prod);
    do {
            //Funkcja z menu (zwracajaca wybor uzytkownika i przekazujaca go do instrukcji switch)
            wybor = wybierz();
            switch(wybor){
                //Wywolanie odpowiednich do wyboru funkcji
                case WYSWIETLENIE:
                        wczytaj_i_wykaz_braki(lista_produktow, ilosc_prod);
                        wyswietl(lista_produktow, ilosc_prod);
                        break;
                case INWENTARYZACJA:
                        inwentaryzacja();
                        break;
                case MAGAZYN:
                        stan_magazyn();
                        break;
    }
            }while (wybor != WYJSCIE);
    usun(&lista_produktow, ilosc_prod);
}

static void stworz(struct Produkty*** lista_produktow, int ilosc_prod) {
    struct Produkty** temp = (struct Produkty **) malloc(sizeof(struct Produkty*)*ilosc_prod);
    for(int i =0; i<ilosc_prod; i++) {
        temp[i] = (struct Produkty *)malloc(sizeof(struct Produkty));
    }
    *lista_produktow = temp;
}


static void wczytaj_i_wykaz_braki(struct Produkty* const* lista_produktow, const int ilosc_prod){
    //Wczytanie posiadanych produktow i informacji o nich z pliku do struktury oraz wykazanie brakow wraz z ich poziomem (!, !!, !!!)
    char string_nazwa[BUFF];
    float ilosc;
    char string_jednostka[BUFF];
    char string_dostawca[BUFF];
    float w_ilosc;
    const char naglowek[] = { "==================== STANY MAGAZYNOWE ===================="};
    const char komunikat[] = {"------> UWAGA!!! Brakuje nastepujacych produktow:"};
    const char legenda[][60] = {"LEGENDA:", "! - niewielkie braki - zacznij planowac dostawe", "!! - znaczne braki - zamow dostawe",
                                "!!! - niedopuszczalne braki - natychmiast zamow dostawe"};
    FILE *fp;
    fp = fopen("magazyn.txt.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    system("cls");
    printf("%s\n\n", naglowek);
    for (int i = 0; i < 4; i++){
        printf("%s\n", legenda[i]);
    }
    printf("\n\n%s", komunikat);
    for(int i=0; i< ilosc_prod; i++) {
    fscanf(fp,"%s %f %s %s %f", string_nazwa, &ilosc, string_jednostka, string_dostawca, &w_ilosc );
    strcpy(lista_produktow[i]->nazwa, string_nazwa);
    lista_produktow[i]->ilosc = ilosc;
    strcpy(lista_produktow[i]->jednostka, string_jednostka);
    strcpy(lista_produktow[i]->dostawca, string_dostawca);
    lista_produktow[i]->wym_ilosc = w_ilosc;
    char p = 37;
    if (ilosc < w_ilosc) {
        printf("\n *** %s  %.2f%c - dostawca %s ", string_nazwa, ilosc*100/w_ilosc, p, string_dostawca);
        if (ilosc*100/w_ilosc >= 90)
        {
            printf(" !");
        }
        else if (ilosc*100/w_ilosc <= 90 && ilosc*100/w_ilosc >= 80 )
        {
            printf(" !!");
        }
        else if (ilosc*100/w_ilosc < 80)
        {
            printf(" !!!");
        }

    }
    }
    printf("\n\n\n");
    fclose(fp);
}

static void wyswietl(struct Produkty * const * const lista_produktow, int ilosc_prod) {
    //Wyswietlenie listy posiadanych produktow wraz z informacjami o nich
    const char naglowek[] = {"--------- W MAGAZYNIE ZNAJDUJE SIE ---------"};
    const char ozdoba[] = {"--------------------------------------------"};
    printf("%s\n", naglowek);
    for(int i=0; i<ilosc_prod;i++) {
        printf("\[\] %s  %.2f  %s  %s\n%s\n", lista_produktow[i]->nazwa, lista_produktow[i]->ilosc, lista_produktow[i]->jednostka,
               lista_produktow[i]->dostawca, ozdoba);
    }
    getchar();
}

static void inwentaryzacja() {
    //Tworzenie dokumentu inwentaryzacyjnego
    const char tytul_pliku[] = {"biezaca_inwentaryzacja.txt"};
    char string_nazwa[BUFF];
    float ilosc;
    char string_jednostka[BUFF];
    char string_dostawca[BUFF];
    float w_ilosc;
    const char naglowek[] = { "==================== INWENTARYZACJA ===================="};
    const char komunikat[] = { "W formularzu jest miejsce na 70 produktow. Wpisz 0 w polu nazwa aby zakonczyc. Nie uzywaj spacji"};
    const char elementy[][50] = {"Nazwa produktu", "Ilosc produktu", "Jednostka (kg, l, sztuka itd.", "Dostawca produktow", "Wymagana ilosc produktu"};
    FILE *fp;
    fp = fopen(tytul_pliku,"w");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    for(int i=0; i< 70; i++) {
    system("cls");
    printf("%s\n\n%s\n\n",naglowek, komunikat);
    printf("1. %s: ",elementy[0]);
    scanf("%s", string_nazwa);
    if(*string_nazwa == '0') {break;}
    printf("\n2. %s: ",elementy[1]);
    scanf("%f", &ilosc);
    printf("\n3. %s: ", elementy[2]);
    scanf("%s", string_jednostka);
    printf("\n4. %s: ", elementy[3]);
    scanf("%s", &string_dostawca);
    printf("\n5. %s: ", elementy[4]);
    scanf("%f", &w_ilosc);
    fprintf(fp,"%s %.2f %s %s %.2f\n", string_nazwa, ilosc, string_jednostka, string_dostawca, w_ilosc );
    }
    fclose(fp);
}

static void stan_magazyn(){
    //Nadanie losowych wartosci informacjom o magazynie
    const int powierzchnia = 55;
    setlocale(LC_ALL, "Polish");
    srand(time(NULL));
    struct Magazyn magazyn;
    struct Informacje informacje;
    informacje.powierzchnia = powierzchnia;
    informacje.temperatura = -5 + rand() % 30;
    magazyn.informacje = informacje;
    int suma_artykulow = 0;
    int uzywane = 0;
    int nieuzywane = 0;
    int uszkodzone = 0;
    int najbardziej = 0;
    int najbardziej_regal = 0;
    int najbardziej_polka = 0;
    int najmniej = 1001;
    int najmniej_regal = 1001;
    int najmniej_polka = 1001;
    char p = 37;
    const char naglowek[] = { "==================== MAGAZYN ===================="};
    for(int i = 0; i <LICZBAREGALOW; i++){
            magazyn.regal[i].nr_regalu = i + 1;
        for(int j = 0; j< LICZBAPOLEK; j++){
            magazyn.regal[i].polka[j].stan = 1 + rand()% 1000;
            if(magazyn.regal[i].polka[j].stan % 5 == 0) {
                magazyn.regal[i].polka[j].l_przechowywanych_art = 0;
                uszkodzone += 1;
            }
            else if (magazyn.regal[i].polka[j].stan % 4 == 0){
                magazyn.regal[i].polka[j].l_przechowywanych_art = 0;
                nieuzywane += 1;
                }
            else {
                magazyn.regal[i].polka[j].l_przechowywanych_art = 10 + rand()% 60;
                if(magazyn.regal[i].polka[j].l_przechowywanych_art > najbardziej){
                    najbardziej = magazyn.regal[i].polka[j].l_przechowywanych_art;
                    najbardziej_regal = i+1;
                    najbardziej_polka = j+1;
                }
                else if(magazyn.regal[i].polka[j].l_przechowywanych_art <= najmniej){
                    najmniej = magazyn.regal[i].polka[j].l_przechowywanych_art;
                    najmniej_regal = i+1;
                    najmniej_polka = j+1;
                }
                uzywane += 1;
            }
                suma_artykulow = suma_artykulow + magazyn.regal[i].polka[j].l_przechowywanych_art;
        }
    }
    //Wyswietlenie graficznego odwzorowania magazynu i okreslenie stopnia uzycia polek oraz udzialu polek uszkodzonych, nieuzywanych i uzywanych
    system("cls");
    printf("%s\n\n", naglowek);
    const char ozdoba[] = {"----------------------------------------------------------------------------"};
    const char elementy[][50] = {"----POLKA NR", "STAN: USZKODZONA", "STAN: NIEUZYWANA", "STAN: UZYWANA",
                                "LICZBA PRZECHOWYWANYCH ARTYKULOW"};
    printf("\nPOWIERZCHNIA: %d m2", magazyn.informacje.powierzchnia);
    printf("\nTemperatura: %d stopni Celsjusza", magazyn.informacje.temperatura);
    if(magazyn.informacje.temperatura >= 3 && magazyn.informacje.temperatura <= 12){
        printf("------> Odpowiednia temperatura w magazynie");
    }
    else {printf("------> Nieodpowiednia temperatura w magazynie!!! Zmien ja!!!");}
    for (int i = 0; i < LICZBAREGALOW; i++){
        printf("\n%s", ozdoba);
        printf("\n|                                REGAL NR %d                                 |", magazyn.regal[i].nr_regalu);
        printf("\n%s", ozdoba);
        for(int j = 0; j < LICZBAPOLEK; j++){
            printf("\n%s %d",elementy[0], j+1);
            if(magazyn.regal[i].polka[j].stan % 5 == 0){printf("          %s", elementy[1]);}
            else if(magazyn.regal[i].polka[j].stan % 4 == 0) {printf("          %s", elementy[2]);}
            else {printf("          %s", elementy[3]);}
            printf("         %s: %d",elementy[4], magazyn.regal[i].polka[j].l_przechowywanych_art);
        }
    }
    printf("\n\n\nLiczba przechowywanych produktow: %d    czyli srednio: %.2lf na regal i %.2lf na polke", suma_artykulow,
           (double)suma_artykulow/(double)LICZBAREGALOW,
           (double)suma_artykulow/(double)(LICZBAREGALOW*LICZBAPOLEK));
    printf("\n\nLiczba uzywanych polek: %d z %d czyli uzywanych jest %.2lf%c polek", uzywane, (LICZBAREGALOW*LICZBAPOLEK),
           ((double)uzywane/(double)(LICZBAREGALOW*LICZBAPOLEK))*100, p);
    if(((double)uzywane/(double)(LICZBAREGALOW*LICZBAPOLEK))*100 >= 70) {
        printf("\n******** Odpowiednie wykorzystanie magazynu! Tak trzymac!");}
    else {printf("\n******** Nieodpowiednie wykorzystanie magazynu! Zbyt maly procent wykorzystania!");}

   printf("\n\nLiczba nieuzywanych polek: %d z %d czyli uzywanych jest %.2lf%c polek", nieuzywane, (LICZBAREGALOW*LICZBAPOLEK),
           ((double)nieuzywane/(double)(LICZBAREGALOW*LICZBAPOLEK))*100, p);
    if(((double)nieuzywane/(double)(LICZBAREGALOW*LICZBAPOLEK))*100 <= 20) {
            printf("\n******** Odpowiednio niski procent nieuzywanych polek! Tak trzymac!");}
    else {printf("\n******** Za wysoki procent nieuzywanych polek! Pomysl o zmianie organizacji!");}
    printf("\n\nLiczba uszkodzonych polek: %d z %d czyli uszkodzonych jest %.2lf%c polek", uszkodzone, (LICZBAREGALOW*LICZBAPOLEK),
           ((double)uszkodzone/(double)(LICZBAREGALOW*LICZBAPOLEK))*100, p);
    if(((double)uszkodzone/(double)(LICZBAREGALOW*LICZBAPOLEK))*100 <= 10) {
            printf("\n******** Odpowiednio niski procent uszkodzonych polek! Tak trzymac!");}
    else {printf("\n******** Za wysoki procent uszkodzonych polek! Wezwij ekipe naprawcza!");}
    printf("\n\nNajbardziej zajeta polka:    Regal nr: %d    Polka nr:%d    Liczba artykulow: %d ", najbardziej_regal,najbardziej_polka,najbardziej);
    printf("\n\nNajmniej zajeta polka:    Regal nr: %d    Polka nr:%d    Liczba artykulow: %d ", najmniej_regal,najmniej_polka,najmniej);
    getchar();
}

static void usun (struct Produkty*** lista_produktow, int ilosc) {
    for(int i=0; i<ilosc; i++) {
        free((*lista_produktow)[i]);
        (*lista_produktow)[i] = NULL;
    }
    free(*lista_produktow);
    *lista_produktow = NULL;
}









