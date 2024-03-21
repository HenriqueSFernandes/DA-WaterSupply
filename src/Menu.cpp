#include "Menu.h"

using namespace std;

void Menu::start() {
    string option;
    cout << "Hello, welcome to the Water Supply Management System!\n";
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout << "1) Option 1\n2) Option 2\n0) Exit\n";
        cin >> option;
        if (option == "1") {
            cout << "option 1\n";
        } else if (option == "2") {
            cout << "option 2\n";
        } else if (option == "0") {
            exit(0);
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}