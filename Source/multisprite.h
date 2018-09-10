#ifndef MULTISPRITE_H
#define MULTISPRITE_H

#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return images[currentAction][currentFrame]; 
  }
  int getScaledWidth()  const { 
    return getScale()*getImage()->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*getImage()->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return getImage()->getSurface();
  }
  
  int getTotalFrames() const { return totalFrames;}

protected:
  std::vector<std::vector<Image *>> images;

  unsigned actions;
  unsigned currentAction;
  unsigned currentFrame;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  int totalFrames;
 
  void advanceFrame(Uint32 ticks);
  void checkAction();
  MultiSprite& operator=(const MultiSprite&);
};
#endif
