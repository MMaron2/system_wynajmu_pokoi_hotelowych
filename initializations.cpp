#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "header.h"
#include <vector>


using namespace std;

Pokoj::Pokoj() {
    nastepny_pokoj = nullptr;
}

database::database() {
    pierwszy_pokoj = nullptr;
}

void generateMainMenu() {
    // wygenerowanie boxa wraz z nagłówkiem
    cout << char(218);
    for (int i = 0; i < 39; i++) { cout << char(196); }
    cout << char(191) << endl;
    cout << char(179) << "  System rezerwacji pokoi hotelowych   " << char(179) << endl;
    cout << char(192);
    for (int i = 0; i < 39; i++) { cout << char(196); }
    cout << char(217) << endl;

    cout << "\n[1] wynajmij pokoj" << endl;
    cout << "[2] wyszukaj pokoj" << endl;
    cout << "[3] operacje na bazie danych" << endl;
    cout << "[4] import/export bazy danych" << endl;
    cout << "[5] zakoncz" << endl;
}


void databaseOptionsMenu(database *&pokoje) {
    int choose = 0;

    // wyswietlenie menu
    while (true) {
        system("cls");
        cout << char(218);
        for (int i = 0; i < 22; i++) { cout << char(196); }
        cout << char(191) << endl;
        cout << char(179) << "  Opcje bazy danych   " << char(179) << endl;
        cout << char(192);
        for (int i = 0; i < 22; i++) { cout << char(196); }
        cout << char(217) << endl;
        cout << "\n[1] dodaj pokoj" << endl;
        cout << "[2] usun pokoj" << endl;
        cout << "[3] zmien dane pokoju" << endl;
        cout << "[4] wyswietl wszystkie pokoje" << endl;
        cout << "[5] powrot" << endl;

        cout << "Wybor: ";
        cin >> choose;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }

        switch (choose) {
            case 1:
                pokoje->dodajPokoj();
                break;
            case 2:
                pokoje->usunPokoj();
                break;
            case 3:
                pokoje->zmienDanePokoju();
                break;
            case 4:
                pokoje->wyswietlBazeDanych();
                break;
            case 5:
                system("cls");
                return;
            default:
                break;
        }
    }
}


void importExportMenu(database *&pokoje) {
    int choose;

    while (true) {
        system("cls");
        cout << char(218);
        for (int i = 0; i < 17; i++) { cout << char(196); }
        cout << char(191) << endl;
        cout << char(179) << "  Zapis/Odczyt   " << char(179) << endl;
        cout << char(192);
        for (int i = 0; i < 17; i++) { cout << char(196); }
        cout << char(217) << endl;

        cout << "\n[1] zapisz baze danych" << endl;
        cout << "[2] wczytaj baze danych" << endl;
        cout << "[3] powrot" << endl;

        cout << "Wybor: ";
        cin >> choose;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }

        switch (choose) {
            case 1:
                pokoje->zapiszBazeDanych();
                break;
            case 2:
                pokoje->wczytajBazeDanych();
                break;
            case 3:
                system("cls");
                return;
            default:
                break;
        }
    }
}


void searchMenu(database *&pokoje) {
    int choose = 0;
    while (true) {
        system("cls");
        cout << char(218);
        for (int i = 0; i < 12; i++) { cout << char(196); }
        cout << char(191) << endl;
        cout << char(179) << "  Wyszukaj  " << char(179) << endl;
        cout << char(192);
        for (int i = 0; i < 12; i++) { cout << char(196); }
        cout << char(217) << endl;

        cout << "\n[1] wyszukaj po numerze pokoju" << endl;
        cout << "[2] wyszukaj po imieniu i nazwisku" << endl;
        cout << "[3] wyszukaj przez wyrazenia reguralnie" << endl;
        cout << "[4] powrot" << endl;

        cout << "wybor: ";
        cin >> choose;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }

        switch (choose) {
            case 1:
                pokoje->wyszukajPoNumerzePokoju();
                break;
            case 2:
                pokoje->wyszukajPoImieniuINazwisku();
                break;
            case 3:
                pokoje->wyszukajZaPomocaWyrazenRegularnych();
                break;
            case 4:
                system("cls");
                return;
            default:
                system("cls");
                break;
        }
    }
}
// ------------------------------------ FUNKJCE SPRAWDZAJACE ------------------------------------

