//
// Created by jose on 4/6/24.
//

#include "GraphicalUnit.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <cerrno> // Include for errno and perror

void GraphicalUnit::readCities() {
    string city;
    string x_;
    string y_;
    ifstream cityCsv("../data/cityMapping.csv");

    if (!cityCsv) {
        cerr << "Failed to open file 'data/cityMapping.csv': " << errno << endl;
        return;
    }

    string line;
    getline(cityCsv, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.

    while (getline(cityCsv, line)) {
        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, x_, ',');
        getline(iss, y_, '\r');
        cityCoordinates[city] = make_pair(stoi(x_), stoi(y_));
    }
    cityCsv.close();
}

void GraphicalUnit::DisplayToTerminal(vector<pair<Vertex<Location> *, int>> affectedCities){
    prog::Script script = prog::Script();
    script.open("data/portugal.png");
    for( auto el : affectedCities){
        script.fill(cityCoordinates[el.first->getInfo().getCode()].first,cityCoordinates[el.first->getInfo().getCode()].second,20,20,255,5,80);
    }
    script.save("data/portugalchanged.png");

    std::pair<int,int> wh = script.getWidthHeight();

    for (int j = 0; j < wh.first; j += 35) {
        for (int i = 0; i < wh.second; i+=13) {
            int sumR = 0, sumG = 0, sumB = 0;

            for (int x = 0; x < 35; x++) {
                if(j + x >= wh.first) break;
                auto color = script.getColorOfPixel(i, j + x);
                sumR += color[0];
                sumG += color[1];
                sumB += color[2];
            }

            for (int y = 0; y < 18; y++) {
                if(i + y >= wh.second) break;
                auto color = script.getColorOfPixel(i + y, j);
                sumR += color[0];
                sumG += color[1];
                sumB += color[2];
            }
            int avgR = sumR / 53;
            int avgG = sumG / 53;
            int avgB = sumB / 53;
            if(avgR >   150){
                std::cout << "\u001b[38;2;" << 255 << ";" << 10 << ";" << 50 << "m█\u001b[0m";
            }
            else if (avgG > 10) {
                std::cout << "\u001b[38;2;0;255;0m█\u001b[0m";
            } else {
                std::cout << "\u001b[38;2;" << avgR << ";" << avgG << ";" << avgB << "m█\u001b[0m";
            }
        }
        std::cout << std::endl;
    }
}