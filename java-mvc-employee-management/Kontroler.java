package Controller;

import Model.*;
import View.Widok;

import java.io.IOException;
import java.util.*;
import java.util.function.Consumer;

public class Kontroler {
    private ListaPracownikow pracownicy;
    private Widok widok;


    public Kontroler() {
        try {
            pracownicy = new ListaPracownikow();
            widok = new Widok();
        } catch (Exception e) {
            System.err.println("Wystapil bład podczas inicjalizacji kontrolera.");
        }
    }

    public void start() {
        int wybor;
        while(true) {
            widok.wyswietlMenuGlowne();
            try {
                String wyborUzytkownika = widok.pobierzOdUzytkownika("\nWybor> ");
                wybor = Integer.parseInt(wyborUzytkownika);
            } catch (NumberFormatException e) {
                widok.wyswietlBlad("Nieprawidłowy wybór. Proszę wprowadzić liczbę.");
                continue;
            }
            switch (wybor) {
                case 1-> listaPracownikow();
                case 2-> dodajPracownika();
                case 3-> usunPracownika();
                case 4-> kopiaZapasowa();
                case 0-> {
                    widok.zamknijScanner();
                    System.out.println("Zamykanie aplikacji...");
                    return;
                }
                default -> {
                    widok.wyswietlBlad("Nieprawidlowy numer opcji");
                }
            }
        }
    }

    private void listaPracownikow() {
        if (pracownicy.length() == 0) {
            widok.wyswietlBlad("Lista jest pusta.");
            return;
        }
        widok.wyswietl("1.Lista pracowników");
        int licznik = 0;
        for (Pracownik pracownik : pracownicy.getPracownicy()) {
            widok.przerywnik();
            LinkedHashMap<String, String> pracownikInfo = pracownik.toHashMap();
            widok.wyswietlPracownika(pracownikInfo);
            licznik ++;
            widok.wyswietl(Widok.justujPrawo("[Pozycja: " + licznik + "/" +
                    pracownicy.length() +"]"));
            widok.wyswietl("[Enter] - nastepny");
            widok.wyswietl("[Q] - powrót");
            String wybor;
            while(true) {
                try {
                    wybor = widok.pobierzOdUzytkownika();
                    if (wybor.isEmpty()) {
                        break;
                    }
                    else if (wybor.equalsIgnoreCase("Q")) {
                        return;
                    }
                    else throw new IllegalArgumentException("Nierozpoznana komenda");
                } catch (IllegalArgumentException e) {
                    widok.wyswietlBlad(e.getMessage());
                    continue;
                }
            }
            }
        }

    private void dodajPracownika() {
        Pracownik nowyPracownik;
        while (true) {
            try {
                widok.wyswietl("2.Dodaj pracownika");
                String typ = getTypPracownika();
                nowyPracownik = pracownicy.stworzPracownika(typ);
            } catch (IllegalArgumentException e) {
                widok.wyswietlBlad(e.getMessage());
                continue;
            }
            break;
        }
        widok.przerywnik();
        LinkedHashMap<String, Consumer<String>> akcje = nowyPracownik.akcjeDoDodawania();
        for (Map.Entry<String, Consumer<String>> mapa : akcje.entrySet()) {
            while (true) {
                try {
                    String komunikat = mapa.getKey();
                    widok.wyswietlKomunikat(komunikat);
                    String dane = widok.pobierzOdUzytkownika();
                    if (dane.equalsIgnoreCase("Q")) {
                        widok.wyswietl("Anulowano dodawanie pracownika.");
                        return;
                    }
                    Consumer<String> akcja = mapa.getValue();
                    akcja.accept(dane);
                } catch (IllegalArgumentException e) {
                    widok.wyswietlBlad(e.getMessage());
                    System.err.flush();
                    continue;
                }
                break;
            }
        }
        widok.przerywnik();
        System.out.println("[Enter]-zapisz\n[Q]-anuluj");
        String wybor;
        while(true) {
            try {
                wybor = widok.pobierzOdUzytkownika();
                if (wybor.isEmpty()) {
                    pracownicy.dodajPracownika(nowyPracownik);
                    break;
                }
                else if (wybor.equalsIgnoreCase("Q")) {
                        widok.wyswietl("Anulowano dodawanie pracownika.");
                        return;
                }
                else throw new IllegalArgumentException("Wciśnij enter albo wpisz Q");
            } catch (IllegalArgumentException e) {
                widok.wyswietlBlad(e.getMessage());
                continue;
            }
        }
    }

