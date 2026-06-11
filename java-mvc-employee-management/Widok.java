package View;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.function.Supplier;

public class Widok {
    private Scanner scanner;

    public Widok() {
        scanner = new Scanner(System.in);
    }

    public void wyswietlMenuGlowne() {
        System.out.println("MENU");
        System.out.println("\t1. Lista pracownikow");
        System.out.println("\t2. Dodaj pracownika");
        System.out.println("\t3. Usuń pracownika");
        System.out.println("\t4. Kopia zapasowa");
        System.out.println("\t0. Wyjście");
    }

    public String pobierzOdUzytkownika() {
        return scanner.nextLine();
    }

    public String pobierzOdUzytkownika(String wiadomosc) {
        System.out.println(wiadomosc);
        return scanner.nextLine();
    }

    public void wyswietl(String wiadomosc) {
        System.out.println(wiadomosc);
    }

    public void wyswietlKomunikat(String wiadomosc) {
        System.out.print(wyjustujNaTrzy(wiadomosc,":", ""));
    }

    public void wyswietlPracownika(HashMap<String, String> pracownikInfo) {
        for (HashMap.Entry<String, String> mapa : pracownikInfo.entrySet()) {
            System.out.println(wyjustujNaTrzy(mapa.getKey(), ":", mapa.getValue()));
        }
    }

    public static String justujPrawo(String text) {
        int szerokosc = 60;
        int padding = szerokosc - text.length();
        String marginesSpacje = " ".repeat(Math.max(0, padding));
        return marginesSpacje + text;
    }

    private static String wyjustujNaTrzy(String lewy, String srodek, String prawy) {

        int szerokosc = 60;
        int lewyMargines = 0;
        int prawyMargines = 0;

        int srodekStart = (szerokosc - srodek.length()) / 2;
        if (srodekStart < lewy.length() + 1) {
            srodekStart = lewy.length() + 1;
        }
        lewyMargines = srodekStart - lewy.length();
        prawyMargines = szerokosc - srodekStart - srodek.length() - prawy.length() - 1;

        String leweSpacje = " ".repeat(Math.max(0, lewyMargines));
        String praweSpacje = " ".repeat(Math.max(0, prawyMargines));

        return lewy + leweSpacje + srodek + praweSpacje + prawy;
    }

    public void przerywnik() {
        System.out.println("-----------------------------------------------------------------------------------------");
    }

    public void wyswietlBlad(String wiadomosc) {
        System.err.println(wiadomosc);
        scanner.nextLine();
    }
    public void zamknijScanner() {
        if (scanner != null) {
            scanner.close();
        }
    }
}
