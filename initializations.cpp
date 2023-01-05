#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "header.h"
#include <vector>

using namespace std;

Pokoj::Pokoj()
{
    nastepny_pokoj = nullptr;
}

database::database()
{
    pierwszy_pokoj = nullptr;
}

void generateMainMenu()
{
    // wygenerowanie boxa wraz z nagłówkiem
    cout << char(218);      for (int i = 0; i < 39; i++) { cout << char(196); }      cout << char(191) << endl;
    cout << char(179) << "  System rezerwacji pokoi hotelowych   " << char(179) << endl;
    cout << char(192);      for (int i = 0; i < 39; i++) { cout << char(196); }      cout << char(217) << endl;

    cout << "\n[1] wynajmij pokoj" << endl;
    cout << "[2] wyszukaj pokoj" << endl;
    cout << "[3] operacje na bazie danych" << endl;
    cout << "[4] import/export bazy danych" << endl;
    cout << "[5] zakoncz" << endl;
}


void databaseOptionsMenu(database *&pokoje)
{
    int choose = 0;

    // wyswietlenie menu
    while (true)
    {

        system("cls");
        cout << char(218);      for (int i = 0; i < 22; i++) { cout << char(196); }      cout << char(191) << endl;
        cout << char(179) << "  Opcje bazy danych   " << char(179) << endl;
        cout << char(192);      for (int i = 0; i < 22; i++) { cout << char(196); }      cout << char(217) << endl;
        cout << "\n[1] dodaj pokoj" << endl;
        cout << "[2] usun pokoj" << endl;
        cout << "[3] zmien dane pokoju" << endl;
        cout << "[4] wyswietl wszystkie pokoje" << endl;
        cout << "[5] powrot" << endl;

        cout << "Wybor: ";
        cin >> choose;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Wybor: ";
            cin>>choose;
        }

        switch (choose)
        {
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



void importExportMenu(database *&pokoje)
{
    int choose;

    while (true)
    {
        system("cls");
        cout << char(218);      for (int i = 0; i < 17; i++) { cout << char(196); }      cout << char(191) << endl;
        cout << char(179) << "  Zapis/Odczyt   " << char(179) << endl;
        cout << char(192);      for (int i = 0; i < 17; i++) { cout << char(196); }      cout << char(217) << endl;

        cout << "\n[1] zapisz baze danych" << endl;
        cout << "[2] wczytaj baze danych" << endl;
        cout << "[3] powrot" << endl;
        cout << "Wybor: ";
        cin >> choose;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Wybor: ";
            cin>>choose;
        }

        switch (choose)
        {
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


void searchMenu(database *&pokoje)
{
    int choose = 0;
    while (true)
    {
        system("cls");
        cout << char(218);      for (int i = 0; i < 12; i++) { cout << char(196); }      cout << char(191) << endl;
        cout << char(179) << "  Wyszukaj  " << char(179) << endl;
        cout << char(192);      for (int i = 0; i < 12; i++) { cout << char(196); }      cout << char(217) << endl;

        cout << "\n[1] wyszukaj po nr pokoju" << endl;
        cout << "[2] wyszukaj po imieniu i nazwisku" << endl;
        cout << "[3] wyszukaj przez wyrazenia reguralnie" << endl;
        cout << "[4] powrot" << endl;
        cout << "wybor: ";
        cin >> choose;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Wybor: ";
            cin>>choose;
        }

        switch (choose) {
            case 1:
                break;
            case 2:
                break;
            case 3:
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

std::string checkFirstNameAndLastName()
{
    string imie_nazwisko;
    cout << "Podaj imie i nazwisko (wpisz 'puste' jezeli ma pozostac puste): ";
    cin.clear();
    cin.ignore();
    getline(cin, imie_nazwisko);
    if (imie_nazwisko == "puste") return " ";
    else return imie_nazwisko;
}


std::string checkDate(std::string pattern, std::string failInfo, std::string whatToInsertInformation)
{
    string to_check;
    std::regex wzor(pattern);
    do
    {
        cout << whatToInsertInformation;
        cin >> to_check;
        if (!regex_match(to_check, wzor)) cout << failInfo << endl;

    } while (!regex_match(to_check, wzor));
    return to_check;
}

std::string checkPhoneNumber(std::string pattern, std::string failInfo, std::string whatToInsertInformation)
{
    string to_check;
    std::regex wzor(pattern);
    do
    {
        cout << whatToInsertInformation;
        cin >> to_check;
        if (!regex_match(to_check, wzor)) cout << failInfo << endl;

    } while (!regex_match(to_check, wzor));
    return to_check;
}

string checkValid(std::string pattern, std::string failInfo, std::string whatToInsertInformation){
    string to_check;
    std::regex wzor(pattern);
    do
    {
        cout << whatToInsertInformation;
        cin >> to_check;
        if (!regex_match(to_check, wzor)) cout << failInfo << endl;

    } while (!regex_match(to_check, wzor));
    return to_check;
}

void database::dodajPokoj()
{
    int nr_pokoju;
    bool czy_istnieje = true;

    Pokoj *nowy_pokoj = new Pokoj;

    // sprawdzenie czy uzytkownik dodaje pierwszy pokoj
    if (pierwszy_pokoj == nullptr)
    {
        cout << "Podaj numer pokoju: ";
        nowy_pokoj->numer_pokoju = stoi(checkValid("^[0-9]+$", "Podales zle dane, sproboj ponownie", "Podaj numer pokoju (dodatnia liczba calkowita): "));;
    }
    else  // sprawdzenie czy dodajemy drugi pokoj o takim samym numerze jezeli tak wyswietl komuikat o bledzie
    {
        do {
            Pokoj *temp = pierwszy_pokoj;
            nr_pokoju = stoi(checkValid("^[0-9]+$", "Podales zle dane, sproboj ponownie", "Podaj numer pokoju (dodatnia liczba calkowita): "));
            while (temp) {
                if (temp->numer_pokoju == nr_pokoju) {
                    czy_istnieje = true;
                    cout << "taki pokoj juz istnieje wpisz inny numer" << endl;
                    break;
                }
                temp = temp->nastepny_pokoj;
                if (temp == nullptr) czy_istnieje = false;
            }
        } while (czy_istnieje);
        nowy_pokoj->numer_pokoju = nr_pokoju;
    }

    nowy_pokoj->maksymalna_ilosc_osob = stoi(checkValid("^[0-9]+$", "Podano zle dane, sproboj ponownie", "Podaj maksymalna ilosc osob (dodatnia liczba calkowita): "));
    nowy_pokoj->lazienka = stoi(checkValid("^[01]$", "Podano zle dane, sproboj ponownie", "Czy dostepna jest lazienka: (1 jezeli tak falsz 0 nie):"));
    nowy_pokoj->cena_pokoju = stof(checkValid("^[0-9]+(\\.[0-9]+)?$","Podano zle dane, sproboj ponownie", "Podaj cene pokoju (liczba dodatnia) (: "));
    nowy_pokoj->imie_nazwisko = checkFirstNameAndLastName();

    // jezeli uzytkownik poda puste imie i nazwisko dane o numerze telefonu i datach tez pozostana puste
    // w przeciwnym przypadku uzytkownik podaje reszte danych
    if (nowy_pokoj->imie_nazwisko == " ")
    {
        nowy_pokoj->nr_telefonu = 0;
        nowy_pokoj->data_rozpoczecia = " ";
        nowy_pokoj->data_zakonczenia = " ";
    }
    else
    {
        nowy_pokoj->nr_telefonu = stoi(checkPhoneNumber("^\\d{9}$", "Podano zle dane, sproboj ponownie", "Podaj numer telefonu (wpisz 'puste' jezeli ma pozostac puste): "));
        nowy_pokoj->data_rozpoczecia = checkDate("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$", "Podano zle dane, sproboj ponownie", "Podaj date rozpoczecia pobytu (w formacie rrrr-mm-dd): ");
        nowy_pokoj->data_zakonczenia = checkDate("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$", "Podano zle dane, sproboj ponownie", "Podaj date zakonczenia pobytu (w formacie rrrr-mm-dd): ");
    }
    nowy_pokoj->czy_posilki = stoi(checkValid("^[01]$", "Podano zle dane, sproboj ponownie", "Czy dostepne sa posilki: (1 jezeli tak 0 jezeli nie): "));

    // dodanie pokoju do listy
    if (pierwszy_pokoj == nullptr) pierwszy_pokoj = nowy_pokoj;
    else // przejscie na ostatni element listy i dodanie nowego elementu
    {
        Pokoj *temp = pierwszy_pokoj;
        // przejscie na koniec listy
        while (temp->nastepny_pokoj)
        {
            temp = temp->nastepny_pokoj;
        }
        temp->nastepny_pokoj = nowy_pokoj;
        nowy_pokoj->nastepny_pokoj = nullptr;
    }
}

void database::wyswietlWolnePokojeIDodaIchNumeryDoTablicy(vector <int> &numery)
{

    Pokoj *temp = pierwszy_pokoj;

    if (temp == nullptr)
    {
        cout << "Brak elementow w bazie danych lub nie dodano bazy danych" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }

    cout << "----------------- Wolne pokoje -----------------" << endl;

    while (temp)
    {
        if (temp->imie_nazwisko == " ")
        {
            cout << "------------------------------------------------" << endl;
            cout << "Nr. pokoju: " << temp->numer_pokoju << endl;
            cout << "Maksymana ilosc osob: " << temp->maksymalna_ilosc_osob << endl;

            cout << "lazienka: ";
            if (temp->lazienka) cout << "prawda" << endl;
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


void database::wynajmijPokoj()
{
    vector <int> numery_pokoi;
    system("cls");

    wyswietlWolnePokojeIDodaIchNumeryDoTablicy(numery_pokoi);

    system("pause>0");
}

void database::zmienDanePokoju()
{

}

void database::usunPokoj()
{
    if (pierwszy_pokoj == nullptr)
    {
        cout << "Brak elementow w bazie danych" << endl;
        cout << "wcisnij enter aby kontynowac" << endl;
        system("pause>0");
        return;
    }

    string id;
    system("cls");
    id = checkValid("^[0-9]+$", "Wystapil blad sproboj ponownie", "Podaj ID pokoju do usuniecia (pokoje numerowane są od 1): ");

    if (stoi(id) == 1)
    {
        Pokoj *temp = pierwszy_pokoj;
        pierwszy_pokoj = temp->nastepny_pokoj;
        delete temp;
        cout << "Pokoj zostal usuniety pomyslnie" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }

    int x = 1;

    Pokoj *temp = pierwszy_pokoj;

    // wskazanie na element n-1
    while (temp)
    {
        if (x + 1 == stoi(id)) break;

        temp = temp->nastepny_pokoj;
        x++;
        if (temp->nastepny_pokoj == nullptr)
        {
            cout << "Taki pokoj nie istnieje. Wcisnij enter aby kontynuowac" << endl;
            system("pause>0");
            return;
        }

    }

    // sprawdzenie czy usuwamy ostatni element listy
    // jezeli tak usun ostatni element oraz zamien wskaznik przedostatniego elementu tan nullptr
    if(temp->nastepny_pokoj->nastepny_pokoj == nullptr)
    {
        delete temp->nastepny_pokoj;
        temp->nastepny_pokoj = nullptr;
        cout << "Pokoj zostal usuniety pomyslnie" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }

    Pokoj *to_delete = temp->nastepny_pokoj; // wskazanie z elementu n-1 na element n
    temp->nastepny_pokoj = temp->nastepny_pokoj->nastepny_pokoj;
    delete to_delete;
    cout << "Pokoj zostal usuniety pomyslnie" << endl;
    cout << "Wcisnij enter aby kontynuowac" << endl;
    system("pause>0");

}

void database::wyswietlBazeDanych()
{

     Pokoj *temp = pierwszy_pokoj;

     if (temp == nullptr)
     {
         cout << "Brak elementow w bazie danych lub nie dodano bazy danych" << endl;
         cout << "Wcisnij enter aby kontynuowac" << endl;
         system("pause>0");
         return;
     }

     int index = 1;

     while (temp)
     {
         cout << "--------------- [" << index <<"] ---------------" << endl;
         cout << "Nr. pokoju: " << temp->numer_pokoju << endl;
         cout << "Maksymana ilosc osob: " << temp->maksymalna_ilosc_osob << endl;

         cout << "lazienka: ";
         if (temp->lazienka) cout << "prawda" << endl;
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

     cout << "\bWcisnij enter aby kontynuowac" << endl;
     system("pause>0");
}


// funkcja docelowow zapisuje bazy danych w folderze save_databases
void database::zapiszBazeDanych()
{
    string database_name;
    system("cls");

    // sprawdzenie czy baza danych nie jest pusta jezeli tak konczy dzialanie funkcji
    Pokoj *temp = pierwszy_pokoj;
    if (temp == nullptr)
    {
        cout << "Baza danych jest pusta" << endl;
        cout << "Wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }


    database_name = checkValid(".*\\.txt$", "Wystapil blad sproboj ponownie", "wprowadz nazwe bazy danych z koncowka .txt: ");
    ifstream file("../save_databases/" + database_name);
    if (file.good())
    {
        cout << "Baza danych o takiej nazwie juz istnieje" << endl;
        cout << "Wcisnij enter aby kontunuowac" << endl;
        system("pause>0");
        file.close();
        return;
    }

    // zamkniecie pliku sprawdzajacego czy istnieje juz plik o takiej nazwie
    file.close();

    fstream database_file("../save_databases/" + database_name, ios::out);
    string database_record = "";

    while (temp)
    {
        database_record += to_string(temp->numer_pokoju) + ";";
        database_record += to_string(temp->maksymalna_ilosc_osob) + ";";
        database_record += to_string(temp->lazienka) + ";";
        database_record += to_string(temp->cena_pokoju) + ";";
        database_record += temp->imie_nazwisko + ";";
        // sprawdzenie czy numer telefonu jest rowny 0 co oznacza ze jest pusty jezeli tak do pliku wpisywana jest spacja w przeciwnym razie numer telefonu
        if (temp->nr_telefonu == 0) database_record += " ;";
        else database_record += to_string(temp->nr_telefonu) + ";";

        database_record += temp->data_rozpoczecia + ";";
        database_record += temp->data_zakonczenia + ";";
        database_record += to_string(temp->czy_posilki) + "\n";

        // wpisanie do pliku rekordu
        database_file << database_record;
        database_record = "";
        temp = temp->nastepny_pokoj;
    }
    database_file.close();
    cout << "\nWcisnij enter aby kontynuowac" << endl;
    system("pause>0");

}


// funkcja rozdziela pojedynczy wiersz bazy danych na pojedyncze wartosci i zapisuje je do tablicy
void splitString(std::string &rekord, std::string tab[])
{
    string pojedyncza_wartosc_rekordu;
    int i = 0;
    stringstream objekt_pomocniczy(rekord); // stworzenie obiketu stream ktory pozwala na rozdzielenie stringa
    while (getline(objekt_pomocniczy, pojedyncza_wartosc_rekordu, ';'))
    {
        tab[i] = pojedyncza_wartosc_rekordu;
        i++;
    }
}

bool stringToBoolConvert(std::string &wartosc_zmieniana)
{
    if (wartosc_zmieniana == "1") return true;
    return false;
}


// wstepny projekt wczytywania bazy danych do programu
void database::wczytajBazeDanych()
{

    if(pierwszy_pokoj != nullptr)
    {
        cout << "Zapisz aktualna baze danych aby moc wczytac nowa" << endl;
        cout << "wcisnij enter aby kontynuowac" << endl;
        system("pause>0");
        return;
    }
    system("cls");
    string file_path;
    fstream database_file;
    do
    {
        cout << "Podaj sciezkie dostepu do pliku bazodanowego (txt): ";
        cin >> file_path;

        database_file.open(file_path, ios::in);
        if (!database_file.is_open())
        {
            system("cls");
            cout << "Podano niepoprawna sciezke do pliku" << endl;
        }
    } while(!database_file.is_open());

    string linia, tablica_wartosci[9];

    while(getline(database_file, linia)) // przekazywanie wiersza z pliku do zmiennej wewnątrz warunku petli
    {
        splitString(linia, tablica_wartosci);

        Pokoj *nowy_pokoj = new Pokoj;

        nowy_pokoj->numer_pokoju = stoi(tablica_wartosci[0]);
        nowy_pokoj->maksymalna_ilosc_osob = stoi(tablica_wartosci[1]);
        nowy_pokoj->lazienka = stringToBoolConvert(tablica_wartosci[2]);
        nowy_pokoj->cena_pokoju = stof(tablica_wartosci[3]);
        nowy_pokoj->imie_nazwisko = tablica_wartosci[4];

        if(tablica_wartosci[5] == " ") nowy_pokoj->nr_telefonu = 0;
        else nowy_pokoj->nr_telefonu = stoi(tablica_wartosci[5]);

        nowy_pokoj->data_rozpoczecia = tablica_wartosci[6];
        nowy_pokoj->data_zakonczenia = tablica_wartosci[7];
        nowy_pokoj->czy_posilki = stringToBoolConvert(tablica_wartosci[8]);

        // --------------- dodawanie dowego rekordu bazy danych -----------------------
        // sprawdzenie czy dodajemy pierwszy element
        if (pierwszy_pokoj == nullptr) pierwszy_pokoj = nowy_pokoj;
        else
        {
            Pokoj *temp = pierwszy_pokoj;

            // przejscie przez wskazniki na koniec listy
            while(temp->nastepny_pokoj)
            {
                temp = temp->nastepny_pokoj;
            }

            temp->nastepny_pokoj = nowy_pokoj;
            nowy_pokoj->nastepny_pokoj = nullptr;
        }
    }

    database_file.close();
    cout << "Udalo sie wczytac baze danych. Wcisnij enter aby kontynuowac";
    system("pause>0");
}