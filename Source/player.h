#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"
#include "gun.h"

class Player : public Actor {
public:
  Player(const std::string&);
  virtual void update(Uint32 ticks);
  virtual void draw();

  void collided() { collision = true; }
  void missed() { collision = false; }

  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

  void right();
  void left();
  void up();
  void down();
  void shoot();

  const Gun& getGun() const;
 
  bool dead() const { return hp<=0; };
  void hit(){if(!dead()) hp-= 5;};
  int getHP() const { return hp; }

private:
  bool collision;
  Vector2f initVelocity;
  float maxVelocity;
  float acceleration;
  Gun gun;
  int hp;

  enum Facing{RIGHT, LEFT};
  Facing facing;  

  bool exploding;
  int explodingInterval;
  int framesPassed;
  
  void stop();
  void normalize();
};
#endif
