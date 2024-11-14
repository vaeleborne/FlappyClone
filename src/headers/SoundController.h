#ifndef SOUND_CONTROLLER_H
#define SOUND_CONTROLLER_H
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>

/*A singleton that is responsible for audio in our game. Has functions to add sounds and music
which can be played by passing in a key. Recommended use is to clear buffers at the start of a 
game state then add sounds and music that need to be played in that state to preserver memory usage*/
class SoundController
{
public:
    //Delete copy constructor and assignment operator to prevent copies
    SoundController(SoundController&) = delete;
    SoundController operator=(SoundController&) = delete;

    //Function to get the single instance
    static SoundController& GetInstance();

    //Functions to add sounds and music to our 'banks', use at start of a gamestate, call ClearBuffers at end of a state
    bool AddSound(const std::string& key, const std::string& filePath);
    bool AddMusic(const std::string& key, const std::string& filePath, bool loop = true);

   
    //Function clears our stored buffers/sound banks
    void ClearBuffers();

    //Plays the sound that matches the given key or does nothing if key is invalid
    void PlaySound(const std::string& key);

    //Starts playing the music that matches the given key or does nothing if key is invalid
    void PlayMusic(const std::string& key);

    //Stops playing the music (not pause)
    void StopMusic(const std::string& key);

    //Sets the volume of a sound
    void SetSoundVolume(const std::string& key, float volume);

    //Sets the volume of a music
    void SetMusicVolume(const std::string& key, float volume);

private:
    //Variables to store the sound buffers and sound objects as well as music objects

    std::map<std::string, sf::Sound> m_sound_bank;
    std::map<std::string, sf::SoundBuffer> m_buffers;
    std::map<std::string, sf::Music> m_music;

    //Private constructor
    SoundController();
};

#endif