bool sprawdzPoprawnoscDatyZakonczenia(std::string data_rozpoczecia, std::string data_zakonczenia)
{
    int rok_r, rok_z;
    int mies_r, mies_z;
    int dzien_r, dzien_z;

    // rozdzielenie daty na poszczegolne czesci
    rok_r = stoi(data_rozpoczecia.substr(0,4));
    rok_z = stoi(data_zakonczenia.substr(0,4));

    mies_r = stoi(data_rozpoczecia.substr(5,7));
    mies_z = stoi(data_zakonczenia.substr(5,7));

    dzien_r = stoi(data_rozpoczecia.substr(8,10));
    dzien_z = stoi(data_zakonczenia.substr(8,10));

    // sprawdzenie czy nie podajemy przeszlego roku
    if (rok_r < rok_z) return true;
    if (rok_r == rok_z && mies_z > mies_r) return true;
    if (rok_r == rok_z && mies_r == mies_z && dzien_z > dzien_r) return true;

    cout << "wystapil blad" << endl;
    return false;
}

bool database::sprawdzCzyBazaDanychJestPusta() {
    if (pierwszy_pokoj == nullptr) {
        cout << "Brak elementow w bazie danych lub nie dodano bazy danych" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return false;
    }
    return true;
}

std::string checkFirstNameAndLastName() {
    string imie_nazwisko;
    cout << "Podaj imie i nazwisko (wpisz 'puste' jezeli ma pozostac puste): ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, imie_nazwisko);
    if (imie_nazwisko.empty()) return " ";
    if (imie_nazwisko == "puste") return " ";
    else return imie_nazwisko;
}

std::string checkFirstAndLastNameGettering() {
    string imie_nazwisko;
    cout << "Podaj imie i nazwisko: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, imie_nazwisko);
    if (imie_nazwisko.empty()) return " ";
    if (imie_nazwisko == "puste") return " ";
    else return imie_nazwisko;
}

std::string checkValid(std::string pattern, std::string failInfo, std::string whatToInsertInformation) {
    string to_check;
    std::regex wzor(pattern);
    do {
        cout << whatToInsertInformation;
        cin >> to_check;
        if (!regex_match(to_check, wzor)) cout << failInfo << endl;

    } while (!regex_match(to_check, wzor));
    return to_check;
}

std::string checkFisrstNameAndLastNameEditValue(std::string previousValue) {
    string imie_nazwisko;
    cout << "Podaj imie i nazwisko: " << previousValue << " -> ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, imie_nazwisko);
    if (imie_nazwisko.empty()) return previousValue;
    if (imie_nazwisko == "zostaw") return previousValue;
    return imie_nazwisko;
}

std::string checkValidEditValue(std::string pattern, std::string failInfo, std::string whatToInsertInformation,
                                std::string previousValue) {
    string to_check;
    std::regex wzor(pattern);
    do {
        cout << whatToInsertInformation << previousValue << " -> ";
        cin >> to_check;
        if (to_check == "zostaw") return previousValue;
        if (!regex_match(to_check, wzor)) cout << failInfo << endl;

    } while (!regex_match(to_check, wzor));
    return to_check;
}


// ------------------------------- FUNKJE OPIERACJI NA STRINGACH -------------------------------

// funkcja rozdziela pojedynczy wiersz bazy danych na pojedyncze wartosci i zapisuje je do tablicy
void splitString(std::string &rekord, std::string tab[]) {
    string pojedyncza_wartosc_rekordu;
    int i = 0;
    stringstream objekt_pomocniczy(rekord); // stworzenie obiketu stream ktory pozwala na rozdzielenie stringa
    while (getline(objekt_pomocniczy, pojedyncza_wartosc_rekordu, ';')) {
        tab[i] = pojedyncza_wartosc_rekordu;
        i++;
    }
}

bool stringToBoolConvert(std::string &wartosc_zmieniana) {
    if (wartosc_zmieniana == "1") return true;
    return false;
}


// ---------------------------------- FUNKCJE WYSZUKIWANIA W BAZIE DANYCH ----------------------------------

void wyswietlWyszukanePokoje(Pokoj *&pokoj) {
    cout << "---------------------------------------------------------------" << endl;
    cout << "Numer pokoju: " << pokoj->numer_pokoju << endl;
    cout << "Maksymalna ilosc osobo: " << pokoj->maksymalna_ilosc_osob << endl;

    cout << "Czy dostepna lazienka: ";
    if (pokoj->czy_lazienka == 1) cout << "prawda" << endl;
    else cout << "falsz" << endl;

    cout << "Cena pokoju: " << pokoj->cena_pokoju << endl;
    cout << "Imie i Nazwisko: " << pokoj->imie_nazwisko << endl;

    cout << "Numer telefonu: ";
    if (pokoj->nr_telefonu == 0) cout << " " << endl;
    else cout << pokoj->nr_telefonu << endl;

    cout << "Data rozpoczecia pobytu: " << pokoj->data_rozpoczecia << endl;
    cout << "Data zakonczenia pobytu: " << pokoj->data_zakonczenia << endl;

    cout << "Czy dostepne posilki: ";
    if (pokoj->czy_posilki == 1) cout << "prawda" << endl;
    else cout << "falsz" << endl;

}

