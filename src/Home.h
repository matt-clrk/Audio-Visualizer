#ifndef HOME_H
#define HOME_H

#include "CircleAmplitude.h"
#include "LineAmplitude.h"
#include <iostream>

class Home {
public:
    enum Screen {
        SONG,
        START,
        CIRCLE,
        LINE,
        OVER
    };

    Home(RenderWindow& window);
    void run();

private:
    RenderWindow& window;
    int width, height;
    Screen screen;
    Color windowColor;
    LineAmplitude lineAmplitude;
    CircleAmplitude circleAmplitude;
    bool isPlaying;
    bool visualsOnScreen;
    string selectedSongPath;
    string songName;

    void renderStart(Font& font);
    void renderOver(Font& font);
    void renderSongSelection(Font& font);
    // Helper to draw centered text
    void drawCenteredText(const string& message, Font& font, unsigned int size, Color color);
};

#endif //HOME_H
