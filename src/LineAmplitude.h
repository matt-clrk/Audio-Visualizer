#ifndef LINEAMPLITUDE_H
#define LINEAMPLITUDE_H

#include "Amplitude.h"

class LineAmplitude {
public:
    LineAmplitude(RenderWindow& window, Color windowColor, string& audioFile);
    void run(const string& audioFile);

private:
    RenderWindow& window;
    Color windowColor;
    Amplitude amplitude;
    VertexArray amplitudeWaveform;
    // Smoothed amplitude data to reduce jitter
    vector<float> smoothedData;
    float smoothingFactor;

    void update();
    void render();
};

#endif //LINEAMPLITUDE_H
