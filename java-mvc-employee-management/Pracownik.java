package Model;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.function.Consumer;

public abstract class Pracownik implements Serializable {
    private Pesel pesel;
    private String imie;
    private String nazwisko;
    private String stanowisko;
    private BigDecimal wynagrodzenie;
    private String telefon;
    private static final long serialVersionUID = 1L;
    private final List<String> KOMUNIKATY = List.of("Identyfikator PESEL", "Imię",
            "Nazwisko", "Wynagrodzenie (zł)", "Telefon służbowy numer" );

    public Pracownik() {
        this.pesel = new Pesel("00000000000");
        this.imie = "-";
        this.nazwisko = "-";
        this.stanowisko = "-";
        this.wynagrodzenie = BigDecimal.ZERO;
        this.telefon = "-";
    }

    private void setPesel(String pesel) { this.pesel.setPesel(pesel); }
    public String getPesel() { return pesel.getNumer();}
    private void setImie(String imie) {
        if (!Walidator.czyPoprawnaGodnosc(imie)) throw new IllegalArgumentException("Imię musi składać się z liter");
        this.imie = Walidator.ustawPierwszaLitereWielka(imie);
    }
    private void setNazwisko (String nazwisko) {
        if (!Walidator.czyPoprawnaGodnosc(nazwisko)) throw new IllegalArgumentException("Nazwisko musi składać się z liter");
        this.nazwisko = Walidator.ustawPierwszaLitereWielka(nazwisko);
    }
    public void setStanowisko (String stanowisko) {
        if (!Walidator.czySameLitery(stanowisko)) throw new IllegalArgumentException("Stanowisko musi składać się z liter");
        this.stanowisko = Walidator.ustawPierwszaLitereWielka(stanowisko);
    }
    private void setWynagrodzenie (String wynagrodzenie) {
        if (!Walidator.czyLiczba(wynagrodzenie)) throw new IllegalArgumentException("Wynagrodzenie musi być liczbą");
        this.wynagrodzenie = new BigDecimal(wynagrodzenie);
    }
    private void setTelefon (String telefon) {
        if (telefon.equals("-")) this.telefon = "-brak-";
        else if (!Walidator.czyTelefon(telefon)) throw new IllegalArgumentException("Telefon musi składać " +
                "się z 9 cyfr (z lub bez przedrostka +kierunkowy)");
        else this.telefon = telefon;
    }
    public ArrayList<String> getKomunikatyDoPobrania() {
        return new ArrayList<>(KOMUNIKATY);
    }
    public LinkedHashMap <String, String> toHashMap() {
        LinkedHashMap<String, String> wyjscie = new LinkedHashMap<>();
        wyjscie.put(KOMUNIKATY.get(0), pesel.getNumer());
        wyjscie.put(KOMUNIKATY.get(1), imie);
        wyjscie.put(KOMUNIKATY.get(2), nazwisko);
        wyjscie.put("Stanowisko", stanowisko);
        wyjscie.put(KOMUNIKATY.get(3), wynagrodzenie.toString());
        wyjscie.put(KOMUNIKATY.get(4), telefon);
        return wyjscie;
    }
    public LinkedHashMap<String, Consumer<String>> akcjeDoDodawania() {
        LinkedHashMap<String, Consumer<String>> akcje = new LinkedHashMap<>();
        akcje.put(KOMUNIKATY.get(0), this::setPesel);
        akcje.put(KOMUNIKATY.get(1), this::setImie);
        akcje.put(KOMUNIKATY.get(2), this::setNazwisko);
        akcje.put(KOMUNIKATY.get(3), this::setWynagrodzenie);
        akcje.put(KOMUNIKATY.get(4), this::setTelefon);
        return akcje;
    }
}
