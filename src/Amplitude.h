#ifndef AMPLITUDE_H
#define AMPLITUDE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <memory>

using namespace sf;
using namespace std;

class Amplitude {
public:
    Amplitude();
    void loadSong(const std::string& audioFile);
    void playSound();
    void update();
    void pauseVisualization();
    void playVisualization();
    const vector<float>& getAmplitudeData() const;
    const int getChunkSize();
    bool getSongStatus();

private:
    SoundBuffer buffer;
    // SFML 3: Sound is constructed with a buffer, not set separately
    unique_ptr<Sound> sound;
    const int chunkSize = 4096;
    vector<float> amplitudeData;
};

#endif //AMPLITUDE_H
