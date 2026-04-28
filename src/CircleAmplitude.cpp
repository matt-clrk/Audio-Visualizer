#include "CircleAmplitude.h"

CircleAmplitude::CircleAmplitude(RenderWindow& window, Color windowColor, string& audioFile) :
    window(window)
{
    this->windowColor = Color(255, 250, 241);
    this->dancingCircleRadius = 100.f;
    this->minRadius = 60.0f;
    this->maxRadius = 220.0f;
    this->smoothedRadius = minRadius;

    dancingCircle.setRadius(dancingCircleRadius);
    dancingCircle.setFillColor(Color(30, 30, 30));
    dancingCircle.setOutlineColor(Color(80, 80, 80));
    dancingCircle.setOutlineThickness(2.5f);
    // SFML 3: setOrigin and setPosition take Vector2f
    dancingCircle.setOrigin(Vector2f(dancingCircleRadius, dancingCircleRadius));
    dancingCircle.setPosition(Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

    amplitude.loadSong(audioFile);
}

void CircleAmplitude::run(const string& audioFile) {
    amplitude.loadSong(audioFile);
    amplitude.playSound();

    while (window.isOpen()) {
        // SFML 3: new event system using pollEvent() returning optional
        while (auto event = window.pollEvent()) {
            // SFML 3: events are now types, checked with .is<>()
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        update();
        render();
    }
}

void CircleAmplitude::update() {
    amplitude.update();
    const vector<float>& amplitudeData = amplitude.getAmplitudeData();

    float sumAmplitude = 0.0f;
    for (float value : amplitudeData) {
        sumAmplitude += value;
    }
    float averageAmplitude = sumAmplitude / amplitudeData.size();

    float scaleCircle = 0.006f;
    float targetRadius = minRadius + scaleCircle * averageAmplitude;
    targetRadius = max(minRadius, min(targetRadius, maxRadius));

    // Smooth the radius change to avoid jitter
    float smoothing = 0.15f;
    smoothedRadius += (targetRadius - smoothedRadius) * smoothing;

    dancingCircle.setRadius(smoothedRadius);
    dancingCircle.setOrigin(Vector2f(smoothedRadius, smoothedRadius));
    dancingCircle.setPosition(Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

    // Tint the circle color based on size for a reactive feel
    float intensity = (smoothedRadius - minRadius) / (maxRadius - minRadius);
    uint8_t r = static_cast<uint8_t>(30 + intensity * 180);
    uint8_t g = static_cast<uint8_t>(30 + (1.f - intensity) * 100);
    uint8_t b = static_cast<uint8_t>(120 + (1.f - intensity) * 100);
    dancingCircle.setFillColor(Color(r, g, b));
    dancingCircle.setOutlineColor(Color(r + 40, g + 40, b + 40));
}

void CircleAmplitude::render() {
    window.clear(windowColor);
    window.draw(dancingCircle);
    window.display();
}
