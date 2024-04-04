#include "Menu.h"

using namespace std;

void Menu::resetColor() {
    cout << "\033[0m";
}

void Menu::setColorRed() {
    cout << "\033[0;31m";
}

void Menu::setColorCyan() {
    cout << "\033[0;36m";
}

int Menu::askForAValidInt() {
    int number;
    cin >> number;
    while (std::cin.fail()) {
        std::cin.clear(); // Clear the fail state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin >> number;
    }
    return number;
}

void Menu::start() {
    string option;
    cout << "\nHello, welcome to the Water Supply Management System!\n";
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout << "1) Analyse the network.\n2) Evaluate the reliability of the network.\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            analyseMenu();
        } else if (option == "2") {
            cout << "option 2\n";
        } else if (option == "0") {
            exit(0);
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}

void Menu::analyseMenu() {
    string option;
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout
                << "1) Check the flow to a specific city.\n2) Check the flow to all cities.\n3) Check if the demand of each city is met.\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            int id;
            cout << "What is the id of the city?\n";
            id = askForAValidInt();
            try {
                cout << manager.flowToCity(Location(id, "C_" + to_string(id))) << endl;
                cout << "Note: this is the maximum theoretical flow if there were no other cities.\n";
            } catch (const exception &e) {
                setColorRed();
                cout << e.what() << endl;
                resetColor();
            }
        } else if (option == "2") {
            

        } else if (option == "3") {

        } else if (option == "0") {
            break;
        } else {
            cout << "Invalid option, please choose again.\n";
        }

    }
}


