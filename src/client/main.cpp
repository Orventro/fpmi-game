#include "Window.h"

int main()
{
    GameWindow window;
    int frame=0;

    while(!window.render()) {
        // cout << frame++ << endl;
    }
}