void database::wyszukajPoNumerzePokoju() {
    system("cls");
    if (!sprawdzCzyBazaDanychJestPusta()) return;

    string szukany_numer_pokoju;
    szukany_numer_pokoju = checkValid("^[0-9]+$", "Podales zle dane, sprobuj ponownie",
                                      "Podaj numer pokoju (dodatnia liczba calkowita): ");

    system("cls");

    Pokoj *temp = pierwszy_pokoj;
    int liczba_znalezionych_pokoi = 0;

    // wyszukiwanie pokoju w bazie danych
    while (temp) {
        if (temp->numer_pokoju == stoi(szukany_numer_pokoju)) {
            wyswietlWyszukanePokoje(temp);
            liczba_znalezionych_pokoi++;
        }
        temp = temp->nastepny_pokoj;
    }
    // sprawdzenie czy znaleziono jakies pokoje jezeli nie wyswietla odpowiedni komunikat
    if (liczba_znalezionych_pokoi == 0) {
        cout << "Nie znaleziono zadnych pokoi o podanym numerze" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
    }
    system("pause>0");

}

void database::wyszukajPoImieniuINazwisku() {
    system("cls");
    if (!sprawdzCzyBazaDanychJestPusta()) return;

    string szukane_imie_nazwisko;
    cout << "Podaj imie i nazwisko: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, szukane_imie_nazwisko);
    if (szukane_imie_nazwisko.empty()) szukane_imie_nazwisko = " ";

    Pokoj *temp = pierwszy_pokoj;
    int liczba_znalezionych_pokoi = 0;

    // wyszukiwanie pokoju w bazie danych
    while (temp) {
        if (temp->imie_nazwisko == szukane_imie_nazwisko) {
            wyswietlWyszukanePokoje(temp);
            liczba_znalezionych_pokoi++;
        }
        temp = temp->nastepny_pokoj;
    }
    // sprawdzenie czy znaleziono jakies pokoje jezeli nie wyswietla odpowiedni komunikat
    if (liczba_znalezionych_pokoi == 0) {
        cout << "Nie znaleziono zadnych pokoi o podanym imieniu i nazwisku" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;

    }
    system("pause>0");
}

void database::wyszukajZaPomocaWyrazenRegularnych() {
    system("cls");
    if (!sprawdzCzyBazaDanychJestPusta()) return; // sprawdzenie czy baza danych jest pusta

    string wyrazenie_regularne;
    bool czy_poprawne = false;
    // wprowadzenie wyraznia regularnego przez uzytkownika oraz sprawdzenie czy jest ono poprawne

    cout << "Podaj ciag znakow ktory ma zostac wyszukany: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, wyrazenie_regularne);


    Pokoj *temp = pierwszy_pokoj;
    int ile_znalezionych_pokoi = 0;

    system("cls");

    std::regex wzor(wyrazenie_regularne);
    string lazienka, posilki;
    while (temp) {
        if (temp->czy_lazienka) lazienka == "prawda";
        else lazienka = "falsz";

        if (temp->czy_posilki) posilki = "prawda";
        else posilki = "falsz";

        // sprawdzenie cyz jaka kolwiek wartosc pokoju pasuje do wprowadzonego wyrazenia regularnego
        if (regex_search(to_string(temp->numer_pokoju), wzor) ||
            regex_search(to_string(temp->maksymalna_ilosc_osob), wzor) ||
            regex_search(to_string(temp->cena_pokoju), wzor) ||
            regex_search(temp->imie_nazwisko, wzor) ||
            regex_search(to_string(temp->nr_telefonu), wzor) ||
            regex_search(temp->data_rozpoczecia, wzor) ||
            regex_search(temp->data_zakonczenia, wzor) ||
            regex_search(lazienka, wzor) ||
            regex_search(posilki, wzor))
        {
            wyswietlWyszukanePokoje(temp);
            ile_znalezionych_pokoi++;
        }
        temp = temp->nastepny_pokoj;
    }
    // sprawdzenie czy znaleziono jakies pokoje jezeli nie wyswietla odpowiedni komunikat
    if (ile_znalezionych_pokoi == 0) {
        cout << "Nie znaleziono zadnych pokoi pasujacych do wyrazenia regularnego" << endl;
    }
    else
    {
        cout << "Znaleziono " << ile_znalezionych_pokoi << " rekordow" << endl;
    }

    cout << "Wcisnij enter aby kontynuowac" << endl;
    system("pause>0");
}

