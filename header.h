#pragma once
#include <iostream>
#include <vector>


// Stworzenie listy jednokierunkowej
// struktura rekurdu w bazie danych
struct Pokoj
{
    int numer_pokoju; // dodatnia liczba calkowita. przyjmuje ze jest to klucz glowny calej bazy danych wiec musi byc nukatowy
    int maksymalna_ilosc_osob; // dodatnia liczba calkowita
    bool czy_lazienka; // wartosc true/false
    float cena_pokoju; // dodadnia liczba zmiennoprzecinkoa
    std::string imie_nazwisko; // dowolny ciag znakow
    int nr_telefonu; // dodatnia liczba calkowita w formacie xxxxxxxxx
    std::string data_rozpoczecia; // rrrr.mm.dd
    std::string data_zakonczenia; // rrrr.mm.dd
    bool czy_posilki; // jezeli pokoj nie jest wynajety to falsz

    Pokoj* nastepny_pokoj; // wskaznik na nastepny pokoj

    Pokoj(); // konstruktor
};


// glowna struktura
struct database
{
    Pokoj *pierwszy_pokoj; // wskaznik na pierwszy pokoj w liscie
    // funkcja dodaje pokoj do bazdy danych
    // sprawdza czy uzytkownik dodaje drugi pokoj o takim smaymu numerze
    // jezeli tak to zwraca blad i prosi o wybranie innego numeru
    // numer pokoju jest uznany na klucz glowny bazy danych
    void dodajPokoj();
    // funkcja zamienia pokoj na wynajety i wyswietla dostepne pokoje
    void wynajmijPokoj(); // do zrobienia
    // funkcja zmienia dane rekordu w bazie danych
    void zmienDanePokoju(); // do zrobienia
    // funkja usuwa pokoj z bazy danych
    void usunPokoj();
    // funkcja wyswietla cala baze danych
    void wyswietlBazeDanych();
    //fukcja wyszukuje pokoj w liscie o podanym numerze pokoju oraz go wysweitla
    void wyszukajPoNumerzePokoju();
    // funkcja wyszukuje pokoje w liscie o podanym imieniu i nazwisku oraz go wysweitla
    void wyszukajPoImieniuINazwisku();
    // funkcja wszukuje wszystkie pokokje ktorych jakas wartosc pasuje do podanego ciagu znakow oraz je wyswietl
    void wyszukajZaPomocaWyrazenRegularnych();
    // wyswietla pokoje do wynajęcia
    // i dodaje ich numery do tablicy typu vector aby sprawdzic czy uzytkownik wybiera pokoj ktory jest mozliwy do wyboru
    void wyswietlWolnePokojeIDodajIchNumeryDoTablicy(std::vector <int> &numery);
    // funkcja zapisuje baze danych do pliku w folderze save_databases
    void zapiszBazeDanych();
    // funkcja wczytuje baze danych z pliku z dowolnego miejsca na dysku
    void wczytajBazeDanych();
    // funkcja sprawdza czy baza danych jest pusta
    // jezeli tak wyswietla odowiedni komunikat
    bool sprawdzCzyBazaDanychJestPusta();
    database();

};


//funkcja generujaca menu glowne
void generateMainMenu();

//wygenerowanie menu dzialan na bazie danych wraz z menu opcji i odwolaniami do funkcji
// przyjmuje obiekt struktury pokoje jako argument
void databaseOptionsMenu(database *&pokoje);

//wygenerowanie menu importu i eksportu wraz z menu opcji i odwolaniami do funkcji
// przyjmuje obiekt struktury pokoje jako argument
void importExportMenu(database *&pokoje);

//wygenerowanie menu wyszukiwania wraz z menu opcji i odwolaniami do funkcji
// przyjmuje obiekt struktury pokoje jako argument
void searchMenu(database *&pokoje);

//funckja rozdziela jeden wiersz na poszczegolne wartosc rozdzielone srednikami
// zmienna przekazana referencyjnie do zmiennej przechowuje pojedynczy wyraz
void splitString(std::string &rekord, std::string tab[]);

// funkcja zamenia string true/false na bool true/false
bool stringToBoolConvert(std::string &record);

// funkcja sprawdzająca zgodność z wyrazeniem regularnym wpisanych przez użytkownika danych
// zwraca wartosc string jezeli zgadza sie z patternem podanym jako argument funkkcji
std::string checkValid(std::string pattern, std::string failInfo, std::string whatToInsertInformation);

// Funkcja sprawdza czy uzytkownik wprowadzil imie i nazwisko jezeli wpisal "puste" lub pozostawil puste zwraca pusty ciag znakow
std::string checkFirstNameAndLastName();

// funkcja sprawdza czy uzytkownik wprowadzil poprawne dane podaczas zmiany wartosci pokoju
std::string checkFirstAndLastNameGettering();

// funkcja sprawdza poprawnosc wpisanych danych przez uzytkownika podaczas zmieniania wartosci juz istniejacego pokoju w liscie
// jezeli uzytkownik wpisze "zostaw" wartosc zmieniana pozostanie taka sama
// zwraca ciag znakow
std::string checkValidEditValue(std::string pattern, std::string failInfo, std::string whatToInsertInformation, std::string previousValue);

// funkcja sprawdza imie i nazwisko wpisane przez uzytkownika podaczas zmieniania wartosci juz istniejacego pokoju w liscie
// jezeli uzytkownik wpisze "zostaw" wartosc zmieniana pozostanie taka sama
// zwraca ciag znakow
std::string checkFisrstNameAndLastNameEditValue(std::string previousValue);

// funkcja sprawdza czy podany ciag znakow jest poprawnym wyrazeniem regularnym
// jezeli tak zwraca true jezeli nie false
bool czyPoprawneWyrazenie(std::string &wyrazenie);

// funkcja wyswietla wyszukane pokoje w bazie danych pasujace do podanych przez uzytkownika wartosci
void wyswietlWyszukanePokoje(Pokoj *&pokoj);

