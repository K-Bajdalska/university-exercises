package Model;

import java.math.BigDecimal;

class Walidator {

    static boolean czyPoprawnaGodnosc(String str) {
        if (str == null || str.isEmpty()) {
            return false;
        }

        int ileSpacji = 0;

        for (char c : str.toCharArray()) {
            if (!Character.isLetter(c) && c != '-' && c != '\'' && c != ' ' && c != '.') {
                return false;
            }
            if (c == ' ') {
                ileSpacji++;
            }
            if (ileSpacji > 1) {
                return false;
            }
        }
        return true;
    }
    static boolean czySameLitery(String str) {
        if (str == null || str.isEmpty()) {
            return false;
        }

        for (char c : str.toCharArray()) {
            if (!Character.isLetter(c)) {
                return false;
            }
        }

        return true;
    }

     static boolean czyLiczbaCalkowita(String str) {
        if (str == null || str.isEmpty()) {
            return false;
        }
        for (char c : str.toCharArray()) {
            if (!Character.isDigit(c)) {
                return false;
            }
        }
        return true;
    }

    static boolean czyLiczba(String str) {
        if (str == null || str.isEmpty()) {
            return false;
        }
        try {
            new BigDecimal(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    static boolean czyTelefon(String str) {
        String regex = "\\+\\d{2} \\d{9}";
        return (str.matches((regex)) || (czyLiczba(str) && (str.length() == 9)));
    }

    static boolean czyKartaSluzbowa(String str) {
        String regex = "\\d{3}-\\d{3}-\\d{2}-\\d{3}";
        return str.matches(regex);

    }

     static String ustawPierwszaLitereWielka(String str) {
        if (str == null || str.isEmpty()) {
            return str;
        }
        return str.substring(0, 1).toUpperCase() + str.substring(1).toLowerCase();
    }


}