// ---------------------------------- FUNKCJE OPERACJI NA BAZIE DANYCH ----------------------------------
void database::dodajPokoj() {
    system("cls");
    int nr_pokoju;
    bool czy_istnieje_pokoj_o_takim_numerze = true;

    Pokoj *nowy_pokoj = new Pokoj;

    // sprawdzenie czy uzytkownik dodaje pierwszy pokoj
    if (pierwszy_pokoj == nullptr) {
        cout << "Podaj numer pokoju: ";
        nowy_pokoj->numer_pokoju = stoi(checkValid("^[0-9]+$", "Podales zle dane, sprobuj ponownie",
                                                   "Podaj numer pokoju (dodatnia liczba calkowita): "));;
    } else  // sprawdzenie czy dodajemy drugi pokoj o takim samym numerze jezeli tak wyswietl komuikat o bledzie
    {
        do {
            Pokoj *temp = pierwszy_pokoj;
            nr_pokoju = stoi(checkValid("^[0-9]+$", "Podales zle dane, sprobuj ponownie",
                                        "Podaj numer pokoju (dodatnia liczba calkowita): "));
            while (temp) {
                if (temp->numer_pokoju == nr_pokoju) {
                    czy_istnieje_pokoj_o_takim_numerze = true;
                    cout << "taki pokoj juz istnieje wpisz inny numer" << endl;
                    break;
                }
                temp = temp->nastepny_pokoj;
                if (temp == nullptr) czy_istnieje_pokoj_o_takim_numerze = false;
            }
        } while (czy_istnieje_pokoj_o_takim_numerze);
        nowy_pokoj->numer_pokoju = nr_pokoju;
    }

    nowy_pokoj->maksymalna_ilosc_osob = stoi(checkValid("^[0-9]+$", "Podano zle dane, sprobuj ponownie",
                                                        "Podaj maksymalna ilosc osob (dodatnia liczba calkowita): "));
    nowy_pokoj->czy_lazienka = stoi(checkValid("^[01]$", "Podano zle dane, sprobuj ponownie",
                                               "Czy dostepna jest lazienka: (1 jezeli tak 0 jezeli nie): "));
    nowy_pokoj->cena_pokoju = stof(checkValid("^[0-9]+(\\.[0-9]+)?$", "Podano zle dane, sprobuj ponownie",
                                              "Podaj cene pokoju (liczba dodatnia): "));
    nowy_pokoj->imie_nazwisko = checkFirstNameAndLastName();

    // jezeli uzytkownik poda puste imie i nazwisko dane o numerze telefonu i datach tez pozostana puste
    // w przeciwnym przypadku uzytkownik podaje reszte danych
    if (nowy_pokoj->imie_nazwisko == " ") {
        nowy_pokoj->nr_telefonu = 0;
        nowy_pokoj->data_rozpoczecia = " ";
        nowy_pokoj->data_zakonczenia = " ";
    } else {
        nowy_pokoj->nr_telefonu = stoi(checkValid("^\\d{9}$", "Podano zle dane, sprobuj ponownie",
                                                  "Podaj numer telefonu (w formacie xxxxxxxxx): "));
        // wpisanie i walidacja daty
        string data_zakonczenia, data_rozpoczecia;
        int aktualny_rok = 2023;
        do
        {
            data_rozpoczecia = checkValid("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$", "Podano zle dane, sprobuj ponownie", "Podaj date rozpoczecia pobytu (w formacie rrrr-mm-dd): ");
            if (stoi(data_rozpoczecia.substr(0,4)) < aktualny_rok) cout << "wystapil blad, podaj date z aktualnym rokiem" << endl;
        } while (stoi(data_rozpoczecia.substr(0,4)) < aktualny_rok);
        nowy_pokoj->data_rozpoczecia = data_rozpoczecia;

        do
        {
            data_zakonczenia = checkValid("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$", "Podano zle dane, sprobuj ponownie", "Podaj date zakonczenia pobytu (w formacie rrrr-mm-dd): ");
        } while (!sprawdzPoprawnoscDatyZakonczenia(nowy_pokoj->data_rozpoczecia, data_zakonczenia));
        nowy_pokoj->data_zakonczenia = data_zakonczenia;
    }

    nowy_pokoj->czy_posilki = stoi(checkValid("^[01]$", "Podano zle dane, sprobuj ponownie",
                                              "Czy dostepne sa posilki: (1 jezeli tak 0 jezeli nie): "));
    // dodanie pokoju do listy
    if (pierwszy_pokoj == nullptr) pierwszy_pokoj = nowy_pokoj;
    else // przejscie na ostatni element listy i dodanie nowego elementu
    {
        Pokoj *temp = pierwszy_pokoj;
        // przejscie na koniec listy
        while (temp->nastepny_pokoj) {
            temp = temp->nastepny_pokoj;
        }
        temp->nastepny_pokoj = nowy_pokoj;
        nowy_pokoj->nastepny_pokoj = nullptr;

    }
}

