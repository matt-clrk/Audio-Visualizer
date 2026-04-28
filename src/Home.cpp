#include "Home.h"

Home::Home(RenderWindow& window) :
    window(window), windowColor(255, 250, 241), screen(SONG),
    lineAmplitude(window, windowColor, selectedSongPath),
    circleAmplitude(window, windowColor, selectedSongPath)
{
    width = window.getSize().x;
    height = window.getSize().y;
}

// Helper: draws a string centered on screen
void Home::drawCenteredText(const string& message, Font& font, unsigned int size, Color color) {
    // SFML 3: Text constructor takes font reference directly
    Text text(font, message, size);
    text.setFillColor(color);
    FloatRect bounds = text.getLocalBounds();
    text.setOrigin(Vector2f(bounds.position.x + bounds.size.x / 2.f,
                            bounds.position.y + bounds.size.y / 2.f));
    text.setPosition(Vector2f(width / 2.f, height / 2.f));
    window.draw(text);
}

void Home::run() {
    Font font;
    // SFML 3: loadFromFile -> openFromFile
    if (!font.openFromFile("songs/fonts/Arial.ttf")) {
        cerr << "Font could not be loaded" << endl;
        return;
    }

    while (window.isOpen()) {
        // SFML 3: pollEvent returns optional, events checked with .is<>()
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (screen == SONG) {
                    if (keyPressed->code == Keyboard::Key::Num1) {
                        selectedSongPath = "songs/fredagain.wav";
                        songName = "Song: We've Lost Dancing\nArtist: Fred Again...";
                        screen = START;
                    }
                    else if (keyPressed->code == Keyboard::Key::Num2) {
                        selectedSongPath = "songs/talk-tonight.wav";
                        songName = "Song: Talk Tonight\nArtist: Jersey";
                        screen = START;
                    }
                }
                else if (screen == START) {
                    if (keyPressed->code == Keyboard::Key::L) {
                        screen = LINE;
                    }
                    else if (keyPressed->code == Keyboard::Key::C) {
                        screen = CIRCLE;
                    }
                }
            }
        }

        window.clear(windowColor);

        switch (screen) {
            case SONG:
                renderSongSelection(font);
                break;
            case START:
                renderStart(font);
                break;
            case LINE:
                lineAmplitude.run(selectedSongPath);
                screen = OVER;
                break;
            case CIRCLE:
                circleAmplitude.run(selectedSongPath);
                screen = OVER;
                break;
            case OVER:
                renderOver(font);
                break;
        }

        window.display();
    }
}

void Home::renderStart(Font& font) {
    window.clear(windowColor);
    string message = "Welcome to my Audio Visualizer\n\n"
                     "Press [L] for Line Waveform\n"
                     "Press [C] for Dancing Circle\n\n"
                     + songName;
    drawCenteredText(message, font, 24, Color::Black);
}

void Home::renderOver(Font& font) {
    window.clear(windowColor);
    string message = "Song Finished!\n\n"
                     "Press [C] for circle visuals\n"
                     "Press [L] for line waveform";
    drawCenteredText(message, font, 24, Color::Black);

    // Allow restarting from the OVER screen
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == Keyboard::Key::L) {
                screen = LINE;
            }
            else if (keyPressed->code == Keyboard::Key::C) {
                screen = CIRCLE;
            }
        }
    }
}

void Home::renderSongSelection(Font& font) {
    window.clear(windowColor);
    string message = "Audio Visualizer\n\n"
                     "Select a song:\n"
                     "[1]  We've Lost Dancing  —  Fred Again...\n"
                     "[2]  Talk Tonight  —  Jersey";
    drawCenteredText(message, font, 24, Color::Black);
}
