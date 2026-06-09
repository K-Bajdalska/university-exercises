#include "zaloguj.h"

static int licz();
static void stworz(struct Dane_logowania*** dane, int ilosc);
static void pobierz (struct Dane_logowania* const* dane, const int ilosc);
static void usun(struct Dane_logowania*** dane, int ilosc);

int zaloguj() {
    int sukces = 0;
    //Zlicz liczbe loginow i hasel
    int ilosc;
    ilosc = licz();
    struct Dane_logowania** dane = NULL;
    stworz(&dane, ilosc);
    pobierz(dane, ilosc);
    const char ozdoba[] = {"========================================================"};
    const char komunikat[] = {"Zaloguj sie do swojego panelu"};

    do {
        //pobranie loginu i hasla od uzytkownika
        char login [TEXTBUFF];
        char haslo [TEXTBUFF];
        printf("\n%s\n%s\n%s", ozdoba, komunikat, ozdoba);
        printf("\nLogin: ");
        scanf("%s", login);
        printf("\nHaslo: ");
        scanf("%s", haslo);

        //sprawdzenie poprawnoœci wprowadzonych danych
        if((strcmp( login, dane[0]->login) == 0) && ( strcmp( haslo, dane[0]->haslo) == 0 )) {
            sukces = 1;
        }
        else if((strcmp( login, dane[1]->login) == 0) && ( strcmp( haslo, dane[1]->haslo ) == 0 )) {
            sukces = 1;
        }
         else if((strcmp( login, dane[2]->login) == 0) && ( strcmp( haslo, dane[2]->haslo ) == 0 )) {
            sukces = 3;
        }
        else if((strcmp( login, dane[3]->login) == 0) && ( strcmp( haslo, dane[3]->haslo ) == 0 )) {
            sukces = 3;
        }
        system("cls");
    } while (sukces == 0);
    system("cls");
    usun(&dane, ilosc);
    return sukces;
}

static int licz() {
    int c, linie = 0;
    FILE* fp;
    fp = fopen("dane_log.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    while((c = fgetc(fp)) != EOF){
        if(c == '\n') ++linie;}
    linie += 1;
    return linie;
}

static void stworz(struct Dane_logowania*** dane, int ilosc){
    struct Dane_logowania** temp = (struct Dane_logowania **) malloc (sizeof(struct Dane_logowania*) * ilosc);
    for(int i = 0; i<ilosc;i++){
        temp[i] = (struct Dane_logowania *) malloc(sizeof(struct Dane_logowania));
    }
    *dane = temp;
}

static void pobierz (struct Dane_logowania* const* dane, const int ilosc) {
    char login [TEXTBUFF];
    char haslo [TEXTBUFF];
    //pobranie danych z pliku
    FILE *fp;
    fp = fopen("dane_log.txt","r");
    if(fp==NULL) {
        printf("\nPrzepraszamy, wystapil blad. Skontaktuj sie ze swoim dostawca uslug.");}
    for(int i=0; i<ilosc; i++){
    fscanf(fp,"%s %s", login, haslo);
    strcpy(dane[i]->login, login );
    strcpy(dane[i]->haslo, haslo );
    }
    fclose(fp);
}

static void usun(struct Dane_logowania*** dane, int ilosc){
    for(int i=0; i<ilosc; i++){
        free((*dane)[i]);
        (*dane)[i] = NULL;
    }
    free (*dane);
    *dane = NULL;
}