void database::wyswietlWolnePokojeIDodajIchNumeryDoTablicy(vector<int> &numery) {

    Pokoj *temp = pierwszy_pokoj;

    // sprawdzenie czy w bazie danych sa rekordy
    if (!sprawdzCzyBazaDanychJestPusta()) return;

    cout << "----------------- Wolne pokoje -----------------" << endl;

    while (temp) {
        if (temp->imie_nazwisko == " ") {
            cout << "------------------------------------------------" << endl;
            cout << "Nr. pokoju: " << temp->numer_pokoju << endl;
            cout << "Maksymana ilosc osob: " << temp->maksymalna_ilosc_osob << endl;

            cout << "lazienka: ";
            if (temp->czy_lazienka) cout << "prawda" << endl;
            else cout << "falsz" << endl;

            cout << "Cena pokoju: " << temp->cena_pokoju << endl;

            cout << "Imie i Nazwisko: " << temp->imie_nazwisko << endl;

            if (temp->nr_telefonu == 0) cout << "Nr. telefonu: " << endl;
            else cout << "Nr.telefonu: " << temp->nr_telefonu << endl;

            cout << "Termin rozpoczecia pobytu: " << temp->data_rozpoczecia << endl;
            cout << "Termin zakonczenia pobytu: " << temp->data_zakonczenia << endl;

            cout << "Posilki: ";
            if (temp->czy_posilki) cout << "prawda" << endl;
            else cout << "falsz" << endl;

            // dodanie numeru pokoju do tablicy typu vector w celu pozniejszego sprawdzenia czy uzytkownik wybiera pokoj mozliwy do wynajecia
            numery.push_back(temp->numer_pokoju);
        }
        temp = temp->nastepny_pokoj;
    }
}


void database::wynajmijPokoj() {
    system("cls");

    // sprawdzenie czy sa rekordy w bazie danych
    if (!sprawdzCzyBazaDanychJestPusta()) return;

    // tablica z numerami wolnych pokoi
    vector<int> numery_pokoi;

    // wyswietlenie wolych pokoi i dodanie ich numerow do listy
    wyswietlWolnePokojeIDodajIchNumeryDoTablicy(numery_pokoi);

    // sprawdza czy w bazie danych są pokoje do wynajecia
    if (numery_pokoi.empty()) {
        cout << "Brak pokoi do wynajecia" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }

    bool czy_mozliwy_do_wynajecia = false;
    int numer_pokoju_do_wynajecia;

    // sprawdzenie poprawnosci wpisywanaych danych przez uzytkownika
    // oraz sprawdzenie czy pokoj jest mozliwy na wynajem
    do {
        numer_pokoju_do_wynajecia = stoi(checkValid("^[0-9]+$", "Wystapil blad sprobuj ponownie",
                                                    "\nPodaj numer pokoju ktory chcesz wynajac (mozna wybrac tylko jeden z wyswietlonych pokoi): "));
        for (int i : numery_pokoi) {
            // sprawdzenie czy numer pokoju znajduje sie w tablicy
            // jezeli tak to mozliwy jest wynajem
            // jezeli nie to prosi o wprowadzeniu numeru jeszcze raz
            if (i == numer_pokoju_do_wynajecia) czy_mozliwy_do_wynajecia = true;
        }

        if (!czy_mozliwy_do_wynajecia)
        {
            cout << "Pokoj niemozliwy do wynajecia lub nie istnieje" << endl;
            system("pause>0");
        }
    } while (!czy_mozliwy_do_wynajecia);

    Pokoj *temp = pierwszy_pokoj;
    // przejscie do pokoju ktory ma wybrany przez uzytkownika numer
    while (temp->numer_pokoju != numer_pokoju_do_wynajecia) {
        temp = temp->nastepny_pokoj;
    }

    system("cls");

    int aktualny_rok = 2023;
    string data_rozpoczecia, data_zakonczenia;

    // wprowadzenie przez uzytkownika danych osoby wynajmujacej
    cout << "---------------------- Podaj dane ----------------------" << endl;
    temp->imie_nazwisko = checkFirstAndLastNameGettering();
    temp->nr_telefonu = stoi(checkValid("^\\d{9}$", "Podano zle dane, sprobuj ponownie",
                                        "Podaj numer telefonu (w formacie xxxxxxxxx): "));
    // wpisanie i walidacja daty
    do
    {
        data_rozpoczecia = checkValid("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$", "Podano zle dane, sprobuj ponownie", "Podaj date rozpoczecia pobytu (w formacie rrrr-mm-dd): ");
        if (stoi(data_rozpoczecia.substr(0,4)) < aktualny_rok) cout << "wystapil blad, podaj date z aktualnym rokiem" << endl;
    } while (stoi(data_rozpoczecia.substr(0,4)) < aktualny_rok);
    temp->data_rozpoczecia = data_rozpoczecia;

    do
    {
        data_zakonczenia = checkValid("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$", "Podano zle dane, sprobuj ponownie", "Podaj date zakonczenia pobytu (w formacie rrrr-mm-dd): ");
    } while (!sprawdzPoprawnoscDatyZakonczenia(temp->data_rozpoczecia, data_zakonczenia));
    temp->data_zakonczenia = data_zakonczenia;

    system("cls");
    cout << "Wynajecie pokoju przebieglo pomyslnie. Zyczymy udanego pobytu" << endl;
    cout << "Wcisnij enter aby kontynuowac" << endl;
    system("pause>0");
}


