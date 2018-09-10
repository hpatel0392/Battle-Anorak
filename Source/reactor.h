#ifndef REACTOR_H
#define REACTOR_H

#include <string>
#include "multisprite.h"

class Actor;
class Reactor : public MultiSprite{
public:
  Reactor(const std::string&);
  Reactor(const Reactor& r);
  Reactor& operator=(const Reactor& r);

  const Actor * getTarget() const { return target; }

  virtual void update(Uint32 ticks);
  void setTarget(const Actor * a ) { target = a; }
  virtual void react();
  virtual void draw() { MultiSprite::draw();};

private:
  friend class Boss;
  const Actor * target;
  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
