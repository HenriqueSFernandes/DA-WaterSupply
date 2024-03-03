#include <iostream>
#include "Image/Script.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    prog::Script script = prog::Script();
    script.open("Image/input/portugal.png");
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
            if (avgG > 0) {
                std::cout << "\u001b[38;2;0;255;0m█\u001b[0m";
            } else {
                std::cout << "\u001b[38;2;" << avgR << ";" << avgG << ";" << avgB << "m█\u001b[0m";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