void database::zmienDanePokoju() {
    system("cls");
    // sprawdzenie czy w bazie danych sa rekordy
    if (!sprawdzCzyBazaDanychJestPusta()) return;

    Pokoj *temp = pierwszy_pokoj;

    // wyswietlenie dostepnych numerow pokoi
    cout << "Dostepne numery pokoi:" << endl;
    while (temp) {
        cout << temp->numer_pokoju << ", ";
        temp = temp->nastepny_pokoj;
    }
    // ponowne ustawienie na pierwszy element
    temp = pierwszy_pokoj;

    // sprawdzenie czy uzytkownik wprowadza poporawne dane
    string numer_pokoju_do_zmiany;
    numer_pokoju_do_zmiany = checkValid("^[0-9]+$", "Wystapil blad sprobuj ponownie",
                                        "\nPodaj numer pokoju (dodatnia liczba calkowita): ");
    string tempStringValue;

    // przejscie na szukany element jezeli nie istnieje wyswietla komunikat
    while (temp) {
        // nadanie wartosci szukanemu pokojowi
        // kazda wartosc wprowadzana przez urzytkownika jest sprawdzana
        // jezeli uzytkownik wpisze "zostaw" wartosc zmiennej pozostanie niezmieniona
        if (temp->numer_pokoju == stoi(numer_pokoju_do_zmiany)) {
            cout << "Zmiana danych pokoju, wpisz 'zostaw' jezeli ma pozostac bez zmian" << endl;

            tempStringValue = to_string(temp->numer_pokoju);
            temp->numer_pokoju = stoi(checkValidEditValue("^[0-9]+$", "Wystapil blad sprobuj ponownie",
                                                          "Numer pokoju (dodatnia liczba calkowita): ",
                                                          tempStringValue));

            tempStringValue = to_string(temp->maksymalna_ilosc_osob);
            temp->maksymalna_ilosc_osob = stoi(checkValidEditValue("^[0-9]+$", "Wystapil blad sprobuj ponownie",
                                                                   "Maksymalna ilosc osob (dodatnia liczba calkowita): ",
                                                                   tempStringValue));

            tempStringValue = to_string(temp->czy_lazienka);
            temp->czy_lazienka = stoi(checkValidEditValue("^[01]$", "Wystapil blad sprobuj ponownie",
                                                          "Czy dostepna jest lazienka (1 jezeli tak 0 jezeli nie): ",
                                                          tempStringValue));

            tempStringValue = to_string(temp->cena_pokoju);
            temp->cena_pokoju = stof(checkValidEditValue("^[0-9]+(\\.[0-9]+)?$", "Wystapil blad sprobuj ponownie",
                                                         "Cena pokoju (liczba dodatnia): ", tempStringValue));

            temp->imie_nazwisko = checkFisrstNameAndLastNameEditValue(temp->imie_nazwisko);

            tempStringValue = to_string(temp->nr_telefonu);
            temp->nr_telefonu = stoi(checkValidEditValue("^\\d{9}$", "Wystapil blad sprobuj ponownie",
                                                         "Numer telefonu (w formacie xxxxxxxxx): ", tempStringValue));

            tempStringValue = temp->data_rozpoczecia;
            temp->data_rozpoczecia = checkValidEditValue("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$",
                                                         "Wystapil blad sprobuj ponownie",
                                                         "Data rozpoczecia pobytu (w formacie rrrr-mm-dd): ",
                                                         tempStringValue);

            tempStringValue = temp->data_zakonczenia;
            temp->data_zakonczenia = checkValidEditValue("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$",
                                                         "Wystapil blad sprobuj ponownie",
                                                         "Data zakonczenia pobytu (w formacie rrrr-mm-dd): ",
                                                         tempStringValue);

            tempStringValue = to_string(temp->czy_posilki);
            temp->czy_posilki = stoi(checkValidEditValue("^[01]$", "Wystapil blad sprobuj ponownie",
                                                         "Czy dostepne sa posilki (1 jezeli tak 0 jezeli nie): ",
                                                         tempStringValue));

            system("cls");
            cout << "Dane zostaly zmienione posmyslne" << endl;
            cout << "Wcisnij enter aby kontynuowac" << endl;
            system("pause>0");
            return;
        }
        temp = temp->nastepny_pokoj;
    }
    cout << "Pokoj o takim numerze nie istnieje" << endl;
    cout << "Wcisnij enter aby kontynuowac" << endl;
    system("pause>0");
}

