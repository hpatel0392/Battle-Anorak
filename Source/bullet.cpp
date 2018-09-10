#include <iostream>
#include <cmath>
#include "bullet.h"


Bullet::Bullet(const string& name, const Drawable * o) :
  MultiSprite(name), 
  distance(0), 
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
  tooFar(false),
  collided(false),
  owner( o ) 
{ }

Bullet::Bullet(const Bullet& b) :
  MultiSprite(b), 
  distance(b.distance), 
  maxDistance(b.maxDistance), 
  tooFar(b.tooFar),
  collided(b.collided),
  owner( b.owner )
{}

void Bullet::update(Uint32 ticks) { 
  Vector2f pos = getPosition();
  MultiSprite::update(ticks);
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

