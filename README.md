# Audio Visualizer Using SFML
## Contributer
Matthew Clark
## Summary of my program
The program I designed for the final project is an audio visualizer for the amplitude, or how loud, the song is. The project has two different modes for visualization. A waveform visualization and a "dancing circle" visualization. I intended to have other visuals involved but could not figure out how to properely use GSL's FFT library. The only data you can extrude from the .wav files is the amplitude. However despite this the program still offers some very interesting visuals. Most of the concepts used in this program came from Module 4 or the graphics module. However instead of using the graphics libraries from Module 4, I opted to use SFML. SFML stands for Simple and Fast Multimedia Library. Although SFML wraps over OpenGL it still offers more opportunities for expansion without the need for external libraries, for example the audio library. SFML offers an audio library that allows for the decoding of audio files to be used for projects like mine. By using SFML, it allowed me to focus more on the visuals. Other modules incorporated were Module 2 and Module 1.
## User Input in Different Screens
To start the program the user must click the keys listed on screen to chose the desired song and visualization. Only after that will the visualizations start.
## Waveform Visualization (LineAmplitude)
The waveform visualization mode displays the amplitude of the audio as a line graph with each point representing the audio sample at a specific time. The graph updates to reflect the changes in amplitude over time. This provides a more meaningful insight into the amplitude of the audio than the dancing circle visualization (CircleAmplitude).
## Dancing Circle Visualization
The "dancing circle" visualization offers a more fun and smoother visualization of the audio's amplitude. CircleAmplitude creates a circle that grows and shrink in response to the audio's amplitude.
## Operating System run on
I ran this program on an Apple MacBook Air that uses an M1 chip with an ARM64 architecture.
## Added Installations
The only added installation necessary for this project is the SFML library. I intended to use GSL's FFT (Fast Fourier Transform) library but faced challenges in getting it to work with my program. I found the math involved to be a little too complex so commented out the installation of it in the CMakeLists.txt
## Future Implementations
Some future implementations I plan on including are different audio extractions. I plan on adding a beat detection visualization, frequncy spectrum, and particle effects. This involves FFT however and I will need to find a better library for FFT that is easier to integrate. I also plan on adding more user interaction to my program.
## Citations/Code not authored by me
To get the samples extracted from the audio file I looked through another audio visualizer using SFML to see where to start.
https://github.com/JanKleprlik/AudioVisualiser
Along with this I used numerous tutorials and guidelines for the SFML library along with different operations on extracting the data/creating visuals
https://www.sfml-dev.org/documentation/2.6.1/annotated.php
https://www.youtube.com/watch?v=k1jIxFWT6yI
https://www.sfml-dev.org/tutorials/2.6/window-window.php
https://www.sfml-dev.org/tutorials/2.6/audio-sounds.php
https://en.sfml-dev.org/forums/index.php?topic=4559.0
https://dsp.stackexchange.com/questions/24079/what-is-a-proper-chunk-size-for-audio-analysis
https://dsp.stackexchange.com/questions/48918/amplitude-ranges-for-different-bit-depths
https://www.sfml-dev.org/documentation/2.6.1/group__graphics.php
https://www.youtube.com/watch?app=desktop&v=vdYXyWSSMhQ
https://www.sfml-dev.org/tutorials/2.6/audio-sounds.php#:~:text=Unlike%20sf%3A%3ASound%20%2C%20sf,data%20directly%20from%20the%20source.
https://stackoverflow.com/questions/13488957/interpolate-from-one-color-to-another
https://dsp.stackexchange.com/questions/13728/what-are-chunks-when-recording-a-voice-signal#:~:text=The%20chunk%20is%20like%20a,audio%20because%20of%20processing%20power.
https://codereview.stackexchange.com/questions/250282/audio-visualizer-in-c
