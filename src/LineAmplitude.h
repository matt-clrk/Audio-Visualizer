#ifndef LINEAMPLITUDE_H
#define LINEAMPLITUDE_H
#include "Amplitude.h"


class LineAmplitude {
public:
    // Constructor
    LineAmplitude(RenderWindow& window, Color windowColor, string& audioFile);
    // Runs the visualization
    void run(const string& audioFile);

private:
    // Reference to the SFML window
    RenderWindow& window;
    // Color of the window background
    Color windowColor;
    // Amplitude object to handle audio amplitude data
    Amplitude amplitude;
    // SFML vertex array for drawing waveform
    VertexArray amplitudeWaveform;
    // Smoothing factor for waveform visualization to prevent jagged edges more visually appealing visuals
    float smoothingFactor;
    // Updates the visualization
    void update();
    // Renders the visualization
    void render();
};


#endif //LINEAMPLITUDE_H
