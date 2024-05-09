#include "LineAmplitude.h"
// Initializes the LineAmplitude object given the provided window, window color, and audio file
LineAmplitude::LineAmplitude(RenderWindow& window, Color windowColor, string& audioFile) :
        window(window),
        windowColor(255, 250, 241),
        smoothingFactor(10.0f) {
    amplitude.loadSong(audioFile);
    // Initialize amplitude waveform as a VertexArray of type LineStrip
    amplitudeWaveform = VertexArray(LineStrip, amplitude.getChunkSize());
    for (size_t i = 0; i < amplitudeWaveform.getVertexCount(); i++) {
        amplitudeWaveform[i].color = Color::Black;
    }
}

void LineAmplitude::run(const string& audioFile) {
    amplitude.loadSong(audioFile);
    amplitude.playSound();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        update();
        render();
    }
}

void LineAmplitude::update() {
    amplitude.update();
    const vector<float>& amplitudeData = amplitude.getAmplitudeData();
    // Determines the visuals width and is used to calculate the x position of each vertex
    float scale = float(window.getSize().x) / amplitude.getChunkSize();
    // Color variables used in gradient transition of waveform
    Color blue(0, 0, 255);
    Color red(255, 0, 0);
    // Sets the color and position of each vertex in the amplitude waveform vertex array
    for (size_t i = 0; i < amplitudeWaveform.getVertexCount(); i++) {
        float xPos = i * scale;
        float ratio = xPos / window.getSize().x;
        Color transitionColor = Color(blue.r + ratio * (red.r - blue.r),blue.g + ratio * (red.g - blue.g),blue.b + ratio * (red.b - blue.b));
        amplitudeWaveform[i].color = transitionColor;
        float amplitudeVisual = amplitudeData[i] / 32768.f * window.getSize().y / 2;
        amplitudeWaveform[i].position = Vector2f(xPos, window.getSize().y / 2 - amplitudeVisual);
    }
}

void LineAmplitude::render() {
    window.clear(windowColor);
    window.draw(amplitudeWaveform);
    window.display();
}
