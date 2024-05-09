#include "CircleAmplitude.h"
// Constructor initializes the CircleAmplitude object given the following
CircleAmplitude::CircleAmplitude(RenderWindow& window, Color windowColor, string& audioFile) :
        window(window)
{
    // sets the window color
    this->windowColor = Color(255, 250, 241);
    // Sets the circles radius
    this->dancingCircleRadius = 100.f;
    // Set the minimum radius the circle can be
    this->minRadius = 50.0f;
    // Sets the maximum radius the circle can be
    this->maxRadius = 200.0f;
    dancingCircle.setRadius(dancingCircleRadius);
    dancingCircle.setFillColor(Color::Black);
    dancingCircle.setOutlineColor(Color::Black);
    dancingCircle.setOutlineThickness(2.0f);
    dancingCircle.setOrigin(dancingCircleRadius, dancingCircleRadius);
    dancingCircle.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    amplitude.loadSong(audioFile);
}

void CircleAmplitude::run(const string& audioFile) {
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

void CircleAmplitude::update() {
    amplitude.update();
    const std::vector<float>& amplitudeData = amplitude.getAmplitudeData();
    // Used to calculate the average amplitude
    float sumAmplitude = 0.0f;
    for (float value : amplitudeData) {
        sumAmplitude += value;
    }
    float averageAmplitude = sumAmplitude / amplitudeData.size();
    // Determines how much of an influence the amplitude has on scaling the circle
    float scaleCircle = .005f;
    // Radius of circle is scaled based off how sensitive you want it to be (lower value = less responsive, higher value = more responsive)
    float radius = minRadius + scaleCircle * averageAmplitude;
    radius = max(minRadius, min(radius, maxRadius));
    dancingCircle.setRadius(radius);
    dancingCircle.setOrigin(radius, radius);
    dancingCircle.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

void CircleAmplitude::render() {
    window.clear(windowColor);
    window.draw(dancingCircle);
    window.display();
}