void database::usunPokoj() {
    system("cls");
    // sprawdzenie czy w bazie danych sa rekordy
    if (!sprawdzCzyBazaDanychJestPusta()) return;

    string id;
    system("cls");
    id = checkValid("^[0-9]+$", "Wystapil blad sprobuj ponownie",
                    "Podaj ID pokoju do usuniecia (pokoje numerowane sa od 1): ");

    // sprawdzenie czy usuwamy pierwszy element tablicy
    if (stoi(id) == 1) {
        Pokoj *temp = pierwszy_pokoj;
        pierwszy_pokoj = temp->nastepny_pokoj;
        delete temp;

        system("cls");
        cout << "Pokoj zostal usuniety pomyslnie" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }

    int x = 1;

    Pokoj *temp = pierwszy_pokoj;

    // wskazanie na element n-1
    while (temp) {
        if (x + 1 == stoi(id)) break;

        temp = temp->nastepny_pokoj;
        x++;
        if (temp->nastepny_pokoj == nullptr) {
            system("cls");
            cout << "Taki pokoj nie istnieje. Wcisnij enter aby kontynuowac" << endl;
            system("pause>0");
            return;
        }

    }

    // sprawdzenie czy usuwamy ostatni element listy
    // jezeli tak usun ostatni element oraz zamien wskaznik przedostatniego elementu tan nullptr
    if (temp->nastepny_pokoj->nastepny_pokoj == nullptr) {
        delete temp->nastepny_pokoj;
        temp->nastepny_pokoj = nullptr;

        system("cls");
        cout << "Pokoj zostal usuniety pomyslnie" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }

    Pokoj *to_delete = temp->nastepny_pokoj; // wskazanie z elementu n-1 na element n
    temp->nastepny_pokoj = temp->nastepny_pokoj->nastepny_pokoj;
    delete to_delete;

    system("cls");
    cout << "Pokoj zostal usuniety pomyslnie" << endl;
    cout << "Wcisnij enter aby kontynuowac" << endl;
    system("pause>0");

}

void database::wyswietlBazeDanych() {

    system("cls");
    Pokoj *temp = pierwszy_pokoj;

    if (!sprawdzCzyBazaDanychJestPusta()) return;

    int index = 1;

    while (temp) {
        cout << "--------------- [" << index << "] ---------------" << endl;
        cout << "Nr. pokoju: " << temp->numer_pokoju << endl;
        cout << "Maksymana ilosc osob: " << temp->maksymalna_ilosc_osob << endl;

        cout << "lazienka: ";
        if (temp->czy_lazienka) cout << "prawda" << endl;
        else cout << "falsz" << endl;

        cout << "Cena pokoju: " << temp->cena_pokoju << endl;

        cout << "Imie i Nazwisko: " << temp->imie_nazwisko << endl;
        if (temp->nr_telefonu == 0) cout << "Nr. telefonu: " << endl;
        else cout << "Nr.telefonu: " << temp->nr_telefonu << endl;

        cout << "Termin rozpoczecia pobytu: " << temp->data_rozpoczecia << endl;
        cout << "Termin zakonczenia pobytu: " << temp->data_zakonczenia << endl;

        cout << "Posilki: ";
        if (temp->czy_posilki) cout << "prawda" << endl;
        else cout << "falsz" << endl;

        temp = temp->nastepny_pokoj;
        index++;
    }

    cout << "\nWcisnij enter aby kontynuowac" << endl;
    system("pause>0");
}


