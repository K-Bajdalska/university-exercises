import string
import lab4modul
import random
import os
from datetime import datetime

# ZADANIE 1
def copy_file(plik):
    fh = None
    wh = None
    try:
        fh = open(plik, mode='r', encoding='utf8')
        t = fh.read()
        linie = t.splitlines()
        wh = open('zadanie1KOPIA.txt', mode='w', encoding='utf8')
        i = 0
        for lin in linie:
            i += 1
            wh.write(str(i))
            wh.write(' ')
            wh.write(lin)
            wh.write ('\n')
    except OSError as zm_err:
        print('Błąd odczytu lub zapisu pliku')
        print(zm_err)
    finally:
        if fh is not None:
            fh.close()
        if wh is not None:
            wh.close()

copy_file("zadanie1.txt")

# ZADANIE 2
def create_text_file (plik, num_chars, min_w=3, max_w =12, char_set = string.ascii_letters, min_l = 5, max_l = 100 ):
    wh = None
    try:
        wh = open(plik, mode='w', encoding='utf8')
        wynik = lab4modul.generuj_losowy_tekst(num_chars, min_w, max_w, char_set, min_l, max_l)
        wh.write(wynik)

    except OSError as zm_err:
        print('Błąd tworzenia pliku')
        print(zm_err)
    finally:
        if wh is not None:
            wh.close()

create_text_file('zadanie2.txt', 2000)

# ZADANIE 3
def create_table_file (plik, columns, rows, min_v=0, max_v = 1000 ):
    try:
        wh = open(plik, mode='w', encoding='utf8')
        for _ in range(rows):
            row = []
            for _ in range(columns):
                value = random.randint(min_v,max_v)
                row.append(str(value).rjust(10))
            row_string = ' '.join(row)
            wh.write(row_string + '\n')
    except OSError as zm_err:
        print('Błąd tworzenia pliku')
        print(zm_err)
    finally:
        if wh is not None:
            wh.close()

create_table_file('zadanie3.txt', 6, 12)

# ZADANIE 4
def find_files_info(directory):
    oldest = None
    newest = None
    shortest = None
    longest = None

    for path, subdirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(path, file)
            try:
                file_stat = os.stat(file_path)
                file_size = file_stat.st_size
                file_mtime = file_stat.st_mtime

                # Konwersja czasu modyfikacji na czytelny format
                file_mtime_readable = datetime.fromtimestamp(file_mtime).strftime('%Y-%m-%d %H:%M:%S')

                if oldest is None or file_mtime < oldest['mtime']:
                    oldest = {'name': file, 'path': file_path, 'mtime': file_mtime, 'mtime_readable': file_mtime_readable}

                if newest is None or file_mtime > newest['mtime']:
                    newest = {'name': file, 'path': file_path, 'mtime': file_mtime, 'mtime_readable': file_mtime_readable}

                if shortest is None or file_size < shortest['size']:
                    shortest = {'name': file, 'path': file_path, 'size': file_size}

                if longest is None or file_size > longest ['size']:
                    longest = {'name': file, 'path': file_path, 'size': file_size}

            except OSError as e:
                print(f"Błąd podczas przetwarzania pliku: {file_path}")
                print(e)



    return {
        'oldest': oldest,
        'newest': newest,
        'shortest': shortest,
        'longest': longest
    }

directory = r'C:'
files_info = find_files_info(directory)

print("Najstarszy plik:", files_info['oldest'])
print("Najnowszy plik:", files_info['newest'])
print("Najkrótszy plik:", files_info['shortest'])
print("Najdłuższy plik:", files_info['longest'])

# ZADANIE 5
def find_duplicate(directory):
    file_dict = {}
    try:
        for root, _, files in os.walk(directory):
            for file in files:
                file_path = os.path.join(root, file)
                try:
                    if file not in file_dict:
                        file_dict[file] = []
                    file_dict[file].append(file_path)
                except OSError as e:
                    print(f"Błąd podczas przetwarzania pliku: {file_path}")
                    print(e)
    except OSError as e:
        print(f"Błąd podczas przeszukiwania katalogu: {directory}")
        print(e)

    duplicates = []
    try:
        for file, paths in file_dict.items():
            if len(paths) > 1:
                duplicates.append(file)
    except Exception as e:
        print("Błąd podczas przetwarzania listy plików")
        print(e)
    return duplicates

