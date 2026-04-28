#include "Home.h"

int main() {
    // SFML 3: VideoMode takes a Vector2u, window style is optional
    RenderWindow window(VideoMode({800, 600}), "Audio Visualizer");
    window.setFramerateLimit(60);
    Home home(window);
    home.run();
    return 0;
}
