package Model;

import java.util.Collection;
import java.util.LinkedHashMap;
import java.io.Serializable;


public class ListaPracownikow implements Serializable {
    private LinkedHashMap<String, Pracownik> pracownicy;
    private static final long serialVersionUID = 1L;

    public ListaPracownikow() {
        pracownicy = new LinkedHashMap<>();
    }

    public Pracownik stworzPracownika(String typ) {
        if (typ.equals("D")) {
            return new Dyrektor();
        } else if (typ.equals("H")) {
            return new Handlowiec();
        }
        else {
            throw new IllegalArgumentException("Nieprawidłowy typ stanowiska - wybierz D lub H");
        }
    }

    public void dodajPracownika(Pracownik nowyPracownik) {
        pracownicy.put(nowyPracownik.getPesel(), nowyPracownik);
        Pesel.dodajUnikalnyPesel(nowyPracownik.getPesel());
    }
    public void usunPracownika(String pesel) {
        if (czyJest(pesel)) {
            pracownicy.remove(pesel);
            Pesel.usunUnikalnyPesel(pesel);
        }
    }
    public Collection<Pracownik> getPracownicy() {
        return pracownicy.values();
    }
    public Pracownik getPracownik(String pesel) {
        if (!(pracownicy.containsKey(pesel))) throw  new IllegalArgumentException("Nie znaleziono pracownika " +
                "z podanym identyfikatorem PESEL");
        return pracownicy.get(pesel);
    }
    public int length() {
        return pracownicy.size();
    }
    private boolean czyJest(String pesel) {
        return pracownicy.containsKey(pesel);
    }
}