// funkcja docelowow zapisuje bazy danych w folderze save_databases
void database::zapiszBazeDanych() {

    system("cls");
    string database_name;

    // sprawdzenie czy baza danych nie jest pusta jezeli tak konczy dzialanie funkcji
    if (!sprawdzCzyBazaDanychJestPusta()) return;

    Pokoj *temp = pierwszy_pokoj;

    database_name = checkValid(".*\\.txt$", "Wystapil blad sprobuj ponownie",
                               "wprowadz nazwe bazy danych z koncowka .txt: ");
    ifstream file("../save_databases/" + database_name);
    if (file.good()) {
        cout << "Baza danych o takiej nazwie juz istnieje" << endl;
        cout << "Wcisnij enter aby kontunuowac" << endl;
        system("pause>0");
        file.close();
        return;
    }

    // zamkniecie pliku sprawdzajacego czy istnieje juz plik o takiej nazwie
    file.close();

    fstream database_file("save_databases/" + database_name, ios::out);
    string rekord_bazy_danych = "";

    while (temp) {
        rekord_bazy_danych += to_string(temp->numer_pokoju) + ";";
        rekord_bazy_danych += to_string(temp->maksymalna_ilosc_osob) + ";";
        rekord_bazy_danych += to_string(temp->czy_lazienka) + ";";
        rekord_bazy_danych += to_string(temp->cena_pokoju) + ";";
        rekord_bazy_danych += temp->imie_nazwisko + ";";

        // sprawdzenie czy numer telefonu jest rowny 0 co oznacza ze jest pusty jezeli tak do pliku wpisywana jest spacja w przeciwnym razie numer telefonu
        if (temp->nr_telefonu == 0) rekord_bazy_danych += " ;";
        else rekord_bazy_danych += to_string(temp->nr_telefonu) + ";";

        rekord_bazy_danych += temp->data_rozpoczecia + ";";
        rekord_bazy_danych += temp->data_zakonczenia + ";";
        rekord_bazy_danych += to_string(temp->czy_posilki) + "\n";

        // wpisanie do pliku rekordu
        database_file << rekord_bazy_danych;
        rekord_bazy_danych = "";
        temp = temp->nastepny_pokoj;
    }
    database_file.close();


    system("cls");
    cout << "Baza danych zostala zapisana pomyslnie w folderze 'save_databases'" << endl;
    cout << "\nWcisnij enter aby kontynuowac" << endl;
    system("pause>0");
}

// wstepny projekt wczytywania bazy danych do programu
void database::wczytajBazeDanych() {

    system("cls");

    pierwszy_pokoj = nullptr;
    string file_path = "../save_databases/database.txt";
    fstream database_file;
    do {
//        cout << "Podaj sciezkie dostepu do pliku bazodanowego (txt): ";
//        cin >> file_path;

        database_file.open(file_path, ios::in);
        if (!database_file.is_open()) {
            system("cls");
            cout << "Podano niepoprawna sciezke do pliku" << endl;
        }
    } while (!database_file.is_open());

    string linia, tablica_wartosci[9];

    while (getline(database_file, linia)) // przekazywanie wiersza z pliku do zmiennej wewnątrz warunku petli
    {
        splitString(linia, tablica_wartosci);

        Pokoj *nowy_pokoj = new Pokoj;

        try
        {
            nowy_pokoj->numer_pokoju = stoi(tablica_wartosci[0]);
            nowy_pokoj->maksymalna_ilosc_osob = stoi(tablica_wartosci[1]);
            nowy_pokoj->czy_lazienka = stringToBoolConvert(tablica_wartosci[2]);
            nowy_pokoj->cena_pokoju = stof(tablica_wartosci[3]);
            nowy_pokoj->imie_nazwisko = tablica_wartosci[4];

            if (tablica_wartosci[5] == " ") nowy_pokoj->nr_telefonu = 0;
            else nowy_pokoj->nr_telefonu = stoi(tablica_wartosci[5]);

            nowy_pokoj->data_rozpoczecia = tablica_wartosci[6];
            nowy_pokoj->data_zakonczenia = tablica_wartosci[7];
            nowy_pokoj->czy_posilki = stringToBoolConvert(tablica_wartosci[8]);

        }
        catch (std::invalid_argument& e)
        {
            cerr << "Wystapil blad baza danych nie zostala wczytana" << endl;
            cout << "Wcisnij enter aby kontynuowac" << endl;
            system("pause>0");
            return;
        }
        // --------------- dodawanie dowego rekordu bazy danych -----------------------
        // sprawdzenie czy dodajemy pierwszy element
        if (pierwszy_pokoj == nullptr) pierwszy_pokoj = nowy_pokoj;
        else {
            Pokoj *temp = pierwszy_pokoj;

            // przejscie przez wskazniki na koniec listy
            while (temp->nastepny_pokoj) {
                temp = temp->nastepny_pokoj;
            }

            temp->nastepny_pokoj = nowy_pokoj;
            nowy_pokoj->nastepny_pokoj = nullptr;
        }
    }

    // zamkniecie pliku bazodanowego
    database_file.close();

    system("cls");
    cout << "Udalo sie wczytac baze danych" << endl;
    cout << "Wcisnij enter aby kontynuowac" << endl;
    system("pause>0");
}