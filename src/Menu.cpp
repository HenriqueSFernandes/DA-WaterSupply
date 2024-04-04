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
    string option;
    cout << "\nHello, welcome to the Water Supply Management System!\n";
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout << "1) Analyse the network.\n2) Enable / disable locations.\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            analyseMenu();
        } else if (option == "2") {
            disableLocationsMenu();
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
            id = getValidInt();
            try {
                cout << manager.flowToCity(Location(id, "C_" + to_string(id))) << endl;
                cout << "Note: this is the maximum theoretical flow if there were no other cities.\n";
            } catch (const exception &e) {
                setColorRed();
                cout << e.what() << endl;
                resetColor();
            }
        } else if (option == "2") {
            pair<vector<cityFlow>, int> totalFlow = manager.flowToAllCities();
            for (const cityFlow &city: totalFlow.first) {
                cout << city << endl;
            }
            cout << "\nThe total flow is ";
            setColorCyan();
            cout << totalFlow.second;
            resetColor();
            cout << ".\n";
        } else if (option == "3") {
            vector<pair<Location, int>> citiesWithMoreDemandThanFlow = manager.checkWaterAvailability();
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
        } else if (option == "0") {
            break;
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}

void Menu::disableLocationsMenu() {
    string option;
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout
                << "1) Disable reservoirs.\n2) Disable pumping stations.\n3) Disable pipes.\n4) See the disabled locations.\n5) Calculate the impact of the changes.\n6) Reset\n0) Exit.\n";
        cin >> option;
        if (option == "1") {
            cout << "Currently disabled reservoirs:\n";
            setColorCyan();
            if (disabledReservoirs.empty()) {
                cout << "None\n";
            }
            for (const Location &reservoir: disabledReservoirs) {
                cout << reservoir.getCode() << endl;
            }
            resetColor();
            while (true) {
                cout << "\nPlease insert the id of the reservoir (0 to exit)\n";
                int reservoirId = getValidInt();
                if (reservoirId == 0) break;
                string reservoirCode = "R_" + to_string(reservoirId);
                disabledReservoirs.insert(Location(reservoirId, reservoirCode));
            }

        } else if (option == "2") {
            cout << "\nCurrently disabled pumping stations:\n";
            setColorCyan();
            if (disabledStations.empty()) {
                cout << "None\n";
            }
            for (const Location &station: disabledStations) {
                cout << station.getCode() << endl;
            }
            resetColor();
            while (true) {
                cout << "Please insert the id of the pumping station (0 to exit)\n";
                int stationId = getValidInt();
                if (stationId == 0) break;
                string stationCode = "PS_" + to_string(stationId);
                disabledStations.insert(Location(stationId, stationCode));
            }
        } else if (option == "3") {
            cout << "\nCurrently disabled pipes:\n";
            setColorCyan();
            if (disabledPipes.empty()) {
                cout << "None\n";
            }
            for (const pair<Location, Location> &pipe: disabledPipes) {
                cout << pipe.first.getCode() << " <--> " << pipe.second.getCode() << endl;
            }
            resetColor();
            while (true) {
                cout << "Please insert the code of the origin location (0 to exit)\n";
                string originCode;
                cin >> originCode;
                if (originCode == "0") break;
                cout << "\nPlease insert the code of the destination location (0 to exit)\n";
                string destinationCode;
                cin >> destinationCode;
                if (destinationCode == "0") break;
                disabledPipes.insert({Location(0, originCode),
                                      Location(0, destinationCode)});
            }


        } else if (option == "4") {
            cout << "Currently disabled reservoirs:\n";
            setColorCyan();
            if (disabledReservoirs.empty()) {
                cout << "None\n";
            }
            for (const Location &reservoir: disabledReservoirs) {
                cout << reservoir.getCode() << endl;
            }
            resetColor();
            cout << "\nCurrently disabled pumping stations:\n";
            setColorCyan();
            if (disabledStations.empty()) {
                cout << "None\n";
            }
            for (const Location &station: disabledStations) {
                cout << station.getCode() << endl;
            }
            resetColor();
            cout << "\nCurrently disabled pipes:\n";
            setColorCyan();
            if (disabledPipes.empty()) {
                cout << "None\n";
            }
            for (const pair<Location, Location> &pipe: disabledPipes) {
                cout << pipe.first.getCode() << " <--> " << pipe.second.getCode() << endl;
            }
            resetColor();
        } else if (option == "5") {
            pair<pair<int, int>, vector<pair<Vertex<Location> *, int>>> impact = manager.flowWithDisabledLocations(
                    disabledReservoirs, disabledStations, disabledPipes);
            int oldFlow = impact.first.first;
            int newFlow = impact.first.second;
            vector<pair<Vertex<Location> *, int>> affectedCities = impact.second;
            if (affectedCities.empty()) {
                cout << "There were no affected cities.\n";
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
                cout << ".\n";
            }
        } else if (option == "6") {
            disabledReservoirs.clear();
            disabledStations.clear();
            disabledPipes.clear();
        } else if (option == "0") {
            break;
        } else {
            cout << "Invalid option, please choose again.\n";
        }
    }
}
