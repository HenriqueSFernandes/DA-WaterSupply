#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "Script.hpp"
#include "PNG.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream &operator>>(istream &input, Color &c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script() :
            image(nullptr) {

    }

    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }

    Script::~Script() {
        clear_image_if_any();
    }


    void Script::open(string input) {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        std::filesystem::path absolutePath = std::filesystem::absolute(input);
        filename = absolutePath.string();
        std::string subdirectoryToRemove = "cmake-build-debug/";
        for (char c: filename) {
            if (c == '\\') {
                subdirectoryToRemove = "cmake-build-debug\\";
                break;
            } else if (c == '/') {
                subdirectoryToRemove = "cmake-build-debug/";
                break;
            }
        }
        // Find the position of the substring
        size_t pos = filename.find(subdirectoryToRemove);

        // If the substring is found, erase it
        if (pos != std::string::npos) {
            filename.erase(pos, subdirectoryToRemove.length());
        }
        image = loadFromPNG(filename);

    }


    void Script::save(string ou) {
        // Save current image to PNG file.
        string out;
        std::filesystem::path absolutePath = std::filesystem::absolute(ou);
        out = absolutePath.string();
        std::string subdirectoryToRemove = "cmake-build-debug/";
        for (char c: out) {
            if (c == '\\') {
                subdirectoryToRemove = "cmake-build-debug\\";
                break;
            } else if (c == '/') {
                subdirectoryToRemove = "cmake-build-debug/";
                break;
            }
        }
        // Find the position of the substring
        size_t pos = out.find(subdirectoryToRemove);

        // If the substring is found, erase it
        if (pos != std::string::npos) {
            out.erase(pos, subdirectoryToRemove.length());
        }
        saveToPNG(out, image);
    }

    void Script::fill(int x, int y, int w, int h, rgb_value r, rgb_value g, rgb_value b) {
        //Assign (r, g, b) to all pixels contained in rectangle defined by top-left corner (x, y), width w, and height h


        int x_ = image->width();
        int y_ = image->height();
        for (int i = 0; i < x_; i++) {
            for (int j = 0; j < y_; j++) {
                if ((i >= x and i < x + w) and (j >= y and j < y + h)) {    //Condition for it to be in the rectangle
                    image->at(i, j).red() = r;
                    image->at(i, j).green() = g;
                    image->at(i, j).blue() = b;

                }
            }
        }
    }
    vector<int> Script::getColorOfPixel(int x, int y){
        //the vector will store red green and blue in thsi order
        vector<int> res;
        res.push_back(image->at(x,y).red());
        res.push_back(image->at(x,y).green());
        res.push_back(image->at(x,y).blue());
        return res;

    }
    pair<int,int> Script::getWidthHeight(){
        pair<int,int> res;
        res.first=image->width();
        res.second=image->height();
        return res;

    }


    void window_calculator(vector<int> & helper, int
    i,
    int j,
    int left,
    int right,
    int up,
    int down,
    int n
    ) { //gets the new values for the window taking into consideration the image limits
    int displacement = (n - 1) / 2;
    int newleft, newright, newup, newdown;
    newleft = i - displacement;
    if(newleft<left) {
    newleft = left;
}
newright = i + displacement;
if(newright>right){
newright = right;
}
newup = j - displacement;
if(newup<up){
newup = up;
}
newdown = j + displacement;
if(newdown>down){
newdown = down;
}
helper[0]=
newleft;
helper[1]=
newright;
helper[2]=
newup;
helper[3]=
newdown;

}


}
