package Model;

import java.io.*;
import java.util.zip.GZIPOutputStream;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;
import java.util.zip.ZipInputStream;

public class KopiaZapasowa {

    public static void zapisz(ListaPracownikow listaPracownikow, String nazwaPliku) throws IOException {
        if (!nazwaPliku.endsWith(".gzip") && !nazwaPliku.endsWith(".zip")) {
            throw new IllegalArgumentException("Nieobsługiwany format pliku. Użyj rozszerzenia .gzip lub .zip");
        }
        File plik = new File(nazwaPliku);
        if (plik.exists() && !plik.canWrite()) {
            throw new SecurityException("Brak uprawnień do zapisu w pliku: " + nazwaPliku);
        }
        try (OutputStream os = new FileOutputStream(nazwaPliku)) {
            OutputStream finalStream = os;

            if (nazwaPliku.endsWith(".gzip")) {
                finalStream = new GZIPOutputStream(os);
            } else if (nazwaPliku.endsWith(".zip")) {
                ZipOutputStream zipOut = new ZipOutputStream(os);
                zipOut.putNextEntry(new ZipEntry("listaPracownikow"));
                finalStream = zipOut;
            }
            try (ObjectOutputStream oos = new ObjectOutputStream(finalStream)) {
                oos.writeObject(listaPracownikow);
            }
        }
    }

    public static ListaPracownikow odczytaj(String nazwaPliku) throws IOException {
        if (!nazwaPliku.endsWith(".gzip") && !nazwaPliku.endsWith(".zip")) {
            throw new IllegalArgumentException("Nieobsługiwany format pliku. Użyj rozszerzenia .gzip lub .zip");
        }
        File plik = new File(nazwaPliku);
        if (!plik.exists()) {
            throw new FileNotFoundException("Plik nie istnieje: " + nazwaPliku);
        }
        if (!plik.canRead()) {
            throw new SecurityException("Brak uprawnień do odczytu pliku: " + nazwaPliku);
        }

        try (InputStream is = new FileInputStream(nazwaPliku)) {
            InputStream finalStream = is;
            if (nazwaPliku.endsWith(".gzip")) {
                finalStream = new GZIPInputStream(is);
            } else if (nazwaPliku.endsWith(".zip")) {
                ZipInputStream zipIn = new ZipInputStream(is);
                zipIn.getNextEntry();
                finalStream = zipIn;
            }
            try (ObjectInputStream ois = new ObjectInputStream(finalStream)) {
                return (ListaPracownikow) ois.readObject();
            } catch (ClassNotFoundException e) {
                throw new IOException("Niekompatybilna wersja danych w pliku: " + nazwaPliku, e);
            }
        }
    }
}


