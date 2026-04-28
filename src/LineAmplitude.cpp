#include "LineAmplitude.h"

LineAmplitude::LineAmplitude(RenderWindow& window, Color windowColor, string& audioFile) :
    window(window),
    windowColor(255, 250, 241),
    smoothingFactor(0.2f)
{
    amplitude.loadSong(audioFile);
    // SFML 3: PrimitiveType is now a scoped enum
    amplitudeWaveform = VertexArray(PrimitiveType::LineStrip, amplitude.getChunkSize());
    smoothedData = vector<float>(amplitude.getChunkSize(), 0.0f);

    for (size_t i = 0; i < amplitudeWaveform.getVertexCount(); i++) {
        amplitudeWaveform[i].color = Color::Black;
    }
}

void LineAmplitude::run(const string& audioFile) {
    amplitude.loadSong(audioFile);
    amplitude.playSound();

    while (window.isOpen()) {
        // SFML 3: new event system
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
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

    float scale = float(window.getSize().x) / amplitude.getChunkSize();

    Color blue(60, 80, 220);
    Color red(220, 60, 80);

    for (size_t i = 0; i < amplitudeWaveform.getVertexCount(); i++) {
        // Smooth each sample toward the new value to reduce jitter
        smoothedData[i] += (amplitudeData[i] - smoothedData[i]) * smoothingFactor;

        float xPos = i * scale;
        float ratio = xPos / window.getSize().x;

        // Gradient color transition blue -> red across the waveform
        Color transitionColor = Color(
            static_cast<uint8_t>(blue.r + ratio * (red.r - blue.r)),
            static_cast<uint8_t>(blue.g + ratio * (red.g - blue.g)),
            static_cast<uint8_t>(blue.b + ratio * (red.b - blue.b))
        );
        amplitudeWaveform[i].color = transitionColor;

        // Scale amplitude to window height, centered vertically
        float amplitudeVisual = smoothedData[i] / 32768.f * window.getSize().y / 2.f;
        amplitudeWaveform[i].position = Vector2f(xPos, window.getSize().y / 2.f - amplitudeVisual);
    }
}

void LineAmplitude::render() {
    window.clear(windowColor);
    window.draw(amplitudeWaveform);
    window.display();
}
