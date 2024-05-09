#include "Amplitude.h"
// Code to help get started figuring out how to get data from sound samples taken from JanKleprlik
// https://github.com/JanKleprlik/AudioVisualiser/blob/master/Code/Source%20Code/Modes.cpp

// Constructor for the amplitude class which initializes the amplitudeData vector
Amplitude::Amplitude() {
    // Vector of amplitude data taken from buffer at specified chunk size
    amplitudeData = vector<float>(chunkSize, 0.0f);
}

// Loads an audio file into the buffer
void Amplitude::loadSong(const string& audioFile) {
    if (!buffer.loadFromFile(audioFile)) {
        cerr << "Unable to load audio file" << endl;
    }
}

// Plays the audio file
void Amplitude::playSound() {
    sound = make_unique<Sound>();
    sound->setBuffer(buffer);
    sound->play();
}

// Updates the amplitude data based on the current point in the audio that you are hearing and inserts into audioData vector
void Amplitude::update() {
    if (!sound || sound->getStatus() != Sound::Playing) {
        return;
    }
    // Gets the elapsed time in seconds since the beginning of the sound
    const float elapsedTime = sound->getPlayingOffset().asSeconds();
    // Highest index where the starting sample can be chosen from
    const int maxStartSample = buffer.getSampleCount() - chunkSize;
    // Index in the buffer to start reading samples to process
    const int startSample = min(static_cast<int>(elapsedTime * buffer.getSampleRate()), maxStartSample);
    // Ensures that the amplitude data is extracted from the audio buffer at the specified chunk of samples
    for (int i = 0; i < chunkSize; ++i) {
        int sampleIndex = startSample + i;
        // If sample index is less than 0 (accessing the data before start of buffer) or accessing beyond the buffer set amplitude to 0
        if (sampleIndex < 0 || sampleIndex >= buffer.getSampleCount()) {
            amplitudeData[i] = 0.0f;
            continue;
        }
        amplitudeData[i] = abs(float(buffer.getSamples()[sampleIndex]));
    }
}

// Getter to return the amplitude data
const vector<float>& Amplitude::getAmplitudeData() const {
    return amplitudeData;
}

// Getter to return the chunk size
const int Amplitude::getChunkSize() {
    return chunkSize;
}

// Unused due to time but was going to add pause/play functionality
void Amplitude::pauseVisualization() {
    sound->pause();
}
void Amplitude::playVisualization() {
    sound->play();
}
// Returns a bool for pause/play functionality
bool Amplitude::getSongStatus() {
    bool isPlaying = true;
    if (sound->getStatus() == Sound::Stopped) {
        isPlaying = false;
        return isPlaying;
    }
    else {
        isPlaying = true;
        return isPlaying;
    }
}