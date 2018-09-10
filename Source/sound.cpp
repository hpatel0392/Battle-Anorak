#include <string>
#include <iostream>
#include <ctime>
#include "sound.h"
#include "gamedata.h"
using std::string;

SDLSound::~SDLSound() {
  std::cout << "Cleaning up sounds ..." << std::endl;
  std::clock_t start = std::clock();
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  for (unsigned int i = 0; i < sounds.size(); ++i) {
    Mix_FreeChunk(sounds[i]);
  }
  Mix_CloseAudio();
  std::clock_t duration = std::clock() - start;
  std::cout << "Clean up took " << duration << " ticks\n";
}

SDLSound::SDLSound() : 
  volume(SDL_MIX_MAXVOLUME * Gamedata::getInstance().getXmlFloat("maxVolume")), 
  currentSound(-1), 
  music(NULL),
  audioRate(22050), 
  audioChannels(2), 
  audioBuffers(4096),
  sounds(),
  channels() 
{

  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, 
                   audioBuffers)){
    throw string("Unable to open audio!");
  }
  music = Mix_LoadMUS(Gamedata::getInstance().getXmlStr("music").c_str());
  // Need to install midi to play the following:
  // music = Mix_LoadMUS("sound/ballad2.mid");
  if (!music) throw string("Couldn't load Revengeance.mp3 ")+Mix_GetError();

  startMusic();

  sounds.push_back( Mix_LoadWAV("sound/vegeta_yell.wav") );
  sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  for (unsigned int i = 0; i < sounds.size(); ++i) channels.push_back(i);
  std::cout << "Music and Sound is loaded" << std::endl;
}

void SDLSound::toggleMusic() {
  if( Mix_PausedMusic() ) { 
    Mix_ResumeMusic(); 
  } 
  else { 
    Mix_PauseMusic(); 
  } 
}

void SDLSound::operator[](int index) {
  //if(currentSound == index) return;
  if(currentSound >= 0) Mix_HaltChannel(currentSound);
  currentSound = index;
  if(currentSound == -1) return;
  if(index == 0)
     Mix_VolumeChunk(sounds[index], SDL_MIX_MAXVOLUME);
  else
     Mix_VolumeChunk(sounds[index], SDL_MIX_MAXVOLUME*0.5);
  channels[index] = 
     Mix_PlayChannel(-1, sounds[index], 0);
}

void SDLSound::startMusic() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, -1);
}

void SDLSound::stopMusic() {
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

