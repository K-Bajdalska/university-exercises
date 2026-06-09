#include "informacje.h"

static void stworz(struct Restauracja** restaurant);
static void pobierz(struct Restauracja* const restaurant);
static void wyswietl(const struct Restauracja* const restaurant, int upr);
static void zmien (struct Restauracja* const restaurant);
static void usun (struct Restauracja*** restaurant);

void informacje (int upr) {
    //Pobranie i wyswietlenie informacji o restauracji adekwatnych do posiadanych uprawnien
    struct Restauracja* restaurant = NULL;
    stworz(&restaurant);
    pobierz(restaurant);
    wyswietl(restaurant, upr);
    usun(&restaurant);

}

static void stworz(struct Restauracja** restaurant) {
    *restaurant = (struct Restauracja *) malloc(sizeof(struct Restauracja));
}

static void pobierz(struct Restauracja* const restaurant) {
    char string_nazwa[TEXTBUFF];
    char string_adres[TEXTBUFF];
    int nr_tel;
    char string_email[TEXTBUFF];
    char string_kuchnia[TEXTBUFF];
    int powierzchnia;
    int l_stolikow;
    int rok_zalozenia;
    int wymagana_l_pracownikow;
    int l_pracownikow;
    int ocz_dochod_mies;
    int dochod_mies;
    int ocz_dochod_roczny;
    int dochod_roczny;
    //pobranie danych z pliku
    FILE *fp;
    fp = fopen("informacje.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    fgets(string_nazwa,TEXTBUFF,fp);
    fgets(string_adres,TEXTBUFF,fp);
    fscanf(fp,"%d", &nr_tel);
    fscanf(fp,"%s", string_email);
    fscanf(fp,"%s", string_kuchnia);
    fscanf(fp,"%d", &powierzchnia);
    fscanf(fp,"%d", &l_stolikow);
    fscanf(fp,"%d", &rok_zalozenia);
    fscanf(fp,"%d", &wymagana_l_pracownikow);
    fscanf(fp,"%d", &l_pracownikow);
    fscanf(fp,"%d", &ocz_dochod_mies);
    fscanf(fp,"%d", &dochod_mies);
    fscanf(fp,"%d", &ocz_dochod_roczny);
    fscanf(fp,"%d", &dochod_roczny);
    strcpy(restaurant->nazwa,string_nazwa);
    strcpy(restaurant->adres, string_adres);
    restaurant->nr_tel = nr_tel;
    strcpy(restaurant->email, string_email);
    strcpy(restaurant->typ_kuchni, string_kuchnia);
    restaurant->powierzchnia = powierzchnia;
    restaurant->l_stolikow = l_stolikow;
    restaurant->rok_zalozenia = rok_zalozenia;
    restaurant->wymagana_l_pracownikow = wymagana_l_pracownikow;
    restaurant->l_pracownikow = l_pracownikow;
    restaurant->ocz_dochod_mies = ocz_dochod_mies;
    restaurant->dochod_mies = dochod_mies;
    restaurant->ocz_dochod_roczny = ocz_dochod_roczny;
    restaurant->dochod_roczny = dochod_roczny;
    fclose(fp);
}

static void wyswietl(const struct Restauracja* const restaurant, int upr) {
    const char naglowek[] = { "==================== INFORMACJE ===================="};
    const char ozdoba[] = { "----------------------------------------------------" };
    const char elementy [][50] = {"1. Nazwa restauracji", "2. Adres", "3. Numer telefonu", "4. Email", "5. Typ kuchni",
                                "6. Powierzchnia", "7. Liczba stolikow", "8. Rok zalozenia", "9. Liczba pracownikow",
                                "10. Dochod miesieczny", "11. Dochod roczny"};
    if (upr == 1 || upr == 2) {
    // Wyswietlenie wszystkich danych wraz z informacjami o spelnieniu wymagan/oczekiwan
        system("cls");
        printf("%s\n\n", naglowek);
        printf("%s: %s%s\n%s: %s%s\n%s: %d\n%s\n%s: %s\n%s\n%s: %s\n%s", elementy[0],restaurant->nazwa, ozdoba,
               elementy[1],restaurant->adres, ozdoba, elementy[2], restaurant->nr_tel,ozdoba, elementy[3], restaurant->email, ozdoba,
                elementy[4],restaurant->typ_kuchni,ozdoba);
        printf("\n%s: %d m2\n%s\n%s: %d\n%s\n%s: %d\n%s\n%s: %d", elementy[5],
               restaurant->powierzchnia,ozdoba, elementy[6],restaurant->l_stolikow,ozdoba, elementy[7], restaurant->rok_zalozenia,
               ozdoba, elementy[8],restaurant->l_pracownikow);
        if(restaurant->wymagana_l_pracownikow > restaurant->l_pracownikow) {
            printf("\n\tZa malo pracownikow.\n\tRozwaz rekrutacje!");
        }
        else {printf("\n\tPrawidlowa liczba pracownikow.\n\tTak trzymac!");}
        printf("\n%s", ozdoba);
        printf("\n%s: %d", elementy[9], restaurant->dochod_mies);
        if(restaurant->ocz_dochod_mies > restaurant->dochod_mies){
                printf("\n\tZa niski dochod miesieczny.\n\tWymaga analizy!");
        }
        else {printf("\n\tDochod miesieczny na odpowiedniem poziomie.\n\tTak trzymac!");}
        printf("\n%s", ozdoba);
        printf("\n%s: %d", elementy[10], restaurant->dochod_roczny);
        if(restaurant->ocz_dochod_roczny > restaurant->dochod_roczny){
                printf("\n\tZa niski dochod roczny.\nWymaga analizy!");
        }
        else {printf("\n\tDochod roczny na odpowiedniem poziomie.\n\tTak trzymac!");}
        printf("\n%s", ozdoba);
        //Zapytanie o chec zmiany niektorych informacji i w razie potwierdzenia przeniesienie do funkcji, ktora to umozliwia
        printf("\nCzy chcesz zmienic jakies informacje?");
        printf("\n1. Tak    ");
        int wybor;
        char znak;
        scanf("%d", &wybor);
        znak = getchar();
        switch(wybor){
            case 1: zmien(restaurant); break;
        }
    }
    else {
        //Wyswietlenie okrojonych informacji o restauracji bez informacji o spelnieniu okreslonych kryteriow
        system("cls");
        printf("%s\n", naglowek);
        printf("%s: %s%s\n%s: %s%s\n%s: %d\n%s\n%s: %s\n%s\n%s: %s\n%s", elementy[0],
           restaurant->nazwa, ozdoba, elementy[1], restaurant->adres, ozdoba, elementy[2], restaurant->nr_tel, ozdoba,
            elementy[3], restaurant->email, ozdoba, elementy[4], restaurant->typ_kuchni, ozdoba);
        printf("\n%s: %d m2\n%s\n%s: %d\n%s\n%s: %d\n%s", elementy[5],restaurant->powierzchnia,
               ozdoba, elementy[6], restaurant->l_stolikow, ozdoba, elementy[7], restaurant->rok_zalozenia, ozdoba);
        getchar();
    }
}

static void zmien (struct Restauracja* const restaurant) {
    const char naglowek[] = { "================= ZMIEN INFORMACJE ================="};
    const char ozdoba[] = { "----------------------------------------------------" };
    const char elementy [][50] = {"1. Numer telefonu", "2. Email", "3. Powierzchnia", "4. Liczba stolikow", "5. Wymagana liczba pracownikow",
                                "6. Aktualna liczba pracownikow", "7. Oczekiwany dochod miesieczny", "8. Rzeczywisty dochod miesieczny",
                                "9. Oczekiwany dochod roczny", "10. Rzeczywisty dochod roczny", "0.Wyjscie"};
    int wybor;
    char znak;
    do {
        //Wyswietlenie aktualnych informacji, wybor numeru informacji jaka ma zostac zmieniona i zamiana danych
        system("cls");
        printf("%s\n\n", naglowek);
        printf("Jakie informacje chcesz zmienic? :");
        printf("\n%s\n%s (aktualnie %d)\n%s",ozdoba, elementy[0], restaurant->nr_tel, ozdoba);
        printf("\n%s (aktualnie %s)\n%s", elementy[1], restaurant->email, ozdoba);
        printf("\n%s (aktualnie %d m2)\n%s", elementy[2], restaurant->powierzchnia, ozdoba);
        printf("\n%s (aktualnie %d)\n%s", elementy[3], restaurant->l_stolikow, ozdoba);
        printf("\n%s (aktualnie %d)\n%s", elementy[4], restaurant->wymagana_l_pracownikow, ozdoba);
        printf("\n%s (aktualnie %d)\n%s", elementy[5], restaurant->l_pracownikow, ozdoba);
        printf("\n%s (aktualnie %d zl)\n%s", elementy[6], restaurant->ocz_dochod_mies, ozdoba);
        printf("\n%s (aktualnie %d zl)\n%s", elementy[7], restaurant->dochod_mies, ozdoba);
        printf("\n%s (aktualnie %d zl)\n%s", elementy[8], restaurant->ocz_dochod_roczny, ozdoba);
        printf("\n%s (aktualnie %d zl)\n%s", elementy[9], restaurant->dochod_roczny, ozdoba);
        printf("\n\n0. Wyjscie\n");
        scanf("%d", &wybor);
        znak = getchar();
        switch(wybor) {
        case 1:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowy numer telefonu (bez spacji):   ");
            scanf("%d", &restaurant->nr_tel);
            break;
        case 2:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowy email (bez spacji):   ");
            scanf("%s", restaurant->email);
            break;
        case 3:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowa powierzchnie (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->powierzchnia);
            break;
        case 4:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowa liczbe stolikow (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->l_stolikow);
            break;
        case 5:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowa wymagana liczbe pracownikow (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->wymagana_l_pracownikow);
            break;
        case 6:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowa aktualna liczbe pracownikow (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->l_pracownikow);
            break;
        case 7:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowy oczekiwany dochod miesieczny (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->ocz_dochod_mies);
            break;
        case 8:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz zaktualizowany dochod miesieczny (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->dochod_mies);
            break;
        case 9:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz nowy oczekiwany dochod roczny (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->ocz_dochod_roczny);
            break;
         case 10:
            system("cls");
            printf("%s\n\n", naglowek);
            printf("Wpisz zaktualizowany dochod roczny (tylko liczbe, bez spacji):   ");
            scanf("%d", &restaurant->dochod_roczny);
            break;
        default: break;
        }
    }while(wybor != 0);
    FILE *fp;
    fp=fopen("informacje.txt","w");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    fprintf(fp, "%s", restaurant->nazwa);
    fprintf(fp, "%s", restaurant->adres);
    fprintf(fp, "%d ", restaurant->nr_tel);
    fprintf(fp, "%s ", restaurant->email);
    fprintf(fp, "%s ", restaurant->typ_kuchni);
    fprintf(fp, "%d ", restaurant->powierzchnia);
    fprintf(fp, "%d ", restaurant->l_stolikow);
    fprintf(fp, "%d ", restaurant->rok_zalozenia);
    fprintf(fp, "%d ", restaurant->wymagana_l_pracownikow);
    fprintf(fp, "%d ", restaurant->l_pracownikow);
    fprintf(fp, "%d ", restaurant->ocz_dochod_mies);
    fprintf(fp, "%d ", restaurant->dochod_mies);
    fprintf(fp, "%d ", restaurant->ocz_dochod_roczny);
    fprintf(fp, "%d ", restaurant->dochod_roczny);
    fclose(fp);

}

static void usun (struct Restauracja*** restaurant){
    free(*restaurant);
    (*restaurant) = NULL;
}







