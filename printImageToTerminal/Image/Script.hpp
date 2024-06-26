#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"
#include <vector>
using namespace std;
namespace prog {
    class Script {
    public:
        Script();

        ~Script();

        void run();

        void fill(int x, int y, int w, int h, rgb_value r, rgb_value g, rgb_value b);

        void clear_image_if_any();

        void open(std::string in);

        void blank();

        void save(std::string out);
        vector<int> getColorOfPixel(int x, int y);
        pair<int,int> getWidthHeight();

    private:
        // Current image.
        Image *image;


    };
}
#endif