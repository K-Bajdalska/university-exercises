package Model;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.function.Consumer;

public class Dyrektor extends Pracownik implements Serializable {
    private BigDecimal dodatekSluzbowy;
    private String kartaSluzbowaNr;
    private BigDecimal limitKosztow;
    private static final long serialVersionUID = 1L;
    private static final List<String> KOMUNIKATY = List.of("Dodatek służbowy (zł)",
            "Karta służbowa numer", "Limit kosztów/miesiąc (zł)");

    public Dyrektor() {
        super();
        this.setStanowisko("Dyrektor");
        this.dodatekSluzbowy = BigDecimal.ZERO;
        this.kartaSluzbowaNr = "-";
        this.limitKosztow = BigDecimal.ZERO;
    }

    private void setDodatekSluzbowy (String dodatekSluzbowy) {
        if (!Walidator.czyLiczba(dodatekSluzbowy)) throw new IllegalArgumentException("Dodatek slużbowy musi być liczbą");
        this.dodatekSluzbowy = new BigDecimal(dodatekSluzbowy);
    }
    private void setKartaSluzbowaNr (String kartaNr) {
        if (Walidator.czyKartaSluzbowa(kartaNr)) kartaSluzbowaNr = kartaNr;
        else {
            if (!Walidator.czyLiczbaCalkowita(kartaNr)) throw new IllegalArgumentException("Numer karty służbowej" +
                    " musi składać się z 11 cyfr w formacie XXX-XXX-XX-XXX");
            if (kartaNr.length() != 11) throw new IllegalArgumentException("Numer karty służbowej musi mieć dokładnie" +
                    " 11 cyfr");
            kartaSluzbowaNr = kartaNr.substring(0, 3) + "-" + kartaNr.substring(3, 6) + "-" +
                    kartaNr.substring(6, 8) + "-" +  kartaNr.substring(8, 11);
        }
    }
    private void setLimitKosztow (String limit) {
        if (!Walidator.czyLiczba(limit)) throw new IllegalArgumentException("Limit kosztów musi być liczbą");
        limitKosztow = new BigDecimal(limit);
    }

    @Override
    public ArrayList<String> getKomunikatyDoPobrania() {
        ArrayList<String> komunikaty = super.getKomunikatyDoPobrania();
        komunikaty.addAll(KOMUNIKATY);
        return komunikaty;
    }
    @Override
    public LinkedHashMap <String, String> toHashMap() {
        LinkedHashMap<String, String> wyjscie = super.toHashMap();
        wyjscie.put(KOMUNIKATY.get(0), dodatekSluzbowy.toString());
        wyjscie.put(KOMUNIKATY.get(1), kartaSluzbowaNr);
        wyjscie.put(KOMUNIKATY.get(2), limitKosztow.toString());
        return wyjscie;
    }
    @Override
    public LinkedHashMap<String, Consumer<String>> akcjeDoDodawania() {
        LinkedHashMap<String, Consumer<String>> akcje = super.akcjeDoDodawania();
        akcje.put(KOMUNIKATY.get(0), this::setDodatekSluzbowy);
        akcje.put(KOMUNIKATY.get(1), this::setKartaSluzbowaNr);
        akcje.put(KOMUNIKATY.get(2), this::setLimitKosztow);
        return akcje;
    }
}
