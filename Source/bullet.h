#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include "multisprite.h"
#include "gamedata.h"

class Bullet : public MultiSprite {
public:
  Bullet(const string&, const Drawable*);
  Bullet(const Bullet&);

  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  bool collision() const { return collided; }
  void reset() {
    tooFar = false;
    collided = false;
    distance = 0;
  }

private:
  friend class BulletManager;
  float distance;
  float maxDistance;
  bool tooFar;
  bool collided;
  const Drawable* owner;

  bool isOwner(const Drawable* o) { return o == owner; }
  void setCollided(){ collided = true; }

  Bullet& operator=(const Bullet&) = delete;
};
#endif
