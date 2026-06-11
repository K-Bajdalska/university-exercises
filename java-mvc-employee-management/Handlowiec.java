package Model;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.function.Consumer;

public class Handlowiec extends Pracownik implements Serializable {
    private BigDecimal prowizja;
    private BigDecimal limitProwizji;
    private static final long serialVersionUID = 1L;
    private static final List<String> KOMUNIKATY = List.of("Prowizja(%)",
            "Limit prowizji/miesiąc (zł)");

    public Handlowiec() {
        super();
        this.setStanowisko("Handlowiec");
        this.prowizja = BigDecimal.ZERO;
        this.limitProwizji = BigDecimal.ZERO;
    }

    private void setProwizja (String prowizja) {
        if(!Walidator.czyLiczba(prowizja)) throw new IllegalArgumentException("Prowizja musi być liczbą");
        this.prowizja = new BigDecimal(prowizja);
    }

    private void setLimitProwizji (String limit) {
        if(!Walidator.czyLiczba(limit)) throw new IllegalArgumentException("Limit prowizji musi być liczbą");
        limitProwizji = new BigDecimal(limit);
    }

    @Override
    public ArrayList<String> getKomunikatyDoPobrania() {
       ArrayList<String> komunikaty = super.getKomunikatyDoPobrania();
        komunikaty.addAll(KOMUNIKATY);
        return komunikaty;
    }
    @Override
    public LinkedHashMap<String, String> toHashMap() {
        LinkedHashMap<String, String> wyjscie = super.toHashMap();
        wyjscie.put(KOMUNIKATY.get(0), prowizja.toString());
        wyjscie.put(KOMUNIKATY.get(1), limitProwizji.toString());
        return wyjscie;
    }
    @Override
    public LinkedHashMap<String, Consumer<String>> akcjeDoDodawania() {
        LinkedHashMap<String, Consumer<String>> akcje = super.akcjeDoDodawania();
        akcje.put(KOMUNIKATY.get(0), this::setProwizja);
        akcje.put(KOMUNIKATY.get(1), this::setLimitProwizji);
        return akcje;
    }
}
