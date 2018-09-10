#ifndef ACTOR_H
#define ACTOR_H

#include <list>
#include <cmath>
#include <string>
#include "multisprite.h"

class Reactor;
class Actor : public MultiSprite{
public:
  Actor(const std::string&);
  Actor(const Actor&);

  virtual void update(Uint32 ticks) { MultiSprite::update(ticks);}
  void attach( Reactor* o );
  void detach( Reactor* o );

protected:
  std::list<Reactor*> observers;
  Actor& operator=(const Actor&);
};
#endif
