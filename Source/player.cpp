#include "player.h"
#include "gamedata.h"
#include "explosionManager.h"

void Player::stop() {
  static float dampening = Gamedata::getInstance().getXmlFloat("dampening"); 
  if(getVelocity().magnitude() > 0.1) 
     setVelocity(getVelocity() * dampening);
}

void Player::normalize(){
   if(getVelocity().magnitude() > maxVelocity)
      setVelocity(getVelocity().normalize() * maxVelocity);
}

Player::Player( const std::string& name) :
  Actor(name),
  collision(false),
  initVelocity(getVelocity()),
  maxVelocity(Gamedata::getInstance().getXmlFloat(name+"/maxVelocity")),
  acceleration(Gamedata::getInstance().getXmlFloat(name+"/acceleration")),
  gun("DestructoDisc", Gamedata::getInstance().getXmlInt("Player/ammo"), static_cast<const Drawable*>(this)),
  hp(Gamedata::getInstance().getXmlInt("Player/health")),
  facing( RIGHT ),
  exploding(false),
  explodingInterval(Gamedata::getInstance().getXmlFloat("Explosion/frameInterval")),
  framesPassed(0)
{ 
   setVelocity(Vector2f(0, 0));
}


void Player::right() { 
  if(exploding) return;
  if(getVelocityX() + acceleration > initVelocity[0]){
     setVelocityX(initVelocity[0]);
  } else if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(getVelocityX() + acceleration);
  }
  normalize();
  facing = RIGHT;
}
 
void Player::left()  {
  if(exploding) return;
  if(fabs(getVelocityX() - acceleration) > initVelocity[0]){
     setVelocityX(-initVelocity[0]);
  } else if ( getX() > 0) {
    setVelocityX(getVelocityX() - acceleration);
  }
  normalize();
  facing = LEFT;
} 
void Player::up()    { 
  if(exploding) return;
  if(fabs(getVelocityY() - acceleration) > initVelocity[1]){
     setVelocityY(-initVelocity[1]);
  } else if ( getY() > 0) {
    setVelocityY( getVelocityY() - acceleration);
  }
  normalize();
} 
void Player::down()  { 
  if(exploding) return;
  if(getVelocityY() + acceleration > initVelocity[1]){
     setVelocityY(initVelocity[1]);
  } else if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( getVelocityY() + acceleration);
  }
  normalize();
  
}

void Player::shoot(){
  if(exploding) return;
  static Vector2f correctionRight(getScaledWidth(), getScaledHeight()/2);
  static Vector2f correctionLeft(-getScaledWidth(), getScaledHeight()/2);
  
  switch(facing){
    case RIGHT:
      gun.shoot(getPosition()+correctionRight, getVelocity());
      break;
    case LEFT:
      gun.shoot(getPosition()+correctionLeft, getVelocity());
      break;
  }

}

void Player::draw(){
  if(!exploding){
    Actor::draw();
  }
  gun.draw();
}

void Player::update(Uint32 ticks) {
  static int frames = Gamedata::getInstance().getXmlInt("Explosion/frames");

  if ( dead() && collision && !exploding ) {
    ExplosionManager::getInstance().addExplosion(getPosition());
    exploding = true;
    setVelocity(Vector2f(0, 0));
    framesPassed = 0;
  }
  else {
    if (timeSinceLastFrame > explodingInterval) framesPassed++;
    if (framesPassed > frames){
       framesPassed = 0;
       exploding = false;
      if(dead()) hp = 200;
    }
  }
  Actor::update(ticks);
  gun.update(ticks);
  stop();
}

const Gun& Player::getGun() const {
  return gun;
}




