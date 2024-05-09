#include "Home.h"
// Initializes the Home screen object that sets the window color, sets the screen to the song selection screen,
// and initializes the Line and Circle amplitude objects
Home::Home(RenderWindow& window) :
window(window), windowColor(255, 250, 241), screen(SONG),
lineAmplitude(window, windowColor, selectedSongPath),
circleAmplitude(window, windowColor, selectedSongPath) {
    width = window.getSize().x;
    height = window.getSize().y;
}

void Home::run() {
    Font font;
    // Loads fonts from songs directory
    if (!font.loadFromFile("songs/fonts/Arial.ttf")) {
        cerr << "Font could not be loaded" << endl;
        return;
    }
    Text message("", font);
    while (window.isOpen()) {
        Amplitude amplitude;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                // Handle key presses based on the current screen
                if (screen == SONG) {
                    // Handle song selection
                    if (event.key.code == Keyboard::Num1) {
                        selectedSongPath = "songs/fredagain.wav";
                        screen = START;
                        songName = "Song: We've Lost Dancing\n Artist: Fred Again...";
                    }
                    else if (event.key.code == Keyboard::Num2) {
                        selectedSongPath = "songs/talk-tonight.wav";
                        screen = START;
                        songName = "Song: Talk Tonight\nArtist: Jersey";
                    }
                }
                else if (screen == START) {
                    // Handle key presses for selecting visualizations
                    if (event.key.code == Keyboard::L) {
                        screen = LINE;
                    }
                    else if (event.key.code == Keyboard::C) {
                        screen = CIRCLE;
                    }
                }
                else {
                    if (amplitude.getSongStatus()) {
                        screen = OVER;
                    }
                }
            }
        }
        window.clear();
        // Draw different visualizations based on the current screen
        switch (screen) {
            case SONG:
                renderSongSelection();
                break;
            case START:
                renderStart();
                break;
            case LINE:
                lineAmplitude.run(selectedSongPath);
                break;
            case CIRCLE:
                circleAmplitude.run(selectedSongPath);
                break;
            case OVER:
                renderOver();
                break;
        }
        window.display();
    }
}


void Home::renderStart() {
    window.clear(windowColor);
    string message = "Welcome to my Audio Visualizer\nPress [L] for Line Waveform Visualization"
                     "\nPress [C] for a 'Dancing Circle' Visualization\n" + songName;
    Font font;
    if (!font.loadFromFile("songs/fonts/Arial.ttf")) {
        cerr << "Failed to load font" << endl;
        return;
    }
    Text text(message, font);
    text.setCharacterSize(24);
    float xPos = (window.getSize().x - text.getGlobalBounds().width) / 2;
    float yPos = (window.getSize().y - text.getGlobalBounds().height) / 2;
    text.setPosition(xPos, yPos);
    text.setFillColor(Color::Black);
    window.draw(text);
}

void Home::renderOver() {
    string message = "Song Finished! If you would like to run it again \n"
                     "press [C] for circle visuals, or press [L] for line waveform!";
    Font font;
    if (!font.loadFromFile("songs/fonts/Arial.ttf")) {
        cerr << "Failed to load font" << endl;
        return;
    }
    Text text(message, font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Black);
    text.setPosition((width - text.getGlobalBounds().width) / 2, (height - text.getGlobalBounds().height) / 2);
    window.draw(text);
}

void Home::renderSongSelection() {
    window.clear(windowColor);
    string message = "Select a song:\n[1] We've Lost Dancing\n[2] Talk Tonight";
    Font font;
    if (!font.loadFromFile("songs/fonts/Arial.ttf")) {
        cerr << "Failed to load font" << endl;
        return;
    }
    Text text(message, font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Black);
    float xPos = (window.getSize().x - text.getGlobalBounds().width) / 2;
    float yPos = (window.getSize().y - text.getGlobalBounds().height) / 2;
    text.setPosition(xPos, yPos);
    window.draw(text);
}