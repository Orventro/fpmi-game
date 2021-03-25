#include "Window.h"

#include "landscape.h"
#include "perlin_noise.h"
#include "painter.h"
#include "maker_map.h"

int main()
{
    GameWindow window;
    int frame=0;

    while(!window.render()) {
        // cout << frame++ << endl;
    }
}