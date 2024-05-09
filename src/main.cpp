#include "Home.h"

int main() {
    RenderWindow window(VideoMode(800, 600), "Audio Visualizer");
    Home home(window);
    home.run();
    return 0;
}