directory = r'C:'
duplicate_files = find_duplicate(directory)
print("Zdublowane pliki:")
for file in duplicate_files:
    print(file)

# ZADANIE 6
def find_empty_directories(directory):
    empty_dirs = []
    try:
        for root, subdirs, files in os.walk(directory):
            for dir in subdirs:
                dir_path = os.path.join(root, dir)
                try:
                    if not os.listdir(dir_path):
                        empty_dirs.append(dir_path)
                except OSError as e:
                    print(f"Błąd podczas sprawdzania zawartości katalogu: {dir_path}")
                    print(e)
    except OSError as e:
        print(f"Błąd podczas przeszukiwania katalogu: {directory}")
        print(e)
    return empty_dirs

directory = r'C'
empty_directories = find_empty_directories(directory)
print("Puste podkatalogi:")
for dir in empty_directories:
    print(dir)

# ZADANIE 7
def find_files_wth_text(directory, seatch_text):
    matching_files = []
    try:
        for root, _, files in os.walk(directory):
            for file in files:
                file_path = os.path.join(root, file)
                try:
                    fh = open(file_path, 'r', encoding='utf8')
                    try:
                        content = fh.read()
                        if seatch_text in content:
                            matching_files.append(file_path)
                    except UnicodeDecodeError as e:
                        print(f"Błąd dekodowania pliku: {file_path}")
                        print(e)
                    except OSError as e:
                        print(f"Nieoczekiwany błąd podczas odczytu pliku: {file_path}")
                        print(e)
                    finally:
                        fh.close()
                except OSError as e:
                    print(f"Błąd podczas otwierania pliku: {file_path}")
                    print(e)
    except OSError as e:
        print(f"Błąd podczas przeszukiwania katalogu: {directory}")
        print(e)
    return matching_files

directory =r'C'
search_text = 'to skomplikowane'
matching_files = find_files_wth_text(directory, search_text)
print("Pliki zawierające podany tekst:")
for file in matching_files:
    print(file)

# ZADANIE 8
def process_text_file(input_file, output_file = 'zadanie8.txt'):
    try:
        content = None
        fh = open(input_file, 'r', encoding = 'utf8')
        try:
            content = fh.read()
        except Exception as e:
            print(f"Nieoczekiwany błąd podczas odczytu pliku: {input_file}")
            print(e)
        finally:
            fh.close()
    except OSError as e:
        print(f"Błąd podczas otwierania pliku: {input_file}")
        print(e)
    # Nadmiarowe spacje
    if content is not None:
        content = lab4modul.usun_spacje(content)

        # Spacje przed znakami interpunkcyjnymi
        new_content = []
        i = 0
        while i < len(content):
            new_content.append(content[i])
            if content[i] in '.,!?;:' and i > 0 and content[i-1] == ' ':
                new_content.pop(-2)
            i += 1
        content = ''.join(new_content)

        # Podział na zdania
        sentences = []
        sentence = []
        for char in content:
            sentence.append(char)
            if char in '.!?':
                sentences.append(''.join(sentence).strip())
                sentence = []
        if sentence:
            sentences.append(''.join(sentence).strip())

        # Czy pierwsza litera jest duża
        for i in range(len(sentences)):
            sentences[i] = sentences[i].capitalize()

        # Każde w osobnej linii z numerem na początku
        try:
            fh = open(output_file, 'w', encoding='utf8')
            try:
                for i in range(len(sentences)):
                    sentence = sentences[i]
                    fh.write(str(i + 1) + '. ' + sentence + '\n')
            except Exception as e:
                print(f"Nieoczekiwany błąd podczas zapisu do pliku: {output_file}")
                print(e)
            finally:
                fh.close()
        except OSError as e:
            print(f"Błąd podczas otwierania pliku do zapisu: {output_file}")
            print(e)

input_file = 'sample.txt'
output_file = 'corrected_text.txt'
process_text_file(input_file, output_file)




