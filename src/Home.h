#ifndef HOME_H
#define HOME_H
#include "CircleAmplitude.h"
#include "LineAmplitude.h"
#include <iostream>


class Home {
public:
    // Enumerated type of screens
    enum Screen {
        SONG,
        START,
        CIRCLE,
        LINE,
        OVER
    };
    // Constructor that passes reference to SFML window
    Home(RenderWindow& window);
    void run();

private:
    // Reference to SFML window
    RenderWindow& window;
    // Window width and height
    int width, height;
    // Screen type
    Screen screen;
    // Window color
    Color windowColor;
    // Line amplitude object
    LineAmplitude lineAmplitude;
    // Circle amplitude object
    CircleAmplitude circleAmplitude;
    // Rendering for each screen
    void renderStart();
    void renderOver();
    void renderSongSelection();
    // Bool value to check if song is playing
    bool isPlaying;
    // Bool value to check if visuals are playing on screen
    bool visualsOnScreen;
    // Audio file path
    string selectedSongPath;
    // Song details (Song name and Artist name)
    string songName;
};


#endif //HOME_H
