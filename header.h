#pragma once
#include <iostream>
#include <vector>


// Stworzenie listy jednokierunkowej
// struktura rekurdu w bazie danych
struct Pokoj
{
    int numer_pokoju;
    int maksymalna_ilosc_osob;
    bool lazienka;
    float cena_pokoju;
    std::string imie_nazwisko;
    int nr_telefonu;
    std::string data_rozpoczecia; // rrrr.mm.dd
    std::string data_zakonczenia; // rrrr.mm.dd
    bool czy_posilki; // jezeli pokoj nie jest wynajety to falsz

    Pokoj* nastepny_pokoj;

    Pokoj(); // konstruktor
};


// glowna struktura
struct database
{
    Pokoj *pierwszy_pokoj;
    // funkcja dodaje pokoj do bazdy danych
    void dodajPokoj();
    // funkcja zamienia pokoj na wynajety i wyswietla dostepne pokoje
    void wynajmijPokoj(); // do zrobienia
    // funkcja zmienia dane rekordu w bazie danych
    void zmienDanePokoju(); // do zrobienia
    // funkja usuwa pokoj z bazy danych
    void usunPokoj();
    // funkcja wyswietla cala baze danych
    void wyswietlBazeDanych();
    // TODO:: stworzyc funkcje wyszukiwania po imieniu i nazwisku, numerze pokoju, przez wyrazenia regularne
    // wyswietla pokoje do wynajęcia
    // i dodaje ich numery do tablicy typu vector aby sprawdzic czy uzytkownik wybiera pokoj ktory jest mozliwy do wyboru
    void wyswietlWolnePokojeIDodaIchNumeryDoTablicy(std::vector <int> &numery);
    // funkcja zapisuje baze danych do pliku
    void zapiszBazeDanych(); // do zrobienia
    // funkcja wczytuje baze danych z pliku
    void wczytajBazeDanych();
    database();

};


//funkcja generujaca menu glowne
void generateMainMenu();

//wygenerowanie opcij dzialan na bazie danych po wybraniu przez uzytkownika odpowiedniej opcji
void databaseOptionsMenu(database *&pokoje);

//wygenerowanie opcji importu i exportu
void importExportMenu(database *&pokoje);

//wygenerowanie opcji wyszukiwania
void searchMenu(database *&pokoje);

//funckja rozdziela jeden wiersz na poszczegolne wartosc rozdzielone srednikami
void splitString(std::string &rekord, std::string tab[]);

// funkcja zamenia string true/false na bool true/false
bool stringToBoolConvert(std::string &record);

// funkcja sprawdzająca poprawność wpisanych przez użytkownika danych
// zwraca ciag znakow
std::string checkValid(std::string pattern, std::string failInfo, std::string whatToInsertInformation);

// funkcja sprawdza poprawność wpisanego przez użytkownika numeru telefony zwraca albo pusty string albo numer telefonu
std::string checkPhoneNumber(std::string pattern, std::string failInfo, std::string whatToInsertInformation);

// funkcja sprawdza poprawność wpisanej przez uzytkownika daty zwraca albo date albo pusty string
std::string checkDate(std::string pattern, std::string failInfo, std::string whatToInsertInformation);

std::string checkFirstNameAndLastName();