    private void usunPracownika() {
        widok.wyswietl("3. Usuń pracownika");
        String pesel;
        Pracownik pracownik;
        while(true) {
            try {
                widok.wyswietlKomunikat("Podaj Identyfikator PESEL");
                pesel = widok.pobierzOdUzytkownika();
                if (pesel.equalsIgnoreCase("Q")) {
                    widok.wyswietl("Anulowano usuwanie pracownika.");
                    return;
                }
                if (pesel.trim().isEmpty()) {
                    widok.wyswietlBlad("PESEL nie może być pusty. Spróbuj ponownie.");
                    continue;
                }
                if (!pesel.matches("\\d{11}")) {
                    throw new IllegalArgumentException("PESEL musi składać się z 11 cyfr");
                }
                pracownik = pracownicy.getPracownik(pesel);
            }
            catch (IllegalArgumentException e) {
                widok.wyswietlBlad(e.getMessage());
                continue;
            }
            break;
        }
        widok.przerywnik();
        LinkedHashMap<String, String> pracownikInfo = pracownik.toHashMap();
        widok.wyswietlPracownika(pracownikInfo);
        widok.przerywnik();
        System.out.println("[Enter]-zapisz\n[Q]-porzuć");
        String wybor;
        while(true) {
            try {
                wybor = widok.pobierzOdUzytkownika();
                if (wybor.isEmpty()) {
                    pracownicy.usunPracownika(pesel);
                    break;
                }
                else if (wybor.equalsIgnoreCase("Q")) {
                    widok.wyswietl("Anulowano usuwanie pracownika.");
                    return;
                }
                else throw new IllegalArgumentException("Wciśnij enter albo wpisz Q");
            } catch (IllegalArgumentException e) {
                widok.wyswietlBlad(e.getMessage());
                continue;
            }
        }

    }

    private void kopiaZapasowa() {
        widok.wyswietl("4. Kopia zapasowa");
        while (true) {
            try {
                widok.wyswietlKomunikat("[Z]achowaj/[O]dtwórz/[Q] - wyjdź");
                String wybor = widok.pobierzOdUzytkownika();
                if (wybor.equalsIgnoreCase("Q")) return;

                if (wybor.equalsIgnoreCase("Z")) {
                    if (pracownicy.length() == 0) {
                        widok.wyswietlBlad("Lista jest pusta. Nie można zapisać danych.");
                        return;
                    }
                    widok.wyswietlKomunikat("Nazwa pliku:");
                    String nazwaPliku = widok.pobierzOdUzytkownika();
                    if (nazwaPliku.trim().isEmpty()) {
                        widok.wyswietlBlad("Nazwa pliku nie może być pusta.");
                        continue;
                    }
                    KopiaZapasowa.zapisz(pracownicy, nazwaPliku);
                    widok.wyswietl("Dane zostały zapisane do pliku: " + nazwaPliku);

                } else if (wybor.equalsIgnoreCase("O")) {
                    widok.wyswietlKomunikat("Podaj nazwę pliku do odczytu:");
                    String nazwaPliku = widok.pobierzOdUzytkownika();
                    if (nazwaPliku.trim().isEmpty()) {
                        widok.wyswietlBlad("Nazwa pliku nie może być pusta.");
                        continue;
                    }
                    pracownicy = KopiaZapasowa.odczytaj(nazwaPliku);
                    widok.wyswietl("Dane zostały wczytane z pliku: " + nazwaPliku);

                } else {
                    throw new IllegalArgumentException("Nieprawidłowy wybór. Wybierz Z, O lub Q.");
                }
            } catch (IOException e) {
                widok.wyswietlBlad("Błąd operacji wejścia/wyjścia: " + e.getMessage());
            } catch (IllegalArgumentException e) {
                widok.wyswietlBlad(e.getMessage());

            } catch (SecurityException e) {
                widok.wyswietlBlad("Brak uprawnień do pliku: " + e.getMessage());
            }
            catch (Exception e) {
                widok.wyswietlBlad("Nieoczekiwany błąd: " + e.getMessage());
            }
            break;
        }
    }
    private String getTypPracownika() {
        return widok.pobierzOdUzytkownika("[D]yrektor/[H]handlowiec:\t\t");
        }
}
