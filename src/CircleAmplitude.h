#ifndef CIRCLEAMPLITUDE_H
#define CIRCLEAMPLITUDE_H
#include "Amplitude.h"

class CircleAmplitude {
public:
    // COnstructor that initializes the window, window color, and audio file
    CircleAmplitude(RenderWindow& window, Color windowColor, string& audioFile);
    // Runs the circle visuals
    void run(const string& audioFile);

private:
    // Reference to window object
    RenderWindow& window;
    // What color you want the window to be
    Color windowColor;
    // Amplitude object
    Amplitude amplitude;
    // Circle shape object from SFML library
    CircleShape dancingCircle;
    // Radius of circle
    float dancingCircleRadius;
    // Minimum radius the circle can be
    float minRadius;
    // Maximum radius the circle can be
    float maxRadius;
    // Unused variable I was going to implement
    Color strobeColor;

    void update();
    void render();
};


#endif //CIRCLEAMPLITUDE_H
