#include "Amplitude.h"

Amplitude::Amplitude() {
    amplitudeData = vector<float>(chunkSize, 0.0f);
}

void Amplitude::loadSong(const string& audioFile) {
    // SFML 3: loadFromFile -> openFromFile
    if (!buffer.loadFromFile(audioFile)) {
        cerr << "Unable to load audio file" << endl;
    }
}

void Amplitude::playSound() {
    // SFML 3: Sound is constructed with a buffer reference
    sound = make_unique<Sound>(buffer);
    sound->play();
}

void Amplitude::update() {
    // SFML 3: Sound::Status is now a scoped enum
    if (!sound || sound->getStatus() != Sound::Status::Playing) {
        return;
    }

    const float elapsedTime = sound->getPlayingOffset().asSeconds();
    const int maxStartSample = static_cast<int>(buffer.getSampleCount()) - chunkSize;
    const int startSample = min(static_cast<int>(elapsedTime * buffer.getSampleRate()), maxStartSample);

    for (int i = 0; i < chunkSize; ++i) {
        int sampleIndex = startSample + i;
        if (sampleIndex < 0 || sampleIndex >= static_cast<int>(buffer.getSampleCount())) {
            amplitudeData[i] = 0.0f;
            continue;
        }
        amplitudeData[i] = abs(float(buffer.getSamples()[sampleIndex]));
    }
}

const vector<float>& Amplitude::getAmplitudeData() const {
    return amplitudeData;
}

const int Amplitude::getChunkSize() {
    return chunkSize;
}

void Amplitude::pauseVisualization() {
    if (sound) sound->pause();
}

void Amplitude::playVisualization() {
    if (sound) sound->play();
}

bool Amplitude::getSongStatus() {
    if (!sound) return false;
    // SFML 3: scoped enum Sound::Status::Stopped
    return sound->getStatus() != Sound::Status::Stopped;
}
