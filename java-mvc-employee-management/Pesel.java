package Model;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

 class Pesel implements Serializable {
    private String numer;
    private static final long serialVersionUID = 1L;
    private static Set<String> unikalnePesele = new HashSet<>();

    public Pesel(String numer) {
        if (!walidacja(numer)) {
            throw new IllegalArgumentException("Niepoprawny numer PESEL");
        }
        if (unikalnePesele.contains(numer)) {
            throw new IllegalArgumentException("Numer PESEL już istnieje: " + numer);
        }
        this.numer = numer;
    }

    private static boolean walidacja(String pesel) {
        if (pesel == null || !pesel.matches("\\d{11}")) {
            throw new IllegalArgumentException("PESEL musi składać się z 11 liczb");
        }

        int[] wagi = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
        int sumaKontrolna = 0;
        for (int i = 0; i < 10; i++) {
            sumaKontrolna += wagi[i] * Character.getNumericValue(pesel.charAt(i));
        }
       sumaKontrolna += Character.getNumericValue(pesel.charAt(10));
        return sumaKontrolna % 10 == 0;
    }

     String getNumer() {
        return numer;
    }

     void setPesel(String numer) {
        if (!walidacja(numer)) {
            throw new IllegalArgumentException("PESEL niepoprawny - błędna suma kontrolna");
        }
        if (unikalnePesele.contains(numer)) {
            throw new IllegalArgumentException("Numer PESEL już istnieje: " + numer);
        }
        unikalnePesele.remove(this.numer);
        this.numer = numer;
    }

     static void dodajUnikalnyPesel(String pesel) {
        unikalnePesele.add(pesel);
    }

     static void usunUnikalnyPesel(String pesel) {
        unikalnePesele.remove(pesel);
    }
}
