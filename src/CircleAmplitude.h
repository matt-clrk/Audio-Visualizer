#ifndef CIRCLEAMPLITUDE_H
#define CIRCLEAMPLITUDE_H

#include "Amplitude.h"

class CircleAmplitude {
public:
    CircleAmplitude(RenderWindow& window, Color windowColor, string& audioFile);
    void run(const string& audioFile);

private:
    RenderWindow& window;
    Color windowColor;
    Amplitude amplitude;
    CircleShape dancingCircle;
    float dancingCircleRadius;
    float minRadius;
    float maxRadius;
    // Smoothed radius to avoid jittery movement
    float smoothedRadius;

    void update();
    void render();
};

#endif //CIRCLEAMPLITUDE_H
