#include <iostream>
#include "header.h"

using namespace std;

int main()
{

    database* pokoje = new database; //stowrzenie obiektu

    // wyswietlanie menu i podejmowanie decyzji jakie dzialanie podjac
    while (true)
    {
        generateMainMenu();
        int choose;
        cout << "Wybor: ";
        cin >> choose;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Wybor: ";
            cin>>choose;
        }

        switch (choose) {
            case 1:
                pokoje->wynajmijPokoj();
                system("cls");
                break;
            case 2:
                searchMenu(pokoje);
                break;
            case 3:
                databaseOptionsMenu(pokoje);
                break;
            case 4:
                importExportMenu(pokoje);
                break;
            case 5:
                delete pokoje;
                return 0;
            default:
                break;
        }
    }
}