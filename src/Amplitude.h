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
    // Constructor
    Amplitude();
    // Loads song into sound buffer
    void loadSong(const std::string& audioFile);
    // Plays the sound
    void playSound();
    // Retrieves the audio data
    void update();
    // Unused functions
    void pauseVisualization();
    void playVisualization();
    // Returns the amplitude data to be used in other classes
    const vector<float>& getAmplitudeData() const;
    // Returns the chunk size
    const int getChunkSize();
    // Returns whether the song is playing or not
    bool getSongStatus();

private:
    // Buffer object
    SoundBuffer buffer;
    // Sounds object
    unique_ptr<Sound> sound;
    // Size of segments the audio data is divided into to be processed
    const int chunkSize = 4096;
    // Vector of songs amplitude data
    vector<float> amplitudeData;
};


#endif //AMPLITUDE_H
