#include "./headers/SoundController.h"

SoundController::SoundController()
{

}

SoundController& SoundController::GetInstance()
{
    static SoundController instance;
    return instance;
}

bool SoundController::AddSound(const std::string& key,  const std::string& filePath)
{
    //Load the sound buffer
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile(filePath))
    {
        std::cerr << "Couldn't Load Sound Buffer: " << filePath << "\n\n";
        return false;
    }

    m_buffers[key] = buffer;

    //Create sound
    sf::Sound sound;

    sound.setBuffer(m_buffers[key]);

    //Add sound to map
    m_sound_bank[key] = sound;
    return true;
}

 bool SoundController::AddMusic(const std::string& key, const std::string& filePath, bool loop)
 {
    if(!m_music[key].openFromFile(filePath))
    {
        std::cerr << "Couldn't load music!";
        return false;
    }

    m_music[key].setLoop(loop);
    return true;
 }

void SoundController::PlaySound(const std::string& key)
{
    if(m_sound_bank.find(key) != m_sound_bank.end())
    {
        m_sound_bank[key].play(); 
    }
}

void SoundController::PlayMusic(const std::string& key)
{
    if(m_music.find(key) != m_music.end())
    {
        m_music[key].play();
    }
}

void SoundController::StopMusic(const std::string& key)
{
    if(m_music.find(key) != m_music.end())
    {
        m_music[key].stop();
    }
}

void SoundController::SetSoundVolume(const std::string& key, float volume)
{
    if(m_sound_bank.find(key) != m_sound_bank.end())
    {
        m_sound_bank[key].setVolume(volume);
    }
}

void SoundController::SetMusicVolume(const std::string& key, float volume)
{
    if(m_music.find(key) != m_music.end())
    {
        m_music[key].setVolume(volume);
    }
}

void SoundController::ClearBuffers()
{
    m_sound_bank.clear();
    m_buffers.clear();
    m_music.clear();
}