#include "Menu.h"
#include "GraphicalUnit.h"

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

int Menu::getValidInt() {
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
    clearScreen();
    string option;
    cout << "\nHello, welcome to the Water Supply Management System!\n";
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout << "1) Analyse the network.\n2) Enable / disable locations.\n3) Balance network.\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            analyseMenu();
        } else if (option == "2") {
            disableLocationsMenu();
        }
        else if(option=="3"){
            Balance();
        }else if (option == "0") {
            exit(0);
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
        clearScreen();
    }
}

void Menu::analyseMenu() {
    clearScreen();
    string option;
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout
                << "1) Check the flow to a specific city.\n2) Check the flow to all cities.\n3) Check if the demand of each city is met.\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            printFlowToCity();
        } else if (option == "2") {
            printFlowToAllCities();
        } else if (option == "3") {
            Balance();
        } else if (option == "0") {
            break;
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
}

void Menu::Balance() {
    clearScreen();
    string option;
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout
                << "1) Check current balance.\n2) Improve Balance.\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            manager.resetNetwork();
            manager.edmondsKarp(Location(-1,"SOURCE"),Location(-1,"SINK"));
            double avg;
            double var;
            double maximum;
            manager.getNetworkStats(avg,var,maximum);
            setColorCyan();
            cout << "Average: " << avg << endl;
            cout << "Variance: " << var << endl;
            cout << "Maximum: " << maximum << endl;
            resetColor();
        } else if (option == "2") {
            manager.resetNetwork();
            manager.edmondsKarpBalance(Location(-1,"SOURCE"),Location(-1,"SINK"));
            double avg;
            double var;
            double maximum;
            manager.getNetworkStats(avg,var,maximum);
            setColorCyan();
            cout << "Average: " << avg << endl;
            cout << "Variance: " << var << endl;
            cout << "Maximum: " << maximum << endl;
            resetColor();
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
}
void Menu::disableLocationsMenu() {
    clearScreen();
    string option;
    while (true) {
        printCurrentlyDisabledReservoirs();
        printCurrentlyDisabledStations();
        printCurrentlyDisabledPipes();
        cout << "\nWhat do you want to do?\n";
        cout
                << "1) Disable reservoirs.\n2) Disable pumping stations.\n3) Disable pipes.\n4) Calculate the impact of the changes.\n5) Reset\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            clearScreen();
            disableReservoirs();
            clearScreen();

        } else if (option == "2") {
            clearScreen();
            disableStations();
            clearScreen();
        } else if (option == "3") {
            clearScreen();
            disablePipes();
            clearScreen();
        } else if (option == "4") {
            clearScreen();
            printFlowWithDisabledLocations();
        } else if (option == "5") {
            disabledReservoirs.clear();
            disabledStations.clear();
            disabledPipes.clear();
            clearScreen();
        } else if (option == "0") {
            break;
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
}

void Menu::printFlowWithDisabledLocations() {
    pair<pair<int, int>, vector<pair<Vertex<Location> *, int>>> impact = manager.flowWithDisabledLocations(
            disabledReservoirs, disabledStations, disabledPipes);
    int oldFlow = impact.first.first;
    int newFlow = impact.first.second;
    vector<pair<Vertex<Location> *, int>> affectedCities = impact.second;
    if (affectedCities.empty()) {
        setColorCyan();
        cout << "There were no affected cities.\n\n";
        resetColor();
    } else {
        cout << "There were ";
        setColorCyan();
        cout << affectedCities.size();
        resetColor();
        cout << " affected cities:\n";
        for (pair<Vertex<Location> *, int> city: affectedCities) {
            cout << "\tThe flow in ";
            setColorCyan();
            cout << city.first->getInfo().getMunicipality();
            resetColor();
            cout << " decreased from ";
            setColorCyan();
            cout << city.second;
            resetColor();
            cout << " to ";
            setColorCyan();
            cout << city.first->getAdj()[0]->getFlow();
            resetColor();
            cout << ".\n";
        }
        cout << "The global flow decreased from ";
        setColorCyan();
        cout << oldFlow;
        resetColor();
        cout << " to ";
        setColorCyan();
        cout << newFlow;
        resetColor();
        cout << ".\n\n";
        string ans;
        cout << "Do you wish to see the affected cities in a visual format? (y/n)\n";
        cin >> ans;
        if (ans == "y") {
            if (isMadeira) {
                setColorRed();
                cout << "This feature is not supported when using the Madeira dataset!\n";
                resetColor();
            } else {
                graphicalUnit.displayToTerminal(affectedCities);
            }
        }
    }
}

void Menu::disablePipes() {
    // This regex matches valid codes for location (PS_1, R_2, C_3, etc)
    regex pattern("^(PS|C|R)_[1-9]\\d*$");
    while (true) {
        clearScreen();
        printCurrentlyDisabledPipes();
        string originCode;
        string destinationCode;
        while (true) {
            cout << "Please insert the code of the origin location (0 to exit)\n";
            cin >> originCode;
            if (originCode == "0") return;
            if (regex_match(originCode, pattern)) break;
            setColorRed();
            cout << "Invalid code\n";
            resetColor();
        }
        while (true) {
            cout << "\nPlease insert the code of the destination location (0 to exit)\n";
            cin >> destinationCode;
            if (destinationCode == "0") return;
            if (regex_match(destinationCode, pattern)) break;
            setColorRed();
            cout << "Invalid code\n";
            resetColor();
        }
        disabledPipes.insert({Location(0, originCode),
                              Location(0, destinationCode)});
    }
}

void Menu::disableStations() {
    regex pattern("^PS_[1-9]\\d*$");
    while (true) {
        clearScreen();
        printCurrentlyDisabledStations();
        string stationCode;
        while (true) {
            cout << "Please insert the id of the pumping station (0 to exit)\n";
            cin >> stationCode;
            if (stationCode == "0") return;
            if (regex_match(stationCode, pattern)) break;
            setColorRed();
            cout << "Invalid code\n";
            resetColor();
        }
        disabledStations.insert(Location(0, stationCode));
    }
}

void Menu::disableReservoirs() {
    regex pattern("^R_[1-9]\\d*$");
    while (true) {
        clearScreen();
        printCurrentlyDisabledReservoirs();
        string reservoirCode;
        while (true) {
            cout << "\nPlease insert the code of the reservoir (0 to exit)\n";
            cin >> reservoirCode;
            if (reservoirCode == "0") return;
            if (regex_match(reservoirCode, pattern)) break;
            setColorRed();
            cout << "Invalid code\n";
            resetColor();
        }
        disabledReservoirs.insert(Location(0, reservoirCode));
    }
}

void Menu::printWaterAvailability() {
    clearScreen();
    vector<pair<Location, int>> citiesWithMoreDemandThanFlow = manager.checkWaterAvailability();
    if (citiesWithMoreDemandThanFlow.empty()) {
        setColorCyan();
        cout << "Every city is receiving enough water.\n";
        resetColor();
    }
    for (const pair<Location, int> &city: citiesWithMoreDemandThanFlow) {
        setColorCyan();
        cout << city.first.getMunicipality();
        resetColor();
        cout << ", with code " << city.first.getCode()
             << ", is not receiving enough water, since it has a demand of ";
        setColorCyan();
        cout << city.first.getDemand();
        resetColor();
        cout << " and a flow of ";
        setColorCyan();
        cout << city.second;
        resetColor();
        cout << ", which means it has a deficit of ";
        setColorCyan();
        cout << city.first.getDemand() - city.second;
        resetColor();
        cout << ".\n";
    }
}

void Menu::printFlowToAllCities() {
    clearScreen();
    pair<vector<cityFlow>, int> totalFlow = manager.flowToAllCities();
    for (const cityFlow &city: totalFlow.first) {
        cout << city << endl;
    }
    cout << "\nThe total flow is ";
    setColorCyan();
    cout << totalFlow.second;
    resetColor();
    cout << ".\n";
    cout << "Do you wish to save the output to a file? (y/n)\n";
    string saveOutput;
    cin >> saveOutput;
    if (saveOutput == "y") {
        string filename = "flow" + to_string(time(nullptr)) + ".txt";
        ofstream file;
        file.open(filename);
        if (!file) {
            cerr << "Error while opening file!\n";
        } else {
            for (const cityFlow &city: totalFlow.first) {
                // Here we can't use file << city because it would write the colors as text.
                file << city.name << ", with code " << city.code << ", has a flow of " << city.flow << ".\n";
            }
            file << "\nThe total flow is ";
            file << totalFlow.second;
            file << ".\n";
            file.close();
            cout << "File saved to " << filesystem::current_path() / filename << ".\n";
        }
    }
}

void Menu::printFlowToCity() {
    clearScreen();
    regex pattern("^C_[1-9]\\d*$");
    string cityCode;
    while (true) {
        cout << "What is the code of the city?\n";
        cin >> cityCode;
        if (regex_match(cityCode, pattern)) break;
        setColorRed();
        cout << "Invalid code\n";
        resetColor();
    }
    try {
        cout << manager.flowToCity(Location(stoi(cityCode.erase(0, 2)), cityCode)) << endl;
        cout << "Note: this is the maximum theoretical flow if there were no other cities.\n";
    } catch (const exception &e) {
        setColorRed();
        cout << e.what() << endl;
        resetColor();
    }
}

void Menu::printCurrentlyDisabledPipes() {
    cout << "\nCurrently disabled pipes:\n";
    setColorCyan();
    if (disabledPipes.empty()) {
        cout << "None\n";
    }
    for (const pair<Location, Location> &pipe: disabledPipes) {
        cout << pipe.first.getCode() << " <--> " << pipe.second.getCode() << endl;
    }
    resetColor();
}

void Menu::printCurrentlyDisabledStations() {
    cout << "\nCurrently disabled pumping stations:\n";
    setColorCyan();
    if (disabledStations.empty()) {
        cout << "None\n";
    }
    for (const Location &station: disabledStations) {
        cout << station.getCode() << endl;
    }
    resetColor();
}

void Menu::printCurrentlyDisabledReservoirs() {
    cout << "Currently disabled reservoirs:\n";
    setColorCyan();
    if (disabledReservoirs.empty()) {
        cout << "None\n";
    }
    for (const Location &reservoir: disabledReservoirs) {
        cout << reservoir.getCode() << endl;
    }
    resetColor();
}

void Menu::clearScreen() {
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}
