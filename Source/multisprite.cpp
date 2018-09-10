#include <sstream>
#include "multisprite.h"
#include "gamedata.h"
#include "renderContext.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
   timeSinceLastFrame += ticks;
   if (timeSinceLastFrame > frameInterval) {
      currentFrame = (currentFrame+1) % images[currentAction].size();
      totalFrames++;
      timeSinceLastFrame = 0;
   }
}

void MultiSprite::checkAction(){
   currentAction = 0;
   switch (actions) {
      case 4:
         if(getVelocityY() > 0)
            currentAction++;
      case 3: 
      case 2:
         currentAction *= 2;
         if(getVelocityX() < 0)
            currentAction++;
      default:
         break;
   }
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images( ),
  actions(Gamedata::getInstance().getXmlInt(name+"/actions")),
  currentAction(0),
  currentFrame(0),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  totalFrames(0)
{ 
   images.reserve(actions);
   std::stringstream ss;
   for(unsigned i = 0; i < actions; i++){
      ss.str("");
      ss << "/a"<<i+1;
      images.emplace_back( RenderContext::getInstance().getImages(name+ss.str()) );
   }
}

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s), 
  images(s.images),
  actions(s.actions),
  currentAction(s.currentAction),
  currentFrame(s.currentFrame),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  totalFrames(0)
  { }

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  actions = (s.actions);
  currentAction = (s.currentAction);
  currentFrame = (s.currentFrame);
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  totalFrames = s.totalFrames;
  return *this;
}

void MultiSprite::draw() const { 
  getImage()->draw(getX(), getY(), getScale());
}

void MultiSprite::update(Uint32 ticks) { 
  checkAction();
